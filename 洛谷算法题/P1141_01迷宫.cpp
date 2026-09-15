#include<bits/stdc++.h>
using namespace std;

char a[1005][1005];       //存储迷宫,不能用int,因为输入01之前无空格
int n,m,ans[1005][1005];  //ans[i][j]记录i,j所在连通块的大小,即i,j能移动的格数
bool vis[1005][1005];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};

int dfs(int x,int y,vector<pair<int, int>> &nodes){  //&nodes通过引用可直接修改nodes
    vis[x][y]=true;
    nodes.emplace_back(x,y);
    int res=1;                      //连通块大小初始化为1(包含自身)
    for(int i=0;i<4;i++){
        int tx=x+dx[i],ty=y+dy[i];
        if(tx>=1&&tx<=n&&ty>=1&&ty<=n&&!vis[tx][ty]&&a[tx][ty]!=a[x][y]){
            res+=dfs(tx,ty,nodes);  //递归统计子连通块大小,并累加到res
        }
    }
    return res;                     //返回当前连通块的总大小
}

int main(){
    cin>>n>>m;  
    for(int i=1;i<=n;i++)  cin>>a[i]+1;       //a[i]+1=a[i][1],从a[i][1]开始存入一行
    for(int i=1;i<=n;i++){                    //预处理所有连通块,记录每个位置的连通块大小
        for(int j=1;j<=n;j++){
            if(!vis[i][j]){                   //若当前位置未被访问,说明是新的连通块
                vector<pair<int,int>> nodes;  //存储该连通块的所有节点
                int size=dfs(i,j,nodes);      //统计连通块大小
                for(auto &p : nodes){         //将连通块大小赋值给该连通块的所有节点
                                              //&p通过引用避免拷贝元素,提高效率
                    ans[p.first][p.second]=size;
                }
            }
        }
    }
    while(m--){
        int x,y;  cin>>x>>y;
        cout<<ans[x][y]<<endl;                //直接输出该位置所在连通块的大小
    }
    return 0;
}