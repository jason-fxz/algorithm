// 莫队二次离线
#include <bits/stdc++.h>
template <typename Tp>
inline void read(Tp &x) {
    x = 0; bool fg = 0; char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-') fg ^= 1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (Tp)(ch ^ 48), ch = getchar();
    if(fg) x = -x;
}
using namespace std;
typedef long long ll;
const int N = 100010;
struct mds {
    int l, r, id, fg;
};
vector<mds> mdl[N], mdr[N];
vector<mds>::iterator mt;
vector<int>::iterator it;
int a[N], n, m, K;
int L[N], R[N], t[N], bl[N], B;
ll Fl[N], Fr[N], ans[N];
bool cmp(int x, int y) {
    if (bl[L[x]] == bl[L[y]]) return R[x] < R[y];
    return L[x] < L[y];
}
void init() {
    // init Fr,Fl
    for (int i = 1; i < n; ++i) {
        // Fr(i) = f([1,i],i+1)
    }
    for (int i = n - 1; i >= 1; --i) {
        // Fl(i) = f([i+1,n],i)
    }
    for (int i = 2; i <= n; ++i) Fl[i] += Fl[i - 1], Fr[i] += Fr[i - 1];
}
void solve() {
    for (int x = 1; x <= n; ++x) {
        // updata(a[x])
        for (mt = mdr[x].begin(); mt != mdr[x].end(); ++mt)
            for (int i = mt->l; i <= mt->r; ++i) ans[mt->id] += mt->fg * (1/*query(a[i])*/);
    }
    for (int x = n; x >= 1; --x) {
        // updata(a[x])
        for (mt = mdl[x].begin(); mt != mdl[x].end(); ++mt)
            for (int i = mt->l; i <= mt->r; ++i) ans[mt->id] += mt->fg * (1/*query(a[i])*/);
    }

}
int main() {
    read(n); read(m); read(K);
    for (int i = 1; i <= n; ++i) read(a[i]);
    B = sqrt(n); for (int i = 1; i <= n; ++i) bl[i] = (i - 1) / B + 1;
    for (int i = 1; i <= m; ++i) read(L[i]), read(R[i]), t[i] = i;
    sort(t + 1, t + m + 1, cmp);
    init();
    int l = 1, r = 1;
    for (int i = 1; i <= m; ++i) {
        int id = t[i];
        if (r < R[id]) {
            ans[id] += Fr[R[id] - 1] - Fr[r - 1];
            mdr[l - 1].push_back(mds{ r + 1, R[id], id, -1 }); r = R[id];
        }
        if (l > L[id]) {
            ans[id] += Fl[l - 1] - Fl[L[id] - 1];
            mdl[r + 1].push_back(mds{ L[id], l - 1, id, -1 }); l = L[id];
        }
        if (r > R[id]) {
            ans[id] -= Fr[r - 1] - Fr[R[id] - 1];
            mdr[l - 1].push_back(mds{ R[id] + 1, r, id, 1 }); r = R[id];
        }
        if (l < L[id]) {
            ans[id] -= Fl[L[id] - 1] - Fl[l - 1];
            mdl[r + 1].push_back(mds{ l, L[id] - 1, id, 1 }); l = L[id];
        }
    }
    solve();
    for (int i = 1; i <= m; ++i) ans[t[i]] += ans[t[i - 1]];
    for (int i = 1; i <= m; ++i) {
        printf("%lld\n", ans[i]);
    }
    return 0;
}
