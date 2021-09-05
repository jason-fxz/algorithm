
# ACAM.cpp | STRING | OI Algorithm

[**Go Back**](././)

---

```cpp
// AC 自动机，字符串多模式串匹配
#include <bits/stdc++.h>
using namespace std;
namespace ACAM {
    const int MAX = 200010;
    int tr[MAX][26], fail[MAX], sz;
    int tag[MAX];
    void init() {
        memset(tr[0], 0, sizeof(tr[0]));
        fail[0] = 0; sz = 0;
    }
    int newnode() {
        ++sz; fail[sz] = 0; memset(tr[sz], 0, sizeof(tr[sz]));
        return sz;
    }
    int insert(string &s) {
        int p = 0, c;
        for (int i = 0; i < s.size(); ++i) {
            c = s[i] - 'a';
            if (tr[p][c] == 0) tr[p][c] = newnode();
            p = tr[p][c];
        }
        return p;
    }
    void build() {
        queue<int> q;
        for (int i = 0; i < 26; ++i) {
            if (tr[0][i]) q.push(tr[0][i]);
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = 0; i < 26; ++i) {
                if (tr[u][i]) fail[tr[u][i]] = tr[fail[u]][i], q.push(tr[u][i]);
                else tr[u][i] = tr[fail[u]][i];
            }
        }
    }
    void query(string &s) {
        int cur = 0, c;
        for (int i = 0; i <= sz; ++i) tag[i] = 0;
        for (int i = 0; i < s.size(); ++i) {
            c = s[i] - 'a';
            cur = tr[cur][c];
            tag[cur]++;
        }
    }
    void work() {
        static int idg[MAX];
        for (int i = 0; i <= sz; ++i) idg[i] = 0;
        for (int i = 1; i <= sz; ++i) ++idg[fail[i]];
        queue<int> q;
        for (int i = 1; i <= sz; ++i) if (idg[i] == 0) q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (!u) break;
            tag[fail[u]] += tag[u];
            if (--idg[fail[u]] == 0) q.push(fail[u]);
        }
    }
}
int n, ed[200005];
string P[200005], T;
int main() {
    cin >> n;
    ACAM::init();
    for (int i = 0; i < n; ++i)
        cin >> P[i], ed[i] = ACAM::insert(P[i]);
    ACAM::build();
    cin >> T;
    ACAM::query(T);
    ACAM::work();
    for (int i = 0; i < n; ++i)
        cout << ACAM::tag[ed[i]] << "\n";
    return 0;
}

```

---

[**Go Back**](././)
