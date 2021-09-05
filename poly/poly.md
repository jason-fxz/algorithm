
# poly.cpp | POLY | OI Algorithm

[**Go Back**](./../)

---

```cpp
/*
	NTT 多项式全家桶
	p_mul 乘法; p_inv 求逆; p_div 带余数除法; p_sqrt 开方;
	p_ln Ln； p_exp EXP; p_int 积分; p_der 求导; p_pow 快速幂;
	DCFFT 分治 FFT 板子;

	to be continue ...
	多项式三角函数，多项式反三角函数，多项式多点求值，多项式快速差值.....
*/

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define clr(f,n) memset(f,0,sizeof(long long)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(long long)*(n))
#define Outarr(x,n) cerr<<#x<<" : "; for(int i=0;i<n;++i) cerr<<x[i]<<" ";cout<<endl;
#define outarr(x,n) for(int i=0;i<n;++i) printf("%lld%c",x[i],(i==n-1)?'\n':' ');
#define MOD(x) ((x)<mod?(x):((x)%mod))
using namespace std;
template<typename _Tp>
inline void red(_Tp &x) {
    x = 0; bool fg = 0; char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-') fg ^= 1; ch = getchar();}
    while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (_Tp)(ch ^ 48), ch = getchar();
    if (fg) x = -x;
}
typedef long long ll;

namespace poly {
    const int mod = 998244353;
    const int N = (1 << 19);
    const int _G = 3;
    const int _iG = 332748118;
    const int inv2 = 499122177;

    ll fpow(ll a, ll b, ll p) {
        ll r = 1;
        for (; b; a = a * a % p, b >>= 1) if (b & 1) r = r * a % p;
        return r;
    }

    int rev[N], rev_n;
    void prerev(int n) {
        if (n == rev_n) return;
        rev_n = n;
        for (int i = 0; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    }
    // NTT : fg=1 DFT fg=-1 IDFT
    void NTT(ll f[], int n, int fg) {
        prerev(n);
        for (int i = 0; i < n; ++i) if (i < rev[i]) swap(f[i], f[rev[i]]);
        for (int h = 2; h <= n; h <<= 1) {
            ll Dt = fpow((fg == 1) ? _G : _iG, (mod - 1) / h, mod), w;
            int len = h >> 1;
            for (int j = 0; j < n; j += h) {
                w = 1;
                for (int k = j; k < j + len; ++k) {
                    ll tmp = MOD(f[k + len] * w);
                    f[k + len] = f[k] - tmp; (f[k + len] < 0) &&(f[k + len] += mod);
                    f[k] = f[k] + tmp; (f[k] >= mod) &&(f[k] -= mod);
                    w = MOD(w * Dt);
                }
            }
        }
        if (fg == -1) {
            ll invn = fpow(n, mod - 2, mod);
            for (int i = 0; i < n; ++i) f[i] = MOD(f[i] * invn);
        }
    }
    // f(x) = f*g(x) n = def f ; m = def g ; len = 最终长度(保留几位)
    void p_mul(ll f[], ll g[], int n, int m, int len) {
        static ll a[N], b[N];
        int nn = 1 << (int)ceil(log2(n + m - 1));
        clr(a, nn); clr(b, nn); cpy(a, f, n); cpy(b, g, m);
        NTT(a, nn, 1); NTT(b, nn, 1);
        for (int i = 0; i < nn; ++i) a[i] = MOD(a[i] * b[i]);
        NTT(a, nn, -1);
        for (int i = 0; i < len; ++i) f[i] = a[i];
    }
    // f(x) = g^-1(x)  f(x) 为 g(x) 模 x^n 意义下的逆
    void p_inv(ll g[], int n, ll f[]) {
        static ll sav[N];
        int nn = 1 << (int)ceil(log2(n));
        clr(f, n * 2);
        f[0] = fpow(g[0], mod - 2, mod);
        for (int h = 2; h <= nn; h <<= 1) {
            cpy(sav, g, h); clr(sav + h, h);
            NTT(sav, h << 1, 1); NTT(f, h << 1, 1);
            for (int i = 0; i < (h << 1); ++i)
                f[i] = f[i] * (2ll - f[i] * sav[i] % mod + mod) % mod;
            NTT(f, h << 1, -1); clr(f + h, h);
        }
        clr(f + n, nn * 2 - n);
    }
    // f^2(x) = g(x)  f(x) 为 g(x) 模 x^n 意义下的开方
    void p_sqrt(ll g[], int n, ll f[]) {
        static ll sav[N], r[N];
        int nn = 1 << (int)ceil(log2(n));
        clr(f, n * 2); f[0] = 1; // g[0] should be 1 otherwise
        for (int h = 2; h <= nn; h <<= 1) {
            cpy(sav, g, h); clr(sav + h, h); p_inv(f, h, r);
            NTT(sav, h << 1, 1); NTT(r, h << 1, 1);
            for (int i = 0; i < (h << 1); ++i) sav[i] = MOD(sav[i] * r[i]);
            NTT(sav, h << 1, -1);
            for (int i = 0; i < h; ++i) f[i] = MOD((f[i] + sav[i]) * inv2);
            clr(f + h, h);
        }
        clr(f + n, nn * 2 - n);
    }
    // f(x) = g(x) * q(x) + r(x) : q(x) 为商 r(x) 为余数
    void p_div(ll f[], ll g[], int n, int m, ll q[], ll r[]) {
        static ll sav1[N], sav2[N];
        int nn;
        for (nn = 1; nn < n - m + 1; nn <<= 1);
        clr(sav1, nn); clr(sav2, nn); cpy(sav1, f, n); cpy(sav2, g, m);
        reverse(sav1, sav1 + n); reverse(sav2, sav2 + m);
        p_inv(sav2, n - m + 1, q); p_mul(q, sav1, n - m + 1, n, n - m + 1);
        reverse(q, q + n - m + 1);	cpy(r, g, m);
        p_mul(r, q, m, n - m + 1, m - 1);
        for (int i = 0; i < m - 1; ++i) r[i] = MOD(f[i] - r[i] + mod);
    }
    // 预处理乘法逆元
    ll inv[N];
    void Initinv(int n) {
        inv[0] = inv[1] = 1;
        for (int i = 2; i <= n; ++i) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    }
    // 对 f(x) 进行积分  Initinv() first
    void p_int(ll f[], int n) {
        for (int i = n - 1; i; --i) f[i] = MOD(f[i - 1] * inv[i]);
        f[0] = 0;
    }
    // 对 f(x) 进行求导
    void p_der(ll f[], int n) {
        for (int i = 1; i < n; ++i) f[i - 1] = MOD(f[i] * i);
        f[n - 1] = 0;
    }
    //  f(x) <- ln f(x)  f[0] should be 1
    void p_ln(ll f[], int n) {
        static ll g[N];
        p_inv(f, n, g); p_der(f, n);
        p_mul(f, g, n, n, n + n);
        p_int(f, n);
    }

    // f(x) <- exp f(x) (倍增版) f[0] should be 0
    void p_exp(ll f[], int n) {
        static ll g[N], sav[N];
        clr(g, n * 2); clr(sav, n * 2); g[0] = 1;
        for (int h = 2; h <= n; h <<= 1) {
            cpy(sav, g, h); p_ln(sav, h);
            for (int i = 0; i < h; ++i) sav[i] = MOD(f[i] - sav[i] + mod);
            sav[0] = MOD(sav[0] + 1);
            p_mul(g, sav, h, h, h);
        }
        cpy(f, g, n);
    }

    /*
    void _p_exp(ll f[],ll g[],int l,int r) {
    	static ll A[N],B[N];
    	if(r-l==1) {if(l>0) f[l]=MOD(f[l]*fpow(l,mod-2,mod));return ;}
    	int mid=(l+r)>>1,len=mid-l;
    	_p_exp(f,g,l,mid);
    	cpy(A,f+l,len); clr(A+len,len); cpy(B,g,len<<1);
    	p_mul(A,B,len<<1,len<<1,len<<1);
    	for(int i=mid;i<r;++i) f[i]=MOD(f[i]+A[i-l]);
    	_p_exp(f,g,mid,r);
    }
    // f(x) <- exp f(x) (分治 FFT 版) f[0] should be 0
    void p_exp(ll f[],int n) {
    	static ll g[N];
    	cpy(g,f,n); clr(f,n); f[0]=1;
    	for(int i=0;i<n;++i) g[i]=MOD(g[i]*i);
    	_p_exp(f,g,0,n);
    }
    */

    // f(x) <- f^k(x)  f(x) 模 x^n 意义下的 k 次
    void p_pow(ll f[], int n, ll k) {
        p_ln(f, n);
        for (int i = 0; i < n; ++i) f[i] = MOD(f[i] * k);
        p_exp(f, n);
    }

    // 分治FFT [l,r)   F[n] = sum(0<i<=n) F[n-i]G[i]
    void DCFFT(ll f[], ll g[], int l, int r) {
        static ll A[N], B[N];
        if (r - l == 1) return ;
        int mid = (l + r) >> 1, len = mid - l;
        DCFFT(f, g, l, mid);
        cpy(A, f + l, len); clr(A + len, len); cpy(B, g, len << 1);
        p_mul(A, B, len << 1, len << 1, len << 1);
        for (int i = mid; i < r; ++i) f[i] = MOD(f[i] + A[i - l]);
        DCFFT(f, g, mid, r);
    }
}
using namespace poly;

int main() {
    return 0;
}

```

---

[**Go Back**](./../)
