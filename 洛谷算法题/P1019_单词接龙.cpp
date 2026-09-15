#include<bits/stdc++.h>
using namespace std;

const int N=25;
int n,ans=0;
int used[N]={0};
string word[N];

void dfs(string s){
	int ls=s.size();
	ans=max(ans,ls);
	for(int i=0;i<n;i++){
		string w=word[i];
		int lw=w.size();
		for(int j=1;j<ls&&j<lw;j++){
			if(used[i]<2&&s.substr(ls-j)==w.substr(0,j)){
				used[i]++;
				dfs(s+w.substr(j));
				used[i]--;
				break;
			}
		}
	}
} 

int main(){
	cin>>n;
	for(int i=0;i<n;i++)  cin>>word[i];
	string s;  cin>>s;  s="*"+s;
	dfs(s);
	cout<<ans-1;
	return 0;
}
