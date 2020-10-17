#include <cstdio>

namespace fast_io {
    #define MAX_INPUT (1<<23)   // 一次读入量
    #define MAX_OUTPUT (1<<23)  // 一次输出量
    char buf[MAX_INPUT],*p1=buf,*p2=buf,obuf[MAX_OUTPUT],*O=obuf,*end=obuf+MAX_OUTPUT;
    inline char gc() {
        #ifdef DEBUG
            return getchar();
        #endif
        if(p1!=p2) return *p1++;
        p1=buf;
        p2=p1+fread(buf,1,MAX_INPUT,stdin);
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
const int N = 10000000;
long long a[N];
int main() {
    for(int i=0;i<N;i++) red(a[i]);
    for(int i=0;i<N;i++) prt(a[i]),puc('\n');
    fast_io::close();
    return 0;
}