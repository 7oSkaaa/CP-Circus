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


struct Node
{
    ll val;
    Node(ll x = 0)
    {
        val = x;
    }

    void change(ll x)
    {
        val = x;
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
        ans.val = lf.val + ri.val;
        return ans;
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


    void set(int idx, int v, int ni, int lx, int rx)
    {

        if(rx - lx == 1)
        {
            seg_data[ni].change(v);
            return;
        }

        int mid = (lx + rx) / 2;

        if(idx < mid)
            set(idx, v, 2 * ni + 1, lx, mid);
        else
            set(idx, v, 2 * ni + 2, mid, rx);

        seg_data[ni] = merge(seg_data[2 * ni + 1], seg_data[2 * ni + 2]);
    }

    // idx -> zero indexed
    void set(int idx, int v)
    {
        set(idx, v, 0, 0, tree_size);
    }
};

void solve(int tc)
{
    int n, q; cin >> n >> q;
    vector<int> arr(n);

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    SegTree st(n);
    st.Build(arr);

    while (q--)
    {
        int op; cin >> op;
        if(op == 1)
        {
            int idx, v; cin >> idx >> v;
            st.set(idx, v);
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