
# fast_io.cpp | MISC | OI Algorithm

[**Go Back**](./)

---

```cpp
#include <cstdio>

namespace IO {
    const int MAX = 1 << 20;
    char buf[MAX], Buf[MAX], * p1 = buf, * p2 = buf, * P1 = Buf, * P2 = Buf + MAX;
    inline char gc() {
#ifdef DEBUG
        return getchar();
#endif
        if (p1 != p2) return *p1++;
        p1 = buf; p2 = p1 + fread(buf, 1, MAX, stdin); return (p1 == p2) ? (EOF) : (*p1++);
    }
    inline void pc(const char c) {
#ifdef DEBUG
        return putchar(c), void();
#endif
        if (P1 != P2) *P1++ = c;
        else { fwrite(Buf, P1 - Buf, 1, stdout); P1 = Buf; *P1++ = c; }
    }
    void readstr(char *s, bool fg = 0) { // fg=1 for getline
        char ch = gc();
        while (ch == '\n' || ch == '\r' || (!fg && ch == ' ')) ch = gc();
        while (ch != '\n' && ch != '\r' && (fg || ch != ' ')) *s++ = ch, ch = gc();
        *s = '\0';
    }
    void writestr(const char *s, char ch = '\0') { for (const char *p = s; *p; ++p) pc(*p); (ch != '\0') &&(pc(ch), 1); }
    template <typename _Tp>	void read(_Tp &x) {
        x = 0; char ch = gc(); int f = 0;
        while (ch < '0' || ch > '9') { (ch == '-') &&(f ^= 1); ch = gc(); }
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (_Tp)(ch ^ 48), ch = gc();
        f &&(x = -x);
    }
    template<typename Tp, typename... Args>void read(Tp &t, Args &... args) { read(t); read(args...); }
    template<typename Tp> void write(Tp x, char ch = '\n') {
        static int buf[100], d;
        if (x == 0)  pc('0');
        else {
            if (x < 0)  pc('-'), x = -x;
            for (d = 0; x; x /= 10)  buf[++d] = x % 10 + 48;
            while (d) pc((char)buf[d--]);
        }
        if (ch != '\0') pc(ch);
    }
    template <typename Tp, typename... Args> void write(Tp x, Args ...args) { write(x, ' '); write(args...); }
    void flush() { fwrite(Buf, P1 - Buf, 1, stdout); P1 = Buf; }
    struct _flusher {
        ~_flusher() { flush(); }
    } flusher;
}
using IO::read; using IO::write; using IO::readstr; using IO::writestr;

int main() {
    return 0;
}

```

---

[**Go Back**](./)
