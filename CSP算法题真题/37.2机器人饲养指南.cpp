#include<bits/stdc++.h>
using namespace std;
const int N=10010;
int n,C;
long long dp[N],q[N],num[N];
int w,c,m;
int main(){
	cin>>C>>n;
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=n;i++){
		cin>>w; c=i; m=C/i;
		for(int b=0;b<c;b++){
			int head=1,tail=1;
			for(int y=0;y<=(C-b)/c;y++){
				long long tmp=dp[b+y*c]-y*w;
				while(head<tail&&q[tail-1]<=tmp)  tail--;
				q[tail]=tmp;
				num[tail++]=y;
				while(head<tail&&y-num[head]>m)  head++;
				dp[b+y*c]=max(dp[b+y*c],q[head]+y*w);
			}
		}
	} 
	cout<<dp[C];
	return 0; 
}
