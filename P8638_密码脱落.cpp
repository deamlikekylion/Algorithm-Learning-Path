#include<bits/stdc++.h>
using namespace std;

int main(){                           //注意此题不能用贪心,应用DP
    string s1,s2;  cin>>s1;  s2=s1;
    reverse(s2.begin(),s2.end());     //s2为s1的倒序串
    int len=s1.size(),f[1005][1005];  //f[i][j]表示s1前i个字符和s2前j字符中相同的字符个数  
    for(int i=1;i<=len;i++){
        for(int j=1;j<=len;j++){
            if(s1[i-1]==s2[j-1])  f[i][j]=f[i-1][j-1]+1;  //相等则加1
            else  f[i][j]=max(f[i][j-1],f[i-1][j]);       //不相等取最大
        }
    }
    int ans=len-f[len][len];
    cout<<ans;
    return 0;
}