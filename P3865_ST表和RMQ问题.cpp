#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;
int n,m,x,y,lg[N],f[N][20];
//lg[i]:预处理log2值,lg[i]=log2(i)向下取整,用于快速计算区间长度对应的幂次
//f[i][20]:ST表核心数组,f[i][j]表示从位置i开始,长度为2^j的区间的最大值(2^20=104万)

inline int read()  //快读(该题不用快读和printf会TIE)
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int main(){
    n=read();  m=read();  lg[1]=0;
    for(int i=2;i<=n;i++)  lg[i]=lg[i/2]+1;  //预处理lg数组:计算每个数的log2向下取整值
    for(int i=1;i<=n;i++)  f[i][0]=read();     
    //初始化ST表,f[i][0]表示从i开始长度为1(2^0)的区间的最大值,即自身的值
    for(int j=1;j<=lg[n];j++){  //构建ST表(动态规划)
                                //j表示区间长度为2^j,从1开始递推到最大可能的幂次(lg[n])
        for(int i=1;i<=n-(1<<j)+1;i++){  //i表示区间起点,需保证i+2^j-1<=n(即区间不越界)
            f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
            //长度为2^j的区间可拆分为两个长度为2^(j-1)的子区间:
            //[i, i+2^(j-1)-1]和[i+2^(j-1), i+2^j-1] (f[i][j-1]和f[i+2^(j-1))][j-1])
            //两个子区间的最大值的最大值,即为当前区间的最大值
        }
    }
    while(m--){
        x=read();  y=read();
        int len=y-x+1;  //计算区间长度
        int l=lg[len];  //取最大的l,使得2^l<=len(保证两个子区间覆盖大区间)
        int ans=max(f[x][l],f[y-(1<<l)+1][l]);
        //区间[x,y]可被两个长度为2^l的区间覆盖:
        //[x, x+2^l-1]和[y-2^l+1, y] (f[x][l]和f[y-2^l+1][l])
        //两个区间的最大值的最大值,即为[x,y]的最大值
        printf("%d\n",ans);
    }
    return 0;
}