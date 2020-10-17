#include <bits/stdc++.h>
#define re register
using namespace std;
namespace fast_io {
    #define MAX_INPORT (1<<23)   // 一次读入量
    #define MAX_OUTPORT (1<<23)  // 一次输出量
    char buf[MAX_INPORT],*p1=buf,*p2=buf,obuf[MAX_OUTPORT],*O=obuf,*end=obuf+MAX_OUTPORT;
    inline char gc() {
        #ifdef DEBUG
            return getchar();
        #endif
        if(p1!=p2) return *p1++;
        p1=buf;
        p2=p1+fread(buf,1,MAX_INPORT,stdin);
        return p1==p2?EOF:*p1++;
    }
    template<typename T>    // 读入任意类型整数
    inline void red(T &x) {
        x=0;bool fg=0;char ch=gc();
        while(ch<'0'||ch>'9') {if(ch=='-') fg^=1;ch=gc();}
        while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(T)(ch^48),ch=gc();
        if(fg) x=-x;
    }
    inline void puc(char ch) {      // 输出字符
        #ifdef DEBUG
            return putchar(ch),void();
        #endif
        if(O!=end) *O++=ch;
        else {fwrite(obuf,O-obuf,1,stdout);O=obuf;*O++=ch;}
    }
    template<typename T>   
    void _prt(T x) {
        if(x>(T)9) _prt(x/(T)10);
        puc((char)(x%10+(T)'0'));
    }
    template<typename T>     // 读出任意类型整数
    void prt(T x) {if(x<0) puc('-'),x=-x;_prt(x);}
    void close() {fwrite(obuf,O-obuf,1,stdout);} // 输出
}
using fast_io::red;
using fast_io::prt;
using fast_io::puc;
#define ls(p) tr[p].lc
#define rs(p) tr[p].rc
const int N = 200010;

struct node {
    int cnt,lc,rc;
}tr[N*18];int root[N],tot;
int a[N],b[N],tt,n,q;
int newnode() { tr[++tot]={0,0,0};return tot;}
void pushup(int p) {tr[p].cnt=tr[ls(p)].cnt+tr[rs(p)].cnt;}
void modify(int p,int q,int val,int l=1,int r=tt) {
    if(l==r) return (p==0)?tr[q].cnt=1:tr[q].cnt=tr[p].cnt+1,void();
    int mid=(l+r)>>1;
    if(val<=mid) {
        modify(ls(p),ls(q)=newnode(),val,l,mid);
        rs(q)=rs(p);
    }else {
        modify(rs(p),rs(q)=newnode(),val,mid+1,r);
        ls(q)=ls(p);
    }
    pushup(q);
}
int query(int p,int q,int k,int l=1,int r=tt) {
    if(l==r) return b[l];
    int mid=(l+r)>>1,t=tr[ls(q)].cnt-tr[ls(p)].cnt;
    return (k<=t)?query(ls(p),ls(q),k,l,mid):query(rs(p),rs(q),k-t,mid+1,r);
}
int main() {
    red(n);red(q);
    for(re int i=1;i<=n;++i) red(a[i]),b[i]=a[i];
    sort(b+1,b+n+1);
    tt=unique(b+1,b+n+1)-b-1;
    for(re int i=1;i<=n;++i) a[i]=lower_bound(b+1,b+tt+1,a[i])-b;
    root[0]=newnode();
    for(re int i=1;i<=n;++i) {
        root[i]=newnode();
        modify(root[i-1],root[i],a[i]);
    }
    for(re int i=1;i<=q;++i) {
        re int l,r,k;red(l);red(r);red(k);
        prt(query(root[l-1],root[r],k));puc('\n');
    }
    fast_io::close();
    return 0;

}