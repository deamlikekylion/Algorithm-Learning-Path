#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
const int N = 1e6 + 10, mod = 998244353;

ll n, a[N], res;               // n: 数组长度   a[]: 原始数组   res: 最终答案
ll last, stlast;               // 下面两个变量只在合并 gcd 区间时临时用
vector<pair<ll, ll>> vp1, vp2; // vp1: 上一次迭代留下的 (gcd值 , 最左下标) 列表
                               // vp2: 本轮新算出的列表
                               // 每个 pair 的第一个元素是区间的 GCD 值
							   // 第二个元素是该 GCD 对应的最左端点
							   
ll gcd(ll a, ll b) {  // 手写 gcd，递归写法
    return b ? gcd(b, a % b) : a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
 
    // 初始化：以第 1 个数为右端点时只有一个区间 [1,1] 
    vp1.emplace_back(a[1], 1);   // (gcd, left) = (a1, 1)
    res = a[1];                  // 只有一个区间的和就是 a1
 
    // 从第 2 个数开始扫描右端点 i 
    for (int i = 2; i <= n; ++i) {
        vp2.clear();             // 准备本轮的新列表
 
        // 先把 [i,i] 这个新区间放进去
        vp2.emplace_back(a[i], i);
        last = a[i], stlast = i; // last 记录“上一个”gcd 值，方便合并相同值
 
        // 把 vp1 中所有区间和 a[i] 再取一次 gcd，并合并相邻且值相同的区间 
        for (auto v : vp1) {
            ll num = v.first;      // 之前的 gcd 值
            ll st  = v.second;     // 这个 gcd 对应的最左端点
            num = gcd(num, a[i]);  // 新 gcd
            if (num != last) {     // gcd与上一个不同，新开一段
                vp2.emplace_back(num, st);
            } else {               // gcd与上一个相同，向左延长区间
                vp2.back().second = st;
            }
            last = num;            // 更新“上一个”gcd 值
        }
 
        // 计算“以 i 为右端点的所有区间”对答案的贡献 
        last = i + 1;              // last 先设成一个哨兵，便于公式写差分
        for (auto v : vp2) {
            ll g   = v.first;      // 当前这段的 gcd
            ll l   = v.second;     // 这段区间的最左端点
            /* 左端点范围是 [l, last-1]（last 初始为 i+1）
			   其和为 Σj = (l + (last-1)) × (last - l) / 2
               每个左端点 j 对应的贡献是 g × i × j
			  （因为体育价值是 l×r×gcd，这里 r=i，l=j）
			   因此，该区间的总贡献为 g × i × 左端点之和sum */
            ll sum = (last + l - 1) * (last - l) / 2 % mod;
            res = (res + g * i % mod * sum % mod) % mod;
            // ( a×b) % mod = [(a % mod) ×(b % mod)] % mod
            // 括号内 mod 不影响结果同时防止 g* i * sum 溢出 
            last = l;              // 向左推进
        }
 
        // 把 vp2 变成下一轮用的 vp1 （v.swap(v1)复杂度为O(1)） 
        vp1.swap(vp2);  //不可使用直接赋值，其复杂度为O(vp2.size) 
    }
 
    cout << res << '\n';
    return 0;
}