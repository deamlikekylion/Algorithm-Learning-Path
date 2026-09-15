#include<bits/stdc++.h>
using namespace std;

int main(){
    char s[55];  int f[55][55],n;      //f[i][j]表示s[i]到s[j]的最少涂色次数
    scanf("%s",s+1);  n=strlen(s+1);   //从s[1]开始读取
    memset(f,0x3f3f,sizeof(f));        //初始化
    for(int i=1;i<=n;i++)  f[i][i]=1;  //初始化
    for(int i=2;i<=n;i++){             //枚举间隔区间2到n
        for(int l=1;l+i-1<=n;l++){
            int r=l+i-1;
            if(s[l]==s[r])  f[l][r]=min(f[l+1][r],f[l][r-1]);
            //两端相同可由f[l+1][r],f[l][r-1]直接得来,不用涂色
            for(int j=l;j<=r;j++)  f[l][r]=min(f[l][r],f[l][j]+f[j+1][r]);
            //不管两端是否相同,枚举断点取最小
        }
    }
    cout<<f[1][n];
    return 0;
}