#include<bits/stdc++.h>
using namespace std;
deque<int> dp;
int s[100005];
int main()
{
	int n,m;  scanf("%d %d",&n,&m);  //限制最大子序列长度不超过m 
	for(int i=1;i<=n;i++)  scanf("%d",&s[i]);
	for(int i=1;i<=n;i++)  s[i]=s[i-1]+s[i];
	int ans=-1e8;
	dp.push_back(0);
	for(int i=1;i<=n;i++){
		while(!dp.empty()&&dp.front()<i-m)  dp.pop_front();
		if(dp.empty())  ans=max(ans,s[i]);
		else  ans=max(ans,s[i]-s[dp.front()]);
		while(!dp.empty()&&s[dp.back()]>=s[i])  dp.pop_back();
		dp.push_back(i);
	}
	printf("%d\n",ans);
	return 0;
}