#include <iostream>
#include <vector>
using namespace std;

const int MAX_BIT = 19;  // 题目规定 X < 2^20，最高位为19位

int main() {
    // 关闭同步，加速输入输出（应对大数据量）
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> x(n);
        for (int i = 0; i < n; ++i) {
            cin >> x[i];
        }

        int ans = 0;  // 0=平局, 1=Alice胜, -1=Bob胜
        // 从最高位到最低位遍历
        for (int k = MAX_BIT; k >= 0; --k) {
            int cnt1 = 0;  // 第k位为1的数字个数
            for (int num : x) {
                if (num >> k & 1) cnt1++;
            }
            
            // 情况1：该位1的个数为偶数，无法分胜负，继续看下一位
            if (cnt1 % 2 == 0) continue;
            
            // 情况2：该位1的个数为奇数，决胜位！
            if (cnt1 == 1) {
                // 只有1个1，Alice直接拿走，必胜
                ans = 1;
            } else {
                // 1的个数>1，看0的个数的奇偶性
                int cnt0 = n - cnt1;
                if (cnt0 % 2 == 1) {
                    // 0的个数奇数 → Bob胜
                    ans = -1;
                } else {
                    // 0的个数偶数 → Alice胜
                    ans = 1;
                }
            }
            break;  // 找到决胜位，直接退出循环
        }
        cout << ans << '\n';
    }
    return 0;
}