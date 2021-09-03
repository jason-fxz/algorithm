#include <cstdio>
#include <cmath>
#include <algorithm>
#include <ctime>
using namespace std;
typedef long double db;
const int N = 100010;
struct vec {
    db x, y;
    vec(const db &_x = 0, const db &_y = 0): x(_x), y(_y) {}
    vec operator+(const vec &t) const {return vec(x + t.x, y + t.y);}
    vec operator-(const vec &t) const {return vec(x - t.x, y - t.y);}
    vec operator*(const db &t) const {return vec(x * t, y * t);}
    vec operator/(const db &t) const {return vec(x / t, y / t);}
    const db len2() const {return x * x + y * y;}
    const db len() const {return sqrt(len2());}
};
db dot(const vec &a, const vec &b) {return a.x * b.x + a.y * b.y;}
db crs(const vec &a, const vec &b) {return a.x * b.y - a.y * b.x;}
vec pt[N]; int n;
vec rot90(vec a) {return vec(a.y, -a.x);}
vec cross(vec p1, vec v1, vec p2, vec v2) {return p1 + v1 * crs(p2 - p1, v2) / crs(v1, v2);}
vec get_circle(vec a, vec b, vec c) {	return cross((a + b) / 2, rot90(b - a), (b + c) / 2, rot90(c - b));}
void min_circle_cover(vec p[], int t) {
    random_shuffle(p + 1, p + n + 1);
    db r_2 = 0; vec O;
    for (int i = 1; i <= n; ++i) {
        if ((p[i] - O).len2() > r_2) {
            O = p[i], r_2 = 0;
            for (int j = 1; j < i; ++j) {
                if ((p[j] - O).len2() > r_2) {
                    O = (p[i] + p[j]) / 2, r_2 = (p[i] - O).len2();
                    for (int k = 1; k < j; ++k) {
                        if ((p[k] - O).len2() > r_2) {
                            O = get_circle(p[i], p[j], p[k]); r_2 = (p[k] - O).len2();
                        }
                    }
                }
            }
        }
    }
    printf("%.10Lf\n%.10Lf %.10Lf\n", sqrt(r_2), O.x, O.y);
}
int main() {
    srand(time(0));
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%Lf%Lf", &pt[i].x, &pt[i].y);
    min_circle_cover(pt, n);
}
