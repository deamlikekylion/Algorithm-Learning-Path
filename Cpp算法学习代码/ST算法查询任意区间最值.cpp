#include<bits/stdc++.h>
using namespace std;
const int N=5005;
int n,m,a[N],dp_max[N][22],dp_min[N][22],LOG2[N];

void st_init(){
  /*LOG2[0]=-1;
	for(int i=1;i<=N;i++)  LOG2[i]=LOG2[i>>1]+1;*/
	for(int i=1;i<=n;i++){
		dp_min[i][0]=a[i];
		dp_max[i][0]=a[i];
	}  
	int p=log2(n);
//	int p=(int)(long(double(n))/log(2.0));  
	for(int k=1;k<=p;k++){
		for(int s=1;s+(1<<k)<=n+1;s++){
			dp_max[s][k]=max(dp_max[s][k-1],dp_max[s+(1<<(k-1))][k-1]);
			dp_min[s][k]=min(dp_min[s][k-1],dp_min[s+(1<<(k-1))][k-1]);
		}
	}
}

int st_query(int l,int r){
	int k=log2(r-l+1);
//	int k=(int)(long(double(r-l+1))/log(2.0));
//	int k=LOG2[r-l+1];
    int x=max(dp_max[l][k],dp_max[r-(1<<k)+1][k]);
    int y=min(dp_min[l][k],dp_min[r-(1<<k)+1][k]);
    return x-y;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)  scanf("%d",&a[i]);
	st_init;
	for(int i=1;i<=m;i++){
		int l,r;  scanf("%d %d",&l,&r);
		printf("%d\n",st_query(l,r));
	}
	return 0;
}
















