#include<bits/stdc++.h>
using namespace std;

const int N=3e4+5,INF=0x3f3f3f3f;
int n,h,d[N],vis[N];
struct edge{
    int v,w;
};
vector<edge> e[N];
queue<int> q;

void spfa(int s){  //此题一定有解,所以不用判断负环
    memset(d,INF,sizeof(d));
    d[s]=0;  vis[s]=1;  q.push(s);
    while(q.size()){
        int u=q.front();  q.pop();  vis[u]=0;
        for(auto ed : e[u]){
            int v=ed.v,w=ed.w;
            if(d[v]>d[u]+w){
                d[v]=d[u]+w;
                if(!vis[v]){
                    vis[v]=1;  q.push(v);  
                }
            }
        }
    }
}

int main(){
    cin>>n>>h;
    while(h--){  //ab区间(包含ab)至少中c棵树可转换为前缀和sum[b]-sum[a-1]>=c
                 //差分约束得sum[a-1]<=sum[b]-c,由b向a-1建边权为-c的边
        int a,b,c;  cin>>a>>b>>c;
        e[b].push_back({a-1,-c});
    }
    for(int i=0;i<=n;i++)  e[n+1].push_back({i,0});  //i从0开始,因为前面a-1可能为0
    for(int i=1;i<=n;i++){  //因为每个点最多种1棵树,所以0<=sum[i]-sum[i-1]<=1
        e[i-1].push_back({i,1});  //sum[i]<=sum[i-1]+1,由i-1向i建边权为1的边
        e[i].push_back({i-1,0});  //sum[i-1]<=sum[i]+0,由i向i-1建边权为0的边
    }
    spfa(n+1);  //从超级源点出发SPFA
    cout<<d[n]-d[0]<<endl;
    //d[i]对应sum[i],但求出的d[i]只是满足所有约束的一组解,而sum[i]要求所有值>=0
    //d[i]中可能有负值,所以找到最小的dmin,让所以d[i]加上(-dmin)使得最小的d为0以满足sum的定义
    //由因为该题d[i]对应sum[i],所以d[0]一定是最小的,所以输出的sum[n]=d[n]-d[0]
    return 0;
}