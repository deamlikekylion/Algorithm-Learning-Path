#include<bits/stdc++.h>
using namespace std;

int main(){
	int n;  cin>>n;
	map <string,string> mp;  //mp[a]记录1操作中a对应的字符串 
	map <string,int> m;  //m[a]=0为直接赋值
	                     //m[a]>0为间接赋值 
	vector <string> tem[1010];  //tem[ m[a] ]存储a间接赋值的所有变量名 
	int cnt=1;  //m[a]=cnt++ 
	for(int i=0;i<n;i++){
		int op;  cin>>op;   
		if(op==1){
			string a="",ch="",s;  getline(cin,s);  int t=1;
			for(int j=1;j<s.size();j++){
				if(s[j]!=' '&&t)  a+=s[j];
				if(s[j]==' '){
					t=0;  continue;
				}
				if(t==0&&s[j]!=' '&&s[j]!='$'){
					ch+=s[j];
				}
				if(s[j]=='$'){  //注意1操作可能有$ 
					string ch1="";  int k=j+1;
					while(s[k]!=' '&&k<s.size()){
						ch1+=s[k++];
					}
					j=k;  
					if(!m[ch1])  ch+=mp[ch1];  //判断ch1是否是间接赋值的 
					else{
						int s=m[ch1];
					    for(auto it : tem[s]){
						    string b=it;
						    ch+=mp[b];
					    }
					}
				}
			}  
			mp[a]=ch;
			m[a]=0;
		}
		if(op==2){
			string a="",s;  getline(cin,s);  int t=1;
			for(int j=1;j<s.size();j++){
				if(s[j]!=' '&&t)  a+=s[j];
				if(s[j]==' '){
					t=0;  continue;
				}
				if(t==0&&s[j]=='$'){
					string ch="";  int k=j+1;
					while(s[k]!=' '&&k<s.size()){
						ch+=s[k++];
					}
					tem[cnt].push_back(ch);  //存储所有变量名 
					j=k;
				} 
			}  
			mp[a]=a;  //对应自己，防止判断mp是否为空时误判 
			m[a]=cnt++;  //cnt++ 
		}
		if(op==3){
			string a;  cin>>a;
			if(mp.count(a)){  //判断a是否赋值过 
				if(!m[a])  cout<<(mp[a].size())%1000000007<<endl;
				else{
					int s=m[a];
					long long sum=0;
					for(auto it : tem[s]){
						string b=it;
						sum+=mp[b].size();
					}
					cout<<sum%1000000007<<endl;
				} 
			}   
			else cout<<0<<endl;
		}
	}
	return 0;  
}