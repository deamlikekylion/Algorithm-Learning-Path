#include<bits/stdc++.h>
using namespace std;

int n, l;
int a[210][210];
// 定义CSP模板：1表示白（≥k），0表示黑（<k）
int csp[5][9] = {
    {1,1,1,1,1,1,1,1,1},
    {1,0,0,1,0,0,1,0,1},
    {1,0,0,1,1,1,1,1,0},
    {1,0,0,0,0,1,1,0,0},
    {1,1,1,1,1,1,0,0,1}
};
set<int> ans; // 存储所有合法k，自动去重并排序

int main() {
    cin >> n >> l;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    // 枚举所有可能的5×9子矩阵的左上角(i,j)
    for (int i = 0; i <= n - 5; i++) {
        for (int j = 0; j <= n - 9; j++) {
            vector<int> white, black; // 分别存储模板中“白”“黑”位置的像素值
            for (int r = 0; r < 5; r++) {
                for (int col = 0; col < 9; col++) {
                    int val = a[i + r][j + col];
                    if (csp[r][col] == 1) {
                        white.push_back(val);
                    } else {
                        black.push_back(val);
                    }
                }
            }
            // 计算白位置的最小值和黑位置的最大值
            int white_min = *min_element(white.begin(), white.end());
            int black_max = *max_element(black.begin(), black.end());
            // 合法k的范围：white_min ≤ k ≤ black_max
            for (int k = white_min; k <= black_max; k++) {
                ans.insert(k);
            }
        }
    }

    // 输出所有合法k
    for (int k : ans) {
        cout << k << endl;
    }

    return 0;
}