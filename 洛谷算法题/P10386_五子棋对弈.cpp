#include<bits/stdc++.h>
using namespace std;

int ans,mp[10][10],cnt1,cnt2;

bool check(int x,int y,int f){
    int f1=0,f2=0,f3=0,f4=0;
    for(int i=1;i<=5;i++){
        if(mp[x][i]!=f&&i!=y){
            f1=1;  break;
        }
    }
    for(int i=1;i<=5;i++){
        if(mp[i][y]!=f&&i!=x){
            f2=1;  break;
        }
    }
    if(x==y){
        for(int i=1;i<=5;i++){
            if(mp[i][i]!=f&&i!=x){
                f3=1;  break;
            }
        }
    }else  f3=1;
    if(x+y==6){
        for(int i=1;i<=5;i++){
            if(mp[i][6-i]!=f&&i!=x){
                f4=1;  break;
            }
        }
    }else  f4=1;
    if(f1&&f2&&f3&&f4)  return true;
    else  return false;
}

void dfs(int x,int y){
    if(cnt1<13&&check(x,y,1)){
        mp[x][y]=1;  cnt1++;
        //注意终止条件在mp[5][5]下过旗子后判断而不是dfs开头
        if(x==5&&y==5){
            ans++;
            mp[x][y]=0;  cnt1--;
            return;
        }
        if(y<5)  dfs(x,y+1);
        else     dfs(x+1,1);
        mp[x][y]=0;  cnt1--;  
        //注意回溯还原在if里面,因为下棋子操作在if里面
        //如果把还原操作放外面可能都没进if下棋子但仍然还原
    }
    if(cnt2<12&&check(x,y,2)){
        mp[x][y]=2;  cnt2++;
        if(x==5&&y==5){
            ans++;
            mp[x][y]=0;  cnt2--;
            return;
        }
        if(y<5)  dfs(x,y+1);
        else     dfs(x+1,1);
        mp[x][y]=0;  cnt2--;
    }
    return;
}

int main(){
    dfs(1,1);
    cout<<ans;
    return 0;
}