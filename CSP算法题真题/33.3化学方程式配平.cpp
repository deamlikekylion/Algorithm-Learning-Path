#include<bits/stdc++.h>
using namespace std;

int main(){
	int n;  cin>>n;
	int m,cnt,r;
	double a[50][50];
	map <string,int> mp; 
	string s;
	while(n--){
		memset(a,0,sizeof(a));
		cnt=0;
		mp.clear();
		cin>>m;
		for(int id=1;id<=m;id++){
			cin>>s;
			string name="";
			int c=0;
			for(int i=0;i<s.size();i++){
				if(isdigit(s[i])){
					int j=i;
					while(j<s.size()&&isdigit(s[j]))  c=c*10+s[j++]-'0';
					i=j-1;
					int k;
					if(mp.count(name))  k=mp[name];
					else k=mp[name]=++cnt;
					a[k][id]=c;
					name="";
					c=0;
				}else{
					name+=s[i];
				}
			}
		}
		for(int i=1;i<=cnt+1;i++){
			int fg=0;
			for(int j=i;j<=cnt;j++){
				if(abs(a[j][i])>1e-6){
					fg=j;
					break;
				}
			}
			if(!fg){
				r=i-1;
				break;
			}
			for(int k=1;k<=m;k++)  swap(a[i][k],a[fg][k]);
			for(int j=i+1;j<=cnt;j++){
				if(a[j][i]>0){
					double c=a[j][i]/a[i][i];
					for(int k=i;k<=m;k++)  a[j][k]-=c*a[i][k];
				}
			}
		}
		if(r<m)  cout<<"Y"<<endl;
		else  cout<<"N"<<endl;
	}
	return 0;
}
