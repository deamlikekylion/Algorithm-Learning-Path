#include<bits/stdc++.h>
using namespace std;

const int N=2e6+5;  //N=2*n
char s[N];          //s存入字符串
int n,m;            //n为后缀个数(即字符串长度),m为桶的个数(桶排序)
int sa[N];
//sa[i]=j表示后缀排序后,排第i个的为第j后缀
int x[N],y[N],c[N];
//x[i]为桶数组,表示第i后缀所在的桶号
//y[i]为辅助数组,用来暂存sa,x数组
//c[i]为计数数组,表示桶号为i的桶里面有几个元素

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
    scanf("%s",s+1);
    n=strlen(s+1);  m=122;
    get_sa();
    for(int i=1;i<=n;i++)  printf("%d ",sa[i]);
    return 0;
}