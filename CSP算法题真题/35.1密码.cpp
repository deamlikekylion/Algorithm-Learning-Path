#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;  cin>>n;
	int cnt[3]={0};
	map <char,int> mp;
	while(n--){
		string s;  cin>>s;
		memset(cnt,0,sizeof(cnt));
		mp.clear();  int flag=0,fg=0,fr=1;
		for(int i=0;i<s.size();i++){
			if(isalpha(s[i])&&cnt[0]==0)  cnt[0]=1;
			if(isdigit(s[i])&&cnt[1]==0)  cnt[1]=1;
			if(!isalpha(s[i])&&!isdigit(s[i])&&cnt[2]==0)  cnt[2]=1;
			if(mp.count(s[i])){
				mp[s[i]]++;
				if(mp[s[i]]>2){
					flag=1;
					for(int j=0;j<3;j++){
						if(cnt[j]==0)  break;
						if(j==2)  fg=1;
					}
					if(fg)  break;
				}
			}else{
				mp[s[i]]=1;
			}
		}
		if(fg)  cout<<1<<endl;
		else{
			for(int i=0;i<3;i++){
				if(cnt[i]==0){
					cout<<0<<endl;
					fr=0;
					break;
				}
			}
			if(fr){
				if(flag)  cout<<1<<endl;
				else  cout<<2<<endl;
			}
		}
    }
    return 0;
}
