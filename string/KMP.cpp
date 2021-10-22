// KMP
#include <bits/stdc++.h>
using namespace std;
const int N = 1000010;
char P[N], T[N];
int nxt[N], f[N], n, m;
void getnxt() {
    nxt[1] = 0;
    for (int i = 2, j = 0; i <= m; ++i) {
        while (j > 0 && P[i] != P[j + 1]) j = nxt[j];
        if (P[i] == P[j + 1]) ++j;
        nxt[i] = j;
    }
}
void KMP() {
    for (int i = 1, j = 0; i <= n; ++i) {
        while (j > 0 && (j == m || T[i] != P[j + 1])) j = nxt[j];
        if (T[i] == P[j + 1]) ++j;
        f[i] = j;
    }
}
int main() {
    scanf("%s%s", T + 1, P + 1);
    n = strlen(T + 1), m = strlen(P + 1);
    getnxt();
    KMP();
    for (int i = 1; i <= n; ++i) if (f[i] == m) printf("%d\n", i - m + 1);
    for (int i = 1; i <= m; ++i) printf("%d%c", nxt[i], " \n"[i == m]);
    return 0;
}