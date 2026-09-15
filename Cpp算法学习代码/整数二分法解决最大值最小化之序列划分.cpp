#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,k;  cin>>n>>k;
	int a[1005];  for(int i=0;i<n;i++)  cin>>a[i];
	int l=a[0],r=0;
	for(int i=0;i<n;i++){
		r+=a[i];             //r为sum 
		if(a[i]>l)  l=a[i];  //l为maxnum 
	}
	while(l<r){
		int mid=(l+r)>>1,cnt=1,sum=0;
		for(int i=0;i<n;i++){
			if(sum+a[i]>mid){
				cnt++;  sum=a[i];
			}else  sum+=a[i];
		}
		if(cnt<=k)  r=mid;
		else  l=mid+1;
	}
	cout<<"最大值最小化为"<<l<<endl; 
}