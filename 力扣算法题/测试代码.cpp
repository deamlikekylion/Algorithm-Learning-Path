#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        // 1. 将所有数字加入哈希集合，实现 O(1) 查找并自动去重
        unordered_set<int> st(nums.begin(), nums.end());
        
        int maxLen = 0;

        // 2. 遍历集合中的每一个数
        for (const int& num : st) {
            // 核心剪枝：只有当 num - 1 不存在时，num 才是序列的起点
            if (!st.count(num - 1)) {
                int currentNum = num;
                int currentLen = 1;

                // 从起点开始不断向后探索连续数字
                while (st.count(currentNum + 1)) {
                    currentNum += 1;
                    currentLen += 1;
                }

                // 更新全局最大长度
                maxLen = max(maxLen, currentLen);
            }
        }

        return maxLen;
    }
};