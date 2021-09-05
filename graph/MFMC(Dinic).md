
# MFMC(Dinic).cpp | GRAPH | OI Algorithm

[**Go Back**](./)

---

```cpp
#include <bits/stdc++.h>
using namespace std;
template<size_t N, size_t M>
struct SPFA_Dinic {
    const int inf = 0x3f3f3f3f;
    int fl[M << 1], cst[M << 1], pnt[M << 1], nxt[M << 1], cur[N], head[N], dis[N], E, S, T;
    bool vis[N];
    int maxf, minc;
    SPFA_Dinic() {memset(head, -1, sizeof(head)); E = -1;}
    void adde(int u, int v, int c, int w) { // (u,v) c容量限制，w单位费用
        E++; pnt[E] = v; fl[E] = c; cst[E] = w; nxt[E] = head[u]; head[u] = E;
        E++; pnt[E] = u; fl[E] = 0; cst[E] = -w; nxt[E] = head[v]; head[v] = E;
    }
    bool SPFA() {
        memset(dis, 0x3f, sizeof(dis));
        queue<int> q; q.push(S);
        dis[S] = 0; vis[S] = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop(); vis[u] = 0;
            for (int i = head[u]; i != -1; i = nxt[i]) {
                int v = pnt[i];
                if (fl[i] > 0 && dis[v] > dis[u] + cst[i]) {
                    dis[v] = dis[u] + cst[i];
                    if (!vis[v]) q.push(v), vis[v] = 1;
                }
            }
        }
        return dis[T] != inf;
    }
    int DFS(int u, int nf) {
        if (u == T || nf == 0) return nf;
        int flow = 0, tf; vis[u] = 1;
        for (int &i = cur[u]; i != -1; i = nxt[i]) {
            int v = pnt[i];
            if (!vis[v] && fl[i] && dis[v] == dis[u] + cst[i]) {
                tf = DFS(v, min(nf, fl[i]));
                if (tf) {flow += tf; nf -= tf; fl[i] -= tf; fl[i ^ 1] += tf; minc += tf * cst[i];}
            }
            if (nf == 0) break;
        }
        vis[u] = 0;
        return flow;
    }
    void MFMC() {
        maxf = minc = 0;
        int cnt = 0;
        while (SPFA()) {
            memcpy(cur, head, sizeof(cur));
            maxf += DFS(S, inf);
        }
    }
};
SPFA_Dinic<5005, 50005> G;
int n, m, s, t;
int main() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    G.S = s, G.T = t;
    for (int i = 1; i <= m; ++i) {
        int u, v, c, w;
        scanf("%d%d%d%d", &u, &v, &c, &w);
        G.adde(u, v, c, w);
    }
    G.MFMC();
    printf("%d %d\n", G.maxf, G.minc);
    return 0;
}

```

---

[**Go Back**](./)
