#include <cstdio>
#define ls(p) tr[p].lc
#define rs(p) tr[p].rc
#define re register
using namespace std;
namespace fast_io {
    #define MAX_INPORT (1<<21)   // 一次读入量
    #define MAX_OUTPORT (1<<21)  // 一次输出量
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
    void puc(char ch) {      // 输出字符
        if(O!=end) *O++=ch;
        else {fwrite(obuf,O-obuf,1,stdout);O=obuf;*O++=ch;}
    }
    template<typename T>   
    void _prt(T x) {
        if(x>(T)9) _prt(x/(T)10);
        if(O!=end) *O++=(char)(x%10+(T)'0');
        else {fwrite(obuf,O-obuf,1,stdout);O=obuf;*O++=(char)(x%(T)10+(T)'0');}
    }
    template<typename T>     // 读出任意类型整数
    void prt(T x) {if(x<0) puc('-'),x=-x;_prt(x);}
    void close() {fwrite(obuf,O-obuf,1,stdout);} // 输出
}
using fast_io::red;
using fast_io::prt;
using fast_io::puc;
const int N = 1000010;
struct node{
    int lc,rc,val;
}tr[N*21];int tot;
int root[N];
int n,m,a[N];
int newnode() {
    tr[++tot]={0,0,0};
    return tot;
}
void build(int p,int l=1,int r=n) {
    if(l==r) return tr[p].val=a[l],void();
    int mid=(l+r)>>1;
    build(ls(p)=newnode(),l,mid);
    build(rs(p)=newnode(),mid+1,r);
}
void modify(int p,int q,int pos,int val,int l=1,int r=n) {
    if(l==r) return tr[q].val=val,void();
    int mid=(l+r)>>1;
    if(pos<=mid) {
        modify(ls(p),ls(q)=newnode(),pos,val,l,mid);
        rs(q)=rs(p);
    }else {
        modify(rs(p),rs(q)=newnode(),pos,val,mid+1,r);
        ls(q)=ls(p);
    }
}
int query(int p,int pos,int l=1,int r=n) {
    if(l==r) return tr[p].val;
    int mid=(l+r)>>1;
    if(pos<=mid) return query(ls(p),pos,l,mid);
    else return query(rs(p),pos,mid+1,r);
}
int main() {
    red(n);red(m);
    for(re int i=1;i<=n;++i) red(a[i]);
    root[0]=newnode();build(root[0]);
    for(re int i=1;i<=m;++i) {
        re int v,op,loc,vl;
        red(v);red(op);red(loc);
        if(op==1) {
            red(vl);
            modify(root[v],root[i]=newnode(),loc,vl);
        } else {
            prt(query(root[v],loc));puc('\n');
            root[i]=root[v];
        }
    }
    fast_io::close();
}