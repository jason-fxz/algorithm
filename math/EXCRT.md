
# EXCRT.cpp | MATH | OI Algorithm

[**Go Back**](./)

---

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100010;
ll a[N], b[N]; int n;
ll mul(ll a, ll b, ll mod) {
    ll r = 0;
    a = (a % mod + mod) % mod;
    b = (b % mod + mod) % mod;
    while (b) {
        if (b & 1) r = (r + a) % mod;
        a = (a << 1) % mod; b >>= 1;
    } return r;
}
ll gcd(ll a, ll b) {
    return !b ? a : gcd(b, a % b);
}
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {x = 1, y = 0; return a;}
    ll d = exgcd(b, a % b, x, y);
    swap(x, y); y -= a / b * x;
    return d;
}
// x=ai (mod mi)
ll EXCRT(int n, ll a[], ll m[]) {
    for (int i = 2; i <= n; i++) {
        ll d = gcd(m[i - 1], m[i]), x, y;
        if ((a[i] - a[i - 1]) % d != 0) return -1; // 无解
        exgcd(m[i - 1] / d, m[i] / d, x, y);
        m[i] = m[i] / gcd(m[i], m[i - 1]) * m[i - 1];
        a[i] = (a[i - 1] + mul(mul((a[i] - a[i - 1]) / d, x, m[i]), m[i - 1], m[i])) % m[i];
        a[i] = (a[i] + m[i]) % m[i];
    }
    return a[n];
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &a[i], &b[i]);
    ll ans = EXCRT(n, b, a);
    printf("%lld\n", ans);
}
```

---

[**Go Back**](./)
