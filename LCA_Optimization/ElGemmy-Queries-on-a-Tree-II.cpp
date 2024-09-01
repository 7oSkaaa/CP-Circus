#include <bits/stdc++.h>

using namespace std;

#define nl '\n'
#define all(v) v.begin(), v.end()

using ll = long long;
using pii = pair<int, int>;

constexpr int N = 2e4 + 5;
constexpr int MOD = 1e9 + 7;
constexpr int A = 26;
constexpr int inf = 2e9;
constexpr ll llinf = 4e18;
constexpr int LOG = 30;

int n, q;
int up[N][LOG], depth[N], dist[N];
vector<pii> adj[N];

void dfs(const int src, const int par = 0) {
    for (auto &[nxt, wt]: adj[src]) {
        if (nxt == par) {
            continue;
        }
        up[nxt][0] = src;
        depth[nxt] = depth[src] + 1;
        dist[nxt] = dist[src] + wt;
        for (int j = 1; j < LOG; j++) {
            up[nxt][j] = up[up[nxt][j - 1]][j - 1];
        }
        dfs(nxt, src);
    }
}

int kth_anc(int u, const int k) {
    for (int j = 0; j < LOG; j++) {
        if (k >> j & 1) {
            u = up[u][j];
        }
    }
    return u;
}

int get_lca(int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }

    const int k = depth[u] - depth[v];
    u = kth_anc(u, k);

    if (u == v) {
        return u;
    }

    for (int j = LOG - 1; j >= 0; j--) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }

    return up[u][0];
}

void init(const int n) {
    for (int i = 0; i <= n; i++) {
        adj[i].clear();
        depth[i] = 0;
        dist[i] = 0;
        memset(up[i], 0, sizeof up[i]);
    }
}

void solve() {
    int n;
    cin >> n;

    init(n);

    for (int i = 1; i < n; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        adj[u].emplace_back(v, wt);
        adj[v].emplace_back(u, wt);
    }

    dfs(1);

    string s;
    while (cin >> s and s != "DONE") {
        int u, v;
        cin >> u >> v;

        if (s == "DIST") {
            cout << dist[u] + dist[v] - 2 * dist[get_lca(u, v)] << nl;
        } else {
            int k;
            cin >> k;
            --k;
            const int lca = get_lca(u, v);
            const int lft = depth[u] - depth[lca];
            const int rgt = depth[v] - depth[lca];

            if (k < lft) {
                cout << kth_anc(u, k) << nl;
            } else {
                cout << kth_anc(v, rgt - (k - lft)) << nl;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int t = 1;
    cin >> t;

    for (int tc = 1; tc <= t; tc++) {
        // cout << "Case " << tc << ":" << nl;
        solve();
        // cout << nl;
    }

    return 0;
}
