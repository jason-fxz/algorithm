/*
	luogu P4357 [CQOI2016]K 远点对
 	K-D Tree 二维平面邻域查询
	题意：平面上 N (1e5) 个点，求第 K (1e2) 远点对距离
*/
#include <bits/stdc++.h>
template <typename T>
inline void red(T &x) {
    x=0;bool f=0;char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f^=1; ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(T)(ch^48),ch=getchar();
    if(f) x=-x;
}
using namespace std;
typedef double db;
typedef long long ll;
const int N = 100010;
int n,k;
priority_queue<ll,vector<ll>,greater<ll> >q;
template <typename _Tp> inline void umin(_Tp &x,_Tp y) {(x>y)&&(x=y);}
template <typename _Tp> inline void umax(_Tp &x,_Tp y) {(x<y)&&(x=y);}
namespace KDTree {
	struct node {
		int X[2];
		int &operator[](const int k) {return X[k];}
	}p[N];
	int nowd;
	bool cmp(node a,node b) {return a.X[nowd]<b.X[nowd];}
	int lc[N],rc[N],L[N][2],R[N][2]; // lc/rc 左右孩子；L/R 对应超矩形各个维度范围
	inline ll sqr(int x) {return 1ll*x*x;}
	void pushup(int x) { // 更新该点所代表空间范围
		L[x][0]=R[x][0]=p[x][0];
		L[x][1]=R[x][1]=p[x][1];
		if(lc[x]) {
			umin(L[x][0],L[lc[x]][0]); umax(R[x][0],R[lc[x]][0]);
			umin(L[x][1],L[lc[x]][1]); umax(R[x][1],R[lc[x]][1]);
		}
		if(rc[x]) {
			umin(L[x][0],L[rc[x]][0]); umax(R[x][0],R[rc[x]][0]);
			umin(L[x][1],L[rc[x]][1]); umax(R[x][1],R[rc[x]][1]);
		}
	}
	int build(int l,int r) {
		if(l>r) return 0;
		int mid=(l+r)>>1;
		// >>> 方差建树
		db av[2]={0,0},va[2]={0,0}; // av 平均数，va 方差  
		for(int i=l;i<=r;++i) av[0]+=p[i][0],av[1]+=p[i][1];
		av[0]/=(r-l+1); av[1]/=(r-l+1);
		for(int i=l;i<=r;++i) {
			va[0]+=sqr(av[0]-p[i][0]);
			va[1]+=sqr(av[1]-p[i][1]);
		}
		if(va[0]>va[1]) nowd=0; else nowd=1; // 找方差大的维度划分 
		// >>> 轮换建树 nowd=dep%D 
		nth_element(p+l,p+mid,p+r+1,cmp); // 以该维度中位数分割
		lc[mid]=build(l,mid-1); rc[mid]=build(mid+1,r);
		pushup(mid);
		return mid;
	}
	ll dist(int a,int x) { // 估价函数，点 a 到树上 x 点对应空间最远距离
		return max(sqr(p[a][0]-L[x][0]),sqr(p[a][0]-R[x][0]))+
		       max(sqr(p[a][1]-L[x][1]),sqr(p[a][1]-R[x][1]));
	}
	void query(int l,int r,int a) { // 点 a 邻域查询
		if(l>r) return ;
		int mid=(l+r)>>1;
		ll t=sqr(p[mid][0]-p[a][0])+sqr(p[mid][1]-p[a][1]);
		if(t>q.top()) q.pop(),q.push(t); // 更新答案
		ll disl=dist(a,lc[mid]),disr=dist(a,rc[mid]);
		if(disl>q.top()&&disr>q.top()) { // 两边都有机会更新，优先搜大的
			(disl>disr)?(query(l,mid-1,a),query(mid+1,r,a)):(query(mid+1,r,a),query(l,mid-1,a));
		}else {
			(disl>q.top())?query(l,mid-1,a):query(mid+1,r,a);
		}
	}
}
using namespace KDTree;
int main() {
	red(n);red(k);k*=2;
	for(int i=1;i<=k;++i) q.push(0);
	for(int i=1;i<=n;++i) red(p[i][0]),red(p[i][1]);
	build(1,n);
	for(int i=1;i<=n;++i) query(1,n,i);
	printf("%lld\n",q.top());
}