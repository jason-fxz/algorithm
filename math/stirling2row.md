
# stirling2row.cpp | MATH | OI Algorithm

[**Go Back**](./../)

---

```cpp
// 第二类斯特林数·行
#include <algorithm>
#include <cstdio>
#include <iostream>
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
ll S2[N], f[N], g[N];

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


int n, k, nn;
int main() {
    red(n);
    fac[0] = fac[1] = inv[0] = inv[1] = ifac[0] = ifac[1] = 1;
    for (int i = 2; i <= n; ++i) fac[i] = MOD(fac[i - 1] * i);
    for (int i = 2; i <= n; ++i) inv[i] = MOD((mod - mod / i) * inv[mod % i]);
    for (int i = 2; i <= n; ++i) ifac[i] = MOD(ifac[i - 1] * inv[i]);
    for (int k = 0; k <= n; ++k) {
        f[k] = ifac[k];
        if (k & 1) f[k] = MOD(mod - f[k]);
        g[k] = MOD(ifac[k] * fpow(k, n));
    }
    for (nn = 1; nn < (n * 2 + 2); nn <<= 1) ;
    NTT(f, nn, 1); NTT(g, nn, 1);
    for (int i = 0; i < nn; ++i) S2[i] = MOD(f[i] * g[i]);
    NTT(S2, nn, -1);
    for (int i = 0; i <= n; ++i) printf("%lld ", S2[i]);
    printf("\n");
    return 0;
}
```

---

[**Go Back**](./../)
