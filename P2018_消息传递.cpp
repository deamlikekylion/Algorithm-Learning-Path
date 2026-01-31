#include<bits/stdc++.h>
using namespace std;

const int N=1005;
int n,cnt,nxt[N*2],fst[N],to[N*2],dp[N*2],ans[N],tmin=1<<30;
//cnt记录边数/索引,双向图共N*2条边
//fst[i]为i点最后更新的边数,即i遍历的头边
//nxt[i],to[i]为第i条边头结点的邻接边索引和指向的邻接点
//dp[i]为从第i条边出发对应的最少传播时间
//ans[i]为从i点出发对应的最少传播时间
//tmin为最少传播时间,初始化最大值

void  add(int i,int x){  //链式前向星
    nxt[++cnt]=fst[i];   //新边的nxt指向原头边,使其可像链表一样遍历同一个结点的邻接边
    fst[i]=cnt;          //更新头边为当前新边
    to[cnt]=x;           //记录边的终点
}

int dfs(int x,int fa,int k){     //x:当前节点,fa:父节点(避免回走),k:当前边的编号(用于dp记忆化)
    if(k&&dp[k])  return dp[k];  //若该边已计算过dp值,直接返回记忆化结果
    int t=1;                     //初始化当前节点的最大传播时间(注意初始为1)
    priority_queue<int> q;       //大顶堆,用于对子节点传播时间降序排序
    for(int i=fst[x];i!=0;i=nxt[i]){  //遍历当前节点的所有邻接边
        if(to[i]==fa)  continue;      //跳过父节点,避免循环
        q.push(dfs(to[i],x,i));       //递归计算子节点的传播时间,结果入堆
    }
    for(int i=1;!q.empty();i++,q.pop())  t=max(t,q.top()+i);
    //按顺序(从大到小)处理子节点的传播时间,计算当前节点的最大传播时间
    //因为每次只能通知一个子节点,所以所有子节点存在时间差1到子节点数
    //这些时间差可自由安排给各个子节点,显然先通知传播时间长的子节点可以使最终时间更短
    return dp[k]=t;
}

int main(){
    cin>>n;
    for(int i=2;i<=n;i++){
        int x;     cin>>x;
        add(i,x);  add(x,i);
    }
    for(int i=1;i<=n;i++){             //枚举每个节点作为起始点
        ans[i]=dfs(i,0,0);             //计算以i为起点的最小传播时间
        if(ans[i]<tmin)  tmin=ans[i];  //更新全局最小传播时间tmin
    }
    cout<<tmin<<endl;
    for(int i=1;i<=n;i++)  if(ans[i]==tmin)  cout<<i<<' ';
    //输出所有传播时间等于tmin的节点编号
    return 0;
}