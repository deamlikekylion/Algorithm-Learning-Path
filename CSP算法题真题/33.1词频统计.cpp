#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,m,k,a[100],b[100]={0,0,0},c[100]={0,0,0};  scanf("%d %d",&n,&m);
	while(n--){
		scanf("%d",&k);
		for(int i=0;i<k;i++){
			scanf("%d",&a[i]);
		}
		if(k==1){
			b[a[0]]++;
			c[a[0]]++;
		}else{
			sort(a,a+k);  int t=0;
		    for(int i=1;i<k;i++){
		    	if(a[i]!=a[i-1]){
		    		c[a[i-1]]++;
		    		b[a[i-1]]+=i-t;
		    		t=i;
				}
			}
			c[a[k-1]]++;
			b[a[k-1]]+=k-t; 
		}
	}
	for(int i=1;i<=m;i++){
		printf("%d %d\n",c[i],b[i]);
	}
	return 0;
}














