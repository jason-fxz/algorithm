
# simpson.cpp | MATH | OI Algorithm

[**Go Back**](././)

---

```cpp
// 数值积分，自适应辛普森法
#include <cmath>
#include <cstdio>
using namespace std;

typedef double db;

// 要计算的函数
db f(db x) {
    return x * x * x;
}

// 辛普森公式  = (r - l) / 6 * (f(l) + f(r) + 4f((l + r) / 2))
db simpon(db l, db r) {
    db mid = (l + r) / 2.0;
    return (r - l) * (f(l) + f(r) + f(mid) * 4.0) / 6.0;
}

db simpon(db l, db r, db eps, db ans, int step) {
    db mid = (l + r) / 2.0;
    db fl = simpon(l, mid), fr = simpon(mid, r);
    if (fabs(fl + fr - ans) <= 15.0 * eps && step < 0) return fl + fr + (fl + fr - ans) / 15.0;
    return simpon(l, mid, eps / 2.0, fl, step - 1) + simpon(mid, r, eps / 2.0, fr, step - 1);
}

db calc(db l, db r, db eps) {
    return simpon(l, r, eps, simpon(l, r), 12);
}

```

---

[**Go Back**](././)
