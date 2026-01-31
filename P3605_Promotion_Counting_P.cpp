#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;
int h[N],to[N],ne[N],idx;  //链式前向星相关变量
int n,x,s[N],p[N],b[N],ans[N];
//s[i]维护权值出现的次数,即表示能力指数为i的员工有几个
//p[i]一开始存入第i个员工的能力指数,后面进行离散化处理(原数值较大)
//b数组为p数组进行离散化处理的辅助数组
//ans[i]为第i个下属中比i强(权值p比i大)的个数

void add(int a,int b){  //邻接表加边
    to[++idx]=b;  
    ne[idx]=h[a];  
    h[a]=idx;
}

void change(int x,int k){  //向后修,点修改(将包含x的区间和s都加k)
    for(;x<=n;x+=x&-x)  s[x]+=k;  //x&-x取x的低位2次幂,x+x的低位2次幂=父下标(爬链)
}

int query(int x){  //向前查,前缀和
    int res=0;
    for(;x;x-=x&-x)  res+=s[x];
    return res;  //res为到x为止的前缀和(即目前搜索的点中权值<=x的个数)  
}

void dfs(int x){
    ans[x]-=query(n)-query(p[x]);
    //query(n)-query(p[x])表示此时搜索过的点中权值>x的个数  
    //此时未搜索x的子节点(下属)
    for(int i=h[x];i;i=ne[i])  dfs(to[i]);  //搜索x的子节点
    ans[x]+=query(n)-query(p[x]);
    //此时搜索完x的子节点,query(n)-query(p[x])中含有之前搜索过的不是x下属的点
    //但因为之前减去过这些点的个数,所以最后加完ans为下属中权值>x的点个数
    change(p[x],1);  //将权值为p[x]的次数+1(可放在dfs的任意位置)
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++)  cin>>p[i],  b[i]=p[i];
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++)  p[i]=lower_bound(b+1,b+n+1,p[i])-b;
    //离散化,lower_bound返回地址-b[0]的地址,p[i]离散成排序后b数组中的排名
    for(int i=2;i<=n;i++)  cin>>x,  add(x,i);  //上司x指向i
    dfs(1);
    for(int i=1;i<=n;i++)  cout<<ans[i]<<endl;
    return 0;
}