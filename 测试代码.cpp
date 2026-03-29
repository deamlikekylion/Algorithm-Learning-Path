#include<bits/stdc++.h>
using namespace std;

int ans=0;

void dfs(int sum,int cnt){
    if(sum==70)  ans++;
    if(sum==100||cnt>=30)  return;
    cnt++;
    dfs(0,cnt);
    dfs(sum+10,cnt);
}

int main(){
    dfs(0,0);
    cout<<ans;
    return 0;
}