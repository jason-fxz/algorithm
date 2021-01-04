#include <bits/stdc++.h>
#define il inline
using namespace std;
typedef double db;
const db eps = 1e-8;
il int sign(const db &num) {return (num>eps)-(num<-eps);} // 判断符号，为正则 1 为负则 -1 为零则零
il int cmp(const db &a,const db &b) {return sign(a-b);} // 比较大小 
struct vec { // Vector & Point
	db x,y;
	void input() {scanf("%lf%lf",&x,&y);}
	vec(const db &_x=0,const db &_y=0):x(_x),y(_y) {}
	il vec operator+(const vec &v) const {return vec(x+v.x,y+v.y);}
	il vec operator-(const vec &v) const {return vec(x-v.x,y-v.y);}
	il vec operator*(const db &a) const {return vec(x*a,y*a);}
	il vec operator/(const db &a) const {return vec(x/a,y/a);}
	il db len2() const {return x*x+y*y;}
	il db len() const {return hypot(x,y);} // 模长
	il vec turnc(db r) const {db l=len(); if(!sign(l)) return *this; r/=l; return (*this)*r;} // 改变长度 
	bool operator<(const vec t) const {return (cmp(x,t.x)==0)?(cmp(y,t.y)<0):(cmp(x,t.x)<0);}
	bool operator==(const vec t) const {return cmp(x,t.x)==0&&cmp(y,t.y)==0;}
};
typedef vec poi;
il db dot(const vec &a,const vec &b) {return a.x*b.x+a.y*b.y;} // 点积
il db crs(const vec &a,const vec &b) {return a.x*b.y-a.y*b.x;} // 叉积
il db dis(const poi &a,const poi &b) {return (b-a).len();}
vector<poi> pts,pois; int n;

poi O;
bool cmpv(poi a,poi b) {
	int k=sign(crs(a-O,b-O));
	return (k==0)?((a-O).len2()<(b-O).len2()):(k>0);
}
int relat(const poi &a,const poi &b,const poi &c) { // 三点关系
	return sign(crs(b-a,c-b));
}
void Graham(vector<poi> pt,vector<poi> &res) { // Graham 求凸包 (极角排序+单调栈)
	res.clear();
	for(int i=1;i<(int)pt.size();++i) if(pt[i]<pt[0]) swap(pt[i],pt[0]);
	O=pt[0];
	sort(pt.begin()+1,pt.end(),cmpv);
	for(int i=0;i<(int)pt.size();++i) {
		while(res.size()>=2&&relat(res[res.size()-2],res[res.size()-1],pt[i])<=0) res.pop_back();
		res.push_back(pt[i]);
	}
}
int main() {
	scanf("%d",&n);
	pts.resize(n);
	for(int i=0;i<n;++i) pts[i].input();
	Graham(pts,pois);
	db C=0;
	for(int i=0;i<(int)pois.size();++i) {
		if(i!=0) C+=dis(pois[i-1],pois[i]);
		else C+=dis(pois[0],pois.back());
	}
	printf("%.2lf\n",C);
}