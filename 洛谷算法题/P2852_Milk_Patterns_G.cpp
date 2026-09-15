#include<bits/stdc++.h>
using namespace std;

const int N=4e4+5;  //N=2*n
const int M=1e6+5;
int s[N];           //s存入字符串(本题存入数字)
int n,m,k;          //n为后缀个数(即字符串长度),m为桶的个数(桶排序)
int sa[N],rk[N],height[N];
//sa[i]=j表示后缀排序后,排第i个的为第j后缀
//rk[i]=j表示第i后缀的排名为j
//height[i]=LCP(sa[i],sa[i-1]),表示排名为i和i-1的后缀的最长公共前缀的长度
int x[N],y[N],c[N];
//x[i]为桶数组,表示第i后缀所在的桶号
//y[i]为辅助数组,用来暂存sa,x数组
//c[i]为计数数组,表示桶号为i的桶里面有几个元素
int b[N],mp[M];     //用于离散化s[i]的值,以减少桶的数量

void get_sa(){  //桶排序+倍增法得到sa数组
    int i,j,k;
    //按第一个字母排序
    for(i=1;i<=n;i++)  c[x[i]=s[i]]++;     
    for(i=1;i<=m;i++)  c[i]+=c[i-1];
    for(i=n;i;i--)     sa[c[x[i]]--]=i;
    for(k=1;k<=n;k<<=1){  //倍增法
        //按第二关键字排序
        memset(c,0,sizeof(c));
        for(i=1;i<=n;i++)  y[i]=sa[i];  //y数组辅助暂存sa,按第一关键字排序
        for(i=1;i<=n;i++)  c[x[y[i]+k]]++;  
        for(i=1;i<=m;i++)  c[i]+=c[i-1];  
        for(i=n;i;i--)     sa[c[x[y[i]+k]]--]=y[i];
        //按第一关键字排序
        memset(c,0,sizeof(c)); 
        for(i=1;i<=n;i++)  y[i]=sa[i];  //y数组辅助暂存sa,按第二关键字排序
        for(i=1;i<=n;i++)  c[x[y[i]]]++;
        for(i=1;i<=m;i++)  c[i]+=c[i-1];  
        for(i=n;i;i--)     sa[c[x[y[i]]]--]=y[i];
        //把后缀放入桶数组    
        for(i=1;i<=n;i++)  y[i]=x[i];  //y数组辅助暂存x
        for(m=0,i=1;i<=n;i++){  //更新桶数组x,使x[i]存的是i后缀前2k个字母对应的桶号
            if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])  x[sa[i]]=m;
            //如果相邻后缀的第一关键字和第二关键字对应的桶号都相等,则其前2k个字母相同,放入同一桶中
            else  x[sa[i]]=++m;  //不同则放入下一个桶中
        }  
        if(m==n)  break;  //一共有n个桶时表示已排好    
    }  
}

void get_height(){  //求height
    int i,j,k;
    for(i=1;i<=n;i++)  rk[sa[i]]=i;  //rk与sa互为反函数
    for(j=1,k=0;j<=n;j++){  //枚举j后缀
        if(rk[j]==1)  continue;  //排序为1的height为0
        if(k)  k--;  //上一个后缀的height值减1,因为定理:height[rk[j]]>=height[rk[j-1]]-1
        int t=sa[rk[j]-1];  //找出j后缀的前邻t后缀(j后缀排i(rk[j])位,t后缀排i-1(rk[j]-1)位)
        while(j+k<=n&&t+k<=n&&s[j+k]==s[t+k])  k++;
        height[rk[j]]=k;  //注意height的下标为j后缀的排名
    }
}

int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++)  cin>>s[i],b[i]=s[i];
    //离散化:将原始值(0~1e6)映射为连续整数(从1或0开始),减少桶的数量
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++){
        mp[b[i]]=mp[b[i-1]]+(b[i]!=b[i-1]);  //相同值映射为同一整数
        //b[0]=0,mp[0]=0,b[1]!=b[0]则mp[b[1]]=1;b[1]=b[0]则mp[b[1]]=0
        m=max(m,mp[b[i]]);                   //记录离散化后的值域最大值
    }
    for(int i=1;i<=n;i++)  s[i]=mp[s[i]];    //将a数组转换为离散化后的值             
    get_sa();  get_height();

    //题目要求找重复了至少k次的最长子序列
    //对于height数组,其表示排名相邻的后缀的最长公共前缀
    //eg:原串aabaaaab,排名相邻(2,3)的后缀为aaab(5),aab(6),h[3]=2,
    //则他们的最长公共前缀aa在原串至少重复了2次(1次是5后缀的开头,1次是6后缀的开头)
    //而排名相邻(2,3,4)的后缀aaab(5),aab(6),aabaaaab(1),h[3]=2,h[4]=3
    //取h[3],h[4]中的最小值,其对应的公共前缀三个后缀都包含,所以在原串至少重复了3次
    //且是三个后缀的最长公共前缀
    //所以对于k-1个连续的h[i],其中的最小值就是对应k个后缀的最长公共前缀,且在原串至少重复k次
    //而所有连续k−1个height最小值中的最大值就是至少重复k次的最长子序列长度
    int ans=0;  deque<int> q;  
    //通过单调(双端)队列滑动长度为k-1的窗口维护其最左端为k-1区间内最小h的序号(队列存h的序号)  
    for(int i=1;i<=n;i++){
        while(!q.empty()&&height[q.back()]>=height[i])  q.pop_back();
        //如果最右端的值大于当前的值就去除当前的最右端,因为它不可能成为该区间的最小值了
        //(当前的值比它少),维护了队列的单调性(从左往右单增),所以队列里不一定有k-1个元素
        q.push_back(i);
        if(i>=(k-1)){
            while(!q.empty()&&q.front()<=i-(k-1))  q.pop_front();
            //i为最右端,窗口区间为[i-(k-1)+1,i],最左端(q.front())<=i-(k-1)的都要去除
            ans=max(ans,height[q.front()]);
            //滑到下一个区间前取当前队列最左端(当前区间最小值)与ans比较让ans取最大
        }
    }
    cout<<ans;
    return 0;
}