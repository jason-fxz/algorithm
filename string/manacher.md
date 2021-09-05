
# manacher.cpp | STRING | OI Algorithm

[**Go Back**](./)

---

```cpp
/*
    manachar 马拉车算法
    --> 线性求最长回文串
    Oi-wiki(Manacher) --> https://oi-wiki.org/string/manacher/
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1.2e7;
char s[N], str[N << 1];
int p[N << 1];
int manacher() {
    int len = strlen(s), n = 0;
    str[n++] = '$'; str[n++] = '#';
    for (int i = 0; i < len; i++) str[n++] = s[i], str[n++] = '#'; str[n] = '\0';
    int mr = 0, ans = 0, id = 0;
    for (int i = 1; i < n; i++) {
        p[i] = i < mr ? min(p[2 * id - i], p[id] + id - i) : 1;
        while (str[i - p[i]] == str[i + p[i]]) p[i]++;
        if (p[i] + i > mr) mr = p[i] + i, id = i;
        ans = max(ans, p[i]);
    }
    return ans - 1;
}
int main() {
    scanf("%s", s);
    printf("%d\n", manacher());
}
```

---

[**Go Back**](./)
