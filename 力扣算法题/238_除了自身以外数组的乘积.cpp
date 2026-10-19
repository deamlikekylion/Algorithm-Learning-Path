#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<int> nums;
    int n=nums.size();
    vector<int> ans(n);       //必须先分配n个空间,否则为空数组后面不能用下标直接访问  
    ans[0]=1;
    for(int i=1;i<n;i++){     //第一次循环:计算每个元素左边所有数的乘积
        ans[i]=ans[i-1]*nums[i-1];
    }
    int r=1;
    for(int i=n-1;i>=0;i--){  //第二次循环:用变量r维护右边所有数的乘积,并直接乘到ans[i]上
        ans[i]=ans[i]*r;      //左边的积*右边的积
        r*=nums[i];           //把当前数字乘入r,供左边的下一个元素使用
    }
    return 0;
}