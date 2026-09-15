#include<bits/stdc++.h>
using namespace std;

char a[305][305];
int n,m,sx,sy,ans=0,vis[305][305];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};

int main(){
    cin>>n>>m;  
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
            if(a[i][j]=='@')  sx=i,sy=j;
        }
    }
    queue<pair<int,int>> q;  
    q.push({sx,sy});  vis[sx][sy]=1;
    while(!q.empty()){
        int s=q.size();  ans++;
        for(int i=0;i<s;i++){
            pair<int,int> tq=q.front();  q.pop();
            for(int j=0;j<4;j++){
                int tx=tq.first+dx[j],ty=tq.second+dy[j];
                if(tx>=1&&tx<=n&&ty>=1&&ty<=m&&!vis[tx][ty]&&a[tx][ty]!='#'){
                    if(a[tx][ty]=='='){
                        cout<<ans;  return 0;
                    } 
                    if(a[tx][ty]>='A'&&a[tx][ty]<='Z'){ 
                        int flag=0;
                        for(int i1=1;i1<=n;i1++){
                            for(int j1=1;j1<=m;j1++){
                                if(a[i1][j1]==a[tx][ty]&&!(i1==tx&&j1==ty)){
                                    tx=i1,ty=j1,flag=1;  break;
                                }
                            }
                            if(flag)  break;
                        }
                        q.push({tx,ty});  //注意,两个传送门都不用标记vis
                    }else if(a[tx][ty]=='.'){
                        q.push({tx,ty});  vis[tx][ty]=1;
                    }
                }
            }
        }
    }
    cout<<"-1";  return 0;
}