#include<bits/stdc++.h>
using namespace std;

int n,f[100005];  //f[i]表示长度为i的字符串逆序对的最大个数

void get_max(){
    for(int i=2;i<=26;i++)  f[i]=f[i-1]+i-1;
    //对于长度小于26的字符串,最多逆序对即每次在前面加入下一个字母,多i-1个逆序对
    int sum=26,vis1[30];  
    //sum记录字符串长度,vis1[i]表示字符i出现的次数(i从0到25对应a到z)
    for(int i=0;i<26;i++)  vis1[i]=1;
    for(int i=27;f[i-1]<n;i++,sum++){  
    //i从27开始遍历,循环条件:前一个长度的最大逆序对仍小于目标n则继续扩展长度
        int ch=(i%26-1+26)%26;     //计算新增字符编号:按a(0),b(1)...z(25)循环
        f[i]=f[i-1]+sum-vis1[ch];  //新增逆序对=总字符数-同字符数(因为同字符不产生逆序对)
        vis1[ch]++;                //该字符出现次数+1
    }
}

int cnt[30],vis[30];
//cnt[ch]:已确定位置中字符ch的出现次数,vis[ch]:后续待构造位置中,按最大逆序对构造时ch的出现次数

int get_add(int ch){  //计算选择字符ch时,能新增的逆序对数
    int add=0;
    for(int i=0;i<ch;i++)  add+=vis[i];
    //1:已确定字符中<ch的数量→这些字符和ch构成逆序对(ch在后面)
    //(vis是后续待构造的,可任意排列,所以全部算入)
    for(int i=ch+1;i<26;i++)  add+=cnt[i]+vis[i];
    //2:已确定字符中>ch的数量+后续待构造中>ch的数量
    //(cnt已确定位置,ch在前面,所以>ch的都和ch构成逆序对)
    return add;  //返回新增逆序对总数
}

//检查函数:id当前构造到第id个位置,m字符串总长度,ch当前尝试选的字符,sum已累计的逆序对数
//返回值:选ch后,剩余位置按最大逆序对构造,能否让总逆序对数≥n
bool check(int id,int m,int ch,int sum){
    for(int i=id+1;i<=m;i++){
        int maxadd=0,ch1=0;        //maxadd当前位置能新增的最大逆序对,ch1对应字符
        for(int j=0;j<26;j++){     //枚举所有26个字符找能新增最多逆序对的那个(最大构造策略)
            int add=get_add(j);    //计算选j的新增逆序对
            if(maxadd<add){        //更新最大逆序对和对应字符
                maxadd=add;
                ch1=j;
            }
        }
        vis[ch1]++;  sum+=maxadd;  //选中该字符后续构造中该字符数+1,sum累计逆序对数
    }
    memset(vis,0,sizeof(vis));     //重置vis数组(避免影响后续检查)
    return sum>=n;                 //总逆序对≥n则可行,返回true
}

void solve(int m){
    int sum=0;                        //已累计的逆序对数
    string ans;                       //最终答案字符串
    for(int i=1;i<=m;i++){            //逐位置构造(第1位到第m位)
        for(int j=0;j<26;j++){        //枚举当前位置的字符(从a(0)开始,保证字典序最小)
            int initadd=get_add(j);   //计算选字符j时新增的逆序对数
            cnt[j]++;  sum+=initadd;  //已确定字符j的数量+1,sum累计逆序对数
            if(check(i,m,j,sum)){     //检查:选j后,剩余位置能否构造出≥n的逆序对
                ans+=('a'+j);         //可行则加入答案,跳出循环
                break;
            }
            cnt[j]--;  sum-=initadd;  //不可行则回溯:恢复cnt和sum
        }
    }
    cout<<ans;
}

int main(){
    cin>>n;  get_max();     //预计算各长度的最大逆序对数f[i]
    for(int i=2;i<=n;i++){  //找到能容纳n的最短长度m(第一个f[i]≥n的i)
        if(f[i]>=n){
            solve(i);
            break;
        }
    }
    return 0;
}