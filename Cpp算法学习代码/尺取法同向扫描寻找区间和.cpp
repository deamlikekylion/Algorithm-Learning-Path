#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a[10000],n,s;
	cin>>n;
	for(int i=0;i<n;i++)  scanf("%d",&a[i]);
	cin>>s;
	int i=0,j=0;
	int sum=a[0];
	while(j<n){
		if(sum>=s){
			if(sum==s)  printf("%d %d\n",i,j);
			sum-=a[i];
			i++;
			if(i>j){
				sum=a[i];  j++;
			}
		}else{
			j++;  sum+=a[j];
		}
	}
	return 0;
}
