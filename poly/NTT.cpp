#include <bits/stdc++.h>
#define MOD(x) ((x<p)?(x):((x)%p))
template <typename T>
inline void red(T &x) {
    x=0;bool f=0;char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f^=1; ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(T)(ch^48),ch=getchar();
    if(f) x=-x;
}
using namespace std;
typedef long long ll;
const int p = 998244353; // = 119*2^23+1 g=3 是其原根
const int G = 3;
const int invG = 332748118;
const int N = 2097152;
int n,m,rev[N],tot;
ll A[N],B[N];
// NTT 对模数有要求，如果 p = r*2^k+1 是素数，在 mod p 意义下可处理 2^k 以内数据
// 与 FFT 的区别，单位根 w1 = g^((p-1)/n)
ll fpow(ll a,ll b,ll p=::p) {ll r=1;for(;b;b>>=1,a=MOD(a*a)) if(b&1) r=MOD(r*a); return r;}
// fg=1 DFT fg=0 IDFT
void NTT(ll f[],int n,bool fg) { 
	for(int i=0;i<n;++i) rev[i]=(rev[i>>1]>>1)|((i&1)?(n>>1):0); // 可以放到外面预处理
	for(int i=0;i<n;++i) (rev[i]<i)&&(swap(f[i],f[rev[i]]),1);
	for(int h=2;h<=n;h<<=1) {
		int len=h>>1;
		ll Dt=fpow(fg?G:invG,(p-1)/h),w;
		for(int j=0;j<n;j+=h) {
			w=1;
			for(int k=j;k<j+len;++k) {
				ll tt=MOD(w*f[k+len]);
				f[k+len]=f[k]-tt; (f[k+len]<0)&&(f[k+len]+=p);
				f[k]=f[k]+tt; (f[k]>p)&&(f[k]-=p);
				w=MOD(w*Dt);
			}
		}
	}
	if(fg==0) {
		ll invn=fpow(n,p-2);
		for(int i=0;i<n;++i) f[i]=MOD(f[i]*invn);
	}
}
int main() {
	red(n);red(m);
	for(int i=0;i<=n;++i) red(A[i]);
	for(int i=0;i<=m;++i) red(B[i]);
	tot=n+m+1;
	n=ceil(log2(n+m+2)); n=1<<n;
	NTT(A,n,1); NTT(B,n,1);
	for(int i=0;i<n;++i) A[i]=MOD(A[i]*B[i]);
	NTT(A,n,0);
	for(int i=0;i<tot;++i) printf("%lld ",A[i]);
	printf("\n");
}