
# Z-func.cpp | STRING | OI Algorithm

[**Go Back**](./)

---

```cpp
// Z 函数 (EXKMP)
#include <bits/stdc++.h>
using namespace std;
const int N = 40000010;
char s[N], t[N]; int z[N], n, m;
void Z_algo(char *s, int n) {
    for (int i = 1; i <= n; ++i) z[i] = 0;
    for (int i = 2, l = 0, r = 0; i <= n; ++i) {
        if (i <= r) z[i] = min(z[i - l + 1], r - i + 1);
        while (i + z[i] <= n && s[z[i] + 1] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
}
int main() {
    scanf("%s%s", s + 1, t + 1);
    n = strlen(s + 1), m = strlen(t + 1);
    t[m + 1] = '@';
    strcat(t + 1, s + 1);
    Z_algo(t, n + m + 1);
    return 0;
}

```

---

[**Go Back**](./)
