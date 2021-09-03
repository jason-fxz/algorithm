#include <bits/stdc++.h>
using namespace std;
template<typename T>
inline void red(T &x) {
    x = 0; bool fg = 0; char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-') fg ^= 1; ch = getchar();}
    while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (T)(ch ^ 48), ch = getchar();
    if (fg) x = -x;
}
template<size_t N, size_t M>
struct Dinic {
    const int inf = 0x3f3f3f3f;
    int fl[M << 1], pnt[M << 1], nxt[M << 1], cur[N], head[N], dep[N], E, S, T;
    long long maxf;
    Dinic() {memset(head, -1, sizeof(head)); E = -1;}
    void adde(int u, int v, int c) {
        E++; pnt[E] = v; fl[E] = c; nxt[E] = head[u]; head[u] = E;
        E++; pnt[E] = u; fl[E] = 0; nxt[E] = head[v]; head[v] = E;
    }
    bool BFS(int u) {
        memset(dep, 0x3f, sizeof(dep)); dep[S] = 0;
        queue<int> q; q.push(S);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == T) break;
            for (int i = head[u]; i != -1; i = nxt[i]) {
                if (fl[i] > 0 && dep[pnt[i]] == inf)
                    dep[pnt[i]] = dep[u] + 1, q.push(pnt[i]);
            }
        }
        return dep[T] != inf;
    }
    int DFS(int u, int nf) {
        if (u == T || nf == 0) return nf;
        int flow = 0, tf;
        for (int &i = cur[u]; i != -1; i = nxt[i]) {
            int v = pnt[i];
            if (dep[v] != dep[u] + 1) continue;
            tf = DFS(v, min(nf, fl[i]));
            if (tf == 0) continue;
            flow += tf; nf -= tf;
            fl[i] -= tf; fl[i ^ 1] += tf;
            if (nf == 0) break;
        }
        return flow;
    }
    long long maxflow() {
        maxf = 0;
        while (BFS(S)) {
            memcpy(cur, head, sizeof(cur));
            maxf += DFS(S, inf);
        }
        return maxf;
    }
};
Dinic<205, 5005> G;
int n, m, s, t;
int main() {
    // scanf("%d%d%d%d",&n,&m,&s,&t);
    red(n); red(m); red(s); red(t);
    G.S = s, G.T = t;
    for (int i = 1; i <= m; ++i) {
        int u, v, c; red(u); red(v); red(c);
        // scanf("%d%d%d",&u,&v,&c);
        G.adde(u, v, c);
    }
    printf("%lld\n", G.maxflow());
}
