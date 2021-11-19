// 树状数组(Fenwick Tree) 区间加减，区间求和
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000010;
struct fenwick {
    ll s1[N], s2[N]; int n;
    void _add(int p, int v) {for (int x = p; x <= n; x += x & -x) s1[x] += v, s2[x] += (ll)v * p;}
    ll ask(int p) {ll r = 0; for (int x = p; x > 0; x -= x & -x) r += (ll)(p + 1) * s1[x] - s2[x]; return r;}
    ll query(int l, int r) {return ask(r) - ask(l - 1);}
    void modify(int l, int r, int v) {_add(l, v); _add(r + 1, -v);}
    void init(int n, int a[]) {
        fenwick::n = n;
        for (int i = 1, j; i <= n; ++i) {
            s1[i] += a[i] - a[i - 1]; s2[i] += (ll)(a[i] - a[i - 1]) * i;
            j = i + (i & -i);
            if (j <= n) s1[j] += s1[i], s2[j] += s2[i];
        }
    }
} T;
int n, q, a[N];
int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    T.init(n, a);
    while (q--) {
        int op, l, r, x;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1) {
            scanf("%d", &x);
            T.modify(l, r, x);
        } else
            printf("%lld\n", T.query(l, r));
    }
    return 0;
}
