#include <bits/stdc++.h>

#ifndef DEBUGER
#define DEBUGER

#define see(a) cerr<<#a<<" = "<<a<<" "
#define seeln(a) cerr<<#a<<" = "<<a<<endl
#define put(a) cerr<<a
#define outarr(_a,_l,_r) for(int _i=(_l);_i<=(_r);_i++) cerr<<#_a"["<<_i<<"]="<<_a[_i]<<" ";cerr<<endl;
#define Outarr(_a,_l,_r) cerr<<#_a<<" ["<<_l<<", "<<_r<<"] : "; for(int i=(_l);i<=(_r);++i) cerr<<_a[i]<<" ";cerr<<endl;
#define out(a) cerr<<a<<" "
#define outln(a) cerr<<a<<endl

using namespace std;

template<typename Tp> 
ostream &operator<<(ostream &out, vector<Tp> vt) {
    out << "vector of size = "<< vt.size() << " : { " ;
    for(size_t i=0;i<vt.size();++i) out << vt[i] << ", ";
    return out << "} ";
}
template<typename Tp> 
istream &operator>>(istream &in, vector<Tp> &vt) {
    for(size_t i=0;i<vt.size();++i) in >> vt[i];
    return in;
}
template<typename Tp>
ostream &operator<<(ostream &out, set<Tp> st) {
    out << "set of size = "<< st.size() << " : { " ;
    for(auto it=st.begin();it!=st.end();++it) out << *it << ", ";
    return out << "} ";
}
template<typename Tp1, typename Tp2>
ostream &operator<<(ostream &out, map<Tp1, Tp2> mp) {
    out << "map of size = "<< mp.size() << " : { " ;
    for(auto it=mp.begin();it!=mp.end();++it) 
        out << "\"" << it->first << "\": " << it->second << ", ";
    return out << "} ";
}
template<typename Tp1, typename Tp2> 
ostream &operator<<(ostream &out, pair<Tp1, Tp2> P) {
    return out << "(" << P.first << ", " << P.second << ")";
}

#endif
