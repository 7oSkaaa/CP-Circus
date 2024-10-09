// Problem Link: https://atcoder.jp/contests/abc293/tasks/abc293_g

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
const int N = 2e5 + 5, INF = INT_MAX, MOD = 1e9 + 7, SQ = 450;


struct query {
    int l, r, idx;

    bool operator<(query &other) {
        if (l / SQ != other.l / SQ)return l / SQ < other.l / SQ;
        return (l / SQ & 1 ? r < other.r : r > other.r);
    }
};

int frq[N];

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n),mapped(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];

        // a[i] = 7
        // mapped[i] = 4
    }




    vector<query> v(q);
    for (int i = 0; i < q; ++i) {
        cin >> v[i].l >> v[i].r;
        v[i].idx = i;
        v[i].l--, v[i].r--;
    }


    sort(all(v));
    ll cnt = 0;

    auto pairs = [&](int f){
        return 1ll * f * (f - 1) / 2;
    };

    auto add = [&](ll idx) {
        int value = a[idx];
        cnt += pairs(frq[value]);
        frq[value]++;
    };

    auto del = [&](ll idx) {
        int value = a[idx];
        frq[value]--;
        cnt -= pairs(frq[value]);
    };

    auto query = [&]() {
        return cnt;
    };


    int l = 0, r = -1;
    vector<ll> ans(q);
    for (auto &[lq, rq, idx]: v) {
        while (l > lq)add(--l);
        while (r < rq)add(++r);
        while (l < lq)del(l++);
        while (r > rq)del(r--);
        ans[idx] = query();
    }

    for (int i = 0; i < q; ++i) {
        cout << ans[i] << endl;
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
