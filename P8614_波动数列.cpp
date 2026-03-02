#include<bits/stdc++.h>
using namespace std;

#define ll long long
const ll mod=1e8+7;
int n,s,a,b,dp[1005][1005];

int main(){
    cin>>n>>s>>a>>b;  dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<n;j++){
            dp[i][j]=(dp[i-1][((j-i*a)%n+n)%n]+
                      dp[i-1][((j+i*b)%n+n)%n])%mod;
        }
    }
    cout<<dp[n-1][(s%n+n)%n];
    return 0;
}