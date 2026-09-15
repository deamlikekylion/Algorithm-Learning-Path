//二维费用背包：第i件物品可以放0个或1个，除了考虑物体的体积还考虑物体的重量 
#include<bits/stdc++.h>
using namespace std;
const int VV=105,MM=105;

//朴素算法 滚动数组 
int main(){
	int n,V,M;  //物品数量、背包体积容量、重量容量 
	int v,m,w;  //每一个物品体积、重量、价值
	cin>>n>>V>>M;
	int f[VV][MM]={0};  //f[i][j]为体积为i重量为j的背包装n件物品的最大价值
	for(int i=1;i<=n;i++){
		cin>>v>>m>>w;
		for(int j=V;j>=v;j--){  //体积逆序 
			for(int k=M;k>=m;k--){  //重量逆序 
				f[j][k]=max(f[j][k],f[j-v][k-m]+w);
			}
		}
	} 
	cout<<f[V][M];
	return 0; 
} 