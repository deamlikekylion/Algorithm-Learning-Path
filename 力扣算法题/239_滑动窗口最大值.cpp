#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<int> nums;  int k;
    deque<int> dq;           //存储数组的下标,保持对应数值单调递减
    vector<int> ans;
    for(int i=0;i<nums.size();i++){
        while(!dq.empty()&&nums[dq.back()]<=nums[i]){  
            dq.pop_back();   //淘汰队尾所有比当前nums[i]小或相等的元素
        }
        dq.push_back(i);     //将当前元素下标入队
        if(dq.front()<=i-k){  
            dq.pop_front();  //检查队头元素是否已经滑出了窗口范围(窗口左边界是i-k+1)
        }
        if(i>=k-1){  
            ans.push_back(nums[dq.front()]);  //窗口大小达到k时,队头就是当前窗口的最大值
        }
    }
    //新的元素每次从队尾插入,并不断比较,把小于等于新元素的数字全部淘汰
    //队列从头到尾单调递减,然后从头检查队头是否还在窗口,不在的淘汰
    //最后当前的队头就是当前窗口的最大值
    return 0;
}