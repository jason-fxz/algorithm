/* 
    维护异或和的 01 trie 
    支持插入，删除，修改，全局+1
*/
#include <bits/stdc++.h>

namespace trie {
    #define ls(p) t[p].ch[0]
    #define rs(p) t[p].ch[1]
    const int N = 1000010;
    const int M = 20;
    struct node {
        int ch[2],w,xorw;
    }t[N*M];
    int root[N],tot;
    void pushup(int p) {
        t[p].w=t[p].xorw=0;
        if(ls(p)) {
            t[p].w+=t[ls(p)].w;
            t[p].xorw^=t[ls(p)].xorw<<1;
        }
        if(rs(p)) {
            t[p].w+=t[rs(p)].w;
            t[p].xorw^=(t[rs(p)].xorw<<1)|(t[rs(p)].w&1);
        }
    }
    int newnode() {
        ++tot;t[tot]={0,0,0,0};return tot;
    }
    void insert(int &p,int x,int d=0) {
        if(!p) p=newnode();
        if(d>=M) return ++t[p].w,void();
        insert(t[p].ch[x&1],x>>1,d+1);
        pushup(p);
    }
    void remove(int p,int x,int d=0) {
        if(d>=M) return --t[p].w,void();
        remove(t[p].ch[x&1],x>>1,d+1);
        pushup(p);
    }
    void addall(int p) {
        std::swap(ls(p),rs(p));
        if(ls(p)) addall(ls(p));
        pushup(p);
    }
    int xorsum(int p) {return t[p].xorw;}
}

int main() {

    return 0;
}
