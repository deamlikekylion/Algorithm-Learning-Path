#include<bits/stdc++.h>
using namespace std;

int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
int ans,t[305][305],vis[305][305];
//t[x][y]记录xy遇到陨石的时间,为-1则表示安全无陨石

void bfs(){
    if(t[0][0]==-1){
        cout<<ans;  return;
    }else if(t[0][0]==0){
        cout<<"-1";  return;
    }
    queue<pair<int,int>> q;  q.push({0,0});  vis[0][0]=1;
    while(!q.empty()){
        int s=q.size();  ans++;
        for(int i=0;i<s;i++){
            pair<int,int> tq=q.front();  q.pop();
            for(int j=0;j<4;j++){
                int tx=tq.first+dx[j],ty=tq.second+dy[j];
                if(tx>=0&&ty>=0&&!vis[tx][ty]){
                    if(t[tx][ty]==-1){  //到达安全位置结束
                        cout<<ans;  return;
                    }else if(ans<t[tx][ty]){
                        q.push({tx,ty});  vis[tx][ty]=1;
                    }
                }
            }
        }
    }
    cout<<"-1";  return;
}

int main(){
    int m;  cin>>m;
    for(int i=0;i<305;i++){  //初始化t全为-1
        for(int j=0;j<305;j++){
            t[i][j]=-1;
        }
    }
    while(m--){
        int a,b,c;  cin>>a>>b>>c;
        for(int i=0;i<4;i++){  //被陨石砸落或已标记时间没有该时间早,标记或更新t
            int tx=a+dx[i],ty=b+dy[i];
            if(tx>=0&&ty>=0&&(t[tx][ty]==-1||c<t[tx][ty]))  t[tx][ty]=c;
        }
        if(t[a][b]==-1||c<t[a][b])  t[a][b]=c;
    }
    bfs();
    return 0;
}