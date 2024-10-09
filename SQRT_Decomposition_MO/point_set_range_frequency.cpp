// Problem Link: https://judge.yosupo.jp/problem/point_set_range_frequency

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;

#define fi first
#define se second
#define pp push_back
#define all(x) (x).begin(), (x).end()
#define Ones(n) __builtin_popcount(n)
#define endl '\n'
#define mem(arrr, xx) memset(arrr,xx,sizeof arrr)
//#define int long long
#define debug(x) cout << (#x) << " = " << x << endl

void Gamal() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef Clion
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
}

int dx[] = {+0, +0, -1, +1, +1, +1, -1, -1};
int dy[] = {-1, +1, +0, +0, +1, -1, +1, -1};

const double EPS = 1e-9;
const ll OO = 0X3F3F3F3F3F3F3F3F;
const int N = 2e5 + 5, SQ = 460;


int a[N];
unordered_map<int, int> mp[SQ];


void update(int i, int v) {
    int blkNum = i / SQ;
    mp[blkNum][a[i]]--;
    if (mp[blkNum][a[i]] == 0) {
        mp[blkNum].erase(a[i]);
    }
    a[i] = v;
    mp[blkNum][a[i]]++;
}

// query number of x in prefix [0,r[
int query(int r, int x) {
    int blkNum = r / SQ;
    int cnt = 0;
    for (int i = 0; i < blkNum; ++i) {
        auto it = mp[i].find(x);
        if (it != mp[i].end())
            cnt += it->second;
    }
    for (int i = blkNum * SQ; i < r; ++i) {
        cnt += a[i] == x;
    }
    return cnt;
}

void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        int blkNum = i / SQ;
        mp[blkNum][a[i]]++;
    }

    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int k, v;
            cin >> k >> v;
            update(k, v);
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            cout << query(r, x) - query(l, x) << endl;
        }
    }
}


signed main() {
    Gamal();
    int t = 1;
//    cin >> t;
    while (t--) {
        solve();
    }
}
