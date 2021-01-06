/*
    FFT 快速傅立叶变换
    加法卷积
*/
#include <bits/stdc++.h>
#define _max(x,y) ((x>y)?x:y)
#define _min(x,y) ((x<y)?x:y)
using namespace std;
typedef long long ll;
template<typename _Tp>
inline void red(_Tp &x) {
    x=0;bool fg=0;char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') fg^=1;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(_Tp)(ch^48),ch=getchar();
    if(fg) x=-x;
}
template<typename _Tp> bool umax(_Tp &x,_Tp y) {return (x<y)?(x=y,true):(false);}
template<typename _Tp> bool umin(_Tp &x,_Tp y) {return (x>y)?(x=y,true):(false);}
typedef double db;
const int N = 2097152;
const db Pi = acos(-1);
struct com {
    db r,i;
    com():r(0),i(0) {}
    com(db _r,db _i):r(_r),i(_i){}
    com(int n):r(cos(Pi*2/n)),i(sin(Pi*2/n)){} // w_n^1
    com operator+(const com &b)const{return com(r+b.r,i+b.i);} 
    com operator-(const com &b)const{return com(r-b.r,i-b.i);} 
    com operator*(const com &b)const{return com(r*b.r-i*b.i,i*b.r+r*b.i);}
}A[N],B[N];
int n,m,tot;
namespace sol1{ // 分治版FFT
    com sav[N];
    // flag = 1 DFT  flag = -1 IDFT
    void FFT(com *f,int n,int flag) {
        if(n==1) return ;
        com *fl=f,*fr=f+n/2,Dt(n),w(1,0);
        Dt.i*=flag;
        for(int i=0;i<n;++i) sav[i]=f[i]; 
        for(int i=0;i<n/2;++i) fl[i]=sav[i<<1],fr[i]=sav[i<<1|1];
        FFT(fl,n/2,flag); FFT(fr,n/2,flag);
        for(int i=0;i<n/2;++i) {
            com tmp=w*fr[i];
            sav[i]=fl[i]+tmp;
            sav[i+n/2]=fl[i]-tmp;
            w=w*Dt;
        }
        for(int i=0;i<n;++i) f[i]=sav[i];
    }
}
namespace sol2{ // 迭代版FFT （小常数）
    int rev[N];
    void FFT(com f[],int n,int fg) {
        for(int i=0;i<n;++i) rev[i]=(rev[i>>1]>>1)|((i&1)?(n>>1):0);
        for(int i=0;i<n;++i) (i<rev[i])&&(swap(f[i],f[rev[i]]),1);
        for(int h=2;h<=n;h<<=1) {
            com Dt(h),w,tt; Dt.i*=fg;
            int len=(h>>1);
            for(int j=0;j<n;j+=h) {
                w=com(1,0);
                for(int k=j;k<j+len;++k) {
                    tt=f[k+len]*w;
                    f[k+len]=f[k]-tt;
                    f[k]=f[k]+tt;
                    w=w*Dt;
                } 
            }
        }
    }
}
int main() {
    red(n);red(m);
    for(int i=0;i<=n;++i) scanf("%lf",&A[i].r);
    for(int i=0;i<=m;++i) scanf("%lf",&B[i].r);
    tot=n+m; n=ceil(log2(n+m+2));  n=1<<n;
    using namespace sol2;
    FFT(A,n,1);FFT(B,n,1);
    for(int i=0;i<n;++i) A[i]=A[i]*B[i];
    FFT(A,n,-1);
    for(int i=0;i<=tot;++i) printf("%d ",(int)(A[i].r/n+0.49));
    puts("");
    return 0;
}

