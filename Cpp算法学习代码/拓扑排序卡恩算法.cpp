#include<bits/stdc++.h>
using namespace std;

const int N=1000;
vector <int> e[N],tp;  //tp存拓扑序列
int n,m,din[N];  //din[x]存节点x的入度

bool toposort(){
	queue <int> q;
	for(int i=1;i<=n;i++)  if(din[i]==0)  q.push(i);  //压入所有入度为0的点
	while(q.size()){
		int x=q.front();  q.pop();  //取出入度为0的点
		tp.push_back(x);  //将入度为0的点存入拓扑序列
		for(auto t : e[x])  if(--din[t]==0)  q.push(t);  
		//删除之前入度为0点的所以出边,即其所有邻接点入度减1
		//同时减1后入度为0的点再压入q中循环操作
	}
	return tp.size()==n;
}

int main(){
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int a,b;  cin>>a>>b;
		e[a].push_back(b);
		din[b]++;
	}
	if(!toposort())  cout<<"No Answer!";
	else  for(auto t : tp)  cout<<t<<" ";
	return 0; 
}
