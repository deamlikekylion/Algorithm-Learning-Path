#include<bits/stdc++.h>
using namespace std;

int main(){
    string n;  int k,len,a[255];  
    cin>>n>>k;  len=n.size();
    for(int i=1;i<=len;i++)  a[i]=n[i-1]-'0';  //a[1]为最高位
    int rest=len-k,cnt=0,flag=0,min,t=1;  
    //rest为要留下的数字个数,cnt为目前确认留下的数字个数
    //min,t为每次循环要找的最小数索引和循环开始的索引
    while(cnt<rest){  
    //先从左边k+1中找最小的数,其可留下并删去其左边的所有数(min-t个)
    //接着继续循环其右边(k-(min-t))个再找最小数直到留下rest个数(即删完k个)
        min=t;
        for(int i=t;i<=k+t;i++)  if(a[min]>a[i])  min=i;
        if(a[min])  flag=1;  //a[min]非零则开始输出
        if(flag)  cout<<a[min];
        k-=min-t;  t=min+1;  cnt++;
    }    
    if(!flag)  cout<<0;      //k>n,未进入循环,flag=0,输出0
    return 0;
}