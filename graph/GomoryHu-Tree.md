
# GomoryHu-Tree.cpp | GRAPH | OI Algorithm

[**Go Back**](./)

---

```cpp
// 最小割树
#include <bits/stdc++.h>
template<typename _Tp>
inline void red(_Tp &x) {
    x = 0; bool fg = 0; char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-') fg ^= 1; ch = getchar();}
    while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (_Tp)(ch ^ 48), ch = getchar();
    if (fg) x = -x;
}
using namespace std;
const int N = 505;
const int M = 3005;
const int inf = 0x3f3f3f3f;
int n, m, q;
struct networkflow {
    int head[N], pnt[M << 1], nxt[M << 1], fl[M << 1], E;
    int dep[N], cur[N], maxf;
    void adde(int u, int v, int f) {
        E++; pnt[E] = v; fl[E] = f; nxt[E] = head[u]; head[u] = E;
        E++; pnt[E] = u; fl[E] = 0; nxt[E] = head[v]; head[v] = E;
    }
    void init() {
        memset(head, -1, sizeof(head));
        E = -1;
    }
    void reset() { for (int i = 0; i < E; i += 2) fl[i] += fl[i + 1], fl[i + 1] = 0;}
    bool BFS(int S, int T) {
        memset(dep, 0x3f, sizeof(dep));
        dep[S] = 0; queue<int> q; q.push(S);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = head[u]; i != -1; i = nxt[i]) {
                int v = pnt[i];
                if (fl[i] > 0 && dep[v] == inf) {dep[v] = dep[u] + 1; q.push(v);}
            }
        }
        return dep[T] < inf;
    }
    int DFS(int u, int T, int nf) {
        if (u == T || nf == 0) return nf;
        int flow = 0, tf;
        for (int &i = cur[u]; i != -1; i = nxt[i]) {
            int v = pnt[i];
            if (dep[v] == dep[u] + 1) {
                tf = DFS(v, T, min(nf, fl[i]));
                flow += tf; nf -= tf;
                fl[i] -= tf; fl[i ^ 1] += tf;
                if (nf == 0) break;
            }
        }
        return flow;
    }
    void Dinic(int S, int T) {
        maxf = 0;
        while (BFS(S, T)) {
            memcpy(cur, head, sizeof(head));
            maxf += DFS(S, T, inf);
        }
    }
} G;
int t[N], head[N], pnt[N << 1], nxt[N << 1], wth[N << 1], E;
int tl[N], tr[N];

void adde(int u, int v, int w) {
    // fprintf(stderr,"e : %d %d %d\n",u,v,w);
    E++; pnt[E] = v; wth[E] = w; nxt[E] = head[u]; head[u] = E;
}
void Build(int l, int r) {
    if (l == r) return ;
    G.reset(); G.Dinic(t[l], t[r]);
    adde(t[l], t[r], G.maxf); adde(t[r], t[l], G.maxf);
    int cl = 0, cr = 0;
    for (int i = l; i <= r; ++i) {
        if (G.dep[t[i]] == inf) tr[cr++] = t[i];
        else tl[cl++] = t[i];
    }
    for (int i = 0; i < cl; ++i) t[l + i] = tl[i];
    for (int i = 0; i < cr; ++i) t[l + cl + i] = tr[i];
    Build(l, l + cl - 1); Build(l + cl, l + cl + cr - 1);
}

int fa[10][N], mn[10][N], dep[N];
bool vis[N];
void Prework(int u) {
    vis[u] = 1;
    for (int i = 1; i < 10; ++i) {
        fa[i][u] = fa[i - 1][fa[i - 1][u]];
        if (fa[i][u] == 0) break;
        mn[i][u] = min(mn[i - 1][u], mn[i - 1][fa[i - 1][u]]);
    }
    for (int i = head[u]; i; i = nxt[i]) {
        int v = pnt[i];
        if (v == fa[0][u]) continue;
        fa[0][v] = u; mn[0][v] = wth[i]; dep[v] = dep[u] + 1;
        Prework(v);
    }
}
int Query(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int d = dep[u] - dep[v], ret = inf;
    for (int i = 0; i < 10; ++i) if ((d >> i) & 1)
            ret = min(ret, mn[i][u]), u = fa[i][u];
    if (u == v) return ret;
    for (int i = 9; i >= 0; --i) if (fa[i][u] != fa[i][v])
            ret = min(ret, min(mn[i][u], mn[i][v])),
            u = fa[i][u], v = fa[i][v];
    return min(ret, min(mn[0][u], mn[0][v]));
}

int main() {
    red(n); red(m);
    G.init();
    for (int i = 1; i <= m; ++i) {
        int u, v, w; red(u); red(v); red(w);
        G.adde(u, v, w); G.adde(v, u, w);
    }
    for (int i = 1; i <= n; ++i) t[i] = i;
    Build(1, n);
    Prework(1);
    red(q);
    while (q--) {
        int u, v; red(u); red(v);
        printf("%d\n", Query(u, v));
    }
}
```

---

[**Go Back**](./)
