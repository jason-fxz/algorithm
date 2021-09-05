
# DLX.cpp | DS | OI Algorithm

[**Go Back**](./)

---

```cpp
/*
	Dancing Links X : 舞蹈链优化 X 算法
	干啥的 --> 求解精准覆盖问题
	Oi-wiki(Dancing Links) --> https://oi-wiki.org/search/dlx/
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 505;
int n, m, a[N][N];
namespace DLX { // 舞蹈链，这实际上是个双十字循环链表
    const int N = 10010;
    int tot, fir[N], siz[N];
    int L[N], R[N], U[N], D[N];
    int col[N], row[N], st[N], ans;
    void Remove(int c) {
        L[R[c]] = L[c], R[L[c]] = R[c];
        for (int i = D[c]; i != c; i = D[i]) for (int j = R[i]; j != i;
                    j = R[j]) U[D[j]] = U[j], D[U[j]] = D[j], --siz[col[j]];
    }
    void Recover(int c) {
        for (int i = U[c]; i != c; i = U[i]) for (int j = L[i]; j != i;
                    j = L[j]) U[D[j]] = D[U[j]] = j, ++siz[col[j]];
        L[R[c]] = R[L[c]] = c;
    }
    void Insert(int r, int c) {
        ++tot; row[tot] = r; col[tot] = c; ++siz[c];
        U[tot] = c; D[tot] = D[c]; U[D[c]] = tot; D[c] = tot;
        if (!fir[r])
            fir[r] = L[tot] = R[tot] = tot;

        else {
            L[tot] = fir[r]; R[tot] = R[fir[r]];
            L[R[fir[r]]] = tot; R[fir[r]] = tot;
        }
    }
    void Build(int r, int c) {
        for (int i = 0; i <= c; ++i) L[i] = i - 1, R[i] = i + 1, U[i] = D[i] = i;
        L[0] = c, R[c] = 0; tot = c;
        memset(fir, 0, sizeof(fir));
        memset(siz, 0, sizeof(siz));
    }
    bool Dance(int dep) {
        int c = R[0];
        if (!R[0]) { ans = dep; return 1;}
        for (int i = R[0]; i != 0; i = R[i]) if (siz[i] < siz[c]) c = i;
        Remove(c);
        for (int i = D[c]; i != c; i = D[i]) {
            st[dep] = row[i];
            for (int j = R[i]; j != i; j = R[j]) Remove(col[j]);
            if (Dance(dep + 1)) return 1;
            for (int j = L[i]; j != i; j = L[j]) Recover(col[j]);
        }
        Recover(c);
        return 0;
    }
}
void solve() {
    using namespace DLX;
    Build(n, m);
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) if (a[i][j] == 1) Insert(i, j);
    bool fg = Dance(1);
    if (!fg) puts("No Solution!");
    else {
        for (int i = 1; i < ans; ++i) printf("%d ", st[i]);
        printf("\n");
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) scanf("%d", &a[i][j]);
    solve();
}
```

---

[**Go Back**](./)
