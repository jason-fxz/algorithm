/*
	FMT/FWT 快速莫比乌斯/沃尔什变换 
	位运算卷积 
*/
#include <bits/stdc++.h>
#define re register
#define cpy(f,g,n) memcpy(f,g,sizeof(long long)*(n))
#define clr(f,n) memset(f,0,sizeof(long long)*(n))
#define out(f,n) for(int i=0;i<(n);++i) printf("%lld ",f[i]);puts("")
#define MOD(x) ((x<mod)?(x):((x)%mod))
template <typename T>
inline void red(T &x) {
    x=0;bool f=0;char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f^=1; ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(T)(ch^48),ch=getchar();
    if(f) x=-x;
}
using namespace std;
typedef long long ll;
const int N = 1<<18;
const int mod = 998244353;
const int inv2 = 499122177;
ll A[N],B[N],C[N],ta[N],tb[N];int n;
inline void FMT_OR(ll f[],int n,int fg) { // fg=1 for FMT ; fg=0 for IFMT
	for(re int h=2,k=1;h<=n;h<<=1,k<<=1)
		for(re int i=0;i<n;i+=h)
			for(re int j=0;j<k;++j)
				f[i+j+k]=MOD(f[i+j+k]+f[i+j]*fg+mod);
}
inline void FMT_AND(ll f[],int n,int fg) { // fg=1 for FMT ; fg=0 for IFMT
	for(re int h=2,k=1;h<=n;h<<=1,k<<=1)
		for(re int i=0;i<n;i+=h)
			for(re int j=0;j<k;++j)
				f[i+j]=MOD(f[i+j]+f[i+j+k]*fg+mod);
}
inline void FWT_XOR(ll f[],int n,int fg) { // fg=1 for FWT; fg=1/2(inv 2) for IFWT
	ll t;
	for(re int h=2,k=1;h<=n;h<<=1,k<<=1)
		for(re int i=0;i<n;i+=h)
			for(re int j=0;j<k;++j)
				t=f[i+j+k],f[i+j+k]=MOD(f[i+j]-t+mod),f[i+j]=MOD(f[i+j]+t),
				f[i+j]=MOD(f[i+j]*fg),f[i+j+k]=MOD(f[i+j+k]*fg);

}
void times(ll f[],ll g[],int n) {for(int i=0;i<n;++i) f[i]=MOD(f[i]*g[i]);}
int main() {
	red(n); n=1<<n;
	for(re int i=0;i<n;++i) red(A[i]);
	for(re int i=0;i<n;++i) red(B[i]);
	cpy(ta,A,n);cpy(tb,B,n);FMT_OR(ta,n,1);FMT_OR(tb,n,1);times(ta,tb,n);FMT_OR(ta,n,-1);out(ta,n);
	cpy(ta,A,n);cpy(tb,B,n);FMT_AND(ta,n,1);FMT_AND(tb,n,1);times(ta,tb,n);FMT_AND(ta,n,-1);out(ta,n);
	cpy(ta,A,n);cpy(tb,B,n);FWT_XOR(ta,n,1);FWT_XOR(tb,n,1);times(ta,tb,n);FWT_XOR(ta,n,inv2);out(ta,n);
}