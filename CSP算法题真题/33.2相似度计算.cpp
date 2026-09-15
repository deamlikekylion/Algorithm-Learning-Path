#include<bits/stdc++.h>
using namespace std;
int main(){
	set <string> b,c;
	int n,m;  scanf("%d %d",&n,&m);
	for(int i=0;i<n;i++){
		string str;
		cin>>str;
		int len=str.length();
		for(int j=0;j<len;j++){
			if(str[j]>='A'&&str[j]<='Z')  str[j]+='a'-'A';
		}
		b.insert(str);
	}
	for(int i=0;i<m;i++){
		string str;
		cin>>str;
		int len=str.length();
		for(int j=0;j<len;j++){
			if(str[j]>='A'&&str[j]<='Z')  str[j]+='a'-'A';
		}
		c.insert(str);
	}
	int ans1=0;
	for(auto p : b){  //set自动去重
		for(auto q : c){
			if(q==p){
				ans1++;
				break;
			}
		}
	} 
	int ans2=b.size()+c.size()-ans1;
	cout<<ans1<<endl<<ans2;
	return 0;
}
