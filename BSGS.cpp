#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll fpow(ll a,ll b,ll p) {
	ll r=1ll;
	while(b) {
		if(b&1) r=(r*a)%p;
		a=(a*a)%p;b>>=1;
	}
	return r;
}
ll gcd(ll a,ll b){
	return !b?a:gcd(b,a%b);
}
// calc  a^x=b (mod p)
ll BSGS(ll a,ll b,ll p) {
	if(gcd(a,p)!=1) return -2; //can't solve
	else {
		map<ll,ll> hah;
		b%=p;a%=p;
		ll k=ceil(sqrt(p));
		for(ll i=1;i<=k;i++) {
			hah[fpow(a,i,p)*b%p]=i;
		}
		ll tp=fpow(a,k,p),now=1ll;
		for(ll t=1;t<=k;t++) {
			now=(now*tp)%p;
			if(hah[now]) {
				return t*k-hah[now];
			}
		}
	}
	return -1;
}
int main() {
	ll p,b,n;
	cin>>p>>b>>n;
	ll ans=BSGS(b,n,p);
	if(ans==-1) printf("no solution\n");
	else printf("%lld\n",ans);
}
