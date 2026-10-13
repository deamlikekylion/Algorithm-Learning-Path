#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<int> nums;  int k;
    //法一:借助辅助数组直接移位,时间复杂度O(n),空间复杂度O(n)
    int n=nums.size();
    vector<int> tmp(n);
    for(int i=0;i<n;i++){
        tmp[(i+k)%n]=nums[i];
    }
    nums=tmp;
    //法二:三次翻转,时间复杂度O(n),空间复杂度O(1)
    k%=n;                                  //如果k大于数组长度,取模消去多余的整圈旋转
    reverse(nums.begin(),nums.end());      //1.翻转整个数组
    reverse(nums.begin(),nums.begin()+k);  //2.翻转前k个
    reverse(nums.begin()+k,nums.end());    //3.翻转剩下的元素
    return 0;
}
