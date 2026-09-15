#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N=2e5+5;
ll n,m,s,y,ans;
ll w[N],v[N],l[N],r[N],a[N],b[N];  
//a:重量≥W的矿石数量的前缀和,b:重量≥W的矿石价值的前缀和

bool check(int mid){
    y=0;                       //初始化当前检验结果总和为0
    memset(a,0,sizeof(a));     //重置前缀和数组
    memset(b,0,sizeof(b));
    for(int i=1;i<=n;i++){     //遍历所有矿石,预处理前缀和
        if(w[i]>=mid){         //若矿石重量≥W
            a[i]=a[i-1]+1;     //重量≥W的数量加1
            b[i]=b[i-1]+v[i];  //重量≥W的价值和累加
        }else{
            a[i]=a[i-1];       //继承前一个前缀和
            b[i]=b[i-1];
        }
    }
    for(int i=1;i<=m;i++){     //遍历每个区间,计算每个区间的检验值累加到y
        int lt=l[i],rt=r[i];
        y+=(a[rt]-a[lt-1])*(b[rt]-b[lt-1]);
    }
    if(y>s)  return true;
    else  return false;
}

int main(){
    cin>>n>>m>>s;
    for(int i=1;i<=n;i++)  cin>>w[i]>>v[i];
    for(int i=1;i<=m;i++)  cin>>l[i]>>r[i];
    int ll=1,rr=1e6;  ans=s;      //ll,rr初始化w的上下界,ans初始化s
    while(ll<=rr){                //二分循环,寻找使|s-y|最小的W
        int mid=(ll+rr)/2;
        if(check(mid))  ll=mid+1;
        else  rr=mid-1;
        ans=min(ans,llabs(y-s));  //每次比较完后更新ans,用llabs处理长整型的绝对值
    }
    cout<<ans<<endl;          
    return 0;
}