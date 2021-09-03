#include <cstdio>
#include <iostream>
#define ls(p) tr[p].lc
#define rs(p) tr[p].rc
#define re register
using namespace std;
const int N = 200010;
struct node {
    int lc, rc, val, siz;
} tr[N * 41];
int root[N], tot;
int n, m;
int newnode() {
    tr[++tot] = {0, 0, 0};
    return tot;
}
void build(int p, int l = 1, int r = n) {
    if (l == r) return tr[p].val = l, tr[p].siz = 1, void();
    int mid = (l + r) >> 1;
    build(ls(p) = newnode(), l, mid);
    build(rs(p) = newnode(), mid + 1, r);
}
void modify_fa(int p, int q, int pos, int val, int l = 1, int r = n) {
    if (l == r) return tr[q].val = val, tr[q].siz = tr[p].siz, void();
    int mid = (l + r) >> 1;
    if (pos <= mid) {
        modify_fa(ls(p), ls(q) ? ls(q) : ls(q) = newnode(), pos, val, l, mid);
        if (rs(q) == 0)rs(q) = rs(p);
    } else {modify_fa(rs(p), rs(q) ? rs(q) : rs(q) = newnode(), pos, val, mid + 1, r); if (ls(q) == 0)ls(q) = ls(p);}
}
void modify_dep(int p, int q, int pos, int siz, int l = 1, int r = n) {
    if (l == r) return tr[q].siz = siz, tr[q].val = tr[p].val, void();
    int mid = (l + r) >> 1;
    if (pos <= mid) {
        modify_dep(ls(p), ls(q) ? ls(q) : ls(q) = newnode(), pos, siz, l, mid);
        if (rs(q) == 0)rs(q) = rs(p);
    } else {modify_dep(rs(p), rs(q) ? rs(q) : rs(q) = newnode(), pos, siz, mid + 1, r); if (ls(q) == 0)ls(q) = ls(p);}
}
// return the node number
int query(int p, int pos, int l = 1, int r = n) {
    if (l == r) return p;
    int mid = (l + r) >> 1;
    if (pos <= mid) return query(ls(p), pos, l, mid);
    else return query(rs(p), pos, mid + 1, r);
}
int find(int rt, int u) {
    int pa = query(rt, u);
    if (tr[pa].val == u) return u;
    return find(rt, tr[pa].val);
}
int main() {
    scanf("%d%d", &n, &m);
    root[0] = newnode(); build(root[0]);
    for (re int i = 1; i <= m; ++i) {
        re int opt, a, b;
        scanf("%d%d", &opt, &a);
        if (opt == 1) { // 合并 a,b
            scanf("%d", &b);
            root[i] = newnode();
            int f1 = find(root[i - 1], a), f2 = find(root[i - 1], b);
            int sz1 = tr[query(root[i - 1], f1)].siz, sz2 = tr[query(root[i - 1], f2)].siz;
            if (f1 != f2) {
                if (sz1 > sz2) swap(f1, f2), swap(sz1, sz2);
                modify_fa(root[i - 1], root[i], f1, f2);
                modify_dep(root[i - 1], root[i], f2, sz1 + sz2);
            } else
                root[i] = root[i - 1];
        }
        if (opt == 2) // 回到状态 a
            root[i] = root[a];
        if (opt == 3) { // 询问 a,b 是否在同一集合
            scanf("%d", &b);
            root[i] = root[i - 1];
            int f1 = find(root[i], a), f2 = find(root[i], b);
            printf("%d\n", f1 == f2);
        }
    }
    return 0;
}
