#include<bits/stdc++.h>
double PI=acos(-1.0);
#define eps 1e-5;
double area[10010];
int n,m;

bool check(double mid)
{
	int sum=0;
	for(int i=0;i<n;i++)  sum+=(int)(area[i]/mid);   //向0取整（直接去了小数部分） 
	if(sum>=m)  return 1;
	else  return 0;
}

int main()
{
	int T;  scanf("%d");
	while(T--){
		scanf("%d %d",&m,&n);  m++;
		double maxx=0;
		for(int i=0;i<n;i++){
			int r;  scanf("%d",&r);
			area[i]=PI*r*r;
			if(maxx<area[i])  maxx=area[i];
		}
		double left=0,right=maxx;
		for(int i=0;i<100;i++){   //while((right-left)>eps)
			double mid=left+(right-left)/2;
			if(check(mid))  left=mid;
			else  right=mid;
		}
		printf("%.4f\n",left);
	} 
	return 0;
}