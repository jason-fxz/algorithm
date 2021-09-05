
# Treap.cpp | DS | OI Algorithm

[**Go Back**](././)

---

```cpp
/*
    数组实现的普通Treap
    2020-6-19
    by fxz
*/
#include <bits/stdc++.h>
using namespace std;
struct treap {
  private:
    // N 为节点数
    const static int N = 100010;
    const static int INF = 0x7fffffff;
    // l,r左右儿子下标 val节点关键码 rnd随机权值 cnt副本数 siz子树大小 tot节点数 root树根
    int l[N], r[N], val[N], rnd[N], cnt[N], siz[N], tot, root;
    // 回收利用删除节点
    int eat[N], et;
    //回收节点
    void del(int &p) {
        eat[++et] = p; p = 0;
    }
    //开点
    int newn(int vl) {
        int t = et > 0 ? eat[et--] : ++tot;
        val[t] = vl;
        rnd[t] = rand();
        cnt[t] = siz[t] = 1;
        return t;
    }
    //上载，更新节点
    void updata(int p) {
        siz[p] = siz[l[p]] + siz[r[p]] + cnt[p];
    }
    //右旋
    void zig(int &p) {
        int q = l[p]; l[p] = r[q]; r[q] = p; p = q; updata(r[p]), updata(p);
    }
    //左旋
    void zag(int &p) {
        int q = r[p]; r[p] = l[q]; l[q] = p; p = q; updata(l[p]), updata(p);
    }
    //获取排名
    int rank(int vl, int p) {
        if (p == 0) return 0;
        if (vl == val[p]) return siz[l[p]];
        if (vl < val[p]) return rank(vl, l[p]);
        return rank(vl, r[p]) + siz[l[p]] + cnt[p];
    }
    //获取数值
    int value(int rk, int p) {
        if (p == 0) return INF;
        if (siz[p[l]] >= rk) return value(rk, l[p]);
        if (siz[p[l]] + cnt[p] >= rk) return val[p];
        return value(rk - siz[l[p]] - cnt[p], r[p]);
    }
    //插入
    void _insert(int vl, int &p) {
        if (p == 0) {
            p = newn(vl);
            return ;
        }
        if (vl == val[p]) {
            cnt[p]++; updata(p);
            return ;
        }
        if (vl < val[p]) {
            _insert(vl, l[p]);
            if (rnd[p] < rnd[l[p]]) zig(p);
        } else {
            _insert(vl, r[p]);
            if (rnd[p] < rnd[r[p]]) zag(p);
        }
        updata(p);
    }
    //删除
    void _remove(int vl, int &p) {
        if (p == 0) return ;
        if (vl == val[p]) {
            if (cnt[p] > 1) {
                cnt[p]--; updata(p);
                return ;
            }
            if (l[p] || r[p]) {
                if (r[p] == 0 || rnd[l[p]] > rnd[r[p]]) zig(p), _remove(vl, r[p]);
                else zag(p), _remove(vl, l[p]);
                updata(p);
            } else del(p);
            return ;
        }
        vl < val[p] ? _remove(vl, l[p]) : _remove(vl, r[p]);
        updata(p);
    }
  public:
    //重置，初始化
    void build() {
        tot = et = 0;
        newn(-INF), newn(INF);
        root = 1, r[1] = 2;
        updata(root);
    }
    //获取某值的排名(定义为比它小的个数+1)
    int getrank(int vl) {
        return rank(vl, root);
    }
    //获取排名为rk值
    int getval(int rk) {
        return value(rk + 1, root);
    }
    //插入一个值，可重复
    void insert(int vl) {
        _insert(vl, root);
    }
    //输出某值前驱，若无则-INF
    int getpre(int vl) {
        int ret = 1, p = root; // val[1]==-INF
        while (p) {
            if (vl == val[p]) {
                if (l[p] > 0) {
                    p = l[p];
                    while (r[p] > 0) p = r[p];
                    ret = p;
                }
            }
            if (val[p] < vl && val[p] > val[ret]) ret = p;
            p = vl < val[p] ? l[p] : r[p];
        }
        return val[ret];
    }
    //输出某值后继，若无则INF
    int getnxt(int vl) {
        int ret = 2, p = root; //val[2]=INF
        while (p) {
            if (vl == val[p]) {
                if (r[p] > 0) {
                    p = r[p];
                    while (l[p] > 0) p = l[p];
                    ret = p;
                }
            }
            if (val[p] > vl && val[p] < val[ret]) ret = p;
            p = vl < val[p] ? l[p] : r[p];
        }
        return val[ret];
    }
    //删除某值，如果出现多个只删一个
    void remove(int vl) {
        _remove(vl, root);
    }
    //返回元素个数，包括重复元素
    int size() {
        return siz[root] - 2;
    }
    //判断是否为空
    bool empty() {
        return size() == 0;
    }
} tp;
int n;
int main() {
    tp.build();
    scanf("%d", &n);
    while (n--) {
        int op, x;
        scanf("%d%d", &op, &x);
        switch (op) {
        case 1:
            tp.insert(x); break;
        case 2:
            tp.remove(x); break;
        case 3:
            printf("%d\n", tp.getrank(x)); break;
        case 4:
            printf("%d\n", tp.getval(x)); break;
        case 5:
            printf("%d\n", tp.getpre(x)); break;
        case 6:
            printf("%d\n", tp.getnxt(x)); break;
        }
    }
}
```

---

[**Go Back**](././)
