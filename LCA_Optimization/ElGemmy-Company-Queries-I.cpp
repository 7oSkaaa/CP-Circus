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
int up[N][LOG];
 
int kth_ancestor(int u, const int k) {
    for (int i = 0; i < LOG; i++) {
        if (k >> i & 1) {
            u = up[u][i];
        }
    }
    return u;
}
 
void solve() {
    cin >> n >> q;
 
    for (int i = 2; i <= n; i++) {
        int par;
        cin >> par;
        up[i][0] = par;
        for (int j = 1; j < LOG; j++) {
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }
 
    while (q--) {
        int u, k;
        cin >> u >> k;
 
        const auto ans = kth_ancestor(u, k);
        if (ans) {
            cout << ans;
        } else {
            cout << -1;
        }
        cout << nl;
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