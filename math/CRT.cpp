#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 20;
ll a[N], b[N]; int n;
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
// x=ai (mod mi)   gcd(m1,m2....mn)=1
ll CRT(int n, ll a[], ll m[]) {
    ll M = 1, x = 0;
    for (int i = 1; i <= n; i++) M *= m[i];
    for (int i = 1; i <= n; i++)
        x = (x + (M / m[i]) * inv(M / m[i], m[i]) % M * a[i] % M) % M;
    return x;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld%lld", &a[i], &b[i]);
    ll ans = CRT(n, b, a);
    printf("%lld\n", ans);
}