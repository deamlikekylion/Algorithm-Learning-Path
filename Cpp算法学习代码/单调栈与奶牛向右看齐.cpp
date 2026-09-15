#include<bits/stdc++.h>
using namespace std;
int h[10005],ans[10005];
int main()
{
	int n;  scanf("%d",&n);
	for(int i=1;i<=n;i++)  scanf("%d",&h[i]);
	stack<int> st;
	for(int i=n;i>=1;i--){
		while(!st.empty()&&h[st.top()]<=h[i]){
			st.pop();
		}
		if(st.empty())  ans[i]=0;
		else  ans[i]=st.top();
		st.push(i);
	}
	for(int i=1;i<=n;i++)  printf("%d\n",ans[i]);
	return 0;
}
