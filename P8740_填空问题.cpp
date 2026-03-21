#include<iostream>
using namespace std;
int main() {
    string ans [] = {
        "The answer of task A", // 双引号中替换为 A 题的答案
        "The answer of task B", // 双引号中替换为 B 题的答案
        "The answer of task C", // 双引号中替换为 C 题的答案
        "The answer of task D", // 双引号中替换为 D 题的答案
        "The answer of task E", // 双引号中替换为 E 题的答案
    };
    char T;
    cin >> T;
    cout << ans[T - 'A'] << endl;
    return 0;
}
