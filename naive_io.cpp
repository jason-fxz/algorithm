#include <cstdio>
using namespace std;
const int N = 10000000;
long long a[N];
int main() {
    for(int i=0;i<N;i++) scanf("%d",&a[i]);
    for(int i=0;i<N;i++) printf("%lld\n",a[i]);
    return 0;
}