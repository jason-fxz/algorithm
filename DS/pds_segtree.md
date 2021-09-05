
# pds_segtree.cpp | DS | OI Algorithm

[**Go Back**](././)

---

```cpp
// 主席树，区间第 k 大
#include <cstdio>
#include <algorithm>
#define ls(p) tr[p].lc
#define rs(p) tr[p].rc
#define re register
template <typename T>
inline void red(T &x) {
    x = 0; bool f = 0; char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-') f ^= 1; ch = getchar();}
    while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (T)(ch ^ 48), ch = getchar();
    if (f) x = -x;
}
using namespace std;
const int N = 200010;
struct node {
    int cnt, lc, rc;
} tr[N * 18]; int root[N], tot;
int a[N], b[N], tt, n, q;
int newnode() { tr[++tot] = {0, 0, 0}; return tot;}
void pushup(int p) {tr[p].cnt = tr[ls(p)].cnt + tr[rs(p)].cnt;}
void modify(int p, int q, int val, int l = 1, int r = tt) {
    if (l == r) return (p == 0) ? tr[q].cnt = 1 : tr[q].cnt = tr[p].cnt + 1, void();
    int mid = (l + r) >> 1;
    if (val <= mid) {
        modify(ls(p), ls(q) = newnode(), val, l, mid);
        rs(q) = rs(p);
    } else {
        modify(rs(p), rs(q) = newnode(), val, mid + 1, r);
        ls(q) = ls(p);
    }
    pushup(q);
}
int query(int p, int q, int k, int l = 1, int r = tt) {
    if (l == r) return b[l];
    int mid = (l + r) >> 1, t = tr[ls(q)].cnt - tr[ls(p)].cnt;
    return (k <= t) ? query(ls(p), ls(q), k, l, mid) : query(rs(p), rs(q), k - t, mid + 1, r);
}
int main() {
    red(n); red(q);
    for (re int i = 1; i <= n; ++i) red(a[i]), b[i] = a[i];
    sort(b + 1, b + n + 1);
    tt = unique(b + 1, b + n + 1) - b - 1;
    for (re int i = 1; i <= n; ++i) a[i] = lower_bound(b + 1, b + tt + 1, a[i]) - b;
    root[0] = newnode();
    for (re int i = 1; i <= n; ++i) {
        root[i] = newnode();
        modify(root[i - 1], root[i], a[i]);
    }
    for (re int i = 1; i <= q; ++i) {
        re int l, r, k; red(l); red(r); red(k);
        printf("%d\n", query(root[l - 1], root[r], k));
    }
    return 0;
}
```

---

[**Go Back**](././)
