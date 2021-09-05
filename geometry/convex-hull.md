
# convex-hull.cpp | GEOMETRY | OI Algorithm

[**Go Back**](./../)

---

```cpp
#include <bits/stdc++.h>
#define il inline
using namespace std;
typedef double db;
const db eps = 1e-8;
il int sign(const db &num) {return (num > eps) - (num < -eps);} // 判断符号，为正则 1 为负则 -1 为零则零
il int cmp(const db &a, const db &b) {return sign(a - b);} // 比较大小
struct vec { // Vector & Point
    db x, y;
    void input() {scanf("%lf%lf", &x, &y);}
    vec(const db &_x = 0, const db &_y = 0): x(_x), y(_y) {}
    il vec operator+(const vec &v) const {return vec(x + v.x, y + v.y);}
    il vec operator-(const vec &v) const {return vec(x - v.x, y - v.y);}
    il vec operator*(const db &a) const {return vec(x * a, y * a);}
    il vec operator/(const db &a) const {return vec(x / a, y / a);}
    il db len2() const {return x * x + y * y;}
    il db len() const {return hypot(x, y);} // 模长
    il vec turnc(db r) const {db l = len(); if (!sign(l)) return *this; r /= l; return (*this) * r;} // 改变长度
    bool operator<(const vec t) const {return (cmp(x, t.x) == 0) ? (cmp(y, t.y) < 0) : (cmp(x, t.x) < 0);}
    bool operator==(const vec t) const {return cmp(x, t.x) == 0 && cmp(y, t.y) == 0;}
};
typedef vec poi;
il db dot(const vec &a, const vec &b) {return a.x * b.x + a.y * b.y;} // 点积
il db crs(const vec &a, const vec &b) {return a.x * b.y - a.y * b.x;} // 叉积
il db dis(const poi &a, const poi &b) {return (b - a).len();} // 两点距离
vector<poi> pts, pois; int n;
poi O;
bool cmpv(poi a, poi b) { // 极角排序（这个 cmp 需要保证所有点在原点一侧）
    int k = sign(crs(a - O, b - O));
    return (k == 0) ? ((a - O).len2() < (b - O).len2()) : (k > 0);
}
int relat(const poi &a, const poi &b, const poi &c) { // 三点关系，判断是凸还是凹
    return sign(crs(b - a, c - b));
}
void Graham(vector<poi> pt, vector<poi> &res) { // Graham 求凸包 (极角排序+单调栈)
    res.clear();
    for (int i = 1; i < (int)pt.size(); ++i) if (pt[i] < pt[0]) swap(pt[i], pt[0]);
    O = pt[0];
    sort(pt.begin() + 1, pt.end(), cmpv);
    for (int i = 0; i < (int)pt.size(); ++i) {
        while (res.size() >= 2 && relat(res[res.size() - 2], res[res.size() - 1], pt[i]) <= 0) res.pop_back();
        res.push_back(pt[i]);
    }
}
db Aera(vec a, vec b, vec c) {return abs(crs(b - a, c - a));} // 三角形面积 |(*2)|
db Diam(vector<poi> pt) { // 凸包直径 Diameter “旋转卡壳”
    int n = pt.size(), j = 0; db res = 0;
    if (pt.size() == 2) return (pt[0] - pt[1]).len2();
    pt.push_back(pt[0]);
    for (int i = 0; i < n; ++i) {
        while (Aera(pt[i], pt[i + 1], pt[(j + 1) % n]) >= Aera(pt[i], pt[i + 1], pt[j])) j = (j + 1) % n;
        res = max(res, max((pt[j] - pt[i]).len2(), (pt[j] - pt[i + 1]).len2()));
    }
    return res;
}
db Perim(vector<poi> pt) { // 凸包周长 Perimeter
    db res = 0; int n = pois.size();
    for (int i = 0; i < n; ++i) res += dis(pois[(i == 0) ? (n - 1) : (i - 1)], pois[i]);
    return res;
}
db Area(const vector<poi> &pts) { // 任意多边形面积  (有向面积：顺负逆正)
    db res = 0; int n = pts.size();
    for (int i = 1; i < n - 1; ++i) res += crs(pts[i] - pts[0], pts[i + 1] - pts[0]);
    return res / 2.0;
}
poi Grav(const vector<poi> &pts) { // Center of Gravity  多边形质心
    poi g; db sumarea = 0; int n = pts.size();
    for (int i = 2; i < n; ++i) {
        db S = crs(pts[i - 1] - pts[0], pts[i] - pts[0]);
        g = g + (pts[0] + pts[i - 1] + pts[i]) * S;
        sumarea += S;
    }
    return g / (sumarea * 3);
}
int main() {
    // Readin
    scanf("%d", &n); pts.resize(n);
    for (int i = 0; i < n; ++i) pts[i].input();
}
```

---

[**Go Back**](./../)
