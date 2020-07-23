#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll inv(ll a,ll p) {
	ll r=1ll,b=p-2ll;
	while(b) {
		if(b&1) r=(r*a)%p;
		a=(a*a)%p;b>>=1;
	}
	return r;
}
ll C(ll n,ll m,ll p) {
	ll r=1ll;
	for(ll i=n-m+1ll;i<=n;i++) r=(r*i)%p;
	for(ll i=2ll;i<=m;i++) r=(r*inv(i,p))%p;
	return r;
}
ll lucas(ll n,ll m,ll p) {
	if(m==0) return 1ll;
	return (C(n%p,m%p,p)*lucas(n/p,m/p,p))%p;
}
int T;
int main() {
	cin>>T;
	while(T--) {
		ll n,m,p;
		cin>>n>>m>>p;
		cout<<lucas(n+m,n,p)<<endl;
	}
}
