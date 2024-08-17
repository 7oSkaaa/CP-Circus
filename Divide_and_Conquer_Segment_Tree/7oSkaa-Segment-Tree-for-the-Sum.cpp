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

template < typename treeType = int, typename numsType = int, int Base = 0 >
class Segment_Tree {
private:
    int size, max_level;
    treeType DEFAULT;
    vector < treeType > tree;
    const function < treeType(const treeType&, const treeType&) > operation;

    // Build the segment tree
    void build(const vector < numsType >& nums, int idx, int lx, int rx) {
        if (Base ? lx >= int(nums.size()) : lx > int(nums.size())) return;
        if (rx == lx) tree[idx] = treeType(nums[lx - !Base]);
        else {
            int mx = (rx + lx) / 2;
            build(nums, idx * 2, lx, mx);
            build(nums, idx * 2 + 1, mx + 1, rx);
            tree[idx] = operation(tree[idx * 2], tree[idx * 2 + 1]);
        }
    }

    // Update the segment tree
    void update(int index, numsType value, int idx, int lx, int rx) {
        if (rx == lx) tree[idx] = treeType(value);
        else {
            int mx = (rx + lx) / 2;
            if (index <= mx) update(index, value, idx * 2, lx, mx);
            else update(index, value, idx * 2 + 1, mx + 1, rx);
            tree[idx] = operation(tree[idx * 2], tree[idx * 2 + 1]);
        }
    }

    // Query the segment tree
    treeType query(int l, int r, int idx, int lx, int rx) const {
        if (lx > r || l > rx) return DEFAULT;
        if (lx >= l && rx <= r) return tree[idx];
        int mx = (lx + rx) / 2;
        return operation(query(l, r, idx * 2, lx, mx), query(l, r, idx * 2 + 1, mx + 1, rx));
    }

public:

    Segment_Tree(
        int n = 0, 
        const vector < numsType >& nums = vector < numsType >(), 
        const function < treeType(const treeType&, const treeType&) >& op = [](const treeType& a, const treeType& b) { return a + b; },
        treeType def = 0
    ) : size(1), max_level(1), DEFAULT(def), operation(op) {
        while (size < n) size *= 2, max_level++;
        tree = vector < treeType > (2 * size, DEFAULT);
        if (!nums.empty()) build(nums, 1, 1, size);
    }

    void build(const vector < numsType >& nums) {
        build(nums, 1, 1, size);
    }

    void update(int index, numsType value) {
        update(index, value, 1, 1, size);
    }

    treeType query(int l, int r) const {
        return query(l, r, 1, 1, size);
    }

    treeType operator[](int index) const {
        return query(index, index, 1, 1, size);
    }
};

void Solve(){
    int n, q;
    cin >> n >> q;
    vector < int > a(n);
    cin >> a;
    Segment_Tree < ll, int > st(n, a, [](ll a, ll b) { return a + b; }, 0);
    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int i, v;
            cin >> i >> v;
            st.update(++i, v);
        }else {
            int l, r;
            cin >> l >> r;
            cout << st.query(++l, r) << "\n";
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int test_cases = 1;
    // cin >> test_cases;
    for(int tc = 1; tc <= test_cases; tc++){
        // cout << "Case #" << tc << ": ";
        Solve();
    }
    return 0;
}