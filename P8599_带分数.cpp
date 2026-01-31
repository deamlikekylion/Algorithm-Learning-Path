#include<bits/stdc++.h>
using namespace std;

string a="123456789",b;
bool vis[9];
int n,cnt=0;  

void dfs(int s,int t){
    if(s==9){
        int x=0;
        for(int i=0;i<7;i++){
            x=x*10+b[i]-'0';
            int y=0;
            for(int j=i+1;j<8;j++){
                y=y*10+b[j]-'0';
                int z=0;
                for(int k=j+1;k<9;k++){
                    z=z*10+b[k]-'0';
                }
                if(y%z==0&&x+y/z==n)  cnt++;
            }
        } 
    }
    for(int i=0;i<t;i++){
        if(!vis[i]){
            vis[i]=true;
            b[s]=a[i];
            dfs(s+1,t);
            vis[i]=false;
        }
    }
}

int main(){
    cin>>n;
    dfs(0,9);
    cout<<cnt;
    return 0;
}