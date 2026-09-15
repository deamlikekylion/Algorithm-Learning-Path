#include<bits/stdc++.h>
using namespace std;
int main(){
	string s,s2;  
	getline(cin,s); 
	s2=s;
	string ch="",ck="";
	int n;  cin>>n;
	getchar();
	while(n--){
		string s1;
		getline(cin,s1);
		ch+=s1[1];  ck+=s1[2];
	}
	vector <char> time[100];  //time[i]为s的第i个字符所有可能的变换字符结果
	map <char,int> mp;        //mp[i]为s的第i个字符所有可能的变换字符个数
	for(int i=1;i<s.size()-1;i++){
		char c=s[i];  int t=0;
		do{
			if(ch.find(s[i])!=string::npos){
				int j=ch.find(s[i]);
				s[i]=ck[j];
				time[i].push_back(s[i]);
				t++;
			}else{
				break;
			}
		}while(c!=s[i]);
		if(t!=0)  mp[c]=t;
		else  mp[c]=1;
	}
	int m;  cin>>m;
	while(m--){
		int t1;  cin>>t1;
		string ans="#";
	    for(int i=1;i<s2.size()-1;i++){
	    	int c=s2[i];
	    	if(mp[c]==1)  ans+=c;
	    	else{
	    		int cnt=t1%mp[c];
	    		if(cnt==0)  ans+=c;
	    		else ans+=time[i][cnt-1];
			}
		}
		ans+="#";
		cout<<ans<<endl;
	}
	return 0;
}
