
# v-cut.cpp | GRAPH | OI Algorithm

[**Go Back**](./)

---

```cpp
// 割点（割顶）
#include <bits/stdc++.h>
using namespace std;
const int N = 20010;
const int M = 200010;
int head[N], pnt[M], nxt[M], E, n, m;
int dfn[N], low[N], tim, root;
bool vcut[N];
void adde(int u, int v) {
    E++; pnt[E] = v; nxt[E] = head[u]; head[u] = E;
}
void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    int child = 0;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = pnt[i];
        if (!dfn[v]) {
            tarjan(v); low[u] = min(low[u], low[v]);
            if (dfn[u] <= low[v]) {
                ++child;
                if (u != root || child >= 2) vcut[u] = true;
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
    for (int i = 1; i <= n; ++i) if (!dfn[i]) root = i, tarjan(i);
    return 0;
}
```

---

[**Go Back**](./)
