
# seg_tree.cpp | DS | OI Algorithm

[**Go Back**](./../)

---

```cpp
// 区间加/乘法
#include <stdio.h>
#include <iostream>
using namespace std;
const int N = 100000;
int n, m;
long long mod;
long long sum[N << 2], mult[N << 2], add[N << 2], a[N];
void pushup(int x);
void pushdown(int x, int l, int r, int m);
void build(int x, int l, int r) {
    add[x] = 0; mult[x] = 1;
    if (l == r) {
        sum[x] = a[l];
        return ;
    }
    int m = (l + r) >> 1;
    build(x << 1, l, m);
    build(x << 1 | 1, m + 1, r);
    pushup(x);
}
void init() {
    scanf("%d%d%lld", &n, &m, &mod);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    build(1, 1, n);
}
void pushup(int x) {
    sum[x] = (sum[x << 1] + sum[x << 1 | 1]) % mod;
}
void pushdown(int x, int l, int r, int m) {
    //left son
    sum[x << 1] = (sum[x << 1] * mult[x] + (m - l + 1) * add[x]) % mod;
    mult[x << 1] = (mult[x << 1] * mult[x]) % mod;
    add[x << 1] = (add[x << 1] * mult[x] + add[x]) % mod;
    //right son
    sum[x << 1 | 1] = (sum[x << 1 | 1] * mult[x] + (r - m) * add[x]) % mod;
    mult[x << 1 | 1] = (mult[x << 1 | 1] * mult[x]) % mod;
    add[x << 1 | 1] = (add[x << 1 | 1] * mult[x] + add[x]) % mod;
    //clear
    add[x] = 0;
    mult[x] = 1;
}
void modify(int L, int R, long long val, int x, int l, int r) { //add
    if (L <= l && r <= R) {
        add[x] = (add[x] + val) % mod;
        sum[x] = (sum[x] + val * (long long)(r - l + 1)) % mod;
        return ;
    }
    int m = (l + r) >> 1;
    pushdown(x, l, r, m);
    if (L <= m)
        modify(L, R, val, x << 1, l, m);
    if (R > m)
        modify(L, R, val, x << 1 | 1, m + 1, r);
    pushup(x);
}
void modify1(int L, int R, long long val, int x, int l, int r) { //mult
    if (L <= l && r <= R) {
        sum[x] = (sum[x] * val) % mod;
        add[x] = (add[x] * val) % mod;
        mult[x] = (mult[x] * val) % mod;
        return ;
    }
    int m = (l + r) >> 1;
    pushdown(x, l, r, m);
    if (L <= m)
        modify1(L, R, val, x << 1, l, m);
    if (R > m)
        modify1(L, R, val, x << 1 | 1, m + 1, r);
    pushup(x);
}
long long query(int L, int R, int x, int l, int r) {
    if (L <= l && r <= R)
        return sum[x] % mod;
    int m = (l + r) >> 1;
    pushdown(x, l, r, m);
    long long ret = 0;
    if (L <= m)
        ret += query(L, R, x << 1, l, m);
    if (R > m)
        ret += query(L, R, x << 1 | 1, m + 1, r);
    return ret % mod;
}
int main() {
    init();
    while (m--) {
        int op, x, y;
        long long k;
        scanf("%d", &op);
        if (op == 1) { //mult
            scanf("%d%d%lld", &x, &y, &k);
            modify1(x, y, k, 1, 1, n);
        }
        if (op == 2) { //add
            scanf("%d%d%lld", &x, &y, &k);
            modify(x, y, k, 1, 1, n);
        }
        if (op == 3) { //query
            scanf("%d%d", &x, &y);
            printf("%lld\n", query(x, y, 1, 1, n));
        }
    }
}

```

---

[**Go Back**](./../)
