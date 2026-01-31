#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,ans=0;  cin>>n;
    priority_queue<int,vector<int>,greater<int>> q;  
    //小顶堆优先队列,元素升序,top最小(priority_queue<int> q默认大顶堆,元素降序,top最大)
    while(n--){
        int a;  cin>>a;
        q.push(a);
    }
    while(!q.empty()){
        int x=q.top();  q.pop();
        if(q.empty())  break;
        int y=q.top();  q.pop();
        ans+=(x+y);  q.push(x+y);
    }
    cout<<ans;
    return 0;
}