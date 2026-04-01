#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;
int n,q,c[N],dep[N],fa[N][20],cnt[N][25];
vector<int> e[N];
//LCA算法模板见P3379_最近公共祖先_倍增算法
//dep[i]为i点的深度,fa[i][j]为i点向上跳2^j的祖先节点,最多1e5个点,j取20即可(5e5<2^20)
//cnt[x][i]:根节点到x节点,零食i的出现次数(零食最多20种)

void dfs(int u,int father){
    dep[u]=dep[father]+1;
    fa[u][0]=father;
    for(int i=1;i<=19;i++)  fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int v : e[u])  if(v!=father)  dfs(v,u);
}

int lca(int u,int v){
    if(dep[u]<dep[v])  swap(u,v);
    for(int i=19;i>=0;i--)  if(dep[fa[u][i]]>=dep[v])  u=fa[u][i];
    if(u==v)  return v;
    for(int i=19;i>=0;i--)  if(fa[u][i]!=fa[v][i])  u=fa[u][i],v=fa[v][i];
    return  fa[u][0];
}

//计算cnt数组(前缀和思想:根->x的零食出现次数)
void dfs_cnt(int u,int father){
    for(int v : e[u]){
        if(v==father)  continue;
        for(int i=1;i<=20;i++)  cnt[v][i]=cnt[u][i];
        //从根到v要经过其父节点u,根->u的零食出现次数包含在根->v
        cnt[v][c[v]]++;  //加上当前节点v自己的零食种类
        dfs_cnt(v,u);    //递归子节点
    }
}

int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++)  cin>>c[i];
    for(int i=1;i<=n-1;i++){
        int u,v;  cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,0);  cnt[1][c[1]]++;
    dfs_cnt(1,0);
    while(q--){
        int s,t;  cin>>s>>t;
        int ans=0,nod=lca(s,t);    //nod为s,t的最近公共祖先
        for(int i=1;i<=20;i++){    //遍历所以零食种类
            int num=(cnt[s][i]-cnt[nod][i])+(cnt[t][i]-cnt[nod][i]);
            //cnt[s][i]-cnt[nod][i]为s到nod路径上零食i的数量(包括s不包括nod)
            //(cnt[s][i]-cnt[nod][i])+(cnt[t][i]-cnt[nod][i])
            //即为s到t路径上零食i的数量(包括s,t不包括nod)
            if(c[nod]==i)  num=num+1;
            //单独判断nod结点是否有零食i
            if(num>0)  ans++;  //num>0则有零食i,ans++
        }
        cout<<ans<<endl;
    }
    return 0;
}