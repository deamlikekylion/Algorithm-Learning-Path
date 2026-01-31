#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;
int n,k;

//Trajan算法变量
int dfn[N],low[N],cnt,scc[N],size[N],sum;
//dfn[x]:时间戳,节点x第一次被访问的顺序  cnt:时间戳计数器   
//low[x]:追溯值,从节点x出发所能访问到的最早时间戳
//对于一个强连通分量的根(该连通分量被访问的第一个节点)来说,dfn=low
//scc记录每个节点所属的强连通分量(scc[i]为i节点所在的连通分量编号)
//sum为连通分量总数  size为每个强连通分量的节点数(其i值为1到sum)
stack<int> s;     //将访问到的节点存入栈中
bool instack[N];  //标记存入栈中的节点

int dp[N],in[N];  //dp记录每个强连通分量的最小糖果数;in[i]为新图节点的入度,用于拓扑排序
long long ans;    //最终总糖果数
struct edge{
    int v,w;
};
vector<edge> e[N],ne[N];  //e为原图邻接表,ne为缩点后的新图邻接表

//Tarjan算法找强连通分量
void Tarjan(int u){
    //入x时,盖戳,入栈
    low[u]=dfn[u]=++cnt;
    s.push(u);  instack[u]=true;
    for(auto ed : e[u]){
        int v=ed.v;
        if(dfn[v]==0){                  //未访问过,递归访问
            Tarjan(v);
            low[u]=min(low[u],low[v]);  //回x时更新low值
        }else if(instack[v]){           //访问过且已在栈中
            low[u]=min(low[u],dfn[v]);  //更新low值
        }
    }
    //离x时,记录SCC
    if(dfn[u]==low[u]){                 //找到一个强连通分量的根
        int t;  sum++;                  //强连通分量总数+1,t为该连通分量中的节点
        do{
            t=s.top();  
            s.pop();  instack[t]=false;
            scc[t]=sum;  size[sum]++;
        }while(u!=t);                   //根最后出栈(因为根最先被访问入栈),循环结束
    }
}

void toposort(){
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(in[i]==0){
            q.push(i);  //压入所有入度为0的点  
            dp[i]=1;    //每个分量至少有1个糖果
        }
    }
    while(q.size()){
        int u=q.front();  q.pop();
        for(auto ed : ne[u]){
            int v=ed.v,w=ed.w;
            if(--in[v]==0)  q.push(v);
            //删除之前入度为0点的所以出边,即其所有邻接点入度减1
		    //同时减1后入度为0的点再压入q中循环操作
            dp[v]=max(dp[v],dp[u]+w);
            //满足约束:v的糖果数 ≥ u的糖果数 + 边权
        }
    }
}

int main(){
    cin>>n>>k;
    while(k--){
        int op,x,y;  cin>>op>>x>>y;
        //差分约束建图:节点u指向节点v边权为w满足u+w<=v(与使用spfa算法的差分约束建图规则不同)
        switch(op){
            case 1:{  //x和y糖果数相同 → 双向边,权0
                e[x].push_back({y,0});
                e[y].push_back((edge){x,0});  //结构体输入的第二种方法
                break;
            }
            case 2:{  //x < y → x+1 <= y (x→y,权1)
                e[x].push_back({y,1});
                break;
            }
            case 3:{  //x ≥ y → y <= x (y→x,权0)
                e[y].push_back({x,0});
                break;
            } 
            case 4:{  //x > y → y+1 <= x (y→x,权1)
                e[y].push_back({x,1});
                break;
            }
            case 5:{  //x ≤ y → x <= y (x→y,权0)
                e[x].push_back({y,0});
                break;
            }
        }
    }
    //对所有未访问的节点Tarjan,找强连通分量用于缩点建新图
    for(int i=1;i<=n;i++)  if(dfn[i]==0)  Tarjan(i);  
    //缩点构建新图(因为按照原图建图规则同一个强连通分量边权为0的节点糖果数相同)
    for(int i=1;i<=n;i++){
        for(auto ed : e[i]){
            int v=ed.v,w=ed.w;
            int sci=scc[i],scv=scc[v];  //节点i,v所属的连通分量编号
            if(sci==scv&&w==1){         //若同一强连通分量内有边权为1的边,说明约束矛盾,无解
                                        //(如x+1<=y且y+1<=x,不可能满足)
                cout<<"-1"<<endl;
                return 0;
            }
            if(sci!=scv){               //在不同强连通分量,则建边(原图i指向v所以新图sci指向scv)
                ne[sci].push_back({scv,w});
                in[scv]++;              //新图中scv的入度+1
            }
        }
    }
    //拓扑排序更新dp值
    toposort();
    //累加每个强连通分量的糖果数(分量节点数×该分量的最小糖果数)
    for(int i=1;i<=n;i++)  ans+=(long long)dp[i]*size[i];  
    cout<<ans<<endl;
    return 0;
}