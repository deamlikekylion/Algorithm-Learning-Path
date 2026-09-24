#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<int> nums;  int k;
    unordered_map<int,int> mp;  //哈希表记录:<前缀和,出现次数>
    int pre=0,ans=0;            //pre当前累计的前缀和
    mp[0]=1;                    //关键初始化:特殊情况前缀和为0,默认出现过1次
    for(int i : nums){
        pre+=i;                 //计算当前前缀和
        if(mp.count(pre-k))  ans+=mp[pre-k];
        //如果前面存在某个前缀和pre-k,说明两者之间的子数组(pre-(pre-k))之和就是k
        //ans+=之前前缀和为pre-k的次数
        mp[pre]++;              //把当前前缀和记录到哈希表中
    }
    return 0;
}