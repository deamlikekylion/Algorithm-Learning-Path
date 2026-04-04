#include<bits/stdc++.h>
using namespace std;

#define int long long  //ans可能超出int范围
const int N=1e3+5;
int n,dp[N][N],ans;
//dp[i][j]表示分别以i,j结尾的子串的最长相反长度
string s;

signed main(){  //int宏定义为了long long,int main改为signed main
    string t;  cin>>t;  s=" "+t;  n=t.size();
    //使得从s[1]开始为有效字串,且到s[n]结束
    for(int i=1;i<=n;i++){   //遍历所有i<j的组合(左结尾i,右结尾j)
        for(int j=i+1;j<=n;j++){  
            if(s[i]!=s[j]){  //如果s[i]和s[j]字符相反可以延长子串
                dp[i][j]=min(dp[i-1][j-1]+1,j-i);
                //dp[i-1][j-1]+1:继承前一位的长度+1
                //min(..., j-i):限制长度不超过j-i,保证两个子串不重叠
            }else{          //如果s[i]和s[j]相同则无法构成相反子串,长度为0
                dp[i][j]=0;
            }
            ans+=dp[i][j];
            //累加当前dp值:dp[i][j]是以i,j结尾的最长合法子串长度
            //也就是以i,j结尾的所有合法子串数量
        }
    }
    cout<<ans;
    return 0;
}