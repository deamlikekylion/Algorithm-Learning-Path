#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<int> nums;
    unordered_set<int> s(nums.begin(),nums.end());
    //将所有数字加入哈希集合,实现O(1)查找并自动去重
    //unordered_set:插入n个数O(n),查找1一个数O(1)
    //set:插入n个数O(n*log(n)),查找1一个数O(log(n)),set=unordered_set*log(n),会自动排序
    //set初始化,也可以s={1,2,3}(注意.begin(),.end()对于int a[10]不能用,可用a,a+10)
    int max_len=0;
    for(const int&i : s){   //遍历集合中的每一个数
        if(!s.count(i-1)){  //核心剪枝,只有当i-1不存在时,i才是序列的起点
            int j=i,len=1;
            while(s.count(j+1)){       //从起点开始不断向后探索连续数字
                j++;  len++;
            }
            max_len=max(max_len,len);  //更新全局最大长度
        }
    }
    return 0;
}