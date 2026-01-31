#include<bits/stdc++.h>
using namespace std;
int n,a,b,k[205],vis[205],ans;

void bfs(int a,int b){
    queue<int> q;  q.push(a);  vis[a]=1;
    while(!q.empty()){
        int size=q.size(); ans++;
        for(int i=0;i<size;i++){
            int x=q.front();  q.pop();
            if(x==b){
                ans--;  return;
            }
            if(x+k[x]>0&&x+k[x]<=n&&!vis[x+k[x]]){
                q.push(x+k[x]);  vis[x+k[x]]=1;
            }
            if(x-k[x]>0&&x-k[x]<=n&&!vis[x-k[x]]){
                q.push(x-k[x]);  vis[x-k[x]]=1;
            } 
        }
    }
    ans=-1;
    return;
}

int main(){
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++)  cin>>k[i];
    bfs(a,b);  cout<<ans;
    return 0;
}