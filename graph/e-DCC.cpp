// 边双连通分量 & 缩点
#include <bits/stdc++.h>
using namespace std;
const int N = 20010;
const int M = 200010;
int head[N], pnt[M], nxt[M], E, n, m;
int headc[N], pntc[M], nxtc[M], Ec;
int dfn[N], low[N], tim;
bool ecut[M];
void adde(int u, int v) {
    E++; pnt[E] = v; nxt[E] = head[u]; head[u] = E;
}
void addec(int u, int v) {
    Ec++; pntc[Ec] = v; nxtc[Ec] = headc[u]; headc[u] = Ec;
}
void tarjan(int u, int in_edge) { // 考虑重边
    dfn[u] = low[u] = ++tim;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = pnt[i];
        if (!dfn[v]) {
            tarjan(v, i); 
            low[u] = min(low[u], low[v]);
            if (dfn[u] < low[v]) ecut[i] = ecut[i ^ 1] = true;
        } else if (in_edge != (i ^ 1)) low[u] = min(low[u], dfn[v]);
    }
}
int col[N], dcc;
void dfs(int u) {
    col[u] = dcc;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = pnt[i];
        if (col[v] || ecut[i]) continue;
        dfs(v);        
    }
}
int main() {
    scanf("%d%d", &n, &m);
    E = 1; // !!
    for (int i = 1; i <= m; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        adde(u, v); adde(v, u);
    }
    // e-cut
    for (int i = 1; i <= n; ++i) if (!dfn[i]) tarjan(i, 0);
    // e-DCC 断开割边，每个联通块即 e-DCC
    for (int i = 1; i <= n; ++i) if (!col[i]) {
        ++dcc, dfs(i);
    }
    // e-DCC 缩点
    for (int i = 2; i <= E; ++i) {
        int u = pnt[i], v = pnt[i ^ 1];
        if (col[u] == col[v]) continue;
        addec(col[u], col[v]);
    }
    return 0;
}