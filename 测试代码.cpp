#include <bits/stdc++.h>
using namespace std;
const int N=1005;
int f[N][N];
string s1,s2;
int main() {
	cin>>s1;	s2=s1;
	int l=s1.size();
	reverse(s2.begin(),s2.end());		//翻转串
	for(int i=1;i<=l;++i)			
		for(int j=1;j<=l;++j)
			if(s1[i-1]==s2[j-1])	f[i][j]=f[i-1][j-1]+1;
			else	f[i][j]=max(f[i][j-1],f[i-1][j]);
	cout<<l-f[l][l];
	return 0;
}
