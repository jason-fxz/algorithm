
# EXBSGS.cpp | MATH | OI Algorithm

[**Go Back**](././)

---

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll gcd(ll a, ll b) {return !b ? a : gcd(b, a % b);}
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {x = 1, y = 0; return a;}
    ll d = exgcd(b, a % b, x, y);
    swap(x, y); y -= a / b * x;
    return d;
}
ll inv(ll a, ll b) {
    ll x, y; exgcd(a, b, x, y);
    return (x % b + b) % b;
}
ll BSGS(ll a, ll n, ll p) {
    ll ans = p, t = ceil(sqrt(p)), dt = 1;
    map<ll, ll> hash;
    for (ll B = 1; B <= t; B++) dt = (dt * a) % p, hash[(dt * n) % p] = B;
    for (ll A = 1, num = dt; A <= t;
         A++, num = (num * dt) % p) if (hash.find(num) != hash.end()) ans = min(ans, A * t - hash[num]);
    return ans;
}
//a^x=n (mod p)
ll EXBSGS(ll a, ll n, ll p) {
    int k = 0; ll d, ad = 1;
    while ((d = gcd(a, p)) != 1) {
        if (n % d) return -1;
        n /= d, p /= d; ad *= a / d; ad %= p; k++;
    }
    n = (n * inv(ad, p)) % p;
    ll res = BSGS(a, n, p);
    if (res == p) return -1;
    return res + k;
}
ll a, p, n;
int main() {
    while (cin >> a >> p >> n) {
        if (a == 0 && p == 0 && n == 0) break;
        ll ans = EXBSGS(a, n, p);
        if (ans == -1) printf("No Solution\n");
        else printf("%lld\n", ans);
    }
}
```

---

[**Go Back**](././)
