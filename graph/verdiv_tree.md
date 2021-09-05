
# verdiv_tree.cpp | GRAPH | OI Algorithm

[**Go Back**](./../)

---

```cpp
// 点分树 luogu-P6329
#include <bits/stdc++.h>
#define see(x) cerr<<#x<<"="<<x<<endl;
#define _max(x,y) ((x>y)?x:y)
#define _min(x,y) ((x<y)?x:y)
using namespace std;
typedef long long ll;
template<typename _Tp>
inline void red(_Tp &x) {
    x = 0; bool fg = 0; char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-') fg ^= 1; ch = getchar();}
    while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (_Tp)(ch ^ 48), ch = getchar();
    if (fg) x = -x;
}
const int N = 100010;
const int M = 20;
int head[N], pnt[N << 1], nxt[N << 1], E;
int val[N], son[N], siz[N], dep[N], mxdep, size, root, n, m;
int far[N], Dep[N], dist[M][N];
struct trearr {
    vector<int> t; int n;
    void init(int sz) {t.resize(sz + 1, 0); n = sz;}
    void add(int x, int v) {for (; x <= n; x += x & -x) t[x] += v;}
    int sum(int x) {int r = 0; for (x = _min(x, n); x > 0; x -= x & -x) r += t[x]; return r;}
} Dt[N], dt[N];
trearr *ps[N];
bool vis[N];
void adde(int u, int v) { E++; pnt[E] = v; nxt[E] = head[u]; head[u] = E; }
void getroot(int u, int f) {
    siz[u] = 1; son[u] = 0;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = pnt[i];
        if (v == f || vis[v]) continue;
        getroot(v, u);
        siz[u] += siz[v];
        son[u] = _max(son[u], siz[v]);
    }
    son[u] = _max(son[u], size - siz[u]);
    if (son[u] < son[root]) root = u;
}
void dfs(int u, int f, int S, int fr) {
    Dt[S].add(dep[u], val[u]); dt[fr].add(dep[u], val[u]);
    dist[Dep[S]][u] = dep[u];
    for (int i = head[u]; i; i = nxt[i]) {
        int v = pnt[i];
        if (v == f || vis[v]) continue;
        dfs(v, u, S, fr);
    }
}
void DFS(int u, int f, int d) {
    dep[u] = d; siz[u] = 1; mxdep = _max(mxdep, d);
    for (int i = head[u]; i; i = nxt[i]) {
        int v = pnt[i];
        if (v == f || vis[v]) continue;
        DFS(v, u, d + 1); siz[u] += siz[v];
    }
}
void vdiv(int u) {
    int mx = 0;
    vector<pair<int, int> > sons;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = pnt[i];
        if (vis[v]) continue;
        mxdep = 0; DFS(v, u, 1); mx = _max(mx, mxdep);
        size = siz[v]; root = 0; getroot(v, u);
        sons.push_back(make_pair(v, root)); far[root] = u;
        dt[root].init(mxdep);
    }
    Dt[u].init(mx);
    for (int i = 0; i < sons.size(); ++i)
        dfs(sons[i].first, u, u, sons[i].second);
    vis[u] = 1;
    for (int i = 0; i < sons.size(); ++i) {
        Dep[sons[i].second] = Dep[u] + 1;
        vdiv(sons[i].second);
    }
}
int ask(int x, int K) {
    int ret = 0, fr = -1;
    for (int u = x; u; u = far[u]) {
        int d = K - dist[Dep[u]][x];
        if (d > 0) {
            ret += Dt[u].sum(d);
            if (fr != -1)
                ret -= dt[fr].sum(d);
        }
        if (d >= 0) ret += val[u];
        fr = u;
    }
    return ret;
}
void modify(int x, int vl) {
    int fr = x;
    for (int u = far[x]; u; u = far[u]) {
        int d = dist[Dep[u]][x];
        Dt[u].add(d, -val[x]); dt[fr].add(d, -val[x]);
        Dt[u].add(d, vl); dt[fr].add(d, vl);
        fr = u;
    }
    val[x] = vl;
}
int main() {
    red(n); red(m);
    for (int i = 1; i <= n; ++i) red(val[i]);
    for (int i = 1; i < n; ++i) {
        int u, v; red(u); red(v);
        adde(u, v); adde(v, u);
    }
    size = n; son[root = 0] = n;
    getroot(1, 0);
    vdiv(root);
    int lst = 0;
    while (m--) {
        int op, x, y; red(op); red(x); red(y);
        x ^= lst; y ^= lst;
        if (op == 0) {
            lst = ask(x, y);
            printf("%d\n", lst);
        } else
            modify(x, y);
    }
    return 0;
}
```

---

[**Go Back**](./../)
