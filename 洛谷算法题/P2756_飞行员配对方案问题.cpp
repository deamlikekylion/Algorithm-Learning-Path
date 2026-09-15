#include<bits/stdc++.h>
using namespace std;

const int N=105;  //节点数上限
const int M=N*N;  //出边数上限
int n,m,S,T;      //S:源点,T:汇点
struct edge{
    int v,c,ne;   //v:终点,c:剩余容量,ne:下一条边的索引(邻接表用)
}e[M];            //e[i]存第i条出边信息
int h[N],idx=1,d[N],cur[N];
//h[N]:邻接表头,存u点第一条出边索引;idx:边计数器(索引),从2,3开始,方便反向边通过i^1获取
//^:位形同为0,不同为1,eg:2(10)^1(01)=3(11),3(11)^1(01)=2(10)
//                      11(1011)^1(0001)=10(1010),10(1010)^1(0001)=11(1011)
//d[N]:BFS层次数组;cur[N]:当前弧优化数组,存u点的当前出边,即其当前处理到的边

void add(int a,int b,int c){            //加边,链式前向星
    e[++idx]={b,c,h[a]};
    h[a]=idx;
}

bool bfs(){                             //对点分层,找增广路
    memset(d,0,sizeof(d));              //初始化层次为0(未访问)
    queue<int> q;
    q.push(S);  d[S]=1;                 //源点入队,层次设为1
    while(q.size()){
        int u=q.front();  q.pop();
        for(int i=h[u];i;i=e[i].ne){    //遍历u的所有邻接边
            int v=e[i].v;
            if(d[v]==0&&e[i].c){        //若v未分层且边有剩余容量
                d[v]=d[u]+1;            //v的层次为u的层次+1
                q.push(v);
                if(v==T)  return true;  //到达汇点,存在增广路径
            }
        }
    }
    return false;                       //无法到达汇点,无增广路径
}

//在层次图中寻找增广路径并流出流量,u:当前节点,mf:当前可流出的最大流量
int dfs(int u,int mf){                   //多路增广
    if(u==T)  return mf;                 //到达汇点,返回可流出的流量
    int sum=0;                           //累计u流出的总流量
    //遍历u的邻接边(当前弧优化:从cur[u]开始,避免重复处理已失效的边)
    for(int i=cur[u];i;i=e[i].ne){
        cur[u]=i;                         //当前弧优化(更新当前弧)
        int v=e[i].v;
        if(d[v]==d[u]+1&&e[i].c){         //若v的层次是u的层次+1且边有剩余容量
            int f=dfs(v,min(mf,e[i].c));  //递归推送流量,取剩余可推流量和边容量的最小值
            e[i].c-=f;                    //正向边剩余容量减少f
            e[i^1].c+=f;                  //反向边剩余容量增加f(支持流量回退)
            sum+=f;                       //累加u的流出流量
            mf-=f;                        //减少u的剩余流量
            if(mf==0)  break;             //无剩余流量则停止循环(余量优化)
        }
    }
    if(sum==0)  d[u]=0;                   //若未流出任何流量,标记u不可达,剪枝(残枝优化)
    return sum;
}

int dinic(){       //通过累加可行流计算最大流
    int flow=0;
    while(bfs()){  //只要存在增广路径(循环判断,每次dfs后图都回变,继续寻找增广路)
        memcpy(cur,h,sizeof(h));  //初始化当前弧为邻接表头
        flow+=dfs(S,1e9);         //推送最大可能流量,累加到总流量
    } 
    return flow;   //返回最大流流量,即二分图最大匹配数
}

int main(){
    cin>>m>>n;  
    int a,b;  cin>>a>>b; 
    while(a!=-1&&b!=-1){      //读取二分图的边(左部节点->右部节点),直到输入-1,-1
        add(a,b,1);           //左部到右部的边容量为1(每个节点仅需匹配一次)
        add(b,a,0);           //反向边初始容量为0(确保正反变从2,3开始相邻出现)
        cin>>a>>b;
    }
    S=0,T=n+1;
    for(int i=1;i<=m;i++){    //源点S连接所有左部节点,容量1(每个左部节点最多匹配1次)
        add(S,i,1);
        add(i,S,0);
    }  
    for(int i=m+1;i<=n;i++){  //所有右部节点连接汇点T,容量1(每个右部节点最多匹配1次)
        add(i,T,1);
        add(T,i,0);
    }
    int ans=dinic();          //计算最大流(即最大匹配数)
    cout<<ans<<endl;
    //遍历所有边,提取匹配的边(反向边有流量的正向边即为匹配边)
    for(int i=2;i<=idx;i+=2){        //边成对存储,i从2开始(正向边),步长2
        if(e[i].v!=S&&e[i^1].v!=S){  //过滤与源点/汇点直接相连的边,仅保留左部->右部的边
            if(e[i].v!=T&&e[i^1].v!=T){
                if(e[i^1].c!=0){     //反向边有流量(说明正向边被使用,即匹配成功)
                    cout<<e[i^1].v<<' '<<e[i].v<<endl;  //输出匹配的节点对
                }
            }
        }
    }
    return 0;
}