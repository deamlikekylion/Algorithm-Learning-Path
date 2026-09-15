//分组背包：n组物品每组最多选1个 
#include<bits/stdc++.h>
using namespace std;
const int N=105,M=105;

int main(){
	int n,m;  cin>>n>>m;  //物品组数和背包容量 
	
//朴素算法 二维 
	int f[N][M]={0};  //f[i][j]为容量为j的背包装i组物品的最大价值
	int s[N],c[N][N],w[N][N];  //s[i]为第i组物品数量
	                           //c[i][j],w[i][j]为第i组物品第j个物品的体积、价值
	for(int i=1;i<=n;i++){
		cin>>s[i];
		for(int j=1;j<=s[i];j++)  cin>>c[i][j]>>w[i][j];
	}						    
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){  //体积 
			for(int k=0;k<=s[i];k++){  //决策
				if(j>=c[i][k])  f[i][j]=max(f[i][j],f[i-1][j-c[i][k]]+w[i][k]);
			}
		}
	} 
	cout<<f[n][m];
	
//滚动数组  一维 
    int g[M]={0};  //g[i]为容量为i的背包装n组物品的最大价值，注意初始化	
    int s1,c1[N],w1[N];
    for(int i=1;i<=n;i++){
    	cin>>s1;
    	for(int j=1;j<=s1;j++)  cin>>c1[j]>>w1[j];
    	for(int j=m;j>=1;j--){  //体积逆序 
    		for(int k=0;k<=s1;k++){  //决策 
    			if(j>=c1[k])  g[j]=max(g[j],g[j-c1[k]]+w1[k]);
			}
		}
	}
	cout<<g[m];
	
	return 0; 
} 