#include<bits/stdc++.h>
using namespace std;

int w[2005],f[2005],ew[2005],n,m,root,flag;
//用f和flag是否相等来保留和删除节点
vector<int> s[2005];

int erfenw(int u){  //计算ew[u]:u自身及其所有后代的权值和
	ew[u]=0;
	for(auto t : s[u])  if(f[t]==flag)  ew[u]+=erfenw(t);
	ew[u]+=w[u];
	return ew[u];
}

int ison(int t,int u){  //判断u是否为t后代
	if(t==u)  return 1;
	for(auto ed : s[t])  if(ison(ed,u))  return 1; 
	return 0;
}

void retain(int t){  //保留t和其后代
	f[t]++;
	for(auto ed : s[t])  retain(ed);
}

void remove(int t){  //删除t和其后代
	f[t]--;
	for(auto ed : s[t])  remove(ed);
}

void solve(int u){
	ew[root]=erfenw(root);   
	int q=ew[root],t=root;
	for(int i=1;i<=n;i++){
		if(f[i]==flag){
			if(ew[root]-2*ew[i]<0)  ew[i]=2*ew[i]-ew[root];
			else  ew[i]=ew[root]-2*ew[i];
			if(ew[i]<q)  q=ew[i],t=i;
		}
	}
	cout<<t<<" ";  int cnt=0;
	if(ison(t,u)){
		root=t;  retain(t);  flag++;  
		for(int i=1;i<=n;i++)  if(f[i]==flag)  cnt++;
		if(cnt==1){  //只剩一个节点是结束
			cout<<endl;  return;
		}
		solve(u);
	}else{
		remove(t);  
		for(int i=1;i<=n;i++)  if(f[i]==flag)  cnt++;
		if(cnt==1){
			cout<<endl;  return;
		}
		solve(u);
	}  
}

int main(){
	cin>>n>>m;   
	for(int i=1;i<=n;i++)  cin>>w[i];   
	for(int i=2;i<=n;i++){
		int a;  cin>>a;  s[a].push_back(i);
	}
	while(m--){
		int u;  cin>>u;
		for(int i=1;i<=n;i++)  f[i]=1;  
		flag=1;  root=1;  solve(u);
	}
	return 0;
}
