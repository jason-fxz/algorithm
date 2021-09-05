
# stirling1row.cpp | MATH | OI Algorithm

[**Go Back**](./)

---

```cpp
// 第一类斯特林数·行
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cstring>
#define clr(f,n) memset(f,0,sizeof(long long)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(long long)*(n))
#define _max(x,y) ((x>y)?x:y)
#define _min(x,y) ((x<y)?x:y)
#define MOD(x) ((x)<mod?(x):((x)%mod))
using namespace std;
typedef long long ll;
template<typename _Tp>
inline void red(_Tp &x) {
    x = 0; bool fg = 0; char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-') fg ^= 1; ch = getchar();}
    while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (_Tp)(ch ^ 48), ch = getchar();
    if (fg) x = -x;
}
template<typename _Tp> bool umax(_Tp &x, _Tp y) {return (x < y) ? (x = y, true) : (false);}
template<typename _Tp> bool umin(_Tp &x, _Tp y) {return (x > y) ? (x = y, true) : (false);}
const int N = (1 << 19);
const int mod = 167772161;
const int _G = 3;
const int _iG = 55924054;
int rev[N], rev_n;
ll inv[N], ifac[N], fac[N];
ll fpow(ll a, ll b = mod - 2) {
    ll r = 1;
    for (; b; b >>= 1, a = MOD(a * a)) if (b & 1) r = MOD(r * a);
    return r;
}
void prerev(int n) {
    if (rev_n == n) return ;
    for (int i = 0; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    rev_n = n;
}
void NTT(ll f[], int n, int fg) {
    prerev(n);
    for (int i = 0; i < n; ++i) if (i < rev[i]) swap(f[i], f[rev[i]]);
    for (int h = 2; h <= n; h <<= 1) {
        int len = h >> 1;
        ll Dt = fpow((fg == 1) ? _G : _iG, (mod - 1) / h), w;
        for (int j = 0; j < n; j += h) { // j<n !! not j<=n
            w = 1;
            for (int k = j; k < j + len; ++k) {
                ll tt = MOD(w * f[k + len]);
                f[k + len] = f[k] - tt; (f[k + len] < 0) &&(f[k + len] += mod);
                f[k] = f[k] + tt; (f[k] >= mod) &&(f[k] -= mod);
                w = MOD(w * Dt);
            }
        }
    }
    if (fg == -1) {
        ll invn = fpow(n, mod - 2);
        for (int i = 0; i < n; ++i) f[i] = MOD(f[i] * invn);
    }
}

ll S1[N];
int n;
// change f(x) to f(x+n)
void change(ll f[], int n) {
    static ll g[N];
    int nn;
    for (nn = 1; nn < (2 * n + 2); nn <<= 1) ;
    clr(g, nn); clr(f + n + 1, nn - n - 1);
    for (int i = 0; i <= n; ++i) f[i] = MOD(f[i] * fac[i]);
    for (int i = 0, pw = 1; i <= n; ++i, pw = MOD((ll)pw * n)) g[n - i] = MOD((ll)pw * ifac[i]);
    NTT(f, nn, 1); NTT(g, nn, 1);
    for (int i = 0; i < nn; ++i) f[i] = MOD(f[i] * g[i]);
    NTT(f, nn, -1);
    for (int i = 0; i <= n; ++i)
        f[i] = MOD(f[i + n] * ifac[i]);
    clr(f + n + 1, nn - n - 1);
}

void GetS1(ll f[], int n) {
    static int stk[50], top;
    static ll g[N];
    top = 0;
    while (n) stk[++top] = n, n >>= 1;
    clr(f, n << 1); f[1] = 1;
    for (int tt = top - 1; tt >= 1; --tt) {
        int now = stk[tt], len = stk[tt + 1], nn;
        cpy(g, f, len + 1);
        change(g, len);
        for (nn = 1; nn < (len * 2 + 2); nn <<= 1) ;
        NTT(f, nn, 1); NTT(g, nn, 1);
        for (int i = 0; i < nn; ++i) f[i] = MOD(f[i] * g[i]);
        NTT(f, nn, -1);
        if ((len << 1) + 1 == now) {
            // * (x+now-1)
            for (int i = now; i >= 0; --i) {
                f[i + 1] = MOD(f[i + 1] + f[i]);
                f[i] = MOD(f[i] * (now - 1));
            }
        }
    }
}

int main() {
    red(n);
    fac[0] = fac[1] = inv[0] = inv[1] = ifac[0] = ifac[1] = 1;
    for (int i = 2; i <= n + 1; ++i) fac[i] = MOD(fac[i - 1] * i);
    for (int i = 2; i <= n + 1; ++i) inv[i] = MOD((mod - mod / i) * inv[mod % i]);
    for (int i = 2; i <= n + 1; ++i) ifac[i] = MOD(ifac[i - 1] * inv[i]);
    GetS1(S1, n);
    for (int i = 0; i <= n; ++i)
        printf("%lld ", S1[i]);
    printf("\n");
    return 0;
}
/*
生活不止眼前的 OI
还有 逻辑 与 并行
*/
```

---

[**Go Back**](./)
