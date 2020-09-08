#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int gcd(ll a,ll b) {return !b?a:gcd(b,a%b);}
//a^x=n (mod p)
ll BSGS(ll a,ll n,ll p) {
    ll ans=p,t=ceil(sqrt(p)),dt=1;
    map<ll,ll> hash;
    for(ll B=1;B<=t;B++) dt=(dt*a)%p,hash[(dt*n)%p]=B;
    for(ll A=1,num=dt;A<=t;A++,num=(num*dt)%p) if(hash.find(num)!=hash.end()) ans=min(ans,A*t-hash[num]); 
    return ans;
}
ll a,p,n;
int main() {
    cin>>p>>a>>n;
    ll ans=BSGS(a,n,p);
    if(ans==p) printf("no solution\n");
    else printf("%lld\n",ans);
}
