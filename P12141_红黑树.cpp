#include<bits/stdc++.h>
using namespace std;

bool dfs(int n,int k){              //该节点是红的返回true,黑的返回false
    if(n==1)  return true;
    if(k%2){                        //节点为奇数,为左节点
        int flag=dfs(n-1,(k+1)/2);  //递归判断其父节点的颜色
        if(flag)  return true;      //左节点与父节点颜色一致,flag=true则父为红,子为红返回true
        else  return false;
    }else{                          //节点为偶数,为右节点
        int flag=dfs(n-1,k/2);      //递归判断其父节点的颜色
        if(flag)  return false;     //右节点与父节点颜色相反,flag=true则父为红,子为黑返回false
        else  return true;
    }
}

int main(){
    int m;  cin>>m;
    while(m--){
        int n,k;  cin>>n>>k;
        int flag=dfs(n,k);          //递归判断节点
        if(flag)  cout<<"RED"<<endl;
        else  cout<<"BLACK"<<endl;
    }
    return 0;
}