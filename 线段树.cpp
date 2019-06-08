#include <bits/stdc++.h>
using namespace std;
const int N=100000;
int n,m,a[N];
int sum[N<<2],add[N<<2];
void pushup(int x);
void pushdown(int x,int l,int r,int m);
void build(int x,int l,int r) {
	if(l==r) {
		sum[x]=a[l];
		return ;
	}
	int m=(l+r)>>1;
	build(x<<1,l,m);
	build(x<<1|1,m+1,r);
	pushup(x);
}
void init() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	build(1,1,n);
}
void pushup(int x) {
	sum[x]=sum[x<<1]+sum[x<<1|1];
}
void modify(int L,int R,int val,int x,int l,int r) {
	if(L<=l&&r<=R) {
		sum[x]+=val*(r-l+1);
		add[x]+=val;
		return ;
	}
	int m=(l+r)>>1;
	pushdown(x,l,r,m);
	if(L<=m) {
		modify(L,R,val,x<<1,l,m);
	}
	if(R>m) {
		modify(L,R,val,x<<1|1,m+1,r);
	}
	pushup(x);
}
int query(int L,int R,int x,int l,int r) {
	if(L<=l&&r<=R) {
		return sum[x];
	}
	int m=(l+r)>>1;
	pushdown(x,l,r,m);
	int ret=0;
	if(L<=m) {
		ret+=query(L,R,x<<1,l,m);
	}
	if(R>m) {
		ret+=query(L,R,x<<1|1,m+1,r);
	}
	return ret;
}
void pushdown(int x,int l,int r,int m) {
	
	add[x<<1]+=add[x];
	sum[x<<1]+=add[x]*(m-l+1);
	add[x<<1|1]+=add[x];
	sum[x<<1|1]+=add[x]*(r-m);
	add[x]=0;
}
int main() {
	init();
	while(m--) {
		int op,x,y,k;
		scanf("%d",&op);
		if(op==1) {
			scanf("%d%d%d",&x,&y,&k);
			modify(x,y,k,1,1,n);
		}
		if(op==2) {
			scanf("%d%d",&x,&y);
			cout<<query(x,y,1,1,n)<<endl;
		}
	}
}
