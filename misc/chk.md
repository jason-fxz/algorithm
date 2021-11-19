
# chk.cpp | MISC | OI Algorithm

[**Go Back**](./)

---

```cpp
#include <windows.h>
#include <cstdio>
#include <string>
#include <cstring>
#include <ctime>
using namespace std;
string tmp;

int st;
void setclock() {st = clock();}
int getclock() {return clock() - st;}

int ifcpl = 1, test_times = 1e9;
string comd = "-std=c++11 -Wall -O2";

void PrintHelp() {
    printf("Uesge:\n");
    printf("\tchk <std.cpp> <test.cpp> <mker.cpp> [-t (test-times)] [-q | -c <commond>]\n");
    printf("-t (test-times) : run test for (test-times) times\n");
    printf("-q              : without compile\n");
    printf("-c <commond>    : commonds for compile\n");
    exit(1);
}
void Genarg(int argc, char const *argv[]) {
    if (argc < 4) PrintHelp();
    for (int i = 4; i < argc; ++i) {
        if (strcmp(argv[i], "-q") == 0) ifcpl = 0;
        else if (strcmp(argv[i], "-t") == 0) {
            ++i;
            if (i >= argc) PrintHelp();
            test_times = atoi(argv[i]);
        } else if (strcmp(argv[i], "-c") == 0) {
            ++i;
            if (i >= argc) PrintHelp();
            comd = argv[i];
        } else PrintHelp();
    }
}

int main(int argc, char const *argv[]) {
    Genarg(argc, argv);
    printf("total: %d test\n", test_times);
    if (ifcpl) {
        int fg = 0;
        printf("building...\n");
        tmp = "g++ " + string(argv[1]) + " -o .std " + comd; fg |= system(tmp.c_str());
        tmp = "g++ " + string(argv[2]) + " -o .tst " + comd; fg |= system(tmp.c_str());
        tmp = "g++ " + string(argv[3]) + " -o .mk " + comd; fg |= system(tmp.c_str());
        if (fg) {
            printf("complie error!\n");
            return 2;
        } else
            printf("completed!\n");
    }
    for (int t = 1; t <= test_times; ++t) {
        printf("test #%d\n", t);
        system(".mk > .in.txt");
        int Tstd, Ttst;
        setclock(); system(".std < .in.txt > .ans.txt"); Tstd = getclock(); printf("std: %dms ", Tstd);
        setclock(); system(".tst < .in.txt > .out.txt"); Ttst = getclock(); printf("tst: %dms\n", Ttst);
        if (system("fc .ans.txt .out.txt")) {
            printf("Wrong Answer !\n");
            getchar();
        }
    }
    return 0;
}


```

---

[**Go Back**](./)
