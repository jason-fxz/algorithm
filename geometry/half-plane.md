
# half-plane.cpp | GEOMETRY | OI Algorithm

[**Go Back**](./)

---

```cpp
/*
	半平面交
	本代码 --> 求凸多边形面积并
*/
#include <bits/stdc++.h>
#define il inline
using namespace std;

typedef double db;
const db Pi = acos(-1.0);
const db eps = 1e-7;

il int sign(db num) {return (num > eps) - (num < -eps);}
il int cmp(db a, db b) {return sign(a - b);}

struct vec {
    db x, y;
    vec(db _x = 0, db _y = 0): x(_x), y(_y) {}
    il void input() {scanf("%lf%lf", &x, &y);}
    il vec operator+(const vec &t) const {return vec(x + t.x, y + t.y);}
    il vec operator-(const vec &t) const {return vec(x - t.x, y - t.y);}
    il vec operator*(const db  &t) const {return vec(x * t, y * t);}
    il vec operator/(const db  &t) const {return vec(x / t, y / t);}
    il db len2() const {return x * x + y * y;}
    il db len()  const {return hypot(x, y);}
    bool operator<(const vec &t) const {return (cmp(x, t.x) == 0) ? (cmp(y, t.y) < 0) : (cmp(x, t.x) < 0);}
};
typedef vec poi;
il db dot(const vec &a, const vec &b) {return a.x * b.x + a.y * b.y;}
il db crs(const vec &a, const vec &b) {return a.x * b.y - a.y * b.x;}
il db dis(const vec &a, const vec &b) {return (a - b).len();}
struct lin {
    poi s, e; db k;
    lin(poi _s, vec _e): s(_s), e(_e), k(atan2((e - s).y, (e - s).x)) {}
    il poi operator()() const {return e - s;}
};
il poi cross(const lin &l1, const lin &l2) {return l1.s + l1() * crs(l2.s - l1.s, l2()) / crs(l1(), l2());}
vector<lin> L; // 半平面们，统一向量左侧为半平面
vector<poi> P, pts; // 多边形们
int n, m;
bool cmpl(lin a, lin b) { // 极角排序，极角相同靠左优先
    if (cmp(a.k, b.k) == 0) return sign(crs(b.e-a.s, a())) > 0;
    return cmp(a.k, b.k) < 0;
}
bool Onright(lin a, lin b, lin c) { // a,b 交点在 c 右边
    poi p = cross(a, b);
    return sign(crs(c(), p - c.s)) <= 0;
}
void Halfplane(vector<lin> Ls, vector<poi> &res) { // 半平面交
    res.clear();
    sort(Ls.begin(), Ls.end(), cmpl);
    deque<int> q;
    for (int i = 0; i < (int)Ls.size(); ++i) {
        if (i != 0 && cmp(Ls[i].k, Ls[i - 1].k) == 0) continue;
        while (q.size() >= 2 && Onright(Ls[q[q.size() - 2]], Ls[q.back()], Ls[i])) q.pop_back();
        while (q.size() >= 2 && Onright(Ls[q.front()], Ls[q[1]], Ls[i])) q.pop_front();
        q.push_back(i);
    }
    while (q.size() >= 2 && Onright(Ls[q[q.size() - 2]], Ls[q.back()], Ls[q.front()])) q.pop_back();
    while (q.size() >= 2 && Onright(Ls[q[0]], Ls[q[1]], Ls[q.back()])) q.pop_front();
    if (q.size() >= 2) res.push_back(cross(Ls[q.back()], Ls[q.front()]));
    while (q.size() >= 2) {
        res.push_back(cross(Ls[q[0]], Ls[q[1]]));
        q.pop_front();
    }
}
db Area(const vector<poi> &pts) { //多边形面积
    db res = 0;
    for (int i = 1; i < (int)pts.size() - 1; ++i) res += crs(pts[i] - pts[0], pts[i + 1] - pts[0]);
    return res / 2.0;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &m);
        pts.resize(m);
        for (int i = 0; i < m; ++i) pts[i].input();
        for (int i = 0; i < m; ++i) L.push_back(lin(pts[i], pts[(i + 1) % m]));
    }
    Halfplane(L, P);
    db ans = Area(P);
    printf("%.3lf\n", ans);
    return 0;
}
```

---

[**Go Back**](./)
