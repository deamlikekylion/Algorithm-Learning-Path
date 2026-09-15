#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a[1000],n,m;
	cin>>n;
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	cin>>m;
	sort(a,a+n);
	int i=0,j=n-1;
	while(i<j){
		int sum=a[i]+a[j];
		if(sum>m)  j--;
		if(sum<m)  i++;
		if(sum==m){
			cout<<a[i]<<" "<<a[j]<<endl;
			i++;
		}
	}
	return 0;
}	
