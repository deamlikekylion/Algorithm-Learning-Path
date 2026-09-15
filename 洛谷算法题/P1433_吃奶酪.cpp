#include<bits/stdc++.h>
using namespace std;

int n;
double x[20],y[20],a[20][20],f[18][1<<18],ans;
//x[i],y[i]为第i个奶酪的横纵坐标,a[i][j]为i到j的距离(0为原点,1~N为奶酪)
//f[i][j]:状压DP数组,表示当前在第i块奶酪,已吃奶酪的状态为j(二进制)时的最短距离
//j的二进制每一位表示是否吃过对应奶酪(如j=1010表示吃过第2,4块奶酪,位从低位到高位对应奶酪1~N)
//f[i][j]中i取18,取20的话j取1<<20会超时

int main(){
    memset(f,127,sizeof(f));  ans=f[0][0];  //初始化f,ans为极大值
    cin>>n;  x[0]=y[0]=0;  
    for(int i=1;i<=n;i++)  cin>>x[i]>>y[i];
    for(int i=0;i<=n;i++){                  //预处理a(包含原点,i从0开始)
        for(int j=i+1;j<=n;j++){
            a[i][j]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
            a[j][i]=a[i][j];
        }
    }
    for(int i=1;i<=n;i++)  f[i][1<<(i-1)]=a[0][i];  
    //初始化f只吃了第i块奶酪的状态,状态为1<<(i-1),即只有第i位为1,最短距离为原点到第i块奶酪的距离

    //状态转移:枚举所有可能的状态k,当前位置i,转移来源j
    for(int k=1;k<(1<<n);k++){                   //枚举所有二进制状态(从1到2^N-1)
        for(int i=1;i<=n;i++){                    //枚举当前所在的奶酪i
			if((k&(1<<(i-1)))==0)  continue;      //如果状态k中不包含i(即第i-1位为0),则跳过
			for(int j=1;j<=n;j++){                //枚举转移来源的奶酪j
				if(i==j)  continue;               //同一个奶酪,无需转移
				if((k&(1<<(j-1)))==0)  continue;  //如果状态k中不包含j(即第j-1位为0),则跳过
				f[i][k]=min(f[i][k],f[j][k-(1<<(i-1))]+a[i][j]);
                //状态转移方程:f[i][k]=min(当前值,f[j][k去掉i的状态]+j到i的距离)
                //即f[i][k1]由f[j][k2]转移来,f[i][k1]=f[j][k2]+a[i][j]
                //需满足k1有i,有j;k2无i,有j;上面的k即为k1
			} 
		} 
    }
    for(int i=1;i<=n;i++)  ans=min(ans,f[i][(1<<n)-1]);
    //遍历所有吃完所有奶酪的状态(状态为(1<<n)-1,即所有位为1),找最小值
    printf("%.2f",ans);  //输出保留两位小数
    return 0;
}