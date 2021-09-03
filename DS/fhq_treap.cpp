#include <bits/stdc++.h>
using namespace std;
template<typename DataType, int N = 100010>
struct fhq_Treap {
  private:
    const DataType inf; //inf的定义
    struct node {
        DataType key; int rnd;
        int siz, l, r;
    } d[N];
    int rt = 0, tot;
    void updata(int t) {
        d[t].siz = d[d[t].l].siz + d[d[t].r].siz + 1;
    }
    pair<int, int> split(int t, int p) {
        pair<int, int> res(0, 0);
        if (t == 0) return res;
        if (p <= d[d[t].l].siz) {
            res = split(d[t].l, p);
            d[t].l = res.second;
            updata(t);
            res.second = t;
        } else {
            res = split(d[t].r, p - 1 - d[d[t].l].siz);
            d[t].r = res.first;
            updata(t);
            res.first = t;
        }
        return res;
    }
    int merge(int a, int b) {
        if (a == 0) return b;
        if (b == 0) return a;
        if (d[a].rnd < d[b].rnd) {
            d[a].r = merge(d[a].r, b);
            updata(a);
            return a;
        }
        d[b].l = merge(a, d[b].l);
        updata(b);
        return b;
    }
    int x_rank(int t, DataType key) {
        if (t == 0) return 1;
        if (!(d[t].key < key)) return x_rank(d[t].l, key); //key<=d[t].key
        return d[d[t].l].siz + 1 + x_rank(d[t].r, key);
    }
    DataType getkey(int t, int rk) {
        if (rk <= d[d[t].l].siz) return getkey(d[t].l, rk);
        if (rk == d[d[t].l].siz + 1) return d[t].key;
        return getkey(d[t].r, rk - d[d[t].l].siz - 1);
    }
    int pre(int t, DataType key, int res = 0) {
        if (t == 0) return res;
        if (d[t].key < key) return pre(d[t].r, key, t);
        return pre(d[t].l, key, res);
    }
    int nxt(int t, DataType key, int res = 0) {
        if (t == 0) return res;
        if (key < d[t].key) return nxt(d[t].l, key, t);
        return nxt(d[t].r, key, res);
    }
    int newnode(DataType key) {
        d[++tot] = {key, rand(), 1, 0, 0};
        return tot;
    }
  public:
    void build() {
        rt = tot = 0;
        srand(time(0));
        rt = newnode(inf); //这里需要修改
        d[rt].l = newnode(-inf);
        updata(rt);
    }
    void insert(DataType key) {
        int k = x_rank(rt, key);
        pair<int, int> a = split(rt, k - 1);
        rt = merge(merge(a.first, newnode(key)), a.second);
    }
    void remove(DataType key) {
        int k = x_rank(rt, key);
        pair<int, int> a = split(rt, k - 1), b = split(a.second, 1);
        rt = merge(a.first, b.second);
    }
    int getrank(DataType key) {
        return x_rank(rt, key);
    }
    DataType getpre(DataType key) {
        return d[pre(rt, key)].key;
    }
    DataType getnxt(DataType key) {
        return d[nxt(rt, key)].key;
    }
    DataType getkey(int rk) {
        return getkey(rt, rk);
    }
    int getroot() {
        return rt;
    }
};