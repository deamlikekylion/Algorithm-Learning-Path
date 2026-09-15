#include<bits/stdc++.h>
using namespace std;

const int N=100005;
vector<pair<int,int>> e[N];  //邻接表:存储(邻接节点,距离)
int dis[N],max_dis;          //dis记录每个节点的距离

int bfs(int start){          //BFS函数:返回(最远节点far_node,最远距离max_dis)
    memset(dis,-1,sizeof(dis));
    queue<int> q;  q.push(start);  dis[start]=0;
    int far_node=start;
    while(!q.empty()){
        int u=q.front();  q.pop();
        for(auto edge : e[u]){
            int v=edge.first,w=edge.second;
            if(dis[v]==-1){
                dis[v]=dis[u]+w;
                q.push(v);
                if(dis[v]>max_dis){
                    max_dis=dis[v];
                    far_node=v;
                }
            }
        }
    }
    return far_node;
}

int main(){
    int n;  cin>>n;
    for(int i=0;i<n-1;i++){
        int a,b,c;  cin>>a>>b>>c;
        e[a].emplace_back(b,c);
        e[b].emplace_back(a,c);
        //无向边,双向存储,emplace_back不用加大括号,push_back({L,R})要加大括号
        //且emplace直接在末尾创建,push要拷贝,对于pair等类型的emplace比push快一点
    }
    max_dis=0;  int u=bfs(1);
    //第一次BFS:找到离节点1最远的节点u
    max_dis=0;  int v=bfs(u);
    //第二次BFS:找到u的最远距离(树的直径,即树中最长的路径)
    //原理:任意一点距离最远的点一定是直径的一个端点
    int ans=10*max_dis+max_dis*(max_dis+1)/2;
    //计算最大路费:(i+10),i从1到max_dis,即10*max_dis+max_dis*(max_dis+1)/2
    cout<<ans<<endl;
    return 0;
}