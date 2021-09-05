
# guess.cpp | MATH | OI Algorithm

[**Go Back**](././)

---

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
double a[N][N];
int n;
void init() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++)
            scanf("%lf", &a[i][j]);
}
void solve() {
    for (int j = 1; j <= n; j++) {
        int mxp = j;
        for (int i = j + 1; i <= n; i++)
            if (fabs(a[i][j]) > fabs(a[mxp][j])) mxp = i;
        for (int i = 1; i <= n + 1; i++)
            swap(a[j][i], a[mxp][i]);
        if (a[j][j] == 0) {
            printf("No Solution\n");
            return ;
        }
        for (int i = 1; i <= n; i++) {
            if (i == j) continue;
            double tmp = a[i][j] / a[j][j];
            for (int k = 1; k <= n + 1; k++)
                a[i][k] -= a[j][k] * tmp;
        }
    }
    for (int i = 1; i <= n; i++)
        printf("%.2lf\n", a[i][n + 1] / a[i][i]);
}
int main() {
    init();
    solve();
    return 0;
}

```

---

[**Go Back**](././)
