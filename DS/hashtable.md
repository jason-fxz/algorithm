
# hashtable.cpp | DS | OI Algorithm

[**Go Back**](./../)

---

```cpp
#include <cstring>
typedef long long ll;

namespace hashtable1 {
    const int M = 19260817;
    const int MAX_SIZE = 2000000;
    struct Hash_map {
        struct data {
            int nxt;
            ll key, value; // (key,value)
        } e[MAX_SIZE];
        int head[M], size;
        inline int f(ll key) { return key % M; } // 哈希函数
        ll &operator[](const ll &key) { // 重载[]
            int ky = f(key);
            for (int i = head[ky]; i != -1; i = e[i].nxt)
                if (e[i].key == key) return e[i].value;
            return e[++size] = data{head[ky], key, 0}, head[ky] = size, e[size].value;
        }
        void clear() { // 清空
            memset(head, -1, sizeof(head));
            size = 0;
        }
        Hash_map() {clear();} // 初始化清空
    };
}

namespace hashtable2 {
    const int M = 19260817;
    const int MAX_SIZE = 2000000;
    struct Hash {
        struct data {
            int nxt;
            ll key, value;
        } e[MAX_SIZE];
        int head[M], size;
        inline int f(ll key) { return key % M; } // 哈希函数
        void clear() { // 清空
            memset(head, -1, sizeof(head));
            size = 0;
        }
        ll query(ll key) { // 查询
            for (int i = head[f(key)]; i != -1; i = e[i].nxt)
                if (e[i].key == key) return e[i].value;
            return -1;
        }
        ll modify(ll key, ll value) { // 修改
            for (int i = head[f(key)]; i != -1; i = e[i].nxt)
                if (e[i].key == key) return e[i].value = value;
            return -1;
        }
        ll insert(ll key, ll value) { // 插入
            if (query(key) != -1) return -1;
            e[++size] = data{head[f(key)], key, value};
            head[f(key)] = size;
            return value;
        }
    };
}

```

---

[**Go Back**](./../)
