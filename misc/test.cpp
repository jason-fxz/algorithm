#include <bits/stdc++.h>
template<typename _Tp>
inline void red(_Tp &x) {
    x=0;bool fg=0;char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') fg^=1;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(_Tp)(ch^48),ch=getchar();
    if(fg) x=-x;
}
template <typename _Tp,typename... Args>void red(_Tp &t,Args &... args){red(t);red(args...);}
using namespace std;
typedef long long ll;

int main() {
    return 0;
}