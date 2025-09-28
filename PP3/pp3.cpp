#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include <string>
using namespace std;

using uint = unsigned int;
using Vertex = unsigned int;

constexpr int INF = numeric_limits<int>::max();
constexpr Vertex NIL = numeric_limits<Vertex>::max();

struct Army {
    string color;
    Vertex pos;
    vector<string> enemies;
    int movesCount;
    int cumWeight;
    bool reached;
    bool blockedByStorm;
    Vertex pendingStormTarget;
    Army()
      : pos(0), movesCount(0), cumWeight(0),
        reached(false), blockedByStorm(false),
        pendingStormTarget(NIL) {}
};

bool isEnemyColor(const vector<string> &enemies, const string &b) {
    for (size_t i = 0; i < enemies.size(); ++i) {
        if (enemies[i] == b) return true;
    }
    return false;
}

struct ArmyResult {
    string color;
    int movesCount;
    int cumWeight;
};

class GraphALW {
private:
    uint N;
    uint V;
    vector< vector< pair<Vertex,int> > > adj;
public:
    GraphALW(): N(0), V(0) {}
    GraphALW(uint n): N(n), V(n*n), adj(V) {}

    void setN(uint n) {
        N = n;
        V = n * n;
        adj.assign(V, vector<pair<Vertex,int>>());
    }

    uint vertices() const { return V; }
    uint sizeN() const { return N; }

    vector<pair<Vertex,int>>& neighbors(Vertex u) {
        return adj[u];
    }

    static string idxToLabel(int r, int c) {
        char file = char('a' + r);
        int rank = c + 1;
        string s;
        s.push_back(file);
        if (rank >= 10) {
            s.push_back(char('0' + (rank / 10)));
            s.push_back(char('0' + (rank % 10)));
        } else {
            s.push_back(char('0' + rank));
        }
        return s;
    }

    static int computeWeightLabel(const string &lu, const string &lv) {
        char au = lu[0];
        char av = lv[0];
        int bu = 0;
        for (size_t i = 1; i < lu.size(); ++i) {
            bu = bu * 10 + (lu[i] - '0');
        }
        int bv = 0;
        for (size_t i = 1; i < lv.size(); ++i) {
            bv = bv * 10 + (lv[i] - '0');
        }
        int term = ( (int)au * bu + (int)av * bv ) % 19;
        return term;
    }

    void buildKnightGraph() {
        adj.assign(V, vector<pair<Vertex,int>>());
        int dx[8] = {2, 2, -2, -2, 1, 1, -1, -1};
        int dy[8] = {1, -1, 1, -1, 2, -2, 2, -2};
        for (int r = 0; r < (int)N; ++r) {
            for (int c = 0; c < (int)N; ++c) {
                int u = r * N + c;
                string lu = idxToLabel(r, c);
                for (int k = 0; k < 8; ++k) {
                    int nr = r + dx[k];
                    int nc = c + dy[k];
                    if (nr >= 0 && nr < (int)N && nc >= 0 && nc < (int)N) {
                        int v = nr * N + nc;
                        string lv = idxToLabel(nr, nc);
                        int w = computeWeightLabel(lu, lv);
                        adj[u].push_back(make_pair(v, w));
                    }
                }
            }
        }
    }
};

template<typename KeyType>
class MinHeap {
private:
    vector< pair<KeyType, Vertex> > heap;
    vector<int> pos;
    void swapNodes(int i, int j) {
        auto tmp = heap[i];
        heap[i] = heap[j];
        heap[j] = tmp;
        pos[ heap[i].second ] = i;
        pos[ heap[j].second ] = j;
    }
    void heapifyUp(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (heap[i].first < heap[p].first) {
                swapNodes(i, p);
                i = p;
            } else break;
        }
    }
    void heapifyDown(int i) {
        int n = (int)heap.size();
        while (true) {
            int l = 2 * i + 1;
            int r = 2 * i + 2;
            int smallest = i;
            if (l < n && heap[l].first < heap[smallest].first) smallest = l;
            if (r < n && heap[r].first < heap[smallest].first) smallest = r;
            if (smallest != i) {
                swapNodes(i, smallest);
                i = smallest;
            } else break;
        }
    }
public:
    MinHeap(int maxV = 0) {
        pos.assign(maxV, -1);
    }
    void ensureSize(int v) {
        if (v >= (int)pos.size()) {
            int old = pos.size();
            pos.resize(v + 1);
            for (int i = old; i <= v; ++i) pos[i] = -1;
        }
    }
    bool contains(Vertex v) const {
        if (v >= (Vertex)pos.size()) return false;
        return pos[v] != -1;
    }
    void insert(Vertex v, KeyType key) {
        ensureSize(v);
        if (contains(v)) {
            int idx = pos[v];
            if (key < heap[idx].first) {
                decreaseKey(v, key);
            }
            return;
        }
        heap.push_back(make_pair(key, v));
        int idx = (int)heap.size() - 1;
        pos[v] = idx;
        heapifyUp(idx);
    }
    bool empty() const {
        return heap.empty();
    }
    pair<KeyType, Vertex> extractMin() {
        auto res = heap[0];
        int last = (int)heap.size() - 1;
        if (last > 0) swapNodes(0, last);
        pos[ res.second ] = -1;
        heap.pop_back();
        if (!heap.empty()) heapifyDown(0);
        return res;
    }
    void decreaseKey(Vertex v, KeyType newKey) {
        int idx = pos[v];
        if (idx == -1) return;
        if (!(newKey < heap[idx].first)) return;
        heap[idx].first = newKey;
        heapifyUp(idx);
    }
};

class Dijkstra {
private:
    GraphALW &G;
public:
    Dijkstra(GraphALW &g): G(g) {}
    void shortestPath(Vertex src, Vertex target,
                      vector<int> &dist, vector<Vertex> &pred) {
        uint Vn = G.vertices();
        dist.assign(Vn, INF);
        pred.assign(Vn, NIL);
        MinHeap<int> heap((int)Vn);
        dist[src] = 0;
        heap.insert(src, 0);
        while (!heap.empty()) {
            auto p = heap.extractMin();
            int du = p.first;
            Vertex u = p.second;
            if (du != dist[u]) continue;
            if (u == target) break;

            vector< pair<Vertex,int> > &nbrs = G.neighbors(u);
            // insertion sort
            for (size_t i = 1; i < nbrs.size(); ++i) {
                auto key = nbrs[i];
                int j = (int)i - 1;
                while (j >= 0 && nbrs[j].second > key.second) {
                    nbrs[j+1] = nbrs[j];
                    --j;
                }
                nbrs[j+1] = key;
            }

            for (size_t k = 0; k < nbrs.size(); ++k) {
                Vertex v = nbrs[k].first;
                int w = nbrs[k].second;
                if (dist[u] != INF && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pred[v] = u;
                    if (heap.contains(v)) {
                        heap.decreaseKey(v, dist[v]);
                    } else {
                        heap.insert(v, dist[v]);
                    }
                }
            }
        }
    }
};

class Simulation {
private:
    GraphALW &G;
    vector<Army> armies;
    vector<char> hasStorm;
    Vertex castleVertex;
    uint N;
public:
    Simulation(GraphALW &g): G(g), castleVertex(NIL) {
        N = g.sizeN();
        hasStorm.assign(G.vertices(), 0);
    }

    void addArmy(const string &color, const string &labelPos,
                 const vector<string> &enemies) {
        Army a;
        a.color = color;
        int r = labelPos[0] - 'a';
        int val = 0;
        for (size_t i = 1; i < labelPos.size(); ++i) {
            val = val * 10 + (labelPos[i] - '0');
        }
        int c = val - 1;
        a.pos = r * N + c;
        a.enemies = enemies;
        armies.push_back(a);
    }

    void setCastle(const string &label) {
        int r = label[0] - 'a';
        int val = 0;
        for (size_t i = 1; i < label.size(); ++i) {
            val = val * 10 + (label[i] - '0');
        }
        int c = val - 1;
        castleVertex = r * N + c;
    }

    void addStorm(const string &label) {
        int r = label[0] - 'a';
        int val = 0;
        for (size_t i = 1; i < label.size(); ++i) {
            val = val * 10 + (label[i] - '0');
        }
        int c = val - 1;
        Vertex id = r * N + c;
        if (id < G.vertices()) {
            hasStorm[id] = 1;
        }
    }

    vector<int> armiesAt(Vertex v) {
        vector<int> res;
        for (size_t i = 0; i < armies.size(); ++i) {
            if (!armies[i].reached && armies[i].pos == v) {
                res.push_back((int)i);
            }
        }
        return res;
    }

    vector<int> groupOf(int idx) {
        if (armies[idx].reached) return vector<int>();
        return armiesAt(armies[idx].pos);
    }

    bool destHasEnemy(const vector<int> &movingGroup, Vertex dest) {
        vector<int> destArm = armiesAt(dest);
        if (destArm.empty()) return false;
        for (int m : movingGroup) {
            for (int d : destArm) {
                if (isEnemyColor(armies[m].enemies, armies[d].color)
                    || isEnemyColor(armies[d].enemies, armies[m].color)) {
                    return true;
                }
            }
        }
        return false;
    }

    vector<int> mergeWithDestAllies(const vector<int> &movingGroup, Vertex dest, const vector<char> &movedFlag) {
        vector<int> res = movingGroup;
        vector<int> destArm = armiesAt(dest);
        for (int d : destArm) {
            if (movedFlag[d]) continue;
            bool conflict = false;
            for (int m : movingGroup) {
                if (isEnemyColor(armies[m].enemies, armies[d].color)
                    || isEnemyColor(armies[d].enemies, armies[m].color)) {
                    conflict = true;
                    break;
                }
            }
            if (!conflict) {
                bool present = false;
                for (int x : res) {
                    if (x == d) { present = true; break; }
                }
                if (!present) {
                    res.push_back(d);
                }
            }
        }
        return res;
    }

    Vertex firstStep(Vertex src, Vertex target,
                      const vector<Vertex> &pred) {
        if (src == target) return NIL;
        if (pred[target] == NIL) return NIL;
        vector<Vertex> path;
        Vertex cur = target;
        while (cur != NIL) {
            path.push_back(cur);
            if (cur == src) break;
            cur = pred[cur];
        }
        if (path.empty()) return NIL;
        if (path.back() != src) return NIL;
        if ((int)path.size() < 2) return NIL;
        return path[(int)path.size() - 2];
    }

    vector<ArmyResult> run() {
        Dijkstra dijkstra(G);
        int num = (int)armies.size();
        vector<char> movedFlag(num, 0);

        while (true) {
            for (int i = 0; i < num; ++i) movedFlag[i] = 0;
            vector<int> reachedThisRound;

            for (int i = 0; i < num; ++i) {
                if (armies[i].reached) continue;
                if (movedFlag[i]) continue;

                vector<int> rawGroup = groupOf(i);
                vector<int> group;
                for (int gid : rawGroup) {
                    if (!movedFlag[gid]) group.push_back(gid);
                }
                if (group.empty()) continue;
                for (int id : group) movedFlag[id] = 1;

                bool anyBlocked = false;
                int blockedIdx = -1;
                for (int id : group) {
                    if (armies[id].blockedByStorm) {
                        anyBlocked = true;
                        blockedIdx = id;
                        break;
                    }
                }
                if (anyBlocked) {
                    Vertex t = armies[blockedIdx].pendingStormTarget;
                    if (t == castleVertex) {
                        armies[blockedIdx].pos = t;
                        armies[blockedIdx].movesCount += 1;
                        armies[blockedIdx].blockedByStorm = false;
                        armies[blockedIdx].pendingStormTarget = NIL;
                        armies[blockedIdx].reached = true;
                        reachedThisRound.push_back(blockedIdx);
                    } else {
                        for (int id : group) {
                            armies[id].blockedByStorm = false;
                            armies[id].pendingStormTarget = NIL;
                        }
                    }
                    continue;
                }

                bool someAtCastle = false;
                for (int id : group) {
                    if (armies[id].pos == castleVertex) {
                        if (!armies[id].reached) {
                            armies[id].reached = true;
                            reachedThisRound.push_back(id);
                        }
                        someAtCastle = true;
                    }
                }
                if (someAtCastle) continue;

                Vertex src = armies[group[0]].pos;
                vector<int> dist;
                vector<Vertex> pred;
                dijkstra.shortestPath(src, castleVertex, dist, pred);
                if (dist[castleVertex] == INF) continue;
                Vertex nxt = firstStep(src, castleVertex, pred);
                if (nxt == NIL) continue;

                if (destHasEnemy(group, nxt)) continue;

                if (hasStorm[nxt]) {
                    if ((int)group.size() >= 2) {
                        hasStorm[nxt] = 0;
                        int edgeW = -1;
                        for (auto &pr : G.neighbors(src)) {
                            if (pr.first == nxt) {
                                edgeW = pr.second;
                                break;
                            }
                        }
                        for (int id : group) {
                            if (armies[id].pos == nxt) continue;
                            if (edgeW >= 0) armies[id].cumWeight += edgeW;
                            armies[id].pos = nxt;
                            armies[id].movesCount += 1;
                            if (nxt == castleVertex) {
                                armies[id].reached = true;
                                reachedThisRound.push_back(id);
                            }
                        }
                    } else {
                        int leader = group[0];
                        armies[leader].blockedByStorm = true;
                        armies[leader].pendingStormTarget = nxt;
                        continue;
                    }
                } else {
                    vector<int> merged = mergeWithDestAllies(group, nxt, movedFlag);
                    int edgeW = -1;
                    for (auto &pr : G.neighbors(src)) {
                        if (pr.first == nxt) {
                            edgeW = pr.second;
                            break;
                        }
                    }
                    for (int id : merged) {
                        if (armies[id].pos == nxt) continue;
                        if (edgeW >= 0) armies[id].cumWeight += edgeW;
                        armies[id].pos = nxt;
                        armies[id].movesCount += 1;
                        if (nxt == castleVertex) {
                            armies[id].reached = true;
                            reachedThisRound.push_back(id);
                        }
                    }
                }
            }

            if (!reachedThisRound.empty()) {
                vector<ArmyResult> out;
                for (int id : reachedThisRound) {
                    ArmyResult ar;
                    ar.color = armies[id].color;
                    ar.movesCount = armies[id].movesCount;
                    ar.cumWeight = armies[id].cumWeight;
                    out.push_back(ar);
                }
                // sort by color
                for (size_t i = 1; i < out.size(); ++i) {
                    ArmyResult key = out[i];
                    int j = (int)i - 1;
                    while (j >= 0 && out[j].color > key.color) {
                        out[j + 1] = out[j];
                        --j;
                    }
                    out[j + 1] = key;
                }
                return out;
            }

            bool anyActive = false;
            for (size_t i = 0; i < armies.size(); ++i) {
                if (!armies[i].reached) {
                    anyActive = true;
                    break;
                }
            }
            if (!anyActive) {
                return vector<ArmyResult>();
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;
    if (N < 1) return 0;

    GraphALW G(N);
    G.buildKnightGraph();

    int M;
    cin >> M;
    string dummy;
    getline(cin, dummy); // consume endline

    Simulation sim(G);

    for (int i = 0; i < M; ++i) {
        string line;
        do {
            if (!getline(cin, line)) break;
        } while (line.size() == 0);
        if (line.size() == 0) break;

        vector<string> toks;
        string cur;
        for (size_t p = 0; p < line.size(); ++p) {
            char ch = line[p];
            if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n') {
                if (!cur.empty()) {
                    toks.push_back(cur);
                    cur.clear();
                }
            } else {
                cur.push_back(ch);
            }
        }
        if (!cur.empty()) toks.push_back(cur);

        if (toks.size() < 2) continue;
        string color = toks[0];
        string pos = toks[1];
        vector<string> enemies;
        for (size_t k = 2; k < toks.size(); ++k) enemies.push_back(toks[k]);
        sim.addArmy(color, pos, enemies);
    }

    string castlePos;
    cin >> castlePos;
    sim.setCastle(castlePos);

    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        string tp;
        cin >> tp;
        sim.addStorm(tp);
    }

    vector<ArmyResult> result = sim.run();
    if (result.empty()) {
        cout << '\n';
    } else {
        bool first = true;
        for (auto &r : result) {
            if (!first) cout << ' ';
            first = false;
            cout << r.color << " " << r.movesCount << " " << r.cumWeight;
        }
        cout << '\n';
    }

    return 0;
}
