#include<bits/stdc++.h>
using namespace std;
const int N=10005;
int olda[N],newa[N];

int main(){
	int n;  scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&olda[i]);
		newa[i]=olda[i];
	}
	sort(olda+1,olda+1+n);
	int cnt=n;
//	int cnt=unique(olda+1,olda+1+n)-(olda+1);  //去重操作
    for(int i=1;i<=cnt;i++)
    	newa[i]=lower_bound(olda+1,olda+1+n,newa[i])-olda;
	for(int i=1;i<=cnt;i++)  
	    printf("%d ",newa[i]);
	printf("\ncnt=%d",cnt);
	return 0;    
}