
# e-cut.cpp | GRAPH | OI Algorithm

[**Go Back**](./)

---

```cpp
// 割边（桥）
#include <bits/stdc++.h>
using namespace std;
const int N = 20010;
const int M = 200010;
int head[N], pnt[M], nxt[M], E, n, m;
int dfn[N], low[N], tim;
bool ecut[M];
void adde(int u, int v) {
    E++; pnt[E] = v; nxt[E] = head[u]; head[u] = E;
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
int main() {
    scanf("%d%d", &n, &m);
    E = 1;
    for (int i = 1; i <= m; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        adde(u, v); adde(v, u);
    }
    for (int i = 1; i <= n; ++i) if (!dfn[i]) tarjan(i, 0);
    return 0;
}
```

---

[**Go Back**](./)
