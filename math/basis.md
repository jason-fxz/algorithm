
# basis.cpp | MATH | OI Algorithm

[**Go Back**](./)

---

```cpp
// P3812 【模板】线性基
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int B = 52;
ll d[B], x;
int tot, n;
void insert(ll x) {
    for (int i = B - 1; i >= 0; --i) if ((x >> i) & 1) {
            if (d[i] == 0) {
                d[i] = x, ++tot; return ;
            }
            x ^= d[i];
        }
}
ll getmax() {
    ll ret = 0;
    for (int i = B - 1; i >= 0; --i) if ((ret ^ d[i]) > ret) ret ^= d[i];
    return ret;
}
ll getmin() {
    if (tot < n) return 0;
    for (int i = 0; i < B; ++i) if (d[i] != 0) return d[i];
    return -1;
}
void work() {
    for (int i = 1; i < B; ++i)
        for (int j = 0; j < i; ++j)
            if ((d[i] >> j) & 1) d[i] ^= d[j];
}
ll getkth(ll k) {
    if (k == 1 && tot < n) return 0;
    if (tot < n) --k;
    work(); ll ret = 0;
    for (int i = 0; i < B; ++i, k >>= 1) if (d[i] && (k & 1)) ret ^= d[i];
    return ret;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> x;
        insert(x);
    }
    printf("%lld\n", getmax());
}

```

---

[**Go Back**](./)
