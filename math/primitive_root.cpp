// 原根
#include <bits/stdc++.h>
using namespace std;
const int N = 1000010;
int p[N], tot, phi[N]; // p[] 素数，phi[] 欧拉函数
bool v[N], has[N]; // v[] 是否是素数, is[] 是否有原根
int Ts;
typedef long long ll;
ll fpow(ll a, ll b, ll p) {ll r = 1; for (; b; b >>= 1, a = (a * a) % p) if (b & 1) r = (r * a) % p; return r;}
int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}
void init(int n) { // 预处理欧拉函数，素数，及那些数有原根
    phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!v[i]) p[++tot] = i, phi[i] = i - 1;
        for (int j = 1; j <= tot && p[j]*i <= n; ++j) {
            v[p[j]*i] = 1;
            if (i % p[j] == 0) {
                phi[i * p[j]] = phi[i] * p[j];
                break;
            }
            phi[i * p[j]] = phi[i] * (p[j] - 1);
        }
    }
    has[2] = has[4] = 1;
    for (int i = 2; i <= tot; ++i) for (ll j = p[i]; j <= n; j *= p[i]) has[j] = 1, (j * 2 <= n)
                    && (has[j * 2] = 1);
}
void devide(int x, vector<int> &ret) { // 分解质因数
    ret.clear();
    for (int i = 1; 1ll * p[i]*p[i] <= x; ++i) if (x % p[i] == 0) {
            ret.push_back(p[i]);
            while (x % p[i] == 0) x /= p[i];
        }
    if (x > 1) ret.push_back(x);
}
bool hasroot(int n) { // 判断一个数是否有原根
    if (n == 2 || n == 4) return 1;
    if (n % 2 == 0) n /= 2;
    if (n % 2 == 0) return 0;
    for (int i = 2; 1ll * p[i]*p[i] <= n; ++i) if (n % p[i] == 0) {
            while (n % p[i] == 0) n /= p[i];
            return (n == 1);
        }
    return 1;
}
void Getroot(int m, vector<int> &res) {
    res.clear();
    if (!has[m]) return ;
    vector<int> factor;
    devide(phi[m], factor);
    int g = 1, mphi = phi[m];
    while (true) {
        bool fg = 1;
        if (gcd(g, m) != 1) fg = 0; //i不存在模n的阶
        else for (int i = 0; i < (int)factor.size(); ++i) {
                if (fpow(g, mphi / factor[i], m) == 1ll) {fg = 0; break;}
            }
        if (fg) break;
        ++g;
    }
    ll pw = 1;
    for (int s = 1; (int)res.size() < phi[mphi]; ++s) {
        pw = (pw * g) % m;
        if (gcd(s, mphi) == 1) res.push_back(pw);
    }
    sort(res.begin(), res.end());
}
int main() {
    init(1e6);
    scanf("%d", &Ts);
    while (Ts--) {
        int n, d; // 找 n 的所有原根
        scanf("%d%d", &n, &d);
        vector<int> ans;
        Getroot(n, ans);
        printf("%d\n", (int)ans.size());
        for (int i = d - 1; i < (int)ans.size(); i += d) printf("%d ", ans[i]);
        printf("\n");
    }
}