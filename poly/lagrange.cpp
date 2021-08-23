// 拉格朗日插值法
// L(x)=\sum_{j=0}^n y_j\prod_{i\ne j}\frac{x-x_i}{x_j-x_i}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000010;
const int mod = 1e9 + 7;
int n, k;

ll fpow(ll a, ll b, ll p = mod) {
    ll r = 1;
    for ( ; b; b >>= 1, a = (a * a) % p) if (b & 1) r = (r * a) % p;
    return r;
}
ll s[N], p[N], fac[N], inv[N], ifac[N];

void init(int n) {
    fac[0] = fac[1] = inv[0] = inv[1] = ifac[0] = ifac[1] = 1;
    for (int i = 2; i <= n; ++i) fac[i] = fac[i - 1] * i % mod;
    for (int i = 2; i <= n; ++i) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    for (int i = 2; i <= n; ++i) ifac[i] = ifac[i - 1] * inv[i] % mod;
}

ll lagrange(int n, ll k, ll x[], ll y[]) { // O(n^2)
    ll r = 0;
    for (int j = 0; j < n; ++j) {
        ll P1 = 1, P2 = 1;
        for (int i = 0; i < n; ++i) if (i != j) {
            P1 = (P1 * (k - x[i] + mod)) % mod;
            P2 = (P2 * (x[j] - x[i] + mod)) % mod;
        }
        r = (r + y[j] * P1 % mod * fpow(P2, mod - 2, mod) % mod) % mod;
    }
    return r;
}

ll lagrange_y(int n, ll k, ll y[]) { // 当 x_i = i (i in [0, n]) O(n)
    init(n);
    p[0] = 1;
    for (int i = 0; i < n; ++i) p[i + 1] = p[i] * (k - i + mod) % mod;
    s[n] = 1;
    for (int i = n; i >= 1; --i) s[i - 1] = s[i] * (k - i + mod) % mod;
    ll r = 0;
    for (int j = 0; j <= n; ++j) {
        ll tmp = p[j] * s[j] % mod * ifac[j] % mod * ifac[n - j] % mod;
        r = (r + (ll)(((n - j) & 1) ? (mod - 1) : 1) * y[j] % mod * tmp % mod) % mod;
    }
    return r;
}
