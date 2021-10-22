// 二分图最大匹配 匈牙利算法
#include <bits/stdc++.h>
using namespace std;
const int N = 505;
vector<int> e[N];
int mx[N], my[N], n, m, E;
bool vis[N];
bool find(int x) {
    for (auto y : e[x]) if (!vis[y]) {
        vis[y] = 1;
        if (my[y] == 0 || find(my[y])) {
            my[y] = x, mx[x] = y;
            return true;
        }
    }
    return false;
}
int march(){
    int cnt = 0;
    memset(my, 0, sizeof(my));
    memset(mx, 0, sizeof(mx));
    for (int i = 1; i <= n; ++i) {
        memset(vis, 0, sizeof(vis));
        cnt += find(i);
    }
    return cnt;
}
int main() {
    scanf("%d%d%d", &n, &m, &E);
    for (int i = 1; i <= E; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        e[u].push_back(v);
    }
    printf("%d\n", march());
}