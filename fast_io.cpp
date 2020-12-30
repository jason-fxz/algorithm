#include <cstdio>

namespace IO {
	const int MAX = 1<<20;
	char buf[MAX],Buf[MAX],*p1=buf,*p2=buf,*P1=Buf,*P2=Buf+MAX;
	inline char gc() {
		if(p1!=p2) return *p1++;
		p1=buf;p2=p1+fread(buf,1,MAX,stdin); return (p1==p2)?(EOF):(*p1++);
	}
	inline void pc(const char c) {
		if(P1!=P2) *P1++=c; 
		else {fwrite(Buf,P1-Buf,1,stdout); P1=Buf; *P1++=c;}
	}
	void readstr(char *s,bool fg=0) { // fg=1 for getline
		char ch=gc();
		while(ch=='\n'||(!fg&&ch==' ')) ch=gc();
		while(ch!='\n'&&(fg||ch!=' ')) *s++=ch,ch=gc();
		*s='\0';
	}
	void writestr(const char *s,char ch='\0') {for(const char *p=s;*p;++p) pc(*p);(ch!='\0')&&(pc(ch),1);}
	template <typename _Tp>	void read(_Tp &x) {
		x=0;char ch=gc();int f=0;
		while(ch<'0'||ch>'9') {(ch=='-')&&(f^=1); ch=gc();}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(_Tp)(ch^48),ch=gc();
		f&&(x=-x);
	}
	template <typename _Tp> void write(_Tp x,char ch='\0') {
		(x<0)&&(x=-x,pc('-'),1); 
		if(x>(_Tp)10) write(x/10);
		pc(x%10+'0'); (ch!='\0')&&(pc(ch),1);
	}
	void close() {fwrite(Buf,P1-Buf,1,stdout);} 
}
using IO::read; using IO::write; using IO::readstr; using IO::writestr;

int main() {
	
	IO::close();
	return 0;
}
