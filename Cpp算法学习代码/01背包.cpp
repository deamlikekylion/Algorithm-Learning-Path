//01背包：第i件物品可以放0个或1个 
#include<bits/stdc++.h>
using namespace std;
const int N=105,M=105;

int main(){
	int n,m;  //物品数量和背包容量
	int c[N],w[N];  //每一个物品体积和价值
	cin>>n>>m;
	for(int i=1;i<=n;i++)  cin>>c[i]>>w[i];
	
//朴素算法
	int f[N][M]={0};  //f[i][j]为容量为j的背包装i件物品的最大价值
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(j<c[i])  f[i][j]=f[i-1][j];
			else  f[i][j]=max(f[i-1][j],f[i-1][j-c[i]]+w[i]);
		}
	} 
	cout<<f[n][m];
	
//滚动数组
    int g[M]={0};  //g[i]为容量为i的背包装n件物品的最大价值，注意初始化	
    for(int i=1;i<=n;i++){
    	for(int j=m;j>=c[i];j--){  //逆序 
    		g[j]=max(g[j],g[j-c[i]]+w[i]);
		}
	}
	cout<<g[m];
	
	return 0; 
} 