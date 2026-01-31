#include<bits/stdc++.h>
using namespace std;

const int N=5e3+5;
int n,m;
int dfn[N],low[N],cnt,scc[N],size[N],sum;
//dfn[x]:时间戳,节点x第一次被访问的顺序  cnt:时间戳计数器   
//low[x]:追溯值,从节点x出发所能访问到的最早时间戳
//对于一个强连通分量的根(该连通分量被访问的第一个节点)来说,dfn=low
//scc记录每个节点所属的强连通分量(scc[i]为i节点所在的连通分量编号)
//sum为连通分量总数  size为每个强连通分量的节点数(其i值为1到sum)
stack<int> s;      //将访问到的节点存入栈中
bool instack[N];   //标记存入栈中的节点
vector<int> e[N];  //邻接表(此题无边权)

void Tarjan(int u){                     //Tarjan算法找强连通分量
    //入x时,盖戳,入栈
    low[u]=dfn[u]=++cnt;
    s.push(u);  instack[u]=true;
    for(int v : e[u]){
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

int main(){
    cin>>n>>m;
    while(m--){
        int a,b,t;  cin>>a>>b>>t;
        e[a].push_back(b);
        if(t==2)  e[b].push_back(a);
    }
    for(int i=1;i<=n;i++)  if(dfn[i]==0)  Tarjan(i);  //对所有未访问的节点Tarjan
    int mscc=1;                                       //mscc为最大连通分量的节点数(大小)
    for(int i=1;i<=sum;i++)  mscc=max(mscc,size[i]);  //遍历所以连通分量的大小,找最大连通分量
    cout<<mscc<<endl;
    for(int i=1;i<=n;i++){            //从1开始遍历使得输出最小字典序
        int tmp=scc[i];
        if(size[tmp]==mscc){          //第一个大小为mscc的连通分量
            cout<<i<<' ';
            for(int j=i+1;j<=n;j++){  //输出该连通分量的所以节点
                if(scc[j]==tmp)  cout<<j<<' ';
            }
            return 0;
        }
    }
}