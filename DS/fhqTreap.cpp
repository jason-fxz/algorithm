// fhq - treap 简易模板
#include <bits/stdc++.h>
#define ls(p) t[p].l
#define rs(p) t[p].r
#define mid ((l+r)>>1)
using namespace std;
const int N = 100010;
mt19937 rd(random_device{}()); // random maker
struct node {
    int l, r, siz, rnd, val, tag; /* other data/tags */
} t[N]; int tot, root;
/* ---------- for recycle nodes ------------
int cyc[N],cyccnt;
inline void delnode(int p) {cyc[++cyccnt]=p;}
inline void newnode(int val) {
    int id=(cyccnt>0)?cyc[cyccnt--]:++tot;
    t[id]={0,0,1,(int)(rd()),val}; return id;
}
*/
inline int newnode(int val) { t[++tot] = {0, 0, 1, (int)(rd()), val}; return tot;} // create a new node
inline void updata(int p) {t[p].siz = t[ls(p)].siz + t[rs(p)].siz + 1; /* pushup other datas */ }
inline void pushtag(int p, int vl) { /* tag to push */ }
inline void pushdown(int p) {
    if (t[p].tag != std_tag) {
        if (ls(p)) pushtag(ls(p), t[p].tag);
        if (rs(p)) pushtag(rs(p), t[p].tag);
        t[p].tag = std_tag;
    }
}
int merge(int p, int q) {
    if (!p || !q) return p + q;
    if (t[p].rnd < t[q].rnd) {
        pushdown(p);
        rs(p) = merge(rs(p), q);
        updata(p); return p;
    } else {
        pushdown(q);
        ls(q) = merge(p, ls(q));
        updata(q); return q;
    }
}
void split(int p, int k, int &x, int &y) {
    if (!p) x = 0, y = 0;
    else {
        pushdown(p);
        if (t[ls(p)].siz >= k) y = p, split(ls(p), k, x, ls(p));
        else x = p, split(rs(p), k - t[ls(p)].siz - 1, rs(p), y);
        updata(p);
    }
}
int build(int l, int r) { // build tree on a[l..r], return the root
    if (l > r) return 0;
    return merge(build(l, mid - 1), merge(newnode(a[mid]), build(mid + 1, r)));
}
/*
    other functions base on split() and merge()

*/
int main() {
}