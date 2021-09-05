
# KDTree2.cpp | DS | OI Algorithm

[**Go Back**](./../)

---

```cpp
/*
	K-D Tree 维护空间权值 (单点修改 & 空间查询)
	时间复杂度 O(log n) ~ O(n^(1-1/k))
*/
#include <bits/stdc++.h>
template <typename T>
inline void red(T &x) {
    x = 0; bool f = 0; char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-') f ^= 1; ch = getchar();}
    while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (T)(ch ^ 48), ch = getchar();
    if (f) x = -x;
}
using namespace std;
const int N = 200010;
typedef double db;
template <typename _Tp> void umin(_Tp &x, _Tp y) {if (x > y) x = y;}
template <typename _Tp> void umax(_Tp &x, _Tp y) {if (x < y) x = y;}
template <typename _Tp> _Tp sqr(_Tp x) {return x * x;}
namespace KDT {
    struct dat {
        int X[2];
        int &operator[](const int k) {return X[k];}
    } p[N];
    db alp = 0.725; // 重构常数
    int nowd;
    bool cmp(int a, int b) {return p[a][nowd] < p[b][nowd];}
    int root, cur, d[N], lc[N], rc[N], L[N][2], R[N][2], siz[N], sum[N], val[N];
    //  root:根 cur:总点数 d:当前分割维度 lc/rc:左右儿子 L/R:当前空间范围 siz:子树大小  sum/val 空间的值,单点的值
    int g[N], t; // 用于重构的临时数组
    void pushup(int x) {
        siz[x] = siz[lc[x]] + siz[rc[x]] + 1;
        sum[x] = sum[lc[x]] + sum[rc[x]] + val[x];
        L[x][0] = R[x][0] = p[x][0];
        L[x][1] = R[x][1] = p[x][1];
        if (lc[x]) {
            umin(L[x][0], L[lc[x]][0]); umax(R[x][0], R[lc[x]][0]);
            umin(L[x][1], L[lc[x]][1]); umax(R[x][1], R[lc[x]][1]);
        }
        if (rc[x]) {
            umin(L[x][0], L[rc[x]][0]); umax(R[x][0], R[rc[x]][0]);
            umin(L[x][1], L[rc[x]][1]); umax(R[x][1], R[rc[x]][1]);
        }
    }
    int build(int l, int r) { // 对 g[1...t] 进行建树 ，！！注意了，对应点都是 g[x]
        if (l > r) return 0;
        int mid = (l + r) >> 1;
        db av[2] = {0, 0}, va[2] = {0, 0};
        for (int i = l; i <= r; ++i) av[0] += p[g[i]][0], av[1] += p[g[i]][1];
        av[0] /= (r - l + 1); av[1] /= (r - l + 1);
        for (int i = l; i <= r; ++i) va[0] += sqr(av[0] - p[g[i]][0]), va[1] += sqr(av[1] - p[g[i]][1]);
        if (va[0] > va[1]) d[g[mid]] = nowd = 0;
        else d[g[mid]] = nowd = 1;
        nth_element(g + l, g + mid, g + r + 1, cmp);
        lc[g[mid]] = build(l, mid - 1); rc[g[mid]] = build(mid + 1, r);
        pushup(g[mid]);
        return g[mid];
    }
    void expand(int x) { // 将子树展开到临时数组里
        if (!x) return;
        expand(lc[x]);
        g[++t] = x;
        expand(rc[x]);
    }
    void rebuild(int &x) { // x 所在子树重构
        t = 0; expand(x);
        x = build(1, t);
    }
    bool chk(int x) {return alp * siz[x] <= (db)max(siz[lc[x]], siz[rc[x]]);} // 判断失衡
    void insert(int &x, int a) { // 插入点 a , p[a],val[a] 为其信息
        if (!x) { x = a; pushup(x); d[x] = rand() & 1; return; }
        if (p[a][d[x]] <= p[x][d[x]]) insert(lc[x], a);
        else insert(rc[x], a);
        pushup(x);
        if (chk(x)) rebuild(x); // 失衡暴力重构
    }
    dat Lt, Rt; // 询问一块空间的值(为了减小常数把参数放在外面)
    int query(int x) {
        if (!x || Rt[0] < L[x][0] || Lt[0] > R[x][0] || Rt[1] < L[x][1]
            || Lt[1] > R[x][1]) return 0; // 结点为空或与询问取间无交
        if (Lt[0] <= L[x][0] && R[x][0] <= Rt[0] && Lt[1] <= L[x][1]
            && R[x][1] <= Rt[1]) return sum[x]; // 区间完全覆盖
        int ret = 0;
        if (Lt[0] <= p[x][0] && p[x][0] <= Rt[0] && Lt[1] <= p[x][1]
            && p[x][1] <= Rt[1]) ret += val[x]; // 当前点在区间内
        return query(lc[x]) + query(rc[x]) + ret;
    }
}
using namespace KDT;
int n, lstans;
int main() {
    red(n);
    for (int op;;) {
        red(op);
        switch (op) {
        case 1:
            ++cur; red(p[cur][0]); red(p[cur][1]); red(val[cur]);
            p[cur][0] ^= lstans; p[cur][1] ^= lstans; val[cur] ^= lstans;
            insert(root, cur);
            break;
        case 2:
            red(Lt[0]); red(Lt[1]); red(Rt[0]); red(Rt[1]);
            Lt[0] ^= lstans; Lt[1] ^= lstans; Rt[0] ^= lstans; Rt[1] ^= lstans;
            printf("%d\n", lstans = query(root));
            break;
        case 3:	return 0; break;
        }
    }
    return 0;
}

```

---

[**Go Back**](./../)
