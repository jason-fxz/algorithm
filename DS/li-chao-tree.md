
# li-chao-tree.cpp | DS | OI Algorithm

[**Go Back**](./../)

---

```cpp
// 李超线段树 luogu-P4097 [HEOI2013]Segment
#include <bits/stdc++.h>
#define ls (x<<1)
#define rs (x<<1|1)
template<typename _Tp>
inline void red(_Tp &x) {
    x = 0; bool fg = 0; char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-') fg ^= 1; ch = getchar();}
    while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (_Tp)(ch ^ 48), ch = getchar();
    if (fg) x = -x;
}
using namespace std;
typedef long long ll;
typedef double db;
const int N = 100010;
const int M = 40000;
struct line {
    db k, b;
} lin[N];
db val(int id, db X) {return lin[id].k * X + lin[id].b;}
int D[N << 2], n, id;
void modify(int L, int R, int id, int l = 1, int r = M - 1, int x = 1) {
    if (L <= l && r <= R) {
        int mid = (l + r) >> 1, lid = D[x];
        db lst = val(D[x], mid), now = val(id, mid);
        if (l == r) {if (now > lst) D[x] = id; return ;}
        if (lin[id].k > lin[D[x]].k) {
            if (now > lst) D[x] = id, modify(L, R, lid, l, mid, ls); // id->lid
            else modify(L, R, id, mid + 1, r, rs);
        } else if (lin[id].k < lin[D[x]].k) {
            if (now > lst) D[x] = id, modify(L, R, lid, mid + 1, r, rs); // id->lid
            else modify(L, R, id, l, mid, ls);
        } else if (lin[id].b > lin[D[x]].k) D[x] = id;
        return ;
    }
    int mid = (l + r) >> 1;
    if (L <= mid) modify(L, R, id, l, mid, x << 1);
    if (R > mid) modify(L, R, id, mid + 1, r, x << 1 | 1);
}
int gmax(int x, int y, int ps) {
    if (val(x, ps) > val(y, ps)) return x;
    if (val(x, ps) < val(y, ps)) return y;
    return (x < y) ? x : y;
}
int query(int ps, int l = 1, int r = M - 1, int x = 1) {
    if (l == r) return D[x];
    int mid = (l + r) >> 1, ret = D[x], t = 0;
    if (ps <= mid)
        t = query(ps, l, mid, ls);

    else
        t = query(ps, mid + 1, r, rs);
    return gmax(ret, t, ps);
}
int main() {
    red(n);
    int lstans = 0, tot = 0;
    for (int i = 1; i <= n; ++i) {
        int op; red(op);
        if (op == 0) {
            ++tot; int k; red(k); // 询问 x=k 最大交点
            k = (k + lstans - 1) % 39989 + 1;
            lstans = query(k);
            printf("%d\n", lstans);
        } else {
            int x0, y0, x1, y1; ++id; // 添加线段
            red(x0); red(y0); red(x1); red(y1);
            x0 = (x0 + lstans - 1) % 39989 + 1; x1 = (x1 + lstans - 1) % 39989 + 1;
            y0 = (y0 + lstans - 1) % (int)(1e9) + 1; y1 = (y1 + lstans - 1) % (int)(1e9) + 1;
            if (x0 > x1) swap(x0, x1), swap(y0, y1);
            if (x0 == x1) {
                lin[id].k = 0; lin[id].b = max(y1, y0);
            } else {
                lin[id].k = (db)(y1 - y0) / (db)(x1 - x0);
                lin[id].b = (db)y1 - lin[id].k * (db)x1;
            }
            modify(x0, x1, id);
        }
    }
    return 0;
}
```

---

[**Go Back**](./../)
