#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD=1e9+7;
ll pow_10[23],dp[23],a[23],cnt1[15],cnt2[15],ans;
//dp[i]表示i位数字中0到9出现的次数(0到9在i位数字中出现的次数相同)
//考虑前导零,eg:001中0出现两次(但0不影响结果)
//cnt1[i],cnt2[i]记录数字i出现的次数(0没意义就不记录了)

void solve(ll x){  //计算0到x中数字1到9出现的次数
    int len=0;
    while(x){
        a[++len]=x%10;  x/=10;  //将x拆分存入a数组,a[1]为最低位
    }
    for(int i=len;i>=1;i--){  //从高位到低位遍历
        for(int j=1;j<10;j++)    cnt1[j] = (cnt1[j] + dp[i-1] * a[i]) % MOD;
        //最高位为1到a[i]时,1到i-1位出现数字j的次数(此时cnt1[j]不记录最高位)
        for(int j=1;j<a[i];j++)  cnt1[j] = (cnt1[j] + pow_10[i-1]) % MOD;
        //最高位为j时(j<a[i]),1到i-1位可任取,有pow_10[i-1]种
        ll num=0;
        for(int j=i-1;j>=1;j--)  num = (num * 10 + a[j]) % MOD;  //num即为后i-1位数字
        cnt1[a[i]] = (cnt1[a[i]] + num + 1) % MOD;
        //最高位为a[i]时,1到i-1不可任取(比如x=2728,后i-1位只能取0到728(num)一共num+1种)
        //cnt1[0] = (cnt1[0] - pow_10[i-1] + MOD) % MOD; 去除前导零(不影响所以注释了)
    }
}

int main(){  //求L到R的所以数字的数位和(不是区间和)
    ll t,l,r;  cin>>t;  pow_10[0]=1,dp[0]=0;
    for(int i=1;i<=23;i++){  //初始化dp
        dp[i] = (dp[i-1] * 10 % MOD + pow_10[i-1] % MOD) % MOD;
        //eg:对于数字9的dp[2]:
        //由9的dp[1]直接扩展十位(最高位)为0到9,所以为dp[i-1]*10(此时99只算了个位)
        //然后固定十位(最高位)为9,个位(剩下所有低位)有0到9十种选择,所以为pow_10[i-1](99算了十位)   
        pow_10[i] = pow_10[i-1] * 10 % MOD;
    }
    while(t--){
        ans=0;  cin>>l>>r;
        solve(r);  //计算0到r中数字1到9出现的次数 
        for(int i=1;i<10;i++){
            cnt2[i]=cnt1[i];  cnt1[i]=0;  //将cnt1存入cnt2中,同时初始化cnt1
        }
        solve(l-1);  //计算0到l-1中数字1到9出现的次数 
        for(int i=1;i<10;i++){
            ll cnt = (cnt2[i] - cnt1[i] + MOD) % MOD;  //cnt即为r到l中数字1到9出现的次数
            ans = (ans + i * cnt) % MOD;
            cnt1[i]=0;  //初始化cnt1以便下一个查询
        }
        cout<<ans<<endl;
    }
    return 0;
}