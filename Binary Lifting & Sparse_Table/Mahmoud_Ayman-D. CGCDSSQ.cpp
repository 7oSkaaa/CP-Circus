#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+5,Log=22;
ll n,q,arr[N],T[N][Log],skip=0,LOG[N];
ll merge(ll a,ll b)
{
    return __gcd(a,b);
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
ll query(int l,int r)
{
    int len=r-l+1;
    ll ret=skip;
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
    int lg=__lg(len);
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
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    init();
    Build();
    map<ll,ll>ans;
    for(int l=0;l<n;l++)
    {
        int r=l;
        while(r<n)
        {
            int L=r,R=n-1,g=query2(l,r),idx=r;
            while(L<=R)
            {
                int mid=L+R>>1;
                if(query2(l,mid)==g)
                {
                    idx=mid;
                    L=mid+1;
                }
                else
                {
                    R=mid-1;
                }
            }
            ans[g]+=idx-r+1;
            r=idx+1;
        }
    }
    cin>>q;while(q--)
    {
        int x;cin>>x;
        cout<<ans[x]<<'\n';
    }
    return 0;
}