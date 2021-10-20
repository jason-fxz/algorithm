// 点双连通分量 & 缩点
#include <bits/stdc++.h>
using namespace std;
const int N = 20010;
const int M = 200010;
int head[N], pnt[M], nxt[M], E, n, m;
int headc[N], pntc[M], nxtc[M], Ec;
int dfn[N], low[N], tim, root, sta[N], top;
bool vcut[N];
vector<int> dcc[N]; int col[N], cnt;
int tot, new_id[N];
void adde(int u, int v) {
    E++; pnt[E] = v; nxt[E] = head[u]; head[u] = E;
}
void addec(int u, int v) {
    Ec++; pntc[Ec] = v; nxtc[Ec] = headc[u]; headc[u] = Ec;
}
void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    sta[++top] = u;
    if (u == root && head[u] == 0) { // 孤立点
        dcc[++cnt].push_back(u); return;
    }
    int child = 0;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = pnt[i];
        if (!dfn[v]) {
            tarjan(v); low[u] = min(low[u], low[v]);
            if (dfn[u] <= low[v]) {
                ++child;
                if (u != root || child >= 2) vcut[u] = true;
                ++cnt;
                while (1) {
                    dcc[cnt].push_back(sta[top]);
                    if (sta[top--] == v) break;
                }
                dcc[cnt].push_back(u);
            }
        } else low[u] = min(low[u], dfn[v]);
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        adde(u, v); adde(v, u);
    }
    for (int i = 1; i <= n; ++i) if (!dfn[i]) root = i, top = 0, tarjan(i);
    // 割点可以属于多个 v-DCC，其它点只属于一个 v-DCC
    // 缩点: 割点重新编号，每个 v-DCC 向它包含的割点连边
    tot = cnt;
    for (int i = 1; i <= n; ++i) if (vcut[i]) new_id[i] = ++tot;
    for (int i = 1; i <= cnt; ++i) {
        for (auto &u : dcc[i]) {
            if (vcut[u]) {
                addec(i, new_id[u]);
                addec(new_id[u], i);
            } else col[u] = i;
        }
    }
    return 0;
}
