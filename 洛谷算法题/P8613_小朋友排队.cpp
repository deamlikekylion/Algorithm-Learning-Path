#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;
int n,s[N],a[N],b[N];
long long cnt[N],ans;
map<int,int> mp; 
//s[N]为树状数组的核心树组,用于高效统计前缀和单点更新
//a存储原数值,b为辅助数组,通过mp实现a数组的离散化
//cnt[i]为第i个数字需要交换的次数,ans为总代价
//注意后面ans+=cnt[i]*(cnt[i]+1)/2防止溢出cnt,ans需用long long

void change(int x,int k){  //向后修,点修改(将包含x的区间和s都加k,即第x个数加上k)
    for(;x<=n;x+=x&-x)  s[x]+=k;  //x&-x取x的低位2次幂,x+x的低位2次幂=父下标(爬链)
}

int query(int x){  //向前查,前缀和(即求第x个数前面包括x的所以数字的和)
    int res=0;
    for(;x;x-=x&-x)  res+=s[x];
    return res;  //res为到x为止的前缀和
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];  b[i]=a[i];
    }
    sort(b+1,b+1+n);  //离散编号为升序排序编号
    for(int i=1;i<=n;i++)  mp[b[i]]=i;
    for(int i=1;i<=n;i++)  a[i]=mp[a[i]];  //离散化数组a
    for(int i=1;i<=n;i++){  //正序遍历[1,n],统计每个元素前面比它大的数的个数
        change(a[i],1);
        cnt[i]+=(i-query(a[i]));
        //正序遍历i,将树状数组编号为a[i]的值加1,即标记已经遍历过的排在前面的值对应的离散编号(升序编号)
        //排a[i]前的数字均已标记,query(a[i])为树状数组编号a[i]前面标记1的总和,
        //即原数组中a[i]前面比它小或等于的数的个数和,则i-query(a[i])为a[i]前面比它大的数的个数和
    }
    memset(s,0,sizeof(s));  //清空s数组,为第二次统计做准备(change处理的为s数组)
    for(int i=n;i>=1;i--){  //逆序遍历[n,1],统计每个元素后面比它小的数的个数
        change(a[i],1);
        cnt[i]+=query(a[i]-1);
        //逆序遍历i,将树状数组编号为a[i]的值加1,即标记已经遍历过的排在后面的值对应的离散编号(升序编号)
        //排a[i]后的数字均已标记,query(a[i]-1)为树状数组编号a[i]-1后面标记1的总和,
        //即原数组中a[i]后面比a[i]-1小或等于的数的个数和,则query(a[i]-1)为a[i]后面比它小的数的个数和
    }
    for(int i=1;i<=n;i++)  ans+=cnt[i]*(cnt[i]+1)/2;
    //计算总代价ans,对于第i个数,cnt[i]为该数需要交换的次数,则其代价为1加到cnt[i],即cnt[i]*(cnt[i]+1)/2
    cout<<ans;
    return 0;    
}