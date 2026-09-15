#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;
int n,b[N],dp[N];  //树形dp
vector<int> e[N];
//b[u]表示节点u的子节点数,dp[u]表示节点u的最大高度
//e[u]邻接表存储节点u的所有子节点

void dfs(int u){
    for(int v : e[u]){
        dfs(v);
        dp[u]=max(dp[u],dp[v]);
        //每次选择子树最长的子节点作为最后一个节点
        //而不是选择子节点数量最多的
    }
    dp[u]=dp[u]+b[u];
    //dp[u]=最长子树高度(dp[u])+u的子节点数(b[u])
}

int main(){
    cin>>n;  int u;
    for(int i=2;i<=n;i++){
        cin>>u;  b[u]++;
        e[u].push_back(i);
    }
    dfs(1);
    cout<<dp[1];
    return 0;
}