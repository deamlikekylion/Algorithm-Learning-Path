#include<bits/stdc++.h>
using namespace std;

const int N=5e5+5;
long double sum,aver,num,ans,a[N];  //注意该题要用long double,后面平方和double会溢出
int n;

int main(){
    cin>>n>>sum;  aver=sum/(long double)n;  //除以n记得把n转换成long double类型
    for(int i=1;i<=n;i++)  cin>>a[i];
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++){
        num=min(a[i],sum/(long double)(n-i+1));
        sum-=num;  ans+=(num-aver)*(num-aver);
    }
    ans=sqrt(ans/(long double)n);
    printf("%.4Lf",ans);  //注意long double用%Lf(L大写),double:%f,int:%d
    return 0;
}