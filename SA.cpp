/*
    后缀数组 (SA)
    O(nlogn) 倍增做法，外加求 height 数组
    Oi-wiki(后缀数组 ) --> https://oi-wiki.org/string/sa/
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1000010;
typedef long long ll;
int x[N],y[N],sa[N],c[N],rk[N],height[N];
char s[N];
int n,m; 
void getSA() {
    for(int i=1;i<=n;++i) ++c[x[i]=s[i]];
    for(int i=2;i<=m;++i) c[i]+=c[i-1];
    for(int i=n;i>=1;--i) sa[c[x[i]]--]=i;
    for(int k=1;k<=n;k<<=1) {
        int num=0;
        for(int i=n-k+1;i<=n;++i) y[++num]=i;
        for(int i=1;i<=n;++i) if(sa[i]>k) y[++num]=sa[i]-k;
        for(int i=1;i<=m;++i) c[i]=0;
        for(int i=1;i<=n;++i) ++c[x[i]];
        for(int i=2;i<=m;++i) c[i]+=c[i-1];
        for(int i=n;i>=1;--i) sa[c[x[y[i]]]--]=y[i],y[i]=0;
        swap(x,y);
        x[sa[1]]=1;num=1;
        for(int i=2;i<=n;++i){
            x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?num:++num;
        }
        if(num==n) break;
        m=num;
    }
}
void getheight() {
    int k=0;
    for(int i=1;i<=n;++i) rk[sa[i]]=i;
    for(int i=1;i<=n;++i)if(rk[i]!=1) {
        if(k>0) --k;
        int j=sa[rk[i]-1];
        while(j+k<=n&&i+k<=n&&s[i+k]==s[j+k]) ++k;
        height[rk[i]]=k;
    }
}
int main() {
    scanf("%s",s+1);
    n=strlen(s+1);m='z';
    getSA();
    // getheight();
    for(int i=1;i<=n;++i) {
        printf("%d ",sa[i]);
    }printf("\n");
}