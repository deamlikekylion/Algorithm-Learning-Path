//多重背包：第i件物品可以放0个到si个 
#include<bits/stdc++.h>
using namespace std;
const int N=105,M=105;

int main(){
	int n,m;  cin>>n>>m;  //物品数量和背包容量 
	
//二进制拆分成01背包用滚动数组 
    //输入数据 
    int c[N],w[N],s[N];  //每一个物品体积、价值、数量
    for(int i=1;i<=n;i++)  cin>>c[i]>>w[i]>>s[i];
    //二进制拆分
	int cc[N],ww[N];  //二进制拆分后新物品的体积和价值 
	int num=0; 
    for(int i=1;i<=n;i++){
		for(int j=1;j<=s[i];j<<=1){  //二进制枚举：1,2,4等 
			s[i]-=j;  cc[++num]=j*c[i];  ww[num]=j*w[i]; 
		}
		if(s[i]){  //剩余 
			cc[++num]=s[i]*c[i];  ww[num]=s[i]*w[i];
		}
	} 
	//01背包滚动数组
    int f[M]={0};  //f[i]为容量为i的背包装n件物品的最大价值，注意初始化	
    for(int i=1;i<=num;i++){
    	for(int j=m;j>=cc[i];j--){  //逆序 
    		f[j]=max(f[j],f[j-cc[i]]+ww[i]);
		}
	}
	cout<<f[m];

//单调队列优化
    int g[M]={0};  //g[i]为容量为i的背包装n件物品的最大价值，注意初始化	
    int q[N],num1[N];
	for(int i=1;i<=n;i++){
		int c,w,s;  cin>>c>>w>>s;  //每一个物品体积、价值、数量
		if(s>m/c)  s=m/c;
		for(int j=0;j<c;j++){
			int head=1,tail=1;
			for(int k=0;k<=(m-j)/c;k++){
				int tmp=g[j+k*c]-k*w;
				while(head<tail&&q[tail-1]<=tmp)  tail--;
				q[tail]=tmp;  num1[tail++]=k;
				while(head<tail&&k-num1[head]>s)  head++;
				g[j+k*c]=max(g[j+k*c],q[head]+k*w);
			}
		} 
	} 
	cout<<g[m];
	
	return 0; 
} 