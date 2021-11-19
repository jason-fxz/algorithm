
# pbds_tree.cpp | DS | OI Algorithm

[**Go Back**](./)

---

```cpp
/*
__gnu_pbds :: tree 平衡树 使用指南
========================================================================================================
__gnu_pbds ::tree<Key, Mapped, Cmp_Fn = std::less<Key>, Tag = rb_tree_tag,
                  Node_Update = null_tree_node_update,
                  Allocator = std::allocator<char> >

Key:          储存的元素类型
Mapped:       填 null_type 当成 std::set， 填其他类型当成 std::map
Cmp_Fn:       比较函子
Tag:          树的类型（建议 rb_tree_tag）
Node_Update:  更新节点的策略，默认是 null_tree_node_update
              使用 tree_order_statistics_node_update 来允许 order_of_key，find_by_order 方法
Allocator:    空间分配器类型（不用改）

insert(),erase(),lower_bound(),upper_bound(),find(),empty(),size(),begin(),end() 与 std::set 类似
join(other)         将 other 加入当前树，other 树被删除（前提是两棵树的类型一样）
split(val, other)   以 Cmp_Fn 比较，小于等于 val 的属于当前树，其余的属于 other 树
order_of_key(x)     返回 x 以 Cmp_Fn 比较的排名（从 0 开始）
find_by_order(x)    返回 Cmp_Fn 比较的排名所对应元素的迭代器 （从 0 开始）
========================================================================================================
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
__gnu_pbds::tree<std::pair<int, int>, __gnu_pbds::null_type, std::less<std::pair<int, int>>,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update> T;

// 以下是用 pb_ds::tree 实现的 【模板】普通平衡树 https://www.luogu.com.cn/problem/P3369
int Q;
int main() {
    scanf("%d", &Q);
    while (Q--) {
        int opt, x; scanf("%d%d", &opt, &x);
        switch (opt) {
        case 1: {
            auto it = T.lower_bound({x + 1, 0});
            if (it != T.begin() && (--it)->first != x) T.insert({x, 1});
            else T.insert({x, it->second + 1});
            break;
        }
        case 2: {
            auto it1 = --T.lower_bound({x + 1, 0});
            T.erase(it1);
            break;
        }
        case 3: {
            int rk = T.order_of_key({x, 1});
            printf("%d\n", rk + 1);
            break;
        }
        case 4: {
            auto it = T.find_by_order(x - 1);
            printf("%d\n", it->first);
            break;
        }
        case 5: {
            auto it = --T.lower_bound({x, 0});
            printf("%d\n", it->first);
            break;
        }
        case 6: {
            auto it = T.lower_bound({x + 1, 0});
            printf("%d\n", it->first);
            break;
        }
        default:
            break;
        }
        // for (auto i : T) {
        //     printf("%d[%d] ", i.first, i.second);    
        // }
        // puts("");
    }      
    return 0;
}

```

---

[**Go Back**](./)
