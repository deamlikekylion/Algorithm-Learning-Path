// 万能头文件，包含所有C++常用库
#include<bits/stdc++.h>
// 宏定义：简化代码书写，提升编译/运行效率
#define inl inline        // 内联函数，减少函数调用开销
#define reg register     // 寄存器变量，加快变量访问速度
#define int long long    // 核心！全部变量用long long，防止数据溢出（题目数值极大）
#define fst ios::sync_with_stdio(0);cin.tie(0);cout.tie(0); // 加速cin/cout，关闭同步
#define rep(i,x,y) for(reg int i=x;i<=(y);++i)  // 正向循环宏
#define per(i,x,y) for(reg int i=x;i>=(y);--i)  // 反向循环宏
using namespace std;

// 常量定义：数组最大长度（题目n≤1e5，开1e5+5防止越界）
const int N=1e5+5;
// 全局变量：
int n,k,T;        // n=总人数，k=要选的人数，T=方差阈值
int a[N];         // 存储原始成绩数组
int sum_s[N];     // 前缀平方和数组：sum_s[i] = v[1]² + v[2]² + ... +v[i]²
int sum[N];       // 前缀和数组：sum[i] = v[1] + v[2] + ... +v[i]
int v[N];         // 临时数组：存储前x个成绩，用于排序

// ---------------- 核心判断函数 ----------------
// 功能：检查【前x个同学】中，能否选出k个成绩，使得方差 < T
// 返回值：true=满足条件，false=不满足
bool check(int x){
    // 1. 把原始数组前x个成绩复制到临时数组v（不修改原数组）
    rep(i,1,x) v[i]=a[i];
    
    // 2. 贪心核心：对前x个成绩排序
    // 原理：排序后【连续k个数字】的方差一定最小！离散程度最低
    sort(v+1,v+x+1);
    
    // 3. 预处理前缀和 + 前缀平方和（O(x)时间）
    rep(i,1,x){
        sum_s[i] = sum_s[i-1] + v[i]*v[i];  // 累计平方和
        sum[i]   = sum[i-1] + v[i];         // 累计普通和
    }
    
    // 4. 滑动窗口：遍历所有长度为k的连续区间，找最小方差
    // 窗口范围：[i-k+1, i]，i从k开始（保证窗口长度≥k）
    double ans = DBL_MAX;  // 初始化最小方差为无穷大（double最大值）
    rep(i,k,x){
        // 公式核心：方差化简式（避免计算平均值，减少浮点误差）
        // 原方差：σ² = (Σv_i²/k) - (Σv_i)²/(k²)
        // 化简后分子：k*Σv_i² - (Σv_i)²，最终方差 = 分子/(k²)
        
        // sum1 = 窗口内k个数的平方和
        double sum1 = sum_s[i] - sum_s[i-k];
        // sum2 + sum3 是化简后的 (Σv_i)² / k
        double sum2 = 2*(1.0*sum[i]-sum[i-k])*((1.0*sum[i]-sum[i-k])/k);
        double sum3 = ((1.0*sum[i]-sum[i-k])/k)*((1.0*sum[i]-sum[i-k])/k)*k;
        
        // 计算当前窗口的方差，更新最小值
        ans = min(ans, (sum1 - sum2 + sum3)/k);
    }	
    
    // 5. 判断最小方差是否 < 阈值T
    return ans < T;
}

// ---------------- 主函数 ----------------
signed main(){  // 因为用了#define int long long，主函数必须用signed
    fst;  // 开启cin/cout加速
    
    // 输入：总人数n、选k人、方差阈值T
    cin>>n>>k>>T;
    // 输入n个同学的成绩
    rep(i,1,n) cin>>a[i];
    
    // 二分答案：找【最小的检查人数】
    int l = k;    // 左边界：至少要检查k个人（才能选k个）
    int r = n;    // 右边界：最多检查全部n个人
    int ans = -1; // 答案初始化为-1（默认无解）
    
    // 标准二分查找模板
    while(l <= r){
        int mid = (l + r) >> 1; // 取中间值：(l+r)/2，位运算更快
        
        // 检查前mid个人是否满足条件
        if(check(mid)){
            ans = mid;    // 满足条件，记录答案
            r = mid - 1;  // 尝试找更小的答案（往左二分）
        }else{
            l = mid + 1;  // 不满足，需要检查更多人（往右二分）
        }
    }
    
    // 输出最终答案（无解输出-1，有解输出最小人数）
    cout << ans;
    return 0;
}