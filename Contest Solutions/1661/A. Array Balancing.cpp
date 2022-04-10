//Editorial: Just put the minimum numbers in the first array.
// Prithvijit Basak
#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#include<set>
#include<unordered_set>
#include<map>
#include<unordered_map>
#include<queue>
#include<string>
#include<cstring>
#include<stack>
#include<queue>
#include<deque>
#include<numeric>
#include<climits>
#include<iomanip>
#include<bitset>
using namespace std;
typedef long int lo;
typedef long long int ll;
typedef long double ld;
typedef unsigned long long int ull;
const ll mod=1e9+7;
const long double PI=3.141592653589793238462643383279502884197169399375105820974944;
// Template and all utility functions begins //
ll binpow(ll a, ll b)
{
    a %= mod;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
ll sz=1e6;
vector<bool> primes(sz+1);
void seive()
{
	for(ll i=2;i<=sz;i++)
	  primes[i]=true;
	for(ll i=2;i*i<=sz;i++)
	{
		if(primes[i]==true)
		{
			for(ll j=i*i;j<=sz;j+=i)
			{
				primes[j]=false;
			}
		}
	}
}
bool isprime(ll n)
{
	if(n==1)
		return false;
	for(ll i=2;i*i<=n;i++)
	{
		if(n%i==0)
			return false;
	}
	return true;
}
ll fact(ll n)
{
	ll f=1;
	for(ll i=n;i>=1;i--)
	  f*=i;
	return f;
}
ll nPr(ll n,ll r)
{
	ll p=1;
	for(ll i=0;i<r;i++)
	  p*=(n-i);
	return p;
}
ll nCr(ll n,ll r)
{
	ll ans=1;
	for(ll i=0;i<r;i++)
	{
		ans*=(n-i);
		ans/=(i+1);
	}
	return ans;
}
const ll N=1e6+10;
vector<ll> parent(N);
vector<ll> _rank(N);
void makeset(ll v)
{
	parent[v]=v;
	_rank[v]=1;
}
ll findpar(ll node)
{
	if(node==parent[node])
	  return node;
	return parent[node]=findpar(parent[node]);
}
void _union(ll u,ll v)
{
	ll a=findpar(u);
	ll b=findpar(v);
	if(a!=b)
	{
		if(_rank[a]<_rank[b])
		  swap(a,b);
		parent[b]=a;
		_rank[a]+=_rank[b];
	}
}
vector<ll> bit(N);
void updatefen(ll i,ll x)
{
	for(;i<N;i+=(i&-i))
	{
		bit[i]+=x;
	}
}
ll fensum(ll i)
{
	ll ans=0;
	for(;i>0;i-=(i&-i))
	  ans+=bit[i];
	return ans;
}
vector<ll> a(N),seg(4*N);
void buildseg(ll idx,ll low,ll high)
{
	if(low==high)
	{
		seg[idx]=a[low];
		return;
	}
	ll mid=(low+high)/2;
	buildseg(2*idx+1,low,mid);
	buildseg(2*idx+2,mid+1,high);
	seg[idx]=seg[2*idx+1]+seg[2*idx+2];
}
void updateseg(ll pos,ll low,ll high,ll index,ll val)
{
    if(index>high or index<low) //no overlap
        return;
    if(low==high)  //total overlap
    {
        if(low==index)
            seg[pos]=val;
        return;
    }
    // partial overlap
    int mid=(low+high)/2;
    updateseg(2*pos+1,low,mid,index,val);
    updateseg(2*pos+2,mid+1,high,index,val);
    seg[pos]=seg[2*pos+1]+seg[pos*2+2];
}
ll rangesum(ll pos,ll low,ll high,ll left,ll right)
{
	if(left<=low and high<=right) //total overlap
        return seg[pos];
    if(high<left or low>right)  //no overlap
        return 0;
    // partial overlap
    int mid=(low+high)/2;
    return rangesum(2*pos+1,low,mid,left,right)+rangesum(2*pos+2,mid+1,high,left,right);
}
/************************************************************************************************************************************************************************/
void solve()
{
	ll n;
	cin>>n;
	vector<ll> a(n);
	for(ll i=0;i<n;i++)
	  cin>>a[i];
	vector<ll> b(n);
	for(ll i=0;i<n;i++)
	  cin>>b[i];
	for(ll i=0;i<n;i++)
	{
		if(a[i]>b[i])
		  swap(a[i],b[i]);
	}
	ll sum=0;
	for(ll i=0;i<n-1;i++)
	  sum+=abs(a[i]-a[i+1])+abs(b[i]-b[i+1]);
	cout<<sum<<"\n";
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    cin>>t;
    while(t--)
    {
       solve();
    }
}

