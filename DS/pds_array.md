
# pds_array.cpp | DS | OI Algorithm

[**Go Back**](./)

---

```cpp
// 可持久化数组
#include <cstdio>
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
const int N = 1000010;
struct node {
    int lc, rc, val;
} tr[N * 21]; int tot;
int root[N];
int n, m, a[N];
int newnode() {
    tr[++tot] = {0, 0, 0};
    return tot;
}
void build(int p, int l = 1, int r = n) {
    if (l == r) return tr[p].val = a[l], void();
    int mid = (l + r) >> 1;
    build(ls(p) = newnode(), l, mid);
    build(rs(p) = newnode(), mid + 1, r);
}
void modify(int p, int q, int pos, int val, int l = 1, int r = n) {
    if (l == r) return tr[q].val = val, void();
    int mid = (l + r) >> 1;
    if (pos <= mid) {
        modify(ls(p), ls(q) = newnode(), pos, val, l, mid);
        rs(q) = rs(p);
    } else {
        modify(rs(p), rs(q) = newnode(), pos, val, mid + 1, r);
        ls(q) = ls(p);
    }
}
int query(int p, int pos, int l = 1, int r = n) {
    if (l == r) return tr[p].val;
    int mid = (l + r) >> 1;
    if (pos <= mid) return query(ls(p), pos, l, mid);
    else return query(rs(p), pos, mid + 1, r);
}
int main() {
    red(n); red(m);
    for (re int i = 1; i <= n; ++i) red(a[i]);
    root[0] = newnode(); build(root[0]);
    for (re int i = 1; i <= m; ++i) {
        re int v, op, loc, vl;
        red(v); red(op); red(loc);
        if (op == 1) {
            red(vl);
            modify(root[v], root[i] = newnode(), loc, vl);
        } else {
            printf("%d\n", query(root[v], loc));
            root[i] = root[v];
        }
    }
}
```

---

[**Go Back**](./)
