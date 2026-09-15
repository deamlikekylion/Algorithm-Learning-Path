#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;
int n,m,ans,a[N],b[N];
bool v1[N],v2[N];          //分别标记两棵树的节点是否被访问
vector <int> e1[N],e2[N];  //两棵树邻接表
struct node{               //队列中存储的结构体:id1,id2表示当前遍历到两棵树的对应节点,len表示当前公共前缀长度
    int id1,id2,len;
};
queue <node> q;

bool cmp1(int x,int y){    //升序排序自定义函数
    return a[x]<a[y];
}

bool cmp2(int x,int y){
    return b[x]<b[y];
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)  cin>>a[i];
    for(int i=1;i<=m;i++)  cin>>b[i];
    for(int i=1;i<=n-1;i++){
        int u,v;  cin>>u>>v;
        e1[u].push_back(v);  //双向边
        e1[v].push_back(u);
    }
    for(int i=1;i<=m-1;i++){
        int u,v;  cin>>u>>v;
        e2[u].push_back(v);
        e2[v].push_back(u);
    }
    if(a[1]!=b[1]){          //根节点权值不相等则无公共前缀,输出0
        cout<<0<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++)  sort(e1[i].begin(),e1[i].end(),cmp1);  //将每个节点的子节点按权值升序排序
    for(int i=1;i<=m;i++)  sort(e2[i].begin(),e2[i].end(),cmp2);
    q.push({1,1,1});              //初始化BFS:从根节点开始,公共前缀长度为1
    while(!q.empty()){            //开始BFS遍历
        node t=q.front();  q.pop();
        ans=max(ans,t.len);       //更新最长公共前缀长度
        int id1=t.id1,id2=t.id2;  //id1,id2表示当前遍历到两棵树的对应节点,其权值相同,搜索扩展其下一层
        v1[id1]=v2[id2]=true;     //标记当前节点已访问(防止走回头路,重复遍历)
        int i=0,j=0;              //双指针i/j:分别指向二棵树当前遍历节点的邻接点列表起始位置
        while(i<e1[id1].size()&&j<e2[id2].size()){  //同时遍历两个邻接点列表,直到其中一个遍历完毕
            int u1=e1[id1][i],u2=e2[id2][j];        //u1,u2为id1,id2的子节点
            int w1=a[u1],w2=b[u2];
            if(w1<w2)  i++;       //第一棵树id1的子节点权值更小,i后移找更大的值
            else if(w1>w2)  j++;  //第二棵树id2的子节点权值更小,j后移找更大的值
            else if(w1==w2){      //找到权值相同的节点,构成公共前缀的下一个节点
                if(!v1[u1]&&!v2[u2]){         //前提:两个子节点都未被访问过(避免重复)
                    q.push({u1,u2,t.len+1});  //入队:公共前缀长度+1,后面继续遍历下一层
                }
                i++;  j++;        //双指针同时后移,继续寻找该层下一对权值相同的节点入队
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}