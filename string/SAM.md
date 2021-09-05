
# SAM.cpp | STRING | OI Algorithm

[**Go Back**](./../)

---

```cpp
// SAM 后缀自动机
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
const int N = 2000010;
char s[N]; int n;
namespace SAM {
    struct sta {
        int len, link;
        int nxt[26];
    };
    const int MAX = 2000010;
    sta st[MAX];
    int ct[MAX], deg[MAX];
    int sz, lst;
    void init() {
        sz = 1; st[0].len = 0; st[0].link = -1; lst = 0;
    }
    void extend(char c) {
        int cur = sz++, p = lst; st[cur].len = st[lst].len + 1;
        ct[cur]++;
        while (p != -1 && !st[p].nxt[c - 'a']) {
            st[p].nxt[c - 'a'] = cur;
            p = st[p].link;
        }
        if (p == -1) st[cur].link = 0;
        else {
            int q = st[p].nxt[c - 'a'];
            if (st[q].len == st[p].len + 1)
                st[cur].link = q;

            else {
                int cp = sz++;
                st[cp] = st[q];
                st[cp].len = st[p].len + 1;
                while (p != -1 && st[p].nxt[c - 'a'] == q) {
                    st[p].nxt[c - 'a'] = cp;
                    p = st[p].link;
                }
                st[cur].link = st[q].link = cp;
            }
        }
        lst = cur;
    }
    void solve() {
        for (int i = 1; i < sz; ++i)
            deg[st[i].link]++;
        queue<int> q;
        for (int i = 1; i < sz; ++i) {
            if (deg[i] == 0) q.push(i);
        }
        while (!q.empty()) {
            int u = q.front(), f = st[u].link; q.pop();
            if (f != -1) {
                deg[f]--; ct[f] += ct[u];
                if (deg[f] == 0) q.push(f);
            }
        }
        ll ans = 0;
        for (int i = 1; i < sz; ++i) {
            if (ct[i] > 1)
                ans = max(ans, (ll)ct[i] * st[i].len);
        }
        printf("%lld\n", ans);
    }
}

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    SAM::init();
    for (int i = 1; i <= n; ++i) SAM::extend(s[i]);
    SAM::solve();
    return 0;
}

```

---

[**Go Back**](./../)
