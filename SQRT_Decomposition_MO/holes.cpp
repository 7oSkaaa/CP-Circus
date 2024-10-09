// Problem Link: https://codeforces.com/contest/13/problem/E

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
const int N = 2e5 + 5, INF = INT_MAX, MOD = 1e9 + 7, LOG = 20;


void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), c(n), w(n);
    // c[i] -> how many jumps to leave my block
    // w[i] -> which index i will end up at

    int SQ = sqrt(n) + 1;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i] += i;
    }

    for (int i = n - 1; i >= 0; --i) {
        if (i / SQ != a[i] / SQ || a[i] >= n) {
            c[i] = 1;
            w[i] = i;
        } else {
            c[i] = c[a[i]] + 1;
            w[i] = w[a[i]];
        }
    }

    while (m--) {
        int type, i;
        cin >> type >> i;
        i--;
        if (type == 0) {
            int b;
            cin >> b;
            a[i] = b + i;
            int blkNum = i / SQ;
            for (int j = i; j >= blkNum * SQ; --j) {
                if (j / SQ != a[j] / SQ || a[j] >= n) {
                    c[j] = 1;
                    w[j] = j;
                } else {
                    c[j] = c[a[j]] + 1;
                    w[j] = w[a[j]];
                }
            }
        } else {
            int cnt = 0, last = i;
            while (i < n) {
                cnt += c[i];
                last = w[i];
                i = a[w[i]];
            }
            cout << last + 1 << ' ' << cnt << endl;
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
