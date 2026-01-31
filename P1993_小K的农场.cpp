#include<bits/stdc++.h>
using namespace std;

const int N=5005,INF=0x3f3f3f3f;
int n,m,d[N],vis[N],num[N];  //num:节点入队次数(判断负环)
struct edge{
    int v,w;
};
vector<edge> e[N];
queue<int> q;

//SPFA算法:判断以x为起点的图是否存在负环,存在负环返回false,否则返回true
bool spfa(int s){
    memset(d,INF,sizeof(d));
    d[s]=0;  vis[s]=1;  q.push(s);  num[s]++;
    while(q.size()){
        int u=q.front();  q.pop();  vis[u]=0;
        for(auto ed : e[u]){
            int v=ed.v,w=ed.w;
            if(d[v]>d[u]+w){
                d[v]=d[u]+w;
                if(!vis[v]){
                    q.push(v);  vis[v]=1;  num[v]++;
                    if(num[v]==n+1)  return false;  //入队次数超过节点数n,说明存在负环
                }
            }
        }
    }
    return true;
}

//差分约束原理:i-j<=c得i<=j+c,而对与一个正常的图来说d[i]<=d[j]+w(d为其到起点的最小距离,w为ij边权)
//所以对所有约束可由j向i加边权为c的边建图,如果图没负环则可满足所有约束,反之不满足
int main(){  
    cin>>n>>m;
    while(m--){
        int op;  cin>>op;
        if(op==1){                   //类型1:农场a比农场b至少多种c: a-b ≥ c
            int a,b,c;  cin>>a>>b>>c;
            e[a].push_back({b,-c});  //差分约束：b-a ≤ -c → 建边a→b,权值-c
        }else if(op==2){             //类型2:农场a比农场b至多多种c: a-b ≤ c
            int a,b,c;  cin>>a>>b>>c;
            e[b].push_back({a,c});   //差分约束：a-b ≤ c → 建边b→a,权值c
        }else{                       //类型3:农场a和b种植数量一样多: a-b = 0
            int a,b;  cin>>a>>b;
            e[a].push_back({b,0});   //差分约束：a-b ≤ 0 且 b-a ≤ 0 建双向边,权值0
            e[b].push_back({a,0});
        }
    }
    for(int i=1;i<=n;i++)  e[n+1].push_back({i,0});
    //添加"超级源点"n+1,连接到所有农场(权值0),确保所有节点能被遍历
    bool flag=spfa(n+1);          //从超级源点出发SPFA,判断是否存在负环
    if(flag)  cout<<"Yes"<<endl;  //无负环则存在符合条件的情况
    else  cout<<"No"<<endl;       //存在负环则约束矛盾
    return 0;
}