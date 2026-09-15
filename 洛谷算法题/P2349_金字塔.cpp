#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF=0x3f3f3f3f3f3f3f3f;
int n,m;
ll d[105],ma[105];  //d[i]为i点到1的最短路径,ma[i]为该路径上最大的边权值
bool vis[105];
struct edge{
    int v;  ll w;
};
vector<edge> e[105];
queue<int> q;

void spfa(int s){
    for(int i=1;i<=n;i++)  d[i]=INF;
    d[s]=0;  q.push(s);  vis[s]=true;
    while(!q.empty()){
        int u=q.front();  q.pop();  vis[u]=false;
        for(auto ed : e[u]){
            int v=ed.v;  ll w=ed.w;
            if((d[u]+w+max(ma[u],w))<(d[v]+ma[v])){  //从1到u到v的路径小于原来从1到v则更新
                d[v]=d[u]+w;          
                ma[v]=max(ma[u],w); 
                if(!vis[v]){
                    q.push(v);  vis[v]=true;
                }
            }
        }
    }
}

int main(){
    cin>>n>>m;
    while(m--){
        int a,b;  ll c;  cin>>a>>b>>c;
        e[a].push_back({b,c});
        e[b].push_back({a,c});
    }
    spfa(1);
    cout<<d[n]+ma[n]<<endl;  //n到1的最短路径加上其最大边权即为答案
    return 0;
}