
# fastIO.h | MISC | OI Algorithm

[**Go Back**](./../)

---

```cpp
#include <iostream>
#include <cstdio>

#ifndef FASTIO
#define FASTIO

class myin {
  private:
    static const int MAX = 1 << 20;
    char buf[MAX], *p1 = buf, *p2 = buf;
    inline char gc() {
#ifdef DEBUG
        return getchar();
#endif
        if (p1 != p2) return *p1++;
        p1 = buf; p2 = p1 + fread(buf, 1, MAX, stdin); return (p1 == p2) ? (EOF) : (*p1++);
    }
  public:
    myin &operator>>(char *s) {
        char ch = gc();
        while (ch == '\n' || ch == '\r' || ch == ' ') ch = gc();
        while (ch != '\n' && ch != '\r' && ch != ' ') *s++ = ch, ch = gc();
        *s = '\0';
        return *this;
    }
    template <typename Tp>
    myin &operator>>(Tp &x) {
        x = 0; char ch = gc(); bool f = 0;
        while (ch < '0' || ch > '9') {(ch == '-') &&(f ^= 1); ch = gc();}
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (Tp)(ch ^ 48), ch = gc();
        if (f)(x = -x);
        return *this;
    }
    myin &operator>>(double &x) {
        x = 0; bool f = 0; char ch = gc();
        while (ch < '0' || ch > '9') {(ch == '-') &&(f ^= 1); ch = gc();}
        while (ch >= '0' && ch <= '9') x = x * 10 + (double)(ch ^ 48), ch = gc();
        if (ch == '.') {
            ch = gc(); double e = 0.1;
            while (ch >= '0' && ch <= '9') x = x + e * (double)(ch ^ 48), e *= 0.1, ch = gc();
        }
        if (f) x = -x;
        return *this;
    }
} fin;

class myout {
  private:
    static const int MAX = 1 << 20;
    char buf[MAX], *p1 = buf, *p2 = buf + MAX;
    char dbform[10] = "%.6lf";
    inline void pc(const char c) {
#ifdef DEBUG
        putchar(c); return ;
#endif
        if (p1 != p2) *p1++ = c;
        else {fwrite(buf, p1 - buf, 1, stdout); p1 = buf; *p1++ = c;}
    }
    template <typename _Tp> void write(_Tp x) {
        if (x < 0) x = -x, pc('-');
        if (x >= (_Tp)10) write(x / 10);
        pc(x % 10 + '0');
    }
  public:
    void flush() {fwrite(buf, p1 - buf, 1, stdout); p1 = buf;}
    myout &operator<<(const char *s) { for (const char *p = s; *p; ++p) pc(*p); return *this;}
    myout &operator<<(char *s) { for (char *p = s; *p; ++p) pc(*p); return *this;}
    myout &operator<<(const char s) {pc(s); return *this;}
    template <typename Tp> myout &operator<<(Tp x) {write(x); return *this;}
    myout &operator<<(myout & (*__pf)(myout &)) {return __pf(*this);}
    void setpoint(int n) {
        sprintf(dbform + 1, ".%dlf", n);
    }
    myout &operator<<(double x) {
        static char num[100];
        sprintf(num, dbform, x);
        return *this << num;
    }
} fout;

inline myout &edl(myout &out) {out << "\n"; out.flush(); return out;}

#endif

```

---

[**Go Back**](./../)
