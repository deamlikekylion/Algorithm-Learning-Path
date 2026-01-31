#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N=4e6+5;
int n,m,k[10],p[10],a[N],b[N],cnta,cntb,ans;
//a存储前半部分所有可能的和,b存储后半部分所有可能的和
//cnta,cntb是对应数组的元素个数,ans是最终解的个数

int qpow(int x,int p){    //快速幂计算x的p次方(离散数学学过)
    int res=1;
    while(p>0){
        if(p&1)  res*=x;  //如果当前二进制位是1,将当前底数乘入结果
        x*=x;  p>>=1;
    }
    return res;
}

//dfs:枚举区间[l,r]内未知数的所有可能取值,生成所有可能的和存入arr数组
//l,r:当前枚举的未知数区间;sum:当前枚举的和;arr:存储结果的数组;cnt:arr的元素计数
//arr用*可直接复制到a,b数组;cnt用&可直接修改cnta,cntb
void dfs(int l,int r,int sum,int *arr,int &cnt){
    if(l>r){
        arr[++cnt]=sum;  return;  //区间枚举完毕,将当前和存入数组
    } 
    for(int i=1;i<=m;i++)  dfs(l+1,r,sum+k[l]*qpow(i,p[l]),arr,cnt);
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)  cin>>k[i]>>p[i];
    int mid=(1+n)/2;
    dfs(1,mid,0,a,cnta);  dfs(mid+1,n,0,b,cntb);  //进行折半搜索
    sort(a+1,a+cnta+1);  sort(b+1,b+cntb+1);      //排序便于后续查找
    int r=cntb;  
    for(int l=1;l<=cnta&&r>=1;l++){     //双指针法统计"前半和+后半和=0"的组合数
        while(r>=1&&a[l]+b[r]>0)  r--;  //找到最大的r使得a[l]+b[r]<=0
        if(r<1)  break;                 //后半和已全部大于-a[l],无需继续
        int y=0;                        //统计b中等于-a[l]的元素个数
        for(int j=r;j>=1&&a[l]+b[j]==0;j--)  y++;
        if(y==0)  continue;             //没有匹配的后半和,跳过
        int x=1;                        //统计a中与a[l]相同的元素个数
        while(l<cnta&&a[l]==a[l+1])  x++,l++;
        ans+=x*y;                       //累计到ans
    }
    cout<<ans;
    return 0;
}