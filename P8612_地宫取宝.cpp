#include<bits/stdc++.h>
using namespace std;

int n,m,k,a[55][55],ans,ma,sum=1;
bool v[55][55];

void dfs(int x,int y){
    
    if(x<=n&&y<=m&&!v[x][y])  v[x][y]=true;
    else  return;
    
    ma=max(a[x][y],ma);

}

int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)  cin>>a[i][j];
    }
    dfs(1,1);
    cout<<ans;
    return 0;
}