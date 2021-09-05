
# strhash.cpp | STRING | OI Algorithm

[**Go Back**](././)

---

```cpp
#include <iostream>
using namespace std;

#define fi first
#define se second
typedef long long ll;
typedef pair<ll, ll> pll;
const int p1 = 1019260817; // 双模 hash
const int p2 = 1019260819;
const int bs = 125641; // 基数
const int N  = 100000;
pll operator*(const pll &a, const ll &b) {return pll(a.fi * b % p1, a.se * b % p2);}
pll operator*(const pll &a, const pll &b) {return pll(a.fi * b.fi % p1, a.se * b.se % p2);}
pll operator+(const pll &a, const ll &b) {return pll((a.fi + b) % p1, (a.se + b) % p2);}
pll operator-(const pll &a, const pll &b) {return pll((a.fi - b.fi + p1) % p1, (a.se - b.se + p2) % p2);}
pll operator+(const pll &a, const pll &b) {return pll((a.fi + b.fi) % p1, (a.se + b.se) % p2);}
pll pw[N], pws[N]; // pw[i] = bs ^ i, pws[i] = \sum_{j=0}^i bs^j
void init(int n) {
    pw[0] = {1, 1};
    for (int i = 1; i <= n; ++i) pw[i] = pw[i - 1] * bs;
    // pws[0] = {1, 1};
    // for (int i = 1; i <= n; ++i) pws[i] = pws[i - 1] + pw[i];
}
// ---------- 用于线段树维护 Hash ----------
struct dat {
    pll f; // 哈希值
    int len; // 串长
    dat() { f = {0, 0}; len = 0; }
    dat(const pll &_f, const int &_len) { f = _f; len = _len; }
};
dat operator*(const dat &a, const dat &b) { // hash 值拼接
    return dat(a.f * pw[b.len] + b.f, a.len + b.len);
}
// ---------- 字符串 Hash ----------
void initstr(char *S, int n, pll *f) {
    f[0] = pll(0, 0); init(n);
    for (int i = 1; i <= n; ++i)
        f[i] = f[i - 1] * bs + (S[i] - 'a');
}
pll gethash(pll *f, int l, int r) {
    return f[r] - f[l - 1] * pw[r - l + 1];
}

```

---

[**Go Back**](././)
