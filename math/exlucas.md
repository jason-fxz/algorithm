
# exlucas.cpp | MATH | OI Algorithm

[**Go Back**](./)

---

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mul(ll a, ll b, ll p) {
    ll l = ((b >> 30) % p * (1ll << 30) % p) % p;
    ll r = (b & ((1ll << 30) - 1ll)) % p;
    return ((l * a) % p + (r * a) % p) % p;
}
ll fpow(ll a, ll b, ll p) {
    ll r = 1ll;
    while (b) {
        if (b & 1) r = mul(r, a, p);
        a = mul(a, a, p);
        b >>= 1;
    }
    return r;
}
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {x = 1ll, y = 0; return a;}
    ll d = exgcd(b, a % b, x, y); swap(x, y);
    y -= (a / b) * x; return d;
}
ll inv(ll a, ll p) {
    ll iv, k;
    exgcd(a, p, iv, k);
    return (iv % p + p) % p;
}
// calc (n!/p^c) mod p^k which gcd(n!/p^c,p^k)=1
ll fact(ll n, ll p, ll pk) {
    if (!n) return 1ll;
    ll ret = 1ll;
    for (ll i = 1ll; i <= pk; i++) {
        if (i % p) ret = ret * i % pk;
    }
    ret = fpow(ret, n / pk, pk);
    for (ll i = 1ll; i <= n % pk; i++) {
        if (i % p) ret = ret * i % pk;
    }
    return ret * fact(n / p, p, pk) % pk;
}
ll C(ll n, ll m, ll p, ll pk) {
    if (n < m) return 0;
    ll f1 = fact(n, p, pk), f2 = inv(fact(m, p, pk), pk), f3 = inv(fact(n - m, p, pk), pk);
    ll cnt = 0;
    for (ll i = n; i; i /= p) cnt += i / p;
    for (ll i = m; i; i /= p) cnt -= i / p;
    for (ll i = n - m; i; i /= p) cnt -= i / p;
    return f1 * f2 % pk * f3 % pk * fpow(p, cnt, pk) % pk;
}
ll CRT(int n, ll a[], ll m[]) {
    ll M = 1, ret = 0;
    for (int i = 1; i <= n; i++) M *= m[i];
    for (int i = 1; i <= n; i++)
        ret = (ret + a[i] * (M / m[i]) % M * inv(M / m[i], m[i])) % M;
    return (ret % M + M) % M;
}
ll exlucas(ll n, ll m, ll p) {
    ll pk[24], c[24]; int tot = 0;
    for (ll i = 2ll; i <= p / i; i++) {
        if (p % i == 0) {
            pk[++tot] = 1ll;
            while (p % i == 0) p /= i, pk[tot] *= i;
            c[tot] = C(n, m, i, pk[tot]);
        }
    }
    if (p > 1) pk[++tot] = p, c[tot] = C(n, m, p, p);
    return CRT(tot, c, pk);
}
int main() {
    ll n, m, p;
    cin >> n >> m >> p;
    cout << exlucas(n, m, p) << endl;
}


```

---

[**Go Back**](./)
