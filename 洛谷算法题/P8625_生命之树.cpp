#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int N=1e5+5;
int n,a[N];          //a[i]为节点i的权值
ll ans,dp[N];        //dp[i]为以i为根的子树中所有连通分量(均包含i)中最大的权值和
vector<int> adj[N];  //邻接表存储边

void dfs(int u,int f){
    dp[u]=a[u];
    for(int v : adj[u]){
        if(v==f)  continue;
        dfs(v,u);
        dp[u]+=max(dp[v],0ll);  
        //max要求比较的两个类型相同,0ll为0后面加ll,表示为long long类型的0
    }
}

int main(){
    cin>>n;  for(int i=1;i<=n;i++)  cin>>a[i];
    for(int i=1;i<n;i++){
        int u,v;  cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);  //以1为树的根节点遍历,0为其父节点
    for(int i=1;i<=n;i++)  ans=max(dp[i],ans);
    cout<<ans;
    return 0;
}