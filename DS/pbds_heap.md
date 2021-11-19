
# pbds_heap.cpp | DS | OI Algorithm

[**Go Back**](./)

---

```cpp
/*
__gnu_pbds :: priority_queue 堆 使用指南
========================================================================================================
__gnu_pbds ::priority_queue<_Tv, Cmp_Fn = std::less<_Tv>, Tag = pairing_heap_tag,
                           Allocator = std::allocator<char> >

_Tv:          储存的元素类型
Cmp_Fn:       比较函子，默认 std::less<_Tv> 为大根堆
Tag:          堆的类型（默认且建议 pairing_heap_tag）
Allocator:    空间分配器类型（不用改）

push(),pop(),top(),size(),empty() 与 std::priority_queue 类似
join(other)         将 other 加入当前堆，other 堆被删除（前提是两棵树的类型一样）
modify(it, key)     修改迭代器 it 所指的 key，并对底层储存结构进行排序
erase(it)           把迭代器 it 位置的键值从堆中擦除
begin(),end()       返回可以用来遍历的迭代器，不保证有序！且只要进行过修改操作就会变
========================================================================================================
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
const int N = 100010;
__gnu_pbds::priority_queue<pair<int, int>, greater<pair<int, int>>> Q[N];
// 以下是用 pb_ds::tree 实现的 【模板】左偏树（可并堆） https://www.luogu.com.cn/problem/P3377
int fa[N], n, m;
bool del[N];
int find(int u) { 
    return fa[u] == u ? u : fa[u] = find(fa[u]);
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        int x; scanf("%d", &x);
        fa[i] = i, Q[i].push({x, i});
    }
    while (m--) {
        int op, x, y;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d", &x, &y);
            if (del[x] || del[y]) continue;
            x = find(x), y = find(y);
            if (x != y) {
                fa[x] = y;
                Q[y].join(Q[x]);
            }
        } else {
            scanf("%d", &x);
            if (del[x]) {
                puts("-1");
                continue;
            }
            x = find(x);
            printf("%d\n", Q[x].top().first);
            del[Q[x].top().second] = 1;
            Q[x].pop();
        }
    }
}

```

---

[**Go Back**](./)
