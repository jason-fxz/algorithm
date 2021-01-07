/*
	luogu - P2495 [SDOI2011]消耗战
	虚树板子，建树看 build()
	Oi-wiki(虚树) --> https://oi-wiki.org/graph/virtual-tree/
*/
#include <bits/stdc++.h>
using namespace std;
template <typename T>
inline void red(T &x) {
    x=0;bool f=0;char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f^=1; ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(T)(ch^48),ch=getchar();
    if(f) x=-x;
}
const int N = 300000;
const int inf = 0x3f3f3f3f;
typedef long long ll;
int head[N],pnt[N<<1],nxt[N<<1],wth[N<<1],E;
int dfn[N],tim,h[N],K;
int n,Q,fa[N],deg[N],W[N],ty[N];
ll Dp[N];
namespace LCA {
	int siz[N],son[N],top[N],fa[N],dep[N];
	void dfs1(int u,int f,int d) {
		fa[u]=f; dep[u]=d; siz[u]=1;
		for(int i=head[u];i;i=nxt[i]) {
			int v=pnt[i];
			if(v==f) continue;
			dfs1(v,u,d+1); siz[u]+=siz[v]; 
			if(siz[son[u]]<siz[v]) son[u]=v; 
		}
	}
	void dfs2(int u,int topf) {
		top[u]=topf;
		if(son[u]) dfs2(son[u],topf);
		for(int i=head[u];i;i=nxt[i]) {
			int v=pnt[i];
			if(v==son[u]||v==fa[u]) continue;
			dfs2(v,v);
		}
	}
	int lca(int u,int v) {
		int fu=top[u],fv=top[v];
		while(fu!=fv) {
			if(dep[fu]<dep[fv]) swap(fu,fv),swap(u,v);
			u=fa[fu]; fu=top[u];
		}
		return (dep[u]<dep[v])?u:v;
	}
}
using LCA::lca;
void adde(int u,int v,int w) {
	E++;pnt[E]=v;nxt[E]=head[u];wth[E]=w;head[u]=E;
}
bool cmp(int x,int y) {	return dfn[x]<dfn[y];}
void dfs(int u,int f) {
	dfn[u]=++tim;
	for(int i=head[u];i;i=nxt[i]) {
		int v=pnt[i];
		if(v==f) continue;
		W[v]=min(W[u],wth[i]);
		dfs(v,u);
	}
}
// begin : build virtual tree 
int st[N],top,b[N],tot; // b[1:tot] are the nodes in virtual tree 
void build() {
	sort(h+1,h+K+1,cmp);
	st[top=1]=1; deg[1]=fa[1]=0; b[tot=1]=1;
	for(int i=1;i<=K;++i){
		if(h[i]==1) continue;
		int lc=lca(h[i],st[top]);
		if(lc!=st[top]) {
			while(dfn[lc]<dfn[st[top-1]]) {
				fa[st[top]]=st[top-1];
				++deg[st[top-1]];
				top--;
			}
			if(dfn[lc]>dfn[st[top-1]]) {
				fa[st[top]]=lc; deg[lc]=1; 
				fa[lc]=0,st[top]=lc; b[++tot]=lc;
			}
			else{
				fa[st[top--]]=lc; ++deg[lc];
			} 
		}
		st[++top]=h[i]; b[++tot]=h[i];
		deg[h[i]]=fa[h[i]]=0;
	}
	for(int i=2;i<=top;++i) fa[st[i]]=st[i-1],++deg[st[i-1]];
}
// end build
ll solve() {
	queue<int> q;
	for(int i=1;i<=tot;++i) {
		Dp[b[i]]=0;
		if(deg[b[i]]==0) q.push(b[i]);
	}
	while(!q.empty()) {
		int u=q.front(); q.pop();
		if(u==1) break;
		if(ty[u]) Dp[fa[u]]+=W[u];
		else Dp[fa[u]]+=min((ll)W[u],Dp[u]);
		--deg[fa[u]];
		if(deg[fa[u]]==0) q.push(fa[u]);
	}
	return Dp[1];
}
int main() {
	red(n);
	for(int i=1;i<n;++i) {
		int u,v,w;red(u);red(v);red(w);
		adde(u,v,w);adde(v,u,w);
	}
	W[1]=inf;
	dfs(1,0);
	LCA::dfs1(1,0,0);LCA::dfs2(1,1);
	red(Q);
	while(Q--) {
		red(K);
		for(int i=1;i<=K;++i) red(h[i]),ty[h[i]]=1;
		build();
		ll ans=solve();
		printf("%lld\n",ans);
		for(int i=1;i<=K;++i) ty[h[i]]=0;
	}
}