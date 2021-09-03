// 期望 O(n)-O(1) RMQ
// luogu P3793 由乃救爷爷
#include <cstdio>
#define re register
// -------------- ReadIN ----------------
namespace GenHelper {
    unsigned z1, z2, z3, z4, b;
    unsigned rand_() {
        b = ((z1 << 6)^z1) >> 13;
        z1 = ((z1 & 4294967294U) << 18)^b;
        b = ((z2 << 2)^z2) >> 27;
        z2 = ((z2 & 4294967288U) << 2)^b;
        b = ((z3 << 13)^z3) >> 21;
        z3 = ((z3 & 4294967280U) << 7)^b;
        b = ((z4 << 3)^z4) >> 12;
        z4 = ((z4 & 4294967168U) << 13)^b;
        return (z1 ^ z2 ^ z3 ^ z4);
    }
}
void srand(unsigned x) {using namespace GenHelper; z1 = x; z2 = (~x) ^ 0x233333333U; z3 = x ^ 0x1234598766U; z4 = (~x) + 51;}
int read() {
    using namespace GenHelper;
    int a = rand_() & 32767;
    int b = rand_() & 32767;
    return a * 32768 + b;
}
// ----------- END ReadIN -------------

typedef unsigned long long ull;
int n, m, s;
// ------------ BEGIN RMQ -------------
const int N = 20000010;
int a[N];
namespace RMQ {
    inline int gmax(int x, int y) {return a[x] > a[y] ? x : y;}
    const int B = 4434; // B 大概取 log2(n) or sqrt(n) ??  怕被卡的话随机微调块长
    const int M = 16;
    int bl[N], F[M][N / B + 10], ps[N], pre[N], suf[N], LOG[N], tot;
    // bl 属于哪个块，F 块间ST表 ps块内最值下标 pre/suf 块内前缀/后缀最值
    void init() {
        for (re int i = 1; i <= n; ++i) bl[i] = (i - 1) / B + 1;
        for (re int i = 1; i <= n;
             ++i)(bl[i] != bl[i - 1]) ? (pre[i] = i, ps[bl[i - 1]] = pre[i - 1]) : (pre[i] = gmax(pre[i - 1], i));
        for (re int i = 1, j = B; j <= n; ++i, j += B) ps[i] = pre[j];
        tot = bl[n]; ps[tot] = pre[n];
        for (re int i = n; i >= 1; --i)(bl[i] != bl[i + 1]) ? (suf[i] = i) : (suf[i] = gmax(suf[i + 1], i));
        LOG[0] = -1;
        for (re int i = 1; i <= tot; ++i) LOG[i] = LOG[i >> 1] + 1;
        for (re int i = 1; i <= tot; ++i) F[0][i] = ps[i];
        for (re int j = 1; j <= LOG[tot]; ++j) {
            for (re int i = 1; i <= tot; ++i) {
                if (i + (1 << j) - 1 > tot) break;
                F[j][i] = gmax(F[j - 1][i], F[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
    inline int ask(int l, int r) { // 返回区间最值位置
        if (bl[l] == bl[r]) {
            int p = l;
            for (re int i = l + 1; i <= r; ++i) p = gmax(p, i);
            return p;
        }
        if (bl[l] + 1 == bl[r]) return gmax(suf[l], pre[r]);
        int L = bl[l] + 1, R = bl[r] - 1;
        int k = LOG[R - L + 1];
        return gmax(gmax(F[k][L], F[k][R - (1 << k) + 1]), gmax(suf[l], pre[r]));
    }
}
// -------------- END RMQ --------------
inline void swap(int &l, int &r) {l ^= r; r ^= l; l ^= r;}
int main() {
    scanf("%d%d%d", &n, &m, &s);
    srand(s);
    for (re int i = 1; i <= n; ++i) a[i] = read();
    RMQ::init();
    ull ANS = 0;
    for (re int i = 1, l, r; i <= m; ++i) {
        l = read() % n + 1, r = read() % n + 1;
        (l > r) &&(swap(l, r), 1);
        ANS += a[RMQ::ask(l, r)];
    }
    printf("%llu\n", ANS);
}