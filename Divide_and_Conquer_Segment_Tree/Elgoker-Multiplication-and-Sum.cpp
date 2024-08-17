#include <bits/stdc++.h>

using namespace std;

void fileIO(void) {

#ifndef ONLINE_JUDGE

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

#endif

}
void fastIO(void) {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

}
typedef long long ll;
#define int ll
#define len(s)   (ll)s.length()
#define sz(v)    (ll)v.size()
#define all(a)   a.begin(),a.end()
#define all_r(a)   a.rbegin(),a.rend()
#define endl '\n'


const int mod = 1e9 + 7;

struct Node
{
    ll val;
    ll lazy;
    bool is_lazy;

    Node(ll x = 0)
    {
        val = x;
        lazy = 1;
        is_lazy = 0;
    }

    void change(ll x)
    {
        val = val * x % mod;
        lazy = lazy * x % mod;
        is_lazy = 1;
    }
};


struct SegTree
{
    int tree_size;
    vector<Node> seg_data;

    SegTree(int n)
    {
        tree_size = 1;
        while (tree_size < n) tree_size *= 2;
        seg_data.assign(2 * tree_size, Node());
    }

    Node merge(const Node &lf, const Node & ri)
    {
        Node ans = Node();
        ans.val = (lf.val + ri.val) % mod;
        return ans;
    }

    void propagate(int ni, int lx, int rx)
    {
        if(seg_data[ni].is_lazy == 0 || rx - lx == 1) return;

        seg_data[ 2 * ni + 1].change(seg_data[ni].lazy);
        seg_data[ 2 * ni + 2].change(seg_data[ni].lazy);

        seg_data[ni].lazy = 1;
        seg_data[ni].is_lazy = 0;
    }

    void Build(vector<int> &arr, int ni, int lx, int rx)
    {
        if(rx - lx == 1)
        {

            if(lx < (int)arr.size())
                seg_data[ni] = Node(arr[lx]);
            return;
        }
        int mid = (lx + rx) / 2;
        Build(arr, 2 * ni + 1, lx, mid);
        Build(arr, 2 * ni + 2, mid, rx);

        seg_data[ni] = merge(seg_data[2 * ni + 1], seg_data[2 * ni + 2]);
    }
    void Build(vector<int> & arr)
    {
        Build(arr, 0, 0, tree_size);
    }


    // l,r -> zero indexed & r not included
    Node get_range(int l, int r, int ni, int lx, int rx)
    {
        propagate(ni, lx, rx);

        if(lx >= l && rx <= r)
            return seg_data[ni];
        if(rx <= l || lx >= r)
            return Node();

        int mid = (lx + rx) / 2;
        return merge(get_range(l, r, 2 * ni + 1, lx, mid), get_range(l, r, 2 * ni + 2, mid, rx));
    }
    int get_range(int l, int r)
    {
        return get_range(l, r, 0, 0, tree_size).val;
    }


    void set(int l, int r, int v, int ni, int lx, int rx)
    {
        propagate(ni, lx, rx);

        if(lx >= l && rx <= r) {
            seg_data[ni].change(v);
            return;
        }
        if(rx <= l || lx >= r)
            return;

        int mid = (lx + rx) / 2;
        set(l, r, v, 2 * ni + 1, lx, mid);
        set(l, r, v, 2 * ni + 2, mid, rx);

        seg_data[ni] = merge(seg_data[2 * ni + 1], seg_data[2*ni + 2]);
    }

    // idx -> zero indexed
    void set(int l, int r, int v)
    {
        set(l, r, v, 0, 0, tree_size);
    }
};

void solve(int tc)
{
    int n, m; cin >> n >> m;
    vector<int> arr(n, 1);

    SegTree st(n);
    st.Build(arr);

    while (m--)
    {
        int op; cin >> op;
        if(op == 1)
        {
            int l, r, v; cin >> l >> r >> v;
            st.set(l, r, v);
        }
        else
        {
            int l, r; cin >> l >> r;
            cout << st.get_range(l, r) << endl;
        }
    }

}

signed main()
{

    fastIO(); fileIO();
    cout << setprecision(10) << fixed;
    int t = 1; //cin >> t;

    for (int i = 1; i <= t; ++i) solve(i);

    return 0;
}