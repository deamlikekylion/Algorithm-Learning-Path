#include<bits/stdc++.h>
using namespace std;
int dx[4]={1,0,0,-1};
int dy[4]={0,1,-1,0};
queue<string> q;
map<string,int> d;

int bfs(string str){
	q.push(str);  d[str]=0;
	string end="123804765";
	while(q.size()){
		string s=q.front();  q.pop();
		if(s==end)  return d[s];
		int k=s.find('0');
		int x=k/3,y=k%3;
		for(int i=0;i<4;i++){
			int nx=x+dx[i],ny=y+dy[i];
			if(nx<0||nx>=3||ny<0||ny>=3)  continue;
			int dis=d[s];
			swap(s[k],s[nx*3+ny]);
			if(!d.count(s)){
				d[s]=dis+1;  q.push(s); 
			}
			swap(s[k],s[nx*3+ny]);
		}
	}
}

int main(){
	string str;
	cin>>str;
	int ans=bfs(str);
	cout<<ans;
	return 0;
}


