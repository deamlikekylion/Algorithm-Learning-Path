#include<bits/stdc++.h>
using namespace std;

string s;  // 存储完整的正则表达式输入
int idx = 0;  // 全局索引，记录当前遍历到的字符位置

// 递归函数：计算从当前索引开始的正则表达式能匹配的最长长度
int dfs() {
    int res = 0;  // 记录当前分支的最大长度（初始为0）
    int temp = 0; // 记录|左边分支的长度（临时变量）
    
    // 遍历字符，直到字符串结束或遇到右括号）
    while (idx <(int) s.size()) {
        char c = s[idx];  // 获取当前字符
        idx++;  // 索引后移（处理下一个字符）
        
        if (c == 'x') {
            // 遇到x，当前分支长度+1
            temp++;
        } else if (c == '(') {
            // 遇到左括号，递归计算括号内的长度，加到当前分支
            temp += dfs();
        } else if (c == ')') {
            // 遇到右括号，结束当前括号内的计算，返回当前分支最大值
            res = max(res, temp);
            return res;
        } else if (c == '|') {
            // 遇到|，取左边分支的最大值，然后递归计算右边分支
            res = max(res, temp);  // 保存左边分支的最大值
            temp = 0;  // 重置临时变量，计算右边分支
        }
    }
    
    // 遍历到字符串末尾，返回当前分支的最大值
    res = max(res, temp);
    return res;
}

int main() {
    getline(cin, s);
    cout << dfs() << endl;
    return 0;
}