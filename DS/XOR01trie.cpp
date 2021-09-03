/*
    维护异或和的 01 trie
    支持插入，删除，修改，全局+1
*/
#include <bits/stdc++.h>


namespace trie {
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
    const int N = 600010;
    const int DEP = 22;
    int ch[N * DEP][2], w[N * DEP], xorw[N * DEP], sz;
    int newnode() {++sz; ch[sz][0] = ch[sz][1] = 0; w[sz] = xorw[sz] = 0; return sz;}
    void pushup(int p) {
        w[p] = xorw[p] = 0;
        if (ls(p)) {
            w[p] += w[ls(p)];
            xorw[p] ^= xorw[ls(p)] << 1;
        }
        if (rs(p)) {
            w[p] += w[rs(p)];
            xorw[p] ^= (xorw[rs(p)] << 1) | (w[rs(p)] & 1);
        }
    }
    void insert(int &p, int x, int d = 0) {
        if (!p) p = newnode();
        if (d >= DEP) return ++w[p], void();
        insert(ch[p][x & 1], x >> 1, d + 1);
        pushup(p);
    }
    void erase(int p, int x, int d = 0) {
        if (d >= DEP) return --w[p], void();
        erase(ch[p][x & 1], x >> 1, d + 1);
        pushup(p);
    }
    // merge q to p
    int merge(int p, int q) {
        if (!p || !q) return p + q;
        w[p] += w[q]; xorw[p] ^= xorw[q];
        ls(p) = merge(ls(p), ls(q));
        rs(p) = merge(rs(p), rs(q));
        return p;
    }
    void addall(int p) {
        swap(ls(p), rs(p));
        if (ls(p)) addall(ls(p));
        pushup(p);
    }
    int xorsum(int p) {return xorw[p];}
}

int main() {
    return 0;
}
