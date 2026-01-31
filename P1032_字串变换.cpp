#include<bits/stdc++.h>
using namespace std;

int n;
string A,B,a[10],b[10];

int extend(queue<string>&q,unordered_map<string,int>&da,
      unordered_map<string,int>&db,string a[10],string b[10]){
	int m=q.size();
	while(m--){
		string f=q.front();  q.pop();
		for(int i=0;i<n;i++){
			for(int j=0;j<f.size();j++){
				if(f.substr(j,a[i].size())==a[i]){
					string s=f.substr(0,j)+b[i]+f.substr(j+a[i].size());
					if(da.count(s))  continue;  //s已经变过了,去重跳过
					if(db.count(s))  return da[f]+db[s]+1;
					//db中也有s,说明A,B到可以变成s,则A可以变到B,步数da[f]+db[s]+1
					da[s]=da[f]+1;
					q.push(s);
				}
			}
		}
	}
	return 11;
}

int bfs(){
	if(A==B)  return 0;
	queue <string> qa,qb;  unordered_map<string,int> da,db;
	//da[s]表示从A到s要da[s]步,同时可用于去重
	qa.push(A),qb.push(B);  da[A]=db[B]=0;
	int t=10,k;
	while(t--){
		if(qa.size()<=qb.size())  k=extend(qa,da,db,a,b);
		else  k=extend(qb,db,da,b,a);
		if(k<=10)  return k;
	}
	return 11;
}

int main(){
	cin>>A>>B;  int i=0;
	while(cin>>a[i]>>b[i]){
		i++;
	}
	n=i;
	int ans=bfs();
	if(ans==11)  cout<<"NO ANSWER!";
	else  cout<<ans;
	return 0;
}
