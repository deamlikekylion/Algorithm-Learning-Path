#include<bits/stdc++.h>
using namespace std;
typedef long long ll; // 数据范围到1e12，必须用long long

// 求最大公约数（欧几里得算法）
ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

// 分解质因数：返回map<质因数, 指数>
map<ll, ll> factorize(ll x) {
    map<ll, ll> res;
    for (ll i = 2; i * i <= x; ++i) {
        while (x % i == 0) {
            res[i]++;
            x /= i;
        }
    }
    if (x > 1) res[x]++; // 剩余的质因数
    return res;
}

// 求一组数的最大公共底数（所有数都是该底数的整数次幂）
ll get_max_base(vector<ll>& nums) {
    if (nums.size() == 1) return nums[0]; // 只有一个数，底数就是它自己
    
    // 分解第一个数的质因数，作为候选底数的基础
    auto factors = factorize(nums[0]);
    ll max_base = 1;
    
    // 遍历每个候选质因数
    for (auto& [p, e0] : factors) {
        // 检查所有数是否都是p的整数次幂
        bool valid = true;
        vector<ll> exponents; // 存储每个数中p的指数
        exponents.push_back(e0);
        
        for (int i = 1; i < nums.size(); ++i) {
            ll num = nums[i];
            ll cnt = 0;
            while (num % p == 0) {
                cnt++;
                num /= p;
            }
            // 如果num不为1，说明不是p的纯幂次，排除该质因数
            if (num != 1) {
                valid = false;
                break;
            }
            exponents.push_back(cnt);
        }
        
        // 如果该质因数合法，计算指数的最大公约数，得到候选底数
        if (valid) {
            ll g = exponents[0];
            for (ll e : exponents) g = gcd(g, e);
            max_base = max(max_base, (ll)pow(p, g)); // 底数为p^g
        }
    }
    return max_base;
}

int main() {
    int n;
    cin >> n;
    vector<ll> t(n);
    for (int i = 0; i < n; ++i) cin >> t[i];
    
    // 步骤1：去重 + 升序排序
    sort(t.begin(), t.end());
    t.erase(unique(t.begin(), t.end()), t.end()); // 标准去重方法，比手动前移更可靠
    n = t.size();
    if (n <= 1) { // 只有一个数，公比任意（题目保证有解，此处仅防御）
        cout << "1/1" << endl;
        return 0;
    }
    
    // 步骤2：计算相邻数的最简比值（分子、分母分开存储）
    vector<ll> a_list, b_list;
    for (int i = 0; i < n-1; ++i) {
        ll up = t[i+1], down = t[i];
        ll g = gcd(up, down);
        ll a = up / g;   // 最简分子
        ll b = down / g; // 最简分母
        a_list.push_back(a);
        b_list.push_back(b);
    }
    
    // 步骤3：求分子的最大公共底数x，分母的最大公共底数y
    ll x = get_max_base(a_list);
    ll y = get_max_base(b_list);
    
    // 步骤4：输出最简分数（x和y天然互质）
    cout << x << "/" << y << endl;
    
    return 0;
}