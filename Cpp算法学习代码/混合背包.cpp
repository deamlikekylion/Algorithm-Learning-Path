//混合背包：01背包+多重背包+完全背包 
#include<bits/stdc++.h>
using namespace std;
const int N=105,M=105;
 
int main(){
	int n,m;  cin>>n>>m;  //物品数量和背包容量
	int v,w,s;  //物品体积和价值
	            //s=-1为01背包、s=0为完全背包、s>0为多重背包每个物品数量
	            
//用二进制拆分将多重背包转化为01背包	            
	int a[N],b[N],c[N];  //转化后物品的体积、价值、背包类型			 
	int num=0; 
	for(int i=1;i<=n;i++){
		cin>>v>>w>>s;
		if(s==0){  //完全背包 
			a[++num]=v;  b[num]=w;  c[num]=0; 
		}else{
			if(s==-1)  s=1;  //01背包转化成数量为1的多重背包
			for(int j=1;j<=s;j<<=1){  //多重背包转换成01背包 
			    s-=j;  a[++num]=j*v;  b[num]=j*w;  c[num]=1; 
		    }
		    if(s){  //剩余 
			    a[++num]=s*v;  b[num]=s*w;  c[num]=1;
		    }
		}
	} 

//滚动数组处理01背包和完全背包 
    int f[M]={0};  //f[i]为容量为i的背包装n件物品的最大价值，注意初始化	
    for(int i=1;i<=num;i++){
    	if(c[i]==1){  //01背包 
    		for(int j=m;j>=a[i];j--){  //逆序 
    		    f[j]=max(f[j],f[j-a[i]]+b[i]);
		    }
		}
		else{  //完全背包 
			for(int j=a[i];j<=m;j++){  //顺序
    		    f[j]=max(f[j],f[j-a[i]]+b[i]);
		    }
		}
	}
	cout<<f[m];
	
	return 0; 
} 