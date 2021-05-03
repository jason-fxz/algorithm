// Prufer 序列
#include <bits/stdc++.h>
template <typename Tp>
inline void read(Tp &x) {
    x = 0; bool fg = 0; char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-') fg ^= 1; ch = getchar();}
    while(ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (Tp)(ch ^ 48), ch = getchar();
    if(fg) x = -x;
}
using namespace std;
const int N = 5000010;
int n, type, a[N];
long long ans = 0;

namespace prufer {
int p[N], f[N], deg[N];
void encode(int *f, int n) { // father -> prufer
    for (int i = 1; i <= n; ++i) deg[i] = 0;
    for (int i = 1; i < n; ++i) ++deg[f[i]];
    for (int i = 1, j = 1; i <= n - 2; ++i, ++j) {
        while (deg[j]) ++j; p[i] = f[j];
        while (i <= n - 2 && --deg[p[i]] == 0 && p[i] < j) p[i + 1] = f[p[i]], ++i;
    }
    for (int i = 1; i <= n - 2; ++i) ans ^= 1ll * i * p[i];
}

void decode(int *p, int n) { // prufer -> father
    for (int i = 1; i <= n; ++i) deg[i] = 0;
    for (int i = 1; i <= n - 2; ++i) ++deg[p[i]]; p[n - 1] = n;
    for (int i = 1, j = 1; i < n; ++i, ++j) {
        while (deg[j]) ++j; f[j] = p[i];
        while (i < n && --deg[p[i]] == 0 && p[i] < j) f[p[i]] = p[i + 1], ++i;
    }
    for (int i = 1; i <= n - 1; ++i) ans ^= 1ll * i * f[i];
}
}

int main() {
    read(n); read(type);
    for (int i = 1; i <= n - type; ++i) read(a[i]);
    if (type == 1) prufer::encode(a, n);
    else prufer::decode(a, n);
    printf("%lld\n", ans);
    return 0;
}
