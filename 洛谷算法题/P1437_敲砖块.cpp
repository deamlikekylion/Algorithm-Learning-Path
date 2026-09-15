#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,m,a[55][55],sum[55][55],dp[55][55][1300];
    //dp[i][j][k]表示第j列中被敲掉的砖最大行号为i,且一共敲了k个砖(即(i,j)一定被敲了)
    //sum[i][j]表示a[1][j]到a[i][j]的和
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n-i+1;j++){
            cin>>a[i][j];
        } 
    }
    for(int j=1;j<=n;j++){
        for(int i=1;i<=n-j+1;i++){  //第j列的最大行号为n-j+1(eg:第n列只有第1行)
            sum[i][j]=sum[i-1][j]+a[i][j];
        }  
    }
    for(int j=1;j<=n;j++){  //按列从左往右推
        for(int i=0;i<=n-j+1;i++){  //行从上往下
            for(int k=i;k<=m;k++){  //第i行最少消耗i个(i及i以上),所以k从i开始
                for(int t=0;t<=i+1;t++){  //对于状态(i,j),所有满足0≤t≤i+1的状态(t,j−1)均可转移
                                          //可能转移的条件为(t,j-1)可以与(i,j)构成三角形轮廓
                    dp[i][j][k]=max(dp[i][j][k],dp[t][j-1][k-i]+sum[i][j]);
                    //转移即敲(i,j)及其以上的砖,所以转移前消耗为k-i,转移后加上sum[i][j]即可
                }
            }
        }
    }
    int  ans=max(dp[0][n][m],dp[1][n][m]);  
    //按列从左往右推所以最后一个处理的为dp[1][n][m]((1,n)被敲了)
    //和dp[0][n][m]((0,n)被敲即(1,n)不敲)取最大
    cout<<ans;
    return 0;
}