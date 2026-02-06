#include<bits/stdc++.h>
using namespace std;
typedef long long ll;               //定义长整型,防止乘法溢出

const int mod=1e9+7;
int n,m,a,b,p[7]={0,4,5,6,1,2,3};   //p[i]为数字i对面的数字
bool s[7][7];                       //s[x][y]=s[y][x]=1表示数字x,y互斥
ll ans;

struct matrix{                      //矩阵结构体
    ll c[7][7];
    matrix(){memset(c,0,sizeof(c));}  
    //构造函数,创建矩阵时自动将所有元素初始化为0,避免随机值干扰,注意分号在大括号内,外不需要分号
}A,res;  //初始声明(结构体的特殊用法)状态转移矩阵A和结果矩阵res

//重载符号'*'为矩阵乘法运算符:实现两个6阶矩阵的乘法,返回新矩阵t,用于矩阵快速幂函数
matrix operator * (const matrix&x,const matrix&y){
    matrix t;
    for(int i=1;i<=6;i++){
        for(int j=1;j<=6;j++){
            for(int k=1;k<=6;k++){
                t.c[i][j]=(t.c[i][j]+x.c[i][k]*y.c[k][j])%mod;
            }
        }
    }
    return t;
}

//矩阵快速幂函数:计算转移矩阵A的k次幂,结果存储在res中
void fastpow(ll k){
    for(int i=1;i<=6;i++)  res.c[1][i]=4;  //第1骰子且该骰子朝上的一面为数字i的可能性为4
    //构建状态转移矩阵A,其中A.c[i][j]含义为当前骰子朝上面数字为j,该骰子下面的骰子的朝上面数字为j 
    //时的转移系数(当前骰子的f值由其下面的骰子的f值转移得到)
    for(int i=1;i<=6;i++){
        for(int j=1;j<=6;j++){            
            if(s[i][p[j]])  A.c[i][j]=0;   //i与p[j]的数字贴合,如果它们互斥则转移系数为0
            else  A.c[i][j]=4;             //若不互斥系数为4(当前骰子固定朝上面j后有4种可能性)
        }
    }
    //快速幂:把k看作二进制,逐个处理它的最后一位,结果为res*A的k次幂
    while(k){
        if(k&1)  res=res*A;  //如果k的最后一位为1,则需要乘
        A=A*A;               //递推算A的2次幂,4次幂,8次幂,16次幂等
        k>>=1;               //把k右移一位,即去掉刚处理过的最后一位
    }
}

int main(){
    cin>>n>>m;
    while(m--){
        cin>>a>>b;
        s[a][b]=s[b][a]=1;   //标记互斥面
    }
    fastpow(n-1);
    //f[i][j]表示自下往上第i骰子且该骰子朝上的一面为数字j的所有可能性
    //则ans=f[n][i](i从1到6)(F[n]),而F[n]=F[1]*A的n-1次方
    //初始res.c[1][i]为F[1],则fastpow(n-1)后res.c[1][i]为F[n]
    for(int i=1;i<=6;i++)  ans=(ans%mod+res.c[1][i]%mod)%mod;
    //由res.c[1][i]求出ans
    cout<<ans;
    return 0;
}