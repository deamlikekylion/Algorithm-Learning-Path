#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,c,a[55],b[55],sum[55],f[55][55][2];  
    //动态规划状态数组:f[i][j][0/1]:关闭区间[i,j]内所有灯的最小总耗电量
    //0:关闭[i,j]后,人在左端点i的位置;1:关闭[i,j]后,人在右端点j的位置
    cin>>n>>c;  sum[0]=0;  memset(f,127,sizeof(f));
    //初始化f为极大值,后续用min函数更新时,确保未计算的状态不影响结果
    //(memset(127):int类型赋值为0x7f7f7f7f,接近INT_MAX
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];  sum[i]=sum[i-1]+b[i];  //sum为b的前缀和
    }
    f[c][c][0]=f[c][c][1]=0;  //c处出门就关(c,i,j均为路灯序号)
    for(int l=1;l<=n-1;l++){  //枚举区间间隔从1到n
        for(int i=1;i+l<=n;i++){
            int j=i+l;
            f[i][j][0]=min(
                f[i+1][j][0]+(a[i+1]-a[i])*(sum[i]+sum[n]-sum[j]),  //从i+1走到i
                f[i+1][j][1]+(a[j]-a[i])*(sum[i]+sum[n]-sum[j])  //从j走到i
            );
            f[i][j][1]=min(
                f[i][j-1][0]+(a[j]-a[i])*(sum[i-1]+sum[n]-sum[j-1]),  //从i走到j
                f[i][j-1][1]+(a[j]-a[j-1])*(sum[i-1]+sum[n]-sum[j-1])  //从j-1走到j
            );
            //开始除了和f[c][c]相关的之外算完还是INF
        }
    }
    int ans=min(f[1][n][0],f[1][n][1]);
    cout<<ans;
    return 0;
}