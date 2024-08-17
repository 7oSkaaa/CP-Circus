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

vector < int > a;

int cnt_swaps(int l, int r, int h){
    if(l >= r) return 0;
    int m = (l + r) / 2;
    // left part -> [l, m]
    // right part -> [m + 1, r]
    int min_left = INT_MAX, min_right = INT_MAX;
    for(int i = l; i <= m; i++)
        min_left = min(min_left, a[i]);
    for(int i = m + 1; i <= r; i++)
        min_right = min(min_right, a[i]);
    int swaps = min_left > min_right;
    if(abs(min_left - min_right) > (1 << h)) return -1;
    int left_swaps = cnt_swaps(l, m, h - 1);
    int right_swaps = cnt_swaps(m + 1, r, h - 1);
    if(left_swaps == -1 || right_swaps == -1) return -1;
    return swaps + left_swaps + right_swaps;
}

int log2(int n){
    int res = 0;
    while(n > 0)
        n >>= 1, res++;
    return res - 1;
}

void Solve(){
    int n;
    cin >> n;
    a = vector < int > (n);
    for(auto& x : a)
        cin >> x;
    cout << cnt_swaps(0, n - 1, log2(n) - 1) << '\n';
}

int main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int test_cases = 1;
    cin >> test_cases;
    for(int tc = 1; tc <= test_cases; tc++){
        // cout << "Case #" << tc << ": ";
        Solve();
    }
    return 0;
}