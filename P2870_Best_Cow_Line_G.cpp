#include<bits/stdc++.h>
using namespace std;

const int N=2e6+5;  //N=2*n(此处n指加上反转字符串的长度)
char s[N];          //s存入原字符串加上反转后的字符串
int n,m;            //n为后缀个数(即字符串长度),m为桶的个数(桶排序)
int sa[N],rk[N];
//sa[i]=j表示后缀排序后,排第i个的为第j后缀
//rk[i]=j表示第i后缀的排名为j
int x[N],y[N],c[N];
//x[i]为桶数组,表示第i后缀所在的桶号
//y[i]为辅助数组,用来暂存sa,x数组
//c[i]为计数数组,表示桶号为i的桶里面有几个元素
char ans[N];

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

int main(){
    cin>>n;
    for(int i=1;i<=n;i++)  cin>>s[i];
    for(int i=2*n,j=1;i>=n+1,j<=n;i--,j++)  s[i]=s[j];
    n*=2;  m=90;  //大写字母最大的ASCII为Z=90
    get_sa();
    for(int i=1;i<=n;i++)  rk[sa[i]]=i;  
    //rk与sa互为反函数,rk[j]=i,sa[i]=j,所以rk[sa[i]]=i
    n/=2;  //恢复n大小
    int cnt=0,l=1,r=n;  //cnt为结果字符串的长度计数器,双指针:l从左端开始,r从右端开始
    while(l<r){  //当左右指针未相遇时,选择字符
        if(s[l]<s[r])       ans[++cnt]=s[l++];  //左端字符更小,选择左端字符
        else if(s[l]>s[r])  ans[++cnt]=s[r--];  //右端字符更小,选择右端字符
        else{  //两端字符相等时,通过后缀排名判断哪个选择更优
            if(rk[l]<rk[2*n-r+1])  ans[++cnt]=s[l++];
            //比较后缀l和后缀(2*n-r+1)的排名(排名小的优先)
            //前者是原字符串从L开始的后缀,后者是反转字符串中对应R的后缀
            else  ans[++cnt]=s[r--];
        }
    }
    ans[++cnt]=s[l];  //指针相遇后加入最后一个字符
    for(int i=1;i<=n;i++){
        cout<<ans[i];
        if(i%80==0)  cout<<endl;  //每80个字符换行
    }
    return 0;
}