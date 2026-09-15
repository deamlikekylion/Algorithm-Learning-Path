#include<stdio.h>
int main()
{
	int i,j,w,t,n,a[100005],b[100005];
	scanf("%d",&n);
	for(i=0;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(i=1;i<=n;i++){
		scanf("%d",&b[i]);
	}
	for(i=1;i<=n;i++){
		w=a[0],t=0;
		for(j=1;j<=n;j++){
			if(j!=i){
				if(t+b[j]-a[j]<0){
			        w+=a[j]-b[j]-t,t=0;
		        }else{
			        t=t+b[j]-a[j];
	            }
			}else{
				if(t-a[j]<0){
					w+=a[j]-t,t=0;
				}else{
					t=t-a[j];
				}
			}
		}
		printf("%d ",w);
	}
	return 0;
}
