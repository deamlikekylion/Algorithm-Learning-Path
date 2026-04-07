#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll n,m,ans=35,a[35];  //ans为最终要切的瓜数,因为每个只能切1次最多30个瓜,所以初始可为35表示不可解
map <ll,ll> mp;       //mp[sum]=cnt表示dfs1中凑出重量为sum的瓜最少需要切cnt刀
                      //不能用数组存sum对应的cnt是因为sum=m*2上限2e9,数组存不了这么多

void dfs1(ll sum,ll id,ll cnt){  //处理前半部分瓜:sum为当前凑出的重量,id为当前处理第id个瓜,cnt为当前切瓜数
    if(sum>m||id>n/2)  return;   //剪枝1:sum超出目标重量或者前半部分处理完了
    if(sum==m){                  //恰好凑到重量m,更新ans
        ans=min(ans,cnt);
        return;
    }
    if(mp.count(sum)&&mp[sum]<cnt)  return;  //剪枝2:当前sum已经被记录过且对应cnt小于当前cnt
    mp[sum]=cnt;                             //记录当前sum对应的cnt
    dfs1(sum,id+1,cnt);                      //递归分支1:不拿第id+1个瓜
    dfs1(sum+a[id+1],id+1,cnt+1);            //递归分支2:劈第id+1个瓜,拿走一半
    dfs1(sum+a[id+1]*2,id+1,cnt);            //递归分支3:不劈第id+1个瓜,拿走整个瓜
}

void dfs2(ll sum,ll id,ll cnt){         //处理后半部分瓜
    if(sum>m||id>n||cnt>=ans)  return;  //剪枝1:sum超出目标重量或者后半部分处理完了或者当前切瓜数大于ans
    if(mp.count(m-sum)){                //若前半部分能凑出m-sum的重量,即两部分总和为m,则合并次数更新答案
        ans=min(ans,mp[m-sum]+cnt);
        return;
    }
    dfs2(sum,id+1,cnt);
    dfs2(sum+a[id+1],id+1,cnt+1);
    dfs2(sum+a[id+1]*2,id+1,cnt);
}

int main(){
    cin>>n>>m;  m*=2;  //切瓜a[i]/2可能不是整数被取整了,所以可以m*=2,切瓜+a[i],不切+a[i]*2
    for(ll i=1;i<=n;i++)  cin>>a[i];
    sort(a+1,a+1+n);   //排序可以优化搜索
    dfs1(0,0,0);       //处理前半部分瓜(注意从id=0开始,因为递归时加的是a[id+1])
    dfs2(0,n/2,0);     //处理后半部分瓜
    //或者37行从id=1开始,10、38行n/2改成n/2+1,23行n改成n+1,18、19、29、30行id+1改成id
    //前半段处理了1到n/2+1,后半段处理了n/2+1到n+1
    if(ans!=35)  cout<<ans<<endl;  //ans!=35可解,输出ans
    else  cout<<-1<<endl;          //不可解输出ans
    return 0;
}