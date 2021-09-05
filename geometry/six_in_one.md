
# six_in_one.cpp | GEOMETRY | OI Algorithm

[**Go Back**](././)

---

```cpp
/*
	https://vjudge.net/problem/UVA-12304
	计算几何 基du础liu题  点线圆相关

	计算几何板子 v1.0
*/
#include <bits/stdc++.h>
#define il inline
using namespace std;
typedef double db;

const db eps = 1e-10;
il int sign(const db &num) {return (num > eps) - (num < -eps);} // 判断符号，为正则 1 为负则 -1 为零则零
il int cmp(const db &a, const db &b) {return sign(a - b);} // 比较大小

const db Pi = acos(-1);
il db R_to_D(const db &rad) {return 180.0 / Pi * rad;}
il db D_to_R(const db &deg) {return Pi / 180.0 * deg;}

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
    il vec unit() const {db l = len(); return (sign(l) == 0) ? (vec(0, 0)) : (*this / l); } // 单位化
    il vec turnc(db r) const {db l = len(); if (!sign(l)) return *this; r /= l; return (*this) * r;} // 改变长度
    il db angle() const { db k = atan2(y, x); if (sign(k) < 0) k += Pi; if (cmp(k, Pi) == 0) k -= Pi; return k;}
    bool operator<(const vec t) const {return (cmp(x, t.x) == 0) ? (cmp(y, t.y) < 0) : (cmp(x, t.x) < 0);}
    bool operator==(const vec t) const {return cmp(x, t.x) == 0 && cmp(y, t.y) == 0;}
};
typedef vec poi;
struct cir { // Circle
    poi O; db r;
    cir() {}
    cir(const poi &_O, const db &_r): O(_O), r(_r) {}
    void input() {O.input(); scanf("%lf", &r);}
};
struct lin { // Line & Ray
    poi p; vec v;
    lin() {}
    lin(const poi &_p, const vec &_v): p(_p), v(_v) {} // 直线上点p，方向向量v
    lin(const db &_x1, const db &_y1, const db &_x2, const db &_y2): p(_x1, _y1), v(_x2 - _x1,
                _y2 - _y1) {} // 直线上两点
    il db angle() const {return v.angle();}
    void input() {p.input(); v.input(); v = v - p;}
};
typedef lin ray;

il db dot(const vec &a, const vec &b) {return a.x * b.x + a.y * b.y;} // 点积
il db crs(const vec &a, const vec &b) {return a.x * b.y - a.y * b.x;} // 叉积
il vec rot90(const vec &t) {return vec(-t.y, t.x);} // +90
il vec rotn90(const vec &t) {return vec(t.y, -t.x);} // -90
il vec rot180(const vec &t) {return vec(-t.x, -t.y);} // +180
il poi cross(const lin &a, const lin &b) {return a.p + a.v * crs((b.p - a.p), b.v) / crs(a.v, b.v);} // 求两直线交点
il poi foot(const lin &l, const poi &p) {return cross(lin(p, rot90(l.v)), l);} // p 到 l 的垂足
il db dist(const lin &l, const poi &p) {return (p - foot(l, p)).len();} // 点到直线距离
il db Helen(const db &a, const db &b, const db &c) { db p = (a + b + c) / 2; return sqrt(p * (p - a) * (p - b) * (p - c));} // 海伦公式，求三角形面积
il int rela(const cir &c, const poi &p) {return cmp((c.O - p).len(), c.r) + 1;} // 点与圆关系，0:点在圆内；1:点在圆上；2:点在圆外
il int rela(const cir &c, const lin &l); // 圆与直线关系
il int rela(const cir &c, const lin &l); // 圆与圆关系
il void cross(const cir &c, const lin &l, poi &p1, poi &p2); // 圆与直线交点

void ptv(const vec &v) {printf(">>> [%.6lf,%.6lf]\n", v.x, v.y);}
void ptp(const poi &p) {printf(">>> (%.6lf,%.6lf)\n", p.x, p.y);}
void ptl(const lin &l) {printf(">>> (%.6lf,%.6lf) [%.6lf,%.6lf]\n", l.p.x, l.p.y, l.v.x, l.v.y);}
void ptc(const cir &c) {printf(">>> (%.6lf,%.6lf) r=%0.6lf\n", c.O.x, c.O.y, c.r);}
void ptt(const db  &t) {printf(">>> %.6lf\n", t);}

cir OutsideCircle(const poi &A, const poi &B, const poi &C) { // 外接圆
    poi O = cross(lin((A + B) / 2, rot90(B - A)), lin((A + C) / 2, rot90(A - C)));
    return cir(O, (O - A).len());
}

cir InsideCircle(const poi &A, const poi &B, const poi &C) { // 内切圆
    vec a = C - B, c = A - B, b = C - A;
    db p = a.len() + b.len() + c.len();
    db r = abs(crs(a, c) / p);
    poi O = (A * a.len() + B * b.len() + C * c.len()) / p;
    return cir(O, r);
}

void TangentLine(const cir &C, const poi &P, vector<lin> &res) { // 过点 P 到圆的切线
    res.clear();
    int op = cmp((C.O - P).len(), C.r);
    if (op < 0) return ; // P 在圆内无切线
    if (op == 0) {
        res.push_back(lin(P, rot90(C.O - P))); // P 在圆上切线与半径垂直
        return ;
    }
    // P 在圆外两切线
    vec d = P - C.O;
    db t = sqrt(d.len2() - C.r * C.r);
    db h = t * C.r / d.len(), x = C.r * h / t;
    poi F = C.O + d.turnc(x);
    res.push_back(lin(P, (F + rot90(d).turnc(h) - P)));
    res.push_back(lin(P, (F + rotn90(d).turnc(h) - P)));
}

void GetCircle(const poi &P, const lin &l, const db &r,
               vector<poi> &res) { // 给圆上一点,一切线,半径：求圆心
    res.clear();
    if (sign(crs(l.v, l.p - P)) == 0) { // P 在 l 上，P 为切点
        res.push_back(P + rot90(l.v).turnc(r));
        res.push_back(P + rotn90(l.v).turnc(r));
        return ;
    }
    poi F = foot(l, P); // F 为 P 到 l 垂足
    int op = cmp((P - F).len(), 2 * r);
    if (op > 0) return ; // P 到 l 距离大于 2r
    if (op == 0) { // P 到 l 距离等于 2r，PF为直径
        res.push_back((P + F) / 2);
        return ;
    }
    db t = (P - F).len() - r, d = sqrt(r * r - t * t);
    res.push_back(F + l.v.turnc(d) + (P - F).turnc(r));
    res.push_back(F - l.v.turnc(d) + (P - F).turnc(r));
}

void GetCircle(const lin &l1, const lin &l2, const db &r, vector<poi> &res) { // 两切线+半径：求圆心
    res.clear();
    lin l1u = lin(l1.p + rot90(l1.v).turnc(r), l1.v), l1d = lin(l1.p + rotn90(l1.v).turnc(r), l1.v);
    lin l2u = lin(l2.p + rot90(l2.v).turnc(r), l2.v), l2d = lin(l2.p + rotn90(l2.v).turnc(r), l2.v);
    res.push_back(cross(l1u, l2u)); res.push_back(cross(l1u, l2d));
    res.push_back(cross(l1d, l2u)); res.push_back(cross(l1d, l2d));
}

void CircleCross(const cir &c1, const cir &c2, vector<poi> &res) { // 求两圆交点
    res.clear();
    vec d = c2.O - c1.O;
    int op = cmp(c1.r + c2.r, d.len());
    if (op < 0) return ;
    if (op == 0) {
        res.push_back(c1.O + d.turnc(c1.r));
        return ;
    }
    db t = c1.r * (c1.r * c1.r + d.len2() - c2.r * c2.r) / (2.0 * c1.r * d.len());
    db h = sqrt(c1.r * c1.r - t * t);
    res.push_back(c1.O + rot90(d).turnc(h) + d.turnc(t));
    res.push_back(c1.O + rotn90(d).turnc(h) + d.turnc(t));
}

void TangentCircle(const cir &c1, const cir &c2, const db &r,
                   vector<poi> &res) { // 给两无交圆 ，求半径为r的切圆
    CircleCross(cir(c1.O, c1.r + r), cir(c2.O, c2.r + r), res);
}

void output(vector<poi> &pois) {
    sort(pois.begin(), pois.end());
    printf("[");
    for (int i = 0; i < (int)pois.size(); ++i) {
        printf("(%.6lf,%.6lf)", pois[i].x, pois[i].y);
        if (i < (int)pois.size() - 1) putchar(',');
    }
    printf("]\n");
}

void output(vector<db> &nums) {
    sort(nums.begin(), nums.end());
    printf("[");
    for (int i = 0; i < (int)nums.size(); ++i) {
        printf("%.6lf", nums[i]);
        if (i < (int)nums.size() - 1) putchar(',');
    }
    printf("]\n");
}

string opt;

int main() {
    while (cin >> opt) {
        if (opt == "CircumscribedCircle") {
            poi A, B, C; A.input(); B.input(); C.input();
            cir c = OutsideCircle(A, B, C);
            printf("(%.6lf,%.6lf,%.6lf)\n", c.O.x, c.O.y, c.r);
        } else if (opt == "InscribedCircle") {
            poi A, B, C; A.input(); B.input(); C.input();
            cir c = InsideCircle(A, B, C);
            printf("(%.6lf,%.6lf,%.6lf)\n", c.O.x, c.O.y, c.r);
        } else if (opt == "TangentLineThroughPoint") {
            vector<lin> lins; vector<db> degs; poi P; cir c;
            c.input(); P.input();
            TangentLine(c, P, lins);
            for (int i = 0; i < (int)lins.size(); ++i)
                degs.push_back(R_to_D(lins[i].angle()));
            output(degs);
        } else if (opt == "CircleThroughAPointAndTangentToALineWithRadius") {
            vector<poi> pois; poi P; lin l0; db r;
            P.input(); l0.input(); scanf("%lf", &r);
            GetCircle(P, l0, r, pois);
            output(pois);
        } else if (opt == "CircleTangentToTwoLinesWithRadius") {
            vector<poi> pois; lin l1, l2; db r;
            l1.input(); l2.input(); scanf("%lf", &r);
            GetCircle(l1, l2, r, pois);
            output(pois);
        } else if (opt == "CircleTangentToTwoDisjointCirclesWithRadius") {
            vector<poi> pois; cir c1, c2; db r;
            c1.input(); c2.input(); scanf("%lf", &r);
            TangentCircle(c1, c2, r, pois);
            output(pois);
        }
    }
}
```

---

[**Go Back**](././)
