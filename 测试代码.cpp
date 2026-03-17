#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define all(v) v.begin(), v.end()
const double PI = acos(-1);
const double HALF_PI = PI / 2; // 0到90度对应的弧度

void sol() {
    int n;
    cin >> n;
    vector<pair<double, double>> rng; // 存储裁剪后的有效角度区间

    for (int i = 0; i < n; i++) {
        int x, y, r;
        cin >> x >> y >> r;
        
        // 1. 计算地雷圆心的极角θ（[0, π/2]）
        double theta = atan2(y, x);
        // 2. 计算原点到圆心的距离d
        double d = sqrt(x * x + y * y);
        // 3. 计算角度偏差Δθ（相切时的角度偏移）
        double delta = asin(r / d);
        
        // 4. 原始危险区间 [L, R]
        double L = theta - delta;
        double R = theta + delta;
        
        // 5. 裁剪区间到 [0, π/2]
        L = max(L, 0.0);
        R = min(R, HALF_PI);
        
        // 6. 仅保留有效区间（L < R）
        if (L < R) {
            rng.emplace_back(L, R);
        }
    }

    // 7. 按区间左端点排序，为合并做准备
    sort(all(rng), [](const pair<double, double>& a, const pair<double, double>& b) {
        return a.first < b.first;
    });

    // 8. 合并重叠/相邻区间
    vector<pair<double, double>> merged;
    for (auto& interval : rng) {
        if (merged.empty()) {
            merged.push_back(interval);
        } else {
            auto& last = merged.back();
            // 若当前区间与最后一个合并区间重叠/相邻，合并
            if (interval.first <= last.second) {
                last.second = max(last.second, interval.second);
            } else {
                merged.push_back(interval);
            }
        }
    }

    // 9. 计算危险角度总长度
    double danger = 0.0;
    for (auto& [L, R] : merged) {
        danger += R - L;
    }

    // 10. 计算安全概率并输出
    double safe = HALF_PI - danger;
    double ans = safe / HALF_PI;
    cout << fixed << setprecision(3) << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sol();
    return 0;
}