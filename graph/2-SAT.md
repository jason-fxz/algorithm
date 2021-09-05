
# 2-SAT.cpp | GRAPH | OI Algorithm

[**Go Back**](././)

---

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2000100;
int n, m;
struct twosat {
    int head[N], pnt[N], nxt[N], E;
    int dfn[N], low[N], tis, st[N], top, col[N], co, ans[N];
    void add(int u, int v) {
        E++; pnt[E] = v; nxt[E] = head[u]; head[u] = E;
    }
    void tarjan(int u) {
        st[++top] = u; dfn[u] = low[u] = ++tis;
        for (int i = head[u]; i; i = nxt[i]) {
            int v = pnt[i];
            if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
            else if (!col[v]) low[u] = min(low[u], dfn[v]);
        }
        if (low[u] == dfn[u]) {
            col[u] = ++co;
            while (st[top] != u) {col[st[top]] = co; top--;}
            top--;
        }
    }
    bool slove() {
        for (int i = 1; i <= 2 * n; i++) if (!dfn[i]) tarjan(i);
        for (int i = 1; i <= n; i++) {
            if (col[i] == col[i + n]) return 0;
            ans[i] = (col[i] > col[i + n]);
        }
        return 1;
    }
    void insert(int i, bool a, int j, bool b) {
        // here  xi=a or xj=b
        add(i + n * (a ^ 1), j + b * n);
        add(j + n * (b ^ 1), i + a * n);
        // other forms
        // if xi=a then xj=b
        // add(i+a*n,j+b*n);
        // add(j+(b^1)*n,i+(a^1)*n);
    }
} S;
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, a, v, b;
        scanf("%d%d%d%d", &u, &a, &v, &b);
        S.insert(u, a, v, b);
    }
    bool fg = S.slove();
    if (!fg) printf("IMPOSSIBLE\n");
    else {
        printf("POSSIBLE\n");
        for (int i = 1; i <= n; i++) printf("%d ", S.ans[i]);
        printf("\n");
    }
}

```

---

[**Go Back**](././)
