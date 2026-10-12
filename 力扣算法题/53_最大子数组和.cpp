#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<int> nums;
    int max_sum=nums[0];  //为最大子数组和,初始为第一个数(不能初始为0,否则全负数数组输出最大子数组和为0)
    int cur_sum=0;        //为以当前元素结尾的最大子数组和
    for(int i : nums){
        cur_sum=max(i,cur_sum+i);      //dp思想:前面和是正的则继续累加,否则重新从i开始
        max_sum=max(max_sum,cur_sum);  //更新最大子数组和
    }
    return 0;
}