
# MFMC(EK).cpp | GRAPH | OI Algorithm

[**Go Back**](./)

---

```cpp
#include <bits/stdc++.h>
template<typename _Tp>
inline void red(_Tp &x) {
    x = 0; bool fg = 0; char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-') fg ^= 1; ch = getchar();}
    while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (_Tp)(ch ^ 48), ch = getchar();
    if (fg) x = -x;
}
using namespace std;
const int inf = 0x3f3f3f3f;
int n, m, s, t;
struct networkflow {
    static const int N = 5010, M = 100010;
    int head[N], pnt[M], fl[M], nxt[M], cst[M], pre[N], lst[N], E = -1;
    int dis[N]; bool vis[N];
    int minc, maxf;
    void init() {
        memset(head, -1, sizeof(head)); E = -1;
    }
    void adde(int u, int v, int f, int c) {
        ++E; pnt[E] = v; nxt[E] = head[u]; head[u] = E; fl[E] = f; cst[E] = c;
        ++E; pnt[E] = u; nxt[E] = head[v]; head[v] = E; fl[E] = 0; cst[E] = -c;
    }
    bool SPFA(int S, int T) {
        memset(dis, 0x3f, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        dis[S] = 0; vis[S] = 1; queue<int> q; q.push(S);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            vis[u] = 0;
            for (int i = head[u]; i != -1; i = nxt[i]) {
                int v = pnt[i];
                if (fl[i] > 0 && dis[u] + cst[i] < dis[v]) {
                    dis[v] = dis[u] + cst[i]; pre[v] = u; lst[v] = i;
                    if (!vis[v]) q.push(v), vis[v] = 1;
                }
            }
        }
        return dis[T] < inf;
    }
    void work(int S, int T) {
        int flow = inf;
        for (int u = T; u != S; u = pre[u]) flow = min(flow, fl[lst[u]]);
        maxf += flow; minc += flow * dis[T];
        for (int u = T; u != S; u = pre[u]) {
            fl[lst[u]] -= flow;
            fl[lst[u] ^ 1] += flow;
        }
    }
    void MFMC(int S, int T) {
        minc = maxf = 0;
        while (SPFA(S, T)) work(S, T);
    }
} G;
int main() {
    red(n); red(m); red(s); red(t);
    G.init();
    for (int i = 1; i <= m; ++i) {
        int a, b, c, d; red(a); red(b); red(c); red(d);
        G.adde(a, b, c, d);
    }
    G.MFMC(s, t);
    printf("%d %d\n", G.maxf, G.minc);
}
```

---

[**Go Back**](./)
