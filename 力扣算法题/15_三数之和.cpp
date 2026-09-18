#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<int> nums;
    vector<vector<int>> ans;
    int n=nums.size();
    sort(nums.begin(),nums.end());  //先排序
    for(int i=0;i<n;i++){           //固定第一个数字nums[i]
        if(nums[i]>0)  break;       //剪枝:第一个数nums[i]>0由于排序过后面的都大于0,跳出       
        if(i>0&&nums[i]==nums[i-1])  continue;  
        //去重1:每次固定的第一个数字nums[i]不能相同
        int l=i+1,r=n-1;            //从i+1到n-1进行双指针遍历找剩下两个数
        while(l<r){
            int sum=nums[i]+nums[l]+nums[r];
            if(sum<0)  l++;
            else if(sum>0)  r--;
            else{
                ans.push_back({nums[i],nums[l],nums[r]});  //ans元素类型为数组,可用push_back({})添加
                while(l<r&&nums[l]==nums[l+1])  l++;       //去重2:找下一组符合的两个数l和r不能相同
                while(l<r&&nums[r]==nums[r-1])  r--;
                l++;  r--;  //继续移动寻找
            }
        }
    }
    return 0;
}