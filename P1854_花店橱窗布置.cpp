#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;

int main(){
    int f,v,a[105][105],dp[105][105];  //dp[i][j]表示第i只花放或不放在第j个花瓶的最大美学
    pair<int,int> pre[105][105];
    cin>>f>>v;
    for(int i=1;i<=f;i++){
        for(int j=1;j<=v;j++){
            cin>>a[i][j];
        }  
    }
    for(int i=0;i<=f;i++){  //注意此处i,j从0开始,dp[1][j]要从dp[0][j]转移
        for(int j=0;j<=v;j++){
            dp[i][j]=-INF;  //初始化最小值
        }
    }
    for(int j=0;j<=v;j++)  dp[0][j]=0;  //i=0,dp[0][j]=0;
    for(int i=1;i<=f;i++){
        for(int j=i;j<=v;j++){  //dp[i][j]表示i只花放在1到j花瓶中的最大美学,所以j>=i
            int t1=dp[i-1][j-1]+a[i][j];  //第i只花放在第j个花瓶,由dp[i-1][j-1]转移
            int t2=dp[i][j-1];  //第i只花不放在第j个花瓶,则放在1到j-1个花瓶中,有dp[i][j-1]转移
            if(t1>=t2){
                dp[i][j]=t1;
                pre[i][j]={i-1,j-1};  //记录前驱
            }else{
                dp[i][j]=t2;
                pre[i][j]={i,j-1};
            }
        }
    }
    cout<<dp[f][v]<<endl;
    int path[f+5];
    for(int i=f,j=v;i>0;){
        int prei=pre[i][j].first,prej=pre[i][j].second;
        if(prei==i-1)  path[i]=j;  //前驱为i-1,选了a[i][j]
        i=prei,j=prej;
    }
    for(int i=1;i<=f;i++)  cout<<path[i]<<' ';
    return 0;
}