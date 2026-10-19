#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<int> nums;
    int n=nums.size(),ans=n+1;  //初始ans=n+1,后面如果1到n全部都在对应的坑位上,那缺的就是n+1,ans也没变
    for(int i=0;i<n;i++){       //萝卜归位:把每个在[1,n]范围内的数x放到下标x-1的位置
        while(nums[i]>=1&&nums[i]<=n&&nums[i]!=nums[nums[i]-1]){
        //条件:数字nums[i]在[1,n]之间,且目标坑位(nums[nums[i]-1])上的数字不是自己(防止死循环)
            swap(nums[i],nums[nums[i]-1]);            
        }
    }
    for(int i=0;i<n;i++){       //查坑:找出第一个没有对上号的坑位
        if(nums[i]!=i+1){
            ans=i+1;            //下标i应该放i+1,没有放就说明缺它
            break;
        }
    }
    return 0;
}