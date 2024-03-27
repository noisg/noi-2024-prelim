#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define dbg(...) printf(__VA_ARGS__);
#else
#define dbg(...)
#endif
#define sf scanf
#define pf printf
#define fi first
#define se second
#define pb push_back
#define psf push_front
#define ppb pop_back
#define ppf pop_front
#define sz(x) (int)x.size()
#define mnto(x,y) x=min(x,(__typeof__(x))y)
#define mxto(x,y) x=max(x,(__typeof__(x))y)
#define INF 1023456789
#define LINF 1023456789123456789
#define all(x) x.begin(),x.end()
#define lb(x,v) (lower_bound(all(x),v)-x.begin())
#define ub(x,v) (upper_bound(all(x),v)-x.begin())
#define disc(x) sort(all(x));x.resize(unique(all(x))-x.begin());
typedef long long ll;
typedef long double ld;
typedef pair<int,int> ii;
typedef pair<ll,ll> pll;
typedef tuple<int,int,int> iii;
typedef tuple<int,int,int,int> iiii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ii> vii;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define mod 1000000007

inline int add(int a,int b){
	int r=a+b;
	while(r>=mod)r-=mod;
	while(r<0)r+=mod;
	return r;
}

inline int mult(int a,int b){
	return (int)(((ll)(a*b))%mod);
}

#define maxn 1005

int n,s,a[maxn][maxn],ptr[maxn],mx;
priority_queue<ii,vector<ii>,greater<ii>> pq;

int main(){
	sf("%d%d",&n,&s);
	int ans=INF;
	for(int i=0;i<n;++i){
		for(int j=0;j<s;++j){
			sf("%d",&a[i][j]);
		}
		sort(a[i],a[i]+s);
		pq.push({a[i][0],i});
		mx=max(mx,a[i][0]);
	}
	while(true){
		auto[val,i]=pq.top();
		pq.pop();
		ans=min(ans,mx-val);
		if(ptr[i]==s-1)break;
		++ptr[i];
		int nv=a[i][ptr[i]];
		pq.push({nv,i});
		mx=max(mx,nv);
	}
	pf("%d\n",ans);
}
