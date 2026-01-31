#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5;

int main(){
    ll n,a[N],ave=0,c[N],x1,xsum,ans;  cin>>n;  
    //ave为a的平均数,x1为1号小朋友该向左传的糖果数
    //xsum为所有小朋友该向左传的糖果总数即ans
    //c[i]为a[1]到a[i]的和减去i*ave
    for(int i=1;i<=n;i++)  cin>>a[i],ave+=a[i];
    ave/=n;  c[0]=0; 
    for(int i=1;i<=n-1;i++)  c[i]=c[i-1]+a[i]-ave;
    sort(c+1,c+n);  x1=c[(1+n)/2];  xsum=abs(x1);
    //x1为c的中位数,xsum为x1+求和x1-c[i](i从1到n-1)  
    for(int i=1;i<=n-1;i++)  xsum+=abs(x1-c[i]);
    ans=xsum;  cout<<ans;
    return 0;
}