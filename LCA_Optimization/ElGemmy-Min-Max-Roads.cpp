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
int up[N][LOG], depth[N], mn[N][LOG], mx[N][LOG];
vector<pii> adj[N];

void dfs(const int src, const int par = 0) {
    for (const auto &[nxt, wt]: adj[src]) {
        if (nxt == par) {
            continue;
        }
        depth[nxt] = depth[src] + 1;
        up[nxt][0] = src;
        mn[nxt][0] = wt;
        mx[nxt][0] = wt;
        for (int j = 1; j < LOG; j++) {
            up[nxt][j] = up[up[nxt][j - 1]][j - 1];
            mn[nxt][j] = min(mn[nxt][j - 1], mn[up[nxt][j - 1]][j - 1]);
            mx[nxt][j] = max(mx[nxt][j - 1], mx[up[nxt][j - 1]][j - 1]);
        }
        dfs(nxt, src);
    }
}

pii query(int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }
    auto [ans_mn, ans_mx] = pii(inf, 0);

    const int k = depth[u] - depth[v];
    for (int i = 0; i < LOG; i++) {
        if (k >> i & 1) {
            ans_mn = min(ans_mn, mn[u][i]);
            ans_mx = max(ans_mx, mx[u][i]);
            u = up[u][i];
        }
    }

    if (u == v) {
        return {ans_mn, ans_mx};
    }

    for (int j = LOG - 1; j >= 0; j--) {
        if (up[u][j] != up[v][j]) {
            ans_mn = min(ans_mn, min(mn[u][j], mn[v][j]));
            ans_mx = max(ans_mx, max(mx[u][j], mx[v][j]));
            u = up[u][j];
            v = up[v][j];
        }
    }

    ans_mn = min(ans_mn, min(mn[u][0], mn[v][0]));
    ans_mx = max(ans_mx, max(mx[u][0], mx[v][0]));

    return {ans_mn, ans_mx};
}

void init(const int n) {
    for (int i = 0; i <= n; i++) {
        adj[i].clear();
        depth[i] = 0;
        memset(up[i], 0, sizeof up[i]);
        memset(mn[i], 0, sizeof mn[i]);
        for (auto &j: mn[i]) {
            j = inf;
        }
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

    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;

        auto [ans_mn, ans_mx] = query(u, v);

        cout << ans_mn << ' ' << ans_mx << nl;
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
        cout << "Case " << tc << ":" << nl;
        solve();
        // cout << nl;
    }

    return 0;
}
