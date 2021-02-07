/*
	PAM 回文自动机 / 回文树 
	luogu P5496 【模板】回文自动机（PAM）
	Oi-wiki -->	https://oi-wiki.org/string/pam/	
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 500010;
namespace PAM {
	int sz,tot,lst;  // sz:状态数量 tot:字符串长度 lst:上次状态
	int cnt[N],sum[N],ch[N][26],len[N],fail[N]; // cnt:该状态对应原串中出现次数
	// fail 指针跳到该串最长后缀回文，sum 记录跳几次跳完
	char s[N];
	int newnode(int l) {
		++sz; memset(ch[sz],0,sizeof(ch[sz]));
		len[sz]=l; fail[sz]=cnt[sz]=sum[sz]=0;
		return sz;
	}
	void init() {
		sz=-1; lst=0; s[tot=0]='$';
		newnode(0); newnode(-1); fail[0]=1;
	}
	int getfail(int x) {
		while(s[tot-len[x]-1]!=s[tot]) x=fail[x];
		return x;
	}
	void insert(char c) {
		s[++tot]=c;
		int cur=getfail(lst);
		if(!ch[cur][c-'a']) {
			int now=newnode(len[cur]+2);
			fail[now]=ch[getfail(fail[cur])][c-'a'];
			ch[cur][c-'a']=now;
			sum[now]=sum[fail[now]]+1;
		}
		++cnt[lst];
		lst=ch[cur][c-'a'];
	}
	void calc() {for(int i=sz;i>=0;--i) cnt[fail[i]]+=cnt[i];} // 计算每个状态出现次数 
}
char str[N];
int k;
int main() {
	scanf("%s",str);
	PAM::init();
	for(char *ps=str;*ps;++ps) {
		*ps=(*ps-97+k)%26+97;
		PAM::insert(*ps);
		k=PAM::sum[PAM::lst]; // 以 ps 位为结尾的回文串数量
		printf("%d ",k);
	}
	printf("\n");
	return 0;
}