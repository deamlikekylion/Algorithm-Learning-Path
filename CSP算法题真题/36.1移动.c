#include<stdio.h>
int main()
{
	int i,j,n,k,x,y;
	scanf("%d %d",&n,&k);
	char c[105];
	for(i=0;i<k;i++){
		scanf("%d %d",&x,&y);
		scanf("%s",c);
		j=0;
		while(c[j]!='\0'){
			if(c[j]=='f'&&y+1<=n){
				++y;
			}else if(c[j]=='b'&&y-1>=1){
				--y;
			}else if(c[j]=='l'&&x-1>=1){
				--x;
			}else if(c[j]=='r'&&x+1<=n){
				++x;
			}
			++j;
		}
		printf("%d %d",x,y);
	}
	return 0;
}
