// 线段树套主席树
#include <bits/stdc++.h>
#define ls(p) t[p].l
#define rs(p) t[p].r
#define lc (x << 1)
#define rc (x << 1 | 1)
#define mid ((l + r) >> 1)
using namespace std;
template <typename Tp> void read(Tp &x) {
    x = 0; char ch = getchar(); int f = 0;
    while (ch < '0' || ch > '9') { if (ch == '-') f ^= 1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (Tp)(ch ^ 48), ch = getchar();
    if (f) x = -x;
}
template <typename Tp, typename... Args>
void read(Tp &t, Args &... args){ read(t); read(args...); }

const int N = 50010;
const int INF = 2147483647;
const int MAX = 1e8;
const int MIN = -1e8;

int n, m, a[N];
struct node {
    int l, r, sum;
}t[N * 450];
int rt[N << 2], tot;

int newnode() {
    t[++tot] = { 0, 0, 0 };
    return tot;
}

void modify(int &p, int val, int cnt, int l = MIN, int r = MAX) {
    if (!p) p = newnode();
    if (l == r) return t[p].sum += cnt, void();
    if (val <= mid) modify(ls(p), val, cnt, l, mid);
    else modify(rs(p), val, cnt, mid + 1, r);
    t[p].sum = t[ls(p)].sum + t[rs(p)].sum;
}

int query(int p, int L, int R, int l = MIN, int r = MAX) {
    if (!p || L > R) return 0;
    if (L <= l && r <= R) return t[p].sum;
    if (L <= mid && R > mid) return query(ls(p), L, R, l, mid) + query(rs(p), L, R, mid + 1, r);
    return (L <= mid) ? query(ls(p), L, R, l, mid) : query(rs(p), L, R, mid + 1, r);
}

void Build(int l = 1, int r = n, int x = 1) {
    for (int i = l; i <= r; ++i) modify(rt[x], a[i], 1);
    if (l == r) return ;
    Build(l, mid, lc);
    Build(mid + 1, r, rc);
}

// 返回 [L, R] 中 <= k 的个数
int Rank(int L, int R, int k, int l = 1, int r = n, int x = 1) {
    if(L <= l && r <= R) return query(rt[x], 0, k);
    int ret = 0;
    if (L <= mid) ret = Rank(L, R, k, l, mid, lc);
    if (R > mid) ret += Rank(L, R, k, mid + 1, r, rc);
    return ret;
}

vector<int> nods;
void work(int L, int R, int l = 1, int r = n, int x = 1) {
    if (L <= l && r <= R) return nods.push_back(rt[x]);
    if (L <= mid) work(L, R, l, mid, lc);
    if (R > mid) work(L, R, mid + 1, r, rc);
}

// 返回 [L, R] 中排名第 k 的数，不合法则 -INF
int Kth(int L, int R, int k) {
    if (k <= 0 || k > R - L + 1) return -INF;
    nods.clear();
    work(L, R);
    int l = MIN, r = MAX, cnt;
    while (l < r) {
        cnt = 0;
        for (int i = 0; i < (int)nods.size(); ++i) cnt += t[ls(nods[i])].sum;
        if (cnt >= k) {
            for (int i = 0; i < (int)nods.size(); ++i) nods[i] = ls(nods[i]);
            r = mid;
        } else {
            for (int i = 0; i < (int)nods.size(); ++i) nods[i] = rs(nods[i]);
            l = mid + 1;
            k -= cnt;
        }
    }
    return l;
}

void Modify(int pos, int lst, int val, int l = 1, int r = n, int x = 1) {
    modify(rt[x], lst, -1);
    modify(rt[x], val, 1);
    if (l == r) return ;
    if (pos <= mid) Modify(pos, lst, val, l, mid, lc);
    else Modify(pos, lst, val, mid + 1, r, rc);
}


int main() {
    read(n, m);
    for (int i = 1; i <= n; ++i) read(a[i]);
    Build();
    for (int cs = 1; cs <= m; ++cs) {
        int op, x, y, z, k;
        read(op, x, y);
        switch (op)
        {
        case 1:
            read(z);   
            printf("%d\n", Rank(x, y, z - 1) + 1);
            break;
        case 2:
            read(z);
            printf("%d\n", Kth(x, y, z));
            break;
        case 3:
            Modify(x, a[x], y); a[x] = y;
            break;
        case 4:
            read(z);
            k = Kth(x, y, Rank(x, y, z - 1));
            printf("%d\n", k == -INF ? -INF : k);
            break;
        case 5:
            read(z);
            k = Kth(x, y, Rank(x, y, z) + 1);
            printf("%d\n", k == -INF ? INF : k);
            break;
        }
    }
    return 0;
}

/*
1. [l, r] k 排名
找每个区间比 k 小的个数
2. [l, r] 排名为 k
所有区间捞出来，线段树二分？
3. 单点修改下标 pos 的数改为 k 
改就是了
4. [l, r] x 的前驱
Kth(Rank(z - 1))
5. [l, r] x 的后继
Kyh(Rank(z) + 1)
*/
