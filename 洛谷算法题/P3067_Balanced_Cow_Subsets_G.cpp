#include<bits/stdc++.h>
using namespace std;

const int N=(1<<20)+5;  
//用二进制记录选择的情况(子集),第i位为1则对应选了第i头牛
//最多20头,所以要至少二进制位数为20的数字,即(1<<20)-1,所以取N=1<<20+5
//加括号,+优先级大于<<
int n,mid,a[25],ans[N];
//a存储奶牛产奶量,ans[i]为选择情况(子集)为i时是否平衡,平衡为1,不平衡为0
map<int,int> mp;  int cnt;
//mp映射前半段所有sum离散化的id,初始为0,对应没有该sum,cnt为当前sum的id
vector<int> ve[N];
//记录相同sum的选择情况(子集)(即dfs中的now)

//x:当前处理的奶牛编号;sum:当前a-b的和(a是集合A和,b是集合B和)；
//now:状压,二进制表示已选的奶牛
void dfs1(int x,int sum,int now){
    if(x>mid){                          //前半部分处理完毕
        if(mp[sum]==0)  mp[sum]=++cnt;  //若sum未被离散化分配一个唯一id
        ve[mp[sum]].push_back(now);     //记录该sum对应的前半部分选择情况
        return;
    }
    //三种状态:选入集合A(sum+a[x]),选入集合B(sum-a[x]),不选(sum)
    //选入x则将now二进制的第x为变成1:1<<(x-1)使1移动到第x位,now|它则now第x位为1
    dfs1(x+1, sum+a[x], now | (1 << (x-1) ));
    dfs1(x+1, sum-a[x], now | (1 << (x-1) ));
    dfs1(x+1, sum, now);
}

//前半段a放集合A,b方集合B,后半段c放集合A,d方集合B,平衡需满足a+c=b+d
//即a-b=d-c,两段的sum相等,dfs2中sum为d-c的和
void dfs2(int x,int sum,int now){
    if(x>n){            //后半部分处理完毕
        int t=mp[sum];  //查找前半部分中sum对应的离散化id
        if(t){          //若存在对应的前半部分状态则进行标记
            for(int i=0;i<ve[t].size();i++){
                ans[ve[t][i] | now]=1;
                //前半状态与后半状态"或作,得到完整子集选择情况,标记为平衡子集                
            }
        }
        return;
    }
    //三种状态递归
    dfs2(x+1, sum+a[x], now | (1 << (x-1) ));
    dfs2(x+1, sum-a[x], now | (1 << (x-1) ));
    dfs2(x+1, sum, now);
}

int main(){
    cin>>n;  mid=n/2;  
    for(int i=1;i<=n;i++)  cin>>a[i];
    dfs1(1,0,0);      //处理前半部分,生成所有可能的sum和对应状态
    dfs2(mid+1,0,0);  //处理后半部分,与前半部分的sum匹配,标记平衡子集
    int num=0;
    for(int i=1;i<(1<<n);i++)  num+=ans[i];  //统计所有被标记的平衡子集数量
    cout<<num<<endl;
    return 0;
}