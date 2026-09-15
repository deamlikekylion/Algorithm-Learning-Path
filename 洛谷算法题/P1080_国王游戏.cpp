#include<bits/stdc++.h>
using namespace std;

struct node{
    int a,b;
}x[1005];  //结构体存储ab值
int n,sum[1005],tmp[1005],ans[1005],ls,lt,la;
//sum存储当前大臣前面人a的累乘值,ls为其长度(高精度sum[i]储存四位数字)
//tmp存储当前大臣获得的金币数,lt为其长度(高精度tmp[i]储存四位数字)
//ans存储最大的金币数,即最终答案,la为其长度(高精度ans[i]储存四位数字)
//sum[0]为sum的最低位,tmp[0],ans[0]为tmp,ans的最高位

//自定义比较函数,使x数组按a*b的值升序排列
bool cmp(node i,node j){  
    return i.a*i.b<j.a*j.b;
}

//高精度除法:sum/x[d].b,结果存到tmp中(按4位一组处理)
void div(int d){  
    memset(tmp,0,sizeof(tmp));  lt=1;  //清空tmp
    while(ls>0&&sum[ls]==0)  ls--;     //跳过前导零
    int res=0,flag=0;                  //初始化余数res,falg标记是否出现有效数字
    for(int i=ls;i>=1;i--){            //模拟竖式除法:从最高位到最低位处理
        res=10000*res+sum[i];          //余数*10000+当前位来组成新的被除数
        tmp[++lt]=res/x[d].b;          //计算当前位的商(4位组)
        if(tmp[lt]==0&&!flag)  lt--;   //若商为0且未出现有效数字,跳过该位(避免前导零)
        else  flag=1;                  //否则标记已出现有效数字
        res%=x[d].b;                   //更新余数(当前被除数%除数)
    }
}

//tmp>ans返回true
bool compare(){
    int i=1;  while(ans[i]==0&&i<=la)  i++;  //跳过前导零
    int j=1;  while(tmp[j]==0&&j<=lt)  j++;  
    if(la-i+1>lt-j+1)  return false;         //先比较位数,位数多的数更大
    if(la-i+1<lt-j+1)  return true;
    while(i<=la&&j<=lt){                     //位数相同则逐位比较
        if(ans[i]<tmp[j])  return true;
        if(ans[i]>tmp[j])  return false;
        i++;  j++;
    } 
    return false;                            //相等返回false不更新
}

//高精度乘法:sum=sum*x[d].a(按4位一组处理)
void mul(int d){
    for(int i=1;i<=ls;i++)  sum[i]*=x[d].a;  //每一位(4位组)先乘以x[d].a
    for(int i=1;i<=ls;i++){                  //处理进位(按4位一组,进位到下一位)
        sum[i+1]+=sum[i]/10000;              //超过4位的部分进位到下一组
        sum[i]%=10000;                       //当前组保留后4位
    }
    if(sum[ls+1]!=0)  ls++;                  //若最高位有进位,长度+1
}

int main(){
    cin>>n;  
    for(int i=0;i<=n;i++)  cin>>x[i].a>>x[i].b;
    sort(x+1,x+n+1,cmp);   //将大臣按其a*b值升序排列可使最大金币最少

    //计算最大金币数ans
    sum[1]=x[0].a;  ls=1;  //初始化sum,ls
    for(int i=1;i<=n;i++){
        div(i);            //计算sum/x[i].b,结果存入tmp
        if(compare()){     //若tmp大于ans,更新ans
            la=lt;  
            memcpy(ans,tmp,sizeof(tmp));
        }
        mul(i);            //计算sum=sum*x[i].a,更新sum
    }

    //输出ans
    int i=0;  while(i<=la&&ans[i]==0) i++;  //跳过前导零 
    cout<<ans[i];  i++;                     //输出第一位(无需补零)
    for(;i<=la;i++){                        //输出后续位(4位一组,不足4位补前导零)
        if(0<=ans[i]&&ans[i]<=9)           cout<<"000"<<ans[i];
        else if(10<=ans[i]&&ans[i]<=99)    cout<<"00"<<ans[i]; 
        else if(100<=ans[i]&&ans[i]<=999)  cout<<"0"<<ans[i];
        else                               cout<<ans[i]; 
    }
    return 0;
}