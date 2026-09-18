#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<int> nums;
    //解法一
    int len=0;
    for(auto i=nums.begin();i<nums.end();i++){  //通过指针遍历vector(最好换成下面解法的下标遍历)
        if(*i==0)  len++;
        else  *(i-len)=*i;  //指针*(i-len)即为*i的前第len个元素
    }
    for(auto i=nums.end()-1;i>=nums.end()-len;i--){
        *i=0;
    }
    //解法二
    int slow=0;
    for (int fast=0;fast<nums.size();fast++){  //通过下标直接遍历vector,和遍历int a[10]一样
        //只要遇到非0元素,就把它换到前面slow的位置
        if(nums[fast]!=0) {
            swap(nums[slow],nums[fast]);
            slow++;
        }
        //fast一直把非0元素换到前面,slow前面都是fast换过的非0元素,最终[slow,fast)区间全是0
    }
    //解法三
    int slow=0;
    for(int fast=0;fast<nums.size();fast++){  //把所有非0的数依次挪到最前面
        if(nums[fast]!=0)  nums[slow++]=nums[fast];
    }
    while(slow<nums.size())  nums[slow++]=0;  //后面剩余的位置全部填0
    return 0;
}