// EXSAM 广义后缀自动机
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
typedef pair<int, int> P;
const int N = 1000010;
namespace EXSAM {
    const int MAX = 2000010;
    struct sta {
        int len, link;
        int nxt[26];
        int &operator[](const int k) {return nxt[k];}
    } st[MAX];
    int sz;
    void init() {
        sz = 1; st[0].link = -1;
    }
    void _extend(int last, int c) {
        int cur = st[last][c], p = st[last].link; st[cur].len = st[last].len + 1;
        while (p != -1 && st[p][c] == 0) {
            st[p][c] = cur; p = st[p].link;
        }
        if (p == -1) st[cur].link = 0;
        else {
            int q = st[p][c];
            if (st[q].len == st[p].len + 1) st[cur].link = q;
            else {
                int cp = sz++; st[cp].len = st[p].len + 1; st[cp].link = st[q].link;
                for (int i = 0; i < 26; ++i) st[cp][i] = (st[st[q][i]].len == 0) ? 0 : st[q][i];
                st[cur].link = st[q].link = cp;
                while (p != -1 && st[p][c] == q) {
                    st[p][c] = cp;
                    p = st[p].link;
                }
            }
        }
    }
    void build() {
        queue<P> q;
        for (int i = 0; i < 26; ++i) if (st[0][i] != 0) q.push(P(0, i));
        while (!q.empty()) {
            P u = q.front(); q.pop();
            _extend(u.first, u.second);
            int o = st[u.first][u.second];
            for (int i = 0; i < 26; ++i) if (st[o][i] != 0) q.push(P(o, i));
        }
    }
    void insert(char *s, int len) {
        int cur = 0;
        for (int i = 0; i < len; ++i) {
            if (st[cur][s[i] - 'a'] == 0) st[cur][s[i] - 'a'] = sz++;
            cur = st[cur][s[i] - 'a'];
        }
    }
    ll solve() {
        ll r = 0;
        for (int i = 1; i < sz; ++i) r += st[i].len - st[st[i].link].len;
        return r;
    }
}
int n; char s[N];

int main() {
    read(n);
    EXSAM::init();
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s);
        EXSAM::insert(s, strlen(s));
    }
    EXSAM::build();
    printf("%lld\n", EXSAM::solve());
    return 0;
}
