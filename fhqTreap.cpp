#include <bits/stdc++.h>
#define irand (rand()*32768+rand())
using namespace std;
/*
    非旋Treap (fhq treap)模板
    2020-06-19
    by fxz
*/
struct Treap_plus{
    private:
    static const int N=100010;
    const int inf=0x7fffffff;
    struct node {
        int key,rnd;
        int siz,l,r;
    }d[N];
    int rt=0,tot;
    void updata(int t) {
        d[t].siz=d[d[t].l].siz+d[d[t].r].siz+1;
    }
    pair<int,int> split(int t,int p) {
        pair<int,int> res(0,0); 
        if(t==0) return res;
        if(p<=d[d[t].l].siz) {
            res=split(d[t].l,p);
            d[t].l=res.second;
            updata(t);
            res.second=t;
        }
        else {
            res=split(d[t].r,p-1-d[d[t].l].siz);
            d[t].r=res.first;
            updata(t);
            res.first=t;
        }
        return res;
    }
    int merge(int a,int b) {
        if(a==0) return b;
        if(b==0) return a;
        if(d[a].rnd<d[b].rnd) {
            d[a].r=merge(d[a].r,b);
            updata(a);
            return a;
        }
        d[b].l=merge(a,d[b].l);
        updata(b);
        return b;
    }
    int x_rank(int t,int key) {
        if(t==0) return 1;
        if(key<=d[t].key) return x_rank(d[t].l,key);
        return d[d[t].l].siz+1+x_rank(d[t].r,key);
    }
    int getkey(int t,int rk) {
        if(rk<=d[d[t].l].siz) return getkey(d[t].l,rk);
        if(rk==d[d[t].l].siz+1) return d[t].key;
        return getkey(d[t].r,rk-d[d[t].l].siz-1);
    }
    int pre(int t,int key,int res=0) {
        if(t==0) return res;
        if(d[t].key<key) return pre(d[t].r,key,t);
        return pre(d[t].l,key,res);
    }
    int nxt(int t,int key,int res=0) {
        if(t==0) return res;
        if(d[t].key>key) return nxt(d[t].l,key,t);
        return nxt(d[t].r,key,res);
    }
    public:
    void build() {
        srand(233);
        d[rt].rnd=inf;
    }
    void insert(int key) {
        int k=x_rank(rt,key);
        pair<int,int> a=split(rt,k-1);
        d[++tot]={key,irand,1,0,0};
        rt=merge(merge(a.first,tot),a.second);
    }
    void remove(int key) {
        int k=x_rank(rt,key);
        pair<int,int> a=split(rt,k-1),b=split(a.second,1);
        rt=merge(a.first,b.second);
    }
    int getrank(int key) {
        return x_rank(rt,key);
    }
    void print(int t) {
        if(t==0) return ;
        print(d[t].l);
        printf("%d ",d[t].key);
        print(d[t].r);
    }
    int getpre(int key) {
        return d[pre(rt,key)].key;
    }
    int getnxt(int key) {
        return d[nxt(rt,key)].key;
    }
    int getkey(int rk) {
        return getkey(rt,rk);
    }
    int getroot() {
        return rt;
    }
}tp;


int n,op,x;
int main() {
    tp.build();
    scanf("%d",&n);
    while(n--) {
        scanf("%d%d",&op,&x);
        switch(op) {
            case 1:tp.insert(x);break;
            case 2:tp.remove(x);break;
            case 3:printf("%d\n",tp.getrank(x));break;
            case 4:printf("%d\n",tp.getkey(x));break;
            case 5:printf("%d\n",tp.getpre(x));break;
            case 6:printf("%d\n",tp.getnxt(x));break;		
        }
    }
    return 0;
}