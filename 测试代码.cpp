#include<bits/stdc++.h>
using namespace std;

int n,k;
int h[100002];
int w[100002];

bool check(int x){//判断是否大于等于 k
	int s=0;
	for(int i=1; i<=n; i++) s+=(h[i]/x)*(w[i]/x);
	if(s>=k) return true;
	else return false;
}

int main(){
	cin>>n>>k;
	for(int i=1; i<=n; i++) cin>>h[i]>>w[i];
	int l=1,r=100002;
	while(l<r){//二分
		int mid=(l+r+1)/2;
		if(check(mid)) l=mid;
		else r=mid-1;
	}
	cout<<l;
	return 0;
}
