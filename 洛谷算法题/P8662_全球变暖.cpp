#include<bits/stdc++.h>
using namespace std;

const int N=1005;
char mp[N][N];
int n,ans,flag,vis[N][N]={0};
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};

void dfs(int x,int y){
    vis[x][y]=1;
    if(mp[x+1][y]=='#'&&mp[x-1][y]=='#'&&mp[x][y+1]=='#'&&mp[x][y-1]=='#'){
        flag=1;
    }
    for(int i=0;i<4;i++){
        int tx=x+dx[i],ty=y+dy[i];
        if(mp[tx][ty]=='#'&&vis[tx][ty]==0){
            dfs(tx,ty);
        }
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>mp[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(mp[i][j]=='#'&&vis[i][j]==0){
                flag=0;
                dfs(i,j);
                if(flag==0)  ans++;    
            }
        }
    }
    cout<<ans;
    return 0;
}