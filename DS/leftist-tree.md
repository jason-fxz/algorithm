
# leftist-tree.cpp | DS | OI Algorithm

[**Go Back**](./)

---

```cpp
/* 左偏树 (可并堆)
+ 左偏树是一棵二叉树，有堆的性质
+ 每个节点左儿子dist >= 右儿子dist
+ 每个节点的 dist 都等于其右儿子的 dist 加一
*/
#include <bits/stdc++.h>
#define ls(x) t[x].ch[0]
#define rs(x) t[x].ch[1]
using namespace std;
const int N = 100010;
struct node {
    int rt, ch[2], d, val;
    /* other tags */
    node() {}
} t[N];
int n, m;
void settag(int x, int vl) {
    if (!x) { /* set tag */ }
}
void pushdown(int x) {
    /* pushdown tags */
}
int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (t[x].val > t[y].val || (t[x].val == t[y].val && x > y)) swap(x, y);
    pushdown(x); rs(x) = merge(rs(x), y); t[x].rt = t[ls(x)].rt = t[rs(x)].rt = x;
    if (t[ls(x)].d < t[rs(x)].d) swap(ls(x), rs(x));
    t[x].d = t[rs(x)].d + 1;
    return x;
}
int pop(int x) {
    pushdown(x);
    return merge(t[x].ch[0], t[x].ch[1]);
}
int findrt(int u) {return u == t[u].rt ? u : t[u].rt = findrt(t[u].rt);}

int main() {
    return 0;
}
```

---

[**Go Back**](./)
