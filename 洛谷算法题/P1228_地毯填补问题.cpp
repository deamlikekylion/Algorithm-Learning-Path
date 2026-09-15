#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
ll x,y,n=1;  int k;

void solve(ll x,ll y,ll a,ll b,ll n){
    //x,y为不能覆盖或覆盖后的点;a,b为当前棋盘左上角坐标;n为当前棋盘长度
    //solve函数通过ab判断xy处于棋盘四个象限中的那一个后进行处理
    //然后递归四部分象限
    if(n==1)  return;  //长度为1不能划分了递归结束
    if(x-a<=n/2-1&&y-b<=n/2-1){  //左上
        cout<<a+n/2<<' '<<b+n/2<<" 1"<<endl;
        //在另外三个象限的交界处放置L形骨牌,覆盖三个象限各一个格子
        //递归处理四个象限：
        solve(x,y,a,b,n/2);                  //左上:特殊格子仍是(x,y)
        solve(a+n/2-1,b+n/2,a,b+n/2,n/2);    //右上:特殊点为地毯覆盖的点
        solve(a+n/2,b+n/2-1,a+n/2,b,n/2);    //左下:特殊点为地毯覆盖的点
        solve(a+n/2,b+n/2,a+n/2,b+n/2,n/2);  //右下:特殊点为地毯覆盖的点
    }else if(x-a<=n/2-1&&y-b>n/2-1){  //右上
        cout<<a+n/2<<' '<<b+n/2-1<<" 2"<<endl;
        solve(a+n/2-1,b+n/2-1,a,b,n/2);                  
        solve(x,y,a,b+n/2,n/2);    
        solve(a+n/2,b+n/2-1,a+n/2,b,n/2);    
        solve(a+n/2,b+n/2,a+n/2,b+n/2,n/2);  
    }else if(x-a>n/2-1&&y-b<=n/2-1){  //左下
        cout<<a+n/2-1<<' '<<b+n/2<<" 3"<<endl;
        solve(a+n/2-1,b+n/2-1,a,b,n/2);                  
        solve(a+n/2-1,b+n/2,a,b+n/2,n/2);    
        solve(x,y,a+n/2,b,n/2);    
        solve(a+n/2,b+n/2,a+n/2,b+n/2,n/2);
    }else{  //右下
        cout<<a+n/2-1<<' '<<b+n/2-1<<" 4"<<endl;
        solve(a+n/2-1,b+n/2-1,a,b,n/2);                  
        solve(a+n/2-1,b+n/2,a,b+n/2,n/2);    
        solve(a+n/2,b+n/2-1,a+n/2,b,n/2);    
        solve(x,y,a+n/2,b+n/2,n/2);
    }
}

int main(){
    cin>>k>>x>>y;
    while(k--)  n*=2;
    solve(x,y,1,1,n);
    return 0;
}