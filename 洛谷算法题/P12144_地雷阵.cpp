#include<bits/stdc++.h>
using namespace std;

const double PI=acos(-1);  //取弧度制的PI值,即180度

bool cmp(pair<double,double> &a,pair<double,double> &b){
//const &:引用原数据不用拷贝提高了效率,且只读原数据不会被修改
    return a.first<b.first;
}

int main(){
    int n;  cin>>n;
    vector< pair<double,double> > k;  
    //k[i]={L,R},L和R为第i个圆与原点相切的两条线与x轴正方向的夹角
    while(n--){
        int x,y,r;  cin>>x>>y>>r;
        double ang1=atan2(y,x);         //ang1为过原点和圆心的线与x轴的夹角,值为弧度制
        double d=sqrt(x*x+y*y);         //d为圆心和原点的距离
        double ang2=asin(r/d);          //ang2为相切线与过原点圆心线的夹角
        double L=ang1-ang2;
        double R=ang1+ang2;
        L=max(L,0.0);  R=min(R,PI/2);   //限制在第一象限
        if(L<R)  k.emplace_back(L,R);
        //emplace_back不用加大括号,push_back({L,R})要加大括号
        //且emplace直接在末尾创建,push要拷贝,对于pair等类型的emplace比push快一点
        //后面的所有push都可以换成emplace但没有啥区别
    }
    sort(k.begin(),k.end(),cmp);        //按L的大小升序排序
    vector< pair<double,double> > m;    //将k中重叠的区间合并后加入k
    for(auto &i : k){                   //遍历k,此处可用&也可以不用,用避免拷贝提高效率
        if(m.empty())  m.push_back(i);  //开始m为空,直接加入第一个k中的区间
        else{
            auto& j=m.back();           
            //取m的最后一个,也就是当前i的上一个,j与i相邻,可能重叠
            //此处必须用&:引用不用拷贝效率高,且可以直接修改原数据,后面j要修改所以必须要用&                            
            if(i.first<=j.second)  j.second=max(i.second,j.second);
            //L<R,j<i,所以不重叠则j.R<i.L,重叠则j.R>=i.L(i.first<=j.second)
            else  m.push_back(i);       //不重叠则直接加入m
        }
    }
    double danger=0.0;
    for(auto &i : m)  danger+=i.second-i.first;
    double safe=PI/2-danger;
    double ans=safe/(PI/2);
    printf("%.3f",ans);                 //ans为double类型用%f,%.3f表示保留三位小数(int用%d)
    return 0;
}