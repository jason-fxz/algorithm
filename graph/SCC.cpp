// 强连通分量
#include <bits/stdc++.h>
using namespace std;
const int N = 10010;
const int M = 200010;
int head[N], pnt[M], nxt[M], E, n, m;
int dfn[N], low[N], tim, sta[N], top, scc[N], cnt;
void adde(int u, int v) {
    E++; pnt[E] = v; nxt[E] = head[u]; head[u] = E;
}
void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    sta[++top] = u;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = pnt[i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (!scc[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        ++cnt;
        do {
            scc[sta[top]] = cnt;
        } while (sta[top--] != u);
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        adde(u, v); adde(v, u);
    }
    for (int i = 1; i <= n; ++i) if (!dfn[i]) top = 0, tarjan(i);
    return 0;
}
