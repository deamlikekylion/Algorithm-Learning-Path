#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef long long ll;
const int MAX = 4000; // 5√1e18 ≈ 3981，筛到4000足够
vector<int> primes;   // 预处理5次根号内的所有质数
bool is_prime[MAX + 5];

// 埃氏筛预处理质数
void init() {
    fill(is_prime, is_prime + MAX + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= MAX; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * 2; j <= MAX; j += i)
                is_prime[j] = false;
        }
    }
}

// 快速判断是否为立方数
bool is_cubic(ll n) {
    if (n == 1) return true;
    ll x = cbrtl(n);
    return x * x * x == n || (x + 1) * (x + 1) * (x + 1) == n;
}

// 快速判断是否为平方数
bool is_square(ll n) {
    if (n == 1) return true;
    ll x = sqrtl(n);
    return x * x == n || (x + 1) * (x + 1) == n;
}

bool check(ll n) {
    if (n == 1) return true; // 1=1²*1³ 合法
    for (int p : primes) {
        ll p2 = 1LL * p * p;
        if (n % p == 0) {
            // 只能被p整除1次 → 直接无解
            if (n % p2 != 0) return false;
            // 除尽p的所有因子
            while (n % p == 0) n /= p;
        }
        if (n == 1) return true; // 除完了，合法
    }
    // 剩余部分必须是平方数 或 立方数
    return is_square(n) || is_cubic(n);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); // 加速输入输出（必加，T=1e5）
    init();           // 预处理质数

    int T;
    cin >> T;
    while (T--) {
        ll n;
        cin >> n;
        cout << (check(n) ? "yes\n" : "no\n");
    }
    return 0;
}