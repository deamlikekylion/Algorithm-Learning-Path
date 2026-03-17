#include<bits/stdc++.h>
using namespace std;

const double PI=acos(-1);

bool cmp(pair<double,double> a,pair<double,double> b){
    return a.first<b.first;
}

int main(){
    int n;  cin>>n;
    vector< pair<double,double> > k;
    while(n--){
        int x,y,r;  cin>>x>>y>>r;
        double ang1=atan(y/x);
        double d=sqrt(x*x+y*y);
        double ang2=asin(r/d);
        double L=ang1-ang2;
        double R=ang1+ang2;
        L=max(L,0.0);  R=min(R,PI/2);
        if(L<R)  k.push_back({L,R});
    }
    sort(k.begin(),k.end(),cmp);
    vector< pair<double,double> > m;
    for(auto i : k){
        if(m.empty())  m.push_back(i);
        else{
            auto& j=m.back();
            if(i.first<=j.second)  j.second=max(i.second,j.second);
            else  m.push_back(i);
        }
    }

    return 0;
}