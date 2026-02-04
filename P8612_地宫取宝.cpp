#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,m,k,a[55][55],h[55][55][17][17];
//a数组存储对应格子的宝物价值,h[x][y][maxn][sum]四维记忆化缓存数组,
//表示状态为经过(x,y)时拿了sum件宝物且其中最大价值为maxn的合法路径数

//返回值为int的dfs要注意返回值的定义,以及如何处理返回值,重点为ans和h的处理
int dfs(int x,int y,int maxn,int sum){  //记忆化深搜
    if(x>n||y>m)  return 0;
    if(h[x][y][maxn][sum]!=-1)  return h[x][y][maxn][sum];
    //记忆化核心判断:若该状态已计算过(h值≠-1),直接返回缓存结果无需重复递归
    long long ans=0;  //记录当前状态到达终点时符合要求的路径数(注意用long long,int会溢出)
    if(x==n&&y==m){
        if(sum==k||(a[x][y]>maxn&&sum==k-1))  ans++;  
        //不能直接修改sum值,修改的话最后的h数组也变了
    }else{
        ans+=dfs(x,y+1,maxn,sum);                         //1.向右走不拿宝物
        if(a[x][y]>maxn)  ans+=dfs(x,y+1,a[x][y],sum+1);  //2.向右走拿宝物
        ans+=dfs(x+1,y,maxn,sum);                         //3.向下走不拿宝物
        if(a[x][y]>maxn)  ans+=dfs(x+1,y,a[x][y],sum+1);  //4.向下走拿宝物
    }
    h[x][y][maxn][sum]=ans%mod;  //将当前状态的合法路径数取模后存入记忆化数组h
    return h[x][y][maxn][sum];   //返回当前状态的合法路径数
    //注意初始maxn=-1按理来说数组下标应为非负数,但能过,也可以将dfs中h中的maxn都改为maxn+1
}

int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)  cin>>a[i][j];
    }
    memset(h,-1,sizeof(h)); 
    //初始化记忆化数组h为-1(合法路径数可为0,所以不能用0来初始化)
    cout<<dfs(1,1,-1,0)%mod;  //注意输出值取mod
    //从起点(1,1)出发,初始最大值maxn=-1(宝物最小值为0),初始拿到的宝物数sum=0
    return 0;
}