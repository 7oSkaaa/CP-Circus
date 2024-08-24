#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+5,Log=22;
int n,q,arr[N],T[N][Log],skip=INT_MAX,LOG[N];
int merge(int a,int b)
{
    return min(a,b);
}
void Build()
{
    for(int i=0;i<n;i++)
    {
        T[i][0]=arr[i];
    }
    for(int pw=1;(1<<pw)<=n;pw++)// powers of 2
    {
        for(int i=0;i+(1<<pw)<=n;i++) // elements
        {
            T[i][pw]=merge(T[i][pw-1],T[i+(1<<(pw-1))][pw-1]);
        }
    }
}
int query(int l,int r)
{
    int len=r-l+1;
    int ret=skip;
    for(int pw=Log-1;pw>=0;pw--)
    {
        if((len>>pw)&1)
        {
            ret=merge(ret,T[l][pw]);
            l+=(1<<pw);
        }
    }
    return ret;
}
ll query2(int l,int r)
{
    int len=r-l+1;
    int lg=LOG[len];
    return merge(T[l][lg],T[r-(1<<lg)+1][lg]);
}
void init()
{
    LOG[1]=0;
    for(int i=2;i<N;i++)
    {
        LOG[i]=LOG[i/2]+1;
    }
}
signed main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>q;
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    init();
    Build();
    while(q--)
    {
        int l,r;cin>>l>>r;
        cout<<query2(--l,--r)<<'\n';
    }
    return 0;
}