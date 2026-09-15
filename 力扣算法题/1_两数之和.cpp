#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<int> nums;  int target;
    map<int,int> mp;  int i,j;  
    //此题不能用sort排序,因为题目要求的是原始下标,可以用哈希表遍历一次找是否有target-nums[i]
    for(i=0;i<nums.size();i++){
        int x=target-nums[i];
        if(mp.count(x)){
            j=mp[x];  break;  //找到后记得返回
        }
        mp[nums[i]]=i;
    }
    cout<<'['<<j<<','<<i<<']';  
    //j一定比i小,因为正在遍历i,能查到x则它对应的序号j已经遍历过了
    return 0;
}