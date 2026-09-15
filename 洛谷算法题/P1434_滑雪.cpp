#include<bits/stdc++.h>
using namespace std;

int n,m,a[105][105],s[105][105],ans;
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};

int dfs(int x,int y){  //DFS+记忆化,计算从(x,y)出发的最长下降路径长度
    if(s[x][y])  return s[x][y];  
    //记忆化:如果已经计算过(x,y)的最长路径,直接返回结果,避免重复计算
    s[x][y]=1;  //路径至少包含当前点本身,初始长度为1
    for(int i=0;i<4;i++){
        int tx=x+dx[i],ty=y+dy[i];
        if(tx>0&&ty>0&&tx<=n&&ty<=m&&a[x][y]>a[tx][ty]){
            dfs(tx,ty);
            s[x][y]=max(s[x][y],s[tx][ty]+1);
        }
    }
    return s[x][y];
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    for(int i=1;i<=n;i++){  //遍历矩阵中每个点为起点计算最长下降路径更新最大ans
        for(int j=1;j<=m;j++){
            ans=max(ans,dfs(i,j));
        }
    }
    cout<<ans;
    return 0;
}