#include <bits/stdc++.h>

using namespace std;

#define nl '\n'
#define all(v) v.begin(), v.end()

using ll = long long;
using pii = pair<int, int>;

constexpr int N = 2e5 + 5;
constexpr int MOD = 1e9 + 7;
constexpr int A = 26;
constexpr int inf = 2e9;
constexpr ll llinf = 4e18;
constexpr int LOG = 30;

int n, q;
int up[N][LOG], depth[N];
vector<int> adj[N];

int kth_ancestor(int u, const int k) {
    for (int i = 0; i < LOG; i++) {
        if (k >> i & 1) {
            u = up[u][i];
        }
    }
    return u;
}

int get_lca(int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }

    const int k = depth[u] - depth[v];
    u = kth_ancestor(u, k);

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

void dfs(const int src, const int par = 0) {
    for (const auto &nxt: adj[src]) {
        if (nxt == par) {
            continue;
        }
        depth[nxt] = depth[src] + 1;
        up[nxt][0] = src;
        for (int j = 1; j < LOG; j++) {
            up[nxt][j] = up[up[nxt][j - 1]][j - 1];
        }
        dfs(nxt, src);
    }
}

void solve() {
    cin >> n >> q;

    for (int i = 2; i <= n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    dfs(1);

    while (q--) {
        int u, v;
        cin >> u >> v;

        const int lca = get_lca(u, v);

        cout << depth[u] + depth[v] - 2 * depth[lca] << nl;
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
    // cin >> t;

    while (t--) {
        solve();
        cout << nl;
    }

    return 0;
}
