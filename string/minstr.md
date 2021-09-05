
# minstr.cpp | STRING | OI Algorithm

[**Go Back**](./../)

---

```cpp
// 最小表示法
#include <bits/stdc++.h>
template<typename _Tp>
inline void read(_Tp &x) {
    x = 0; bool fg = 0; char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-') fg ^= 1; ch = getchar();}
    while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (_Tp)(ch ^ 48), ch = getchar();
    if (fg) x = -x;
}
template<typename _Tp, typename... Args>void read(_Tp &t, Args &... args) {read(t); read(args...);}
using namespace std;
typedef long long ll;
const int N = 300010;
int a[N], n;
int minstr(int s[], int n) {
    int i = 0, j = 1, k = 0; // i,j 比较的两个循环串开头，k为当前相等长度
    while (i < n && j < n && k < n) {
        if (s[(i + k) % n] == s[(j + k) % n]) ++k;
        else {
            if (s[(i + k) % n] < s[(j + k) % n]) j += k + 1;
            else i += k + 1;
            // 若 s[i..k-1] == s[j..k-1] ,s[i+k]<s[j+k] 说明 j~j+k 都不可能成为最小循环串，
            // 因为都有对应的 i~i+k 比其更小
            if (i == j) ++j;
            k = 0;
        }
    }
    return min(i, j);
}
int main() {
    read(n);
    for (int i = 0; i < n; ++i) read(a[i]);
    int ps = minstr(a, n);
    printf("%d", a[ps]);
    for (int i = (ps + 1) % n; i != ps; i = (i + 1) % n) printf(" %d", a[i]);
    puts("");
    return 0;
}

```

---

[**Go Back**](./../)
