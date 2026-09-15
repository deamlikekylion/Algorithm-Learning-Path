#include<bits/stdc++.h>
using namespace std;

string re;
queue <string> q;
map <string,string> mp;

void FA(string x){
	string y=x;
	for(int i=0;i<4;i++)  swap(x[i],x[7-i]);
	if(mp.count(x)==0){
		q.push(x);  mp[x]=mp[y]+'A';
	}
}

void FB(string x){
	string y=x;
	x[0]=y[3],x[1]=y[0],x[2]=y[1],x[3]=y[2];
	x[4]=y[5],x[5]=y[6],x[6]=y[7],x[7]=y[4];
	if(mp.count(x)==0){
		q.push(x);  mp[x]=mp[y]+'B';
	}
}

void FC(string x){
	string y=x;
	x[1]=y[6],x[2]=y[1],x[5]=y[2],x[6]=y[5];
	if(mp.count(x)==0){
		q.push(x);  mp[x]=mp[y]+'C';
	}
}

void bfs(){
	q.push("12345678");  mp["12345678"]="";
	while(q.size()){
		string s=q.front();  q.pop();
		if(s==re){
			cout<<mp[re].size()<<endl<<mp[re];
			return;
		}
		FA(s);  FB(s);  FC(s);
	}
}

int main(){
	char c;  
	for(int i=1;i<=15;i++){
		if(i%2){
			cin>>c;  re+=c;
		}
	}
	bfs();
	return 0;
}
