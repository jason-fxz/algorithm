/*
 * seg-beats 吉司机线段树
 * 区间最值操作
 * 支持 区间取min，区间取max，区间加减，区间求和，区间最小/大
 * 复杂度 O(m log n)
 */

#include <bits/stdc++.h>
#define ls (x << 1)
#define rs (x << 1 | 1)
#define mid ((l + r) >> 1)
template <typename Tp>
inline void read(Tp &x) {
    x = 0; bool fg = 0; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') fg ^= 1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (Tp)(ch ^ 48), ch = getchar();
    if (fg) x = -x;
}
template <typename Tp, typename... Args>
void read(Tp &t, Args &...args) { read(t); read(args...); }
template <typename Tp>
inline void write(Tp x, char ch = '\n') {
    static char buf[128]; int tot = 0;
    if (x < 0) x = -x, putchar('-');
    while (x) buf[tot++] = '0' + x % 10, x /= 10;
    if (tot == 0) putchar('0');
    while (tot--) putchar(buf[tot]);
    if (ch) putchar(ch);
}
using namespace std;
typedef long long ll;
const int N = 500010;
const int inf = 0x3f3f3f3f;
struct datmn {
    int fi, se, cnt;
    datmn() {fi = se = inf; cnt = 0;}
    void ins(int x, int c) {
        if (x < fi) se = fi, cnt = c, fi = x;
        else if (x == fi) cnt += c;
        else if (x < se) se = x;
    }
    friend datmn operator+(const datmn &a, const datmn &b) {
        datmn r = a; r.ins(b.fi, b.cnt); r.ins(b.se, 0); return r;
    }
};
struct datmx {
    int fi, se, cnt;
    datmx() {fi = se = -inf; cnt = 0;}
    void ins(int x, int c) {
        if (x > fi) se = fi, cnt = c, fi = x;
        else if (x == fi) cnt += c;
        else if (x > se) se = x;
    }
    friend datmx operator+(const datmx &a, const datmx &b) {
        datmx r = a; r.ins(b.fi, b.cnt); r.ins(b.se, 0); return r;
    }
};

struct node {
    datmn mn; datmx
    mx; // mn: (最小值，严格次小值，最小值个数) , mx: (最大值，严格次大值，最大值个数)
    ll sum; int addmn, addmx, add,
    len; // sum 区间和，addmn 最小值lazytag，addmx 最大值lazytag，add 其他数 lazytag，len 区间长度
} t[N << 2];
// ostream &operator<<(ostream& out, const datmx &d) {
//     return out << "dat{ " << d.fi << " (" << d.cnt << ") ," << d.se << " } ";
// }
// ostream &operator<<(ostream& out, const datmn &d) {
//     return out << "dat{ " << d.fi << " (" << d.cnt << ") ," << d.se << " } ";
// }
// ostream &operator<<(ostream& out, const node &d) {
//     return out << "mn" << d.mn << "mx" << d.mx << " sum=" << d.sum << " addmn=" << d.addmn << " addmx=" << d.addmx << " add=" << d.add << " ";
// }
int n, m, a[N];
void pushup(int x) {
    t[x].mx = t[ls].mx + t[rs].mx;
    t[x].mn = t[ls].mn + t[rs].mn;
    t[x].sum = t[ls].sum + t[rs].sum;
}
void build(int l = 1, int r = n, int x = 1) {
    t[x].add = t[x].addmn = t[x].addmx = 0;
    t[x].len = r - l + 1;
    if (l == r) {
        t[x].mx = datmx(); t[x].mx.ins(a[l], 1);
        t[x].mn = datmn(); t[x].mn.ins(a[l], 1);
        t[x].sum = a[l];
        return;
    }
    build(l, mid, ls); build(mid + 1, r, rs);
    pushup(x);
}
void update(int x, int vn, int vx, int v) { // vn: addmn, vx: addmx, v: add
    if (t[x].mn.fi ==
        t[x].mx.fi) { // 所有数相同特判，此时最大值 tag 和最小值 tag 应该相同且不等于其他值 tag
        if (vn == v) vn = vx;
        else vx = vn;
        t[x].sum += (ll)vn * t[x].mn.cnt;
    } else t[x].sum += (ll)vn * t[x].mn.cnt + (ll) vx * t[x].mx.cnt + (ll)v * (t[x].len - t[x].mn.cnt -
                           t[x].mx.cnt);
    if (t[x].mn.se == t[x].mx.fi) t[x].mn.se += vx; // 次小值 = 最大值，应该用最大值 tag 处理
    else if (t[x].mn.se != inf) t[x].mn.se += v;
    if (t[x].mx.se == t[x].mn.fi) t[x].mx.se += vn; // 次大值同理
    else if (t[x].mx.se != -inf) t[x].mx.se += v;
    t[x].mn.fi += vn; t[x].mx.fi += vx;
    t[x].addmn += vn; t[x].addmx += vx; t[x].add += v;
}
void pushdown(int x) {
    int mn = min(t[ls].mn.fi, t[rs].mn.fi);
    int mx = max(t[ls].mx.fi, t[rs].mx.fi);
    update(ls, (mn == t[ls].mn.fi) ? t[x].addmn : t[x].add, (mx == t[ls].mx.fi) ? t[x].addmx : t[x].add,
           t[x].add);
    update(rs, (mn == t[rs].mn.fi) ? t[x].addmn : t[x].add, (mx == t[rs].mx.fi) ? t[x].addmx : t[x].add,
           t[x].add);
    t[x].add = t[x].addmn = t[x].addmx = 0;
}

void modifyadd(int L, int R, int v, int l = 1, int r = n, int x = 1) {
    if (r < L || R < l) return ;
    if (L <= l && r <= R) return update(x, v, v, v);
    pushdown(x);
    modifyadd(L, R, v, l, mid, ls);
    modifyadd(L, R, v, mid + 1, r, rs);
    pushup(x);
}
void modifymin(int L, int R, int v, int l = 1, int r = n, int x = 1) {
    if (r < L || R < l) return ;
    if (L <= l && r <= R && v > t[x].mx.se) {
        if (v >= t[x].mx.fi) return ;
        update(x, 0, v - t[x].mx.fi, 0);
        return;
    }
    pushdown(x);
    modifymin(L, R, v, l, mid, ls);
    modifymin(L, R, v, mid + 1, r, rs);
    pushup(x);
}
void modifymax(int L, int R, int v, int l = 1, int r = n, int x = 1) {
    if (r < L || R < l) return ;
    if (L <= l && r <= R && v < t[x].mn.se) {
        if (v <= t[x].mn.fi) return;
        update(x, v - t[x].mn.fi, 0, 0);
        return;
    }
    pushdown(x);
    modifymax(L, R, v, l, mid, ls);
    modifymax(L, R, v, mid + 1, r, rs);
    pushup(x);
}
int querymax(int L, int R, int l = 1, int r = n, int x = 1) {
    if (r < L || R < l) return -inf;
    if (L <= l && r <= R) return t[x].mx.fi;
    pushdown(x);
    return max(querymax(L, R, l, mid, ls), querymax(L, R, mid + 1, r, rs));
}
int querymin(int L, int R, int l = 1, int r = n, int x = 1) {
    if (r < L || R < l) return inf;
    if (L <= l && r <= R) return t[x].mn.fi;
    pushdown(x);
    return min(querymin(L, R, l, mid, ls), querymin(L, R, mid + 1, r, rs));
}
ll querysum(int L, int R, int l = 1, int r = n, int x = 1) {
    if (r < L || R < l) return 0;
    if (L <= l && r <= R) return t[x].sum;
    pushdown(x);
    return querysum(L, R, l, mid, ls) + querysum(L, R, mid + 1, r, rs);
}
void print(int l = 1, int r = n, int x = 1) {
    if (l == r) {
        cerr << t[x].sum << " ";
        return ;
    }
    pushdown(x);
    print(l, mid, ls);
    print(mid + 1, r, rs);
}
signed main() {
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    build();
    read(m);
    for (int i = 1; i <= m; ++i) {
        int op, l, r, x;
        read(op, l, r);
        if (op <= 3) read(x);
        switch (op) {
        case 1:
            modifyadd(l, r, x);
            break;
        case 2:
            modifymax(l, r, x);
            break;
        case 3:
            modifymin(l, r, x);
            break;
        case 4:
            write(querysum(l, r));
            break;
        case 5:
            write(querymax(l, r));
            break;
        case 6:
            write(querymin(l, r));
            break;
        }
    }
    return 0;
}

