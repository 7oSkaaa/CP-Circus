#include <bits/stdc++.h>

using namespace std;

#define fixed(n) fixed << setprecision(n)
#define ceil(n, m) (((n) + (m) - 1) / (m))
#define add_mod(a, b, m) (((a % m) + (b % m)) % m)
#define sub_mod(a, b, m) (((a % m) - (b % m) + m) % m)
#define mul_mod(a, b, m) (((a % m) * (b % m)) % m)
#define all(vec) vec.begin(), vec.end()
#define rall(vec) vec.rbegin(), vec.rend()
#define sz(x) int(x.size())
#define debug(x) cout << #x << ": " << (x) << "\n";
#define fi first
#define se second
#define ll long long
#define ull unsigned long long
#define EPS 1e-9
constexpr int INF = 1 << 30, Mod = 1e9 + 7;
constexpr ll LINF = 1LL << 62;
#define PI acos(-1)
template < typename T = int > using Pair = pair < T, T >;
vector < string > RET = {"NO", "YES"};

template < typename T = int > istream& operator >> (istream &in, vector < T > &v) {
    for (auto &x : v) in >> x;
    return in;
}

template < typename T = int > ostream& operator << (ostream &out, const vector < T > &v) { 
    for (const T &x : v) out << x << ' '; 
    return out;
}

template < typename treeType = int , typename graphType = int >
class LCA {
public:
    LCA(
        int n = 0,
        const vector < vector < pair < int, graphType > > > &G = {},
        function < treeType(treeType, treeType) > op = [](treeType a, treeType b){ return a + b; },
        treeType _neutral = treeType(),
        int root = 1
    ) : N(n), LOG(0), ROOT(root), adj(G), operation(op), neutral(_neutral) {
        while((1 << LOG) <= N) LOG++;
        anc.assign(N + 5, vector < int > (LOG));
        cost.assign(N + 5, vector < treeType > (LOG, neutral));
        depth.assign(N + 5, 0);
        dfs(ROOT);
    }

    int kth_ancestor(int u, int k) const {
        if(depth[u] < k) return -1;
        for(int bit = 0; bit < LOG; bit++)
            if(k & (1 << bit)) 
                u = anc[u][bit];
        return u;
    }

    int get_lca(int u, int v) const {
        if(depth[u] < depth[v]) swap(u, v);

        u = kth_ancestor(u, depth[u] - depth[v]);
        if(u == v) return u;
        
        for(int bit = LOG - 1; bit >= 0; bit--)
            if(anc[u][bit] != anc[v][bit])
                u = anc[u][bit], v = anc[v][bit];
        
        return anc[u][0];
    }

    treeType query(int u, int v) const {
        int lca = get_lca(u, v);
        return operation(get_cost(u, depth[u] - depth[lca]), get_cost(v, depth[v] - depth[lca]));
    }

private:
    int N, LOG, ROOT;
    const vector < vector < pair < int, graphType > > > &adj;
    vector < vector < int > > anc;
    vector < vector < treeType > > cost;
    vector < int > depth;
    function < treeType(treeType, treeType) > operation;
    treeType neutral;

    void dfs(int u, int p = 0){
        for(auto& [v, w] : adj[u]){
            if(v == p) continue;
            depth[v] = depth[u] + 1;
            anc[v][0] = u, cost[v][0] = treeType(w);
            for(int bit = 1; bit < LOG; bit++){
                anc[v][bit] = anc[anc[v][bit - 1]][bit - 1];
                cost[v][bit] = operation(cost[v][bit - 1], cost[anc[v][bit - 1]][bit - 1]);
            }
            dfs(v, u);
        }
    }

    treeType get_cost(int u, int dist) const {
        if(depth[u] < dist) return neutral;
        treeType ret = neutral;
        for(int bit = 0; bit < LOG; bit++){
            if(dist & (1 << bit)){
                ret = operation(ret, cost[u][bit]);
                u = anc[u][bit];
            }
        }
        return ret;
    }
};

struct Edge {
    int mn, mx;
    Edge(int x){
        mn = mx = x;
    }
    Edge(int _mn, int _mx) : mn(_mn), mx(_mx) {}
};

Edge merge(const Edge &a, const Edge &b) {
    int mn = min(a.mn, b.mn);
    int mx = max(a.mx, b.mx);
    return Edge(mn, mx);
}

void Solve(){
    int n;
    cin >> n;
    vector < vector < pair < int, int > > > adj(n + 5);
    for(int i = 1; i < n; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    LCA < Edge, int > lca(n, adj, [](const Edge& a, const Edge& b){ return merge(a, b); }, Edge(INF, -INF));

    int q;
    cin >> q;
    while(q--){
        int u, v;
        cin >> u >> v;
        auto [mn, mx] = lca.query(u, v);
        cout << mn << " " << mx << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int test_cases = 1;
    cin >> test_cases;
    for(int tc = 1; tc <= test_cases; tc++){
        cout << "Case " << tc << ":\n";
        Solve();
    }
    return 0;
}