// 最小斯坦纳树
// https://www.luogu.com.cn/problem/P6192
#include <bits/stdc++.h>
template <typename Tp>
inline void read(Tp &x) {
    x = 0; bool fg = 0; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') fg ^= 1; ch = getchar();}
    while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (Tp)(ch ^ 48), ch = getchar();
    if (fg) x = -x;
}
template <typename Tp, typename... Args>
void read(Tp &t, Args &...args) { read(t); read(args...); }
using namespace std;
typedef long long ll;
const int N = 105;
const int M = 1010;
const int inf = 0x3f3f3f3f;
int head[N], pnt[M], nxt[M], wth[M], E;
int n, m, k, id[N], _id, ful;
int dp[1 << 10][N];
void adde(int u, int v, int w) {
    E++; pnt[E] = v; wth[E] = w; nxt[E] = head[u]; head[u] = E;
}
struct dat {
    int u, d;
    bool operator<(const dat a) const {
        return d > a.d;
    }
};
bool vis[N];
priority_queue<dat> Q;
void dijk(int S) {
    memset(vis, 0, sizeof(vis));
    while (!Q.empty()) {
        int u = Q.top().u; Q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; i; i = nxt[i]) {
            int v = pnt[i];
            if (!vis[v] && dp[S][v] > dp[S][u] + wth[i]) {
                dp[S][v] = dp[S][u] + wth[i];
                Q.push(dat{v, dp[S][v]});
            }
        }
    }
}

int main() {
    read(n, m, k);
    for (int i = 1; i <= m; ++i) {
        int u, v, w; read(u, v, w);
        adde(u, v, w); adde(v, u, w);
    }
    memset(id, -1, sizeof(id));
    for (int i = 1; i <= k; ++i) {
        int x; read(x); id[x] = _id++;
    }
    ful = (1 << k) - 1;
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; ++i) if (id[i] != -1)
            dp[1 << id[i]][i] = 0;
    for (int S = 1; S <= ful; ++S) {
        for (int i = 1; i <= n; ++i) {
            for (int sub = (S - 1) & S; sub; sub = (sub - 1) & S)
                dp[S][i] = min(dp[S][i], dp[sub][i] + dp[S ^ sub][i]);
            if (dp[S][i] < inf) {
                Q.push(dat{i, dp[S][i]});
            }
        }
        dijk(S);
    }
    int ans = inf;
    for (int i = 1; i <= n; ++i)
        ans = min(ans, dp[ful][i]);
    printf("%d\n", ans);
    return 0;
}
