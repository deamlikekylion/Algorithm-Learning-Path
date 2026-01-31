#include<bits/stdc++.h>
using namespace std;

const int N=5e3+5,mod=80112002;
int n,m,ans,in[N],out[N],num[N];  //in,out为出入度,num为该点都最佳生产者的链上的点数
vector<int> e[N];  //e[i]存储i的所以邻点
queue<int> q;

int main(){
    cin>>n>>m;
    while(m--){
        int x,y;  cin>>x>>y;
        out[x]++;  in[y]++;  //建图为被吃者指向吃者,增加相应的出入度
        e[x].push_back(y);  //添加单向边
    }
    for(int i=1;i<=n;i++){
        if(!in[i]){
            num[i]=1;  q.push(i);  //最佳生产者入度为0,找到最佳生产者赋值其num为1
        }
    }
    while(!q.empty()){
        int t=q.front();  q.pop();
        int len=e[t].size();
        for(int i : e[t]){
            --in[i];                  //删除最佳生产者,其所有邻点入度减1,同时加上其的num
            num[i]=(num[i]+num[t])%mod; 
			if(in[i]==0)  q.push(i);  //入队此时的最佳生产者,不断递归到最佳消费者
        }
    }
    for(int i=1;i<=n;i++){  //最佳消费者出度为0,找到所以的最大消费者累加其num即为答案
		if(!out[i])  ans=(ans+num[i])%mod;
    }        
	cout<<ans;
    return 0;
}