#include <bits/stdc++.h>
using namespace std;

int n;  // 目标逆序对数（冒泡排序交换次数）

/*  
核心思路：
1. 贪心构造最短字符串：先找到能容纳V个逆序对的最短长度m（长度m的最大逆序对数≥V）
2. 贪心构造字典序最小：逐位置枚举字符（从'a'开始），检查选当前字符后，剩余位置按最大逆序对
构造能否凑够V，能则选定（保证字典序最小）
*/

int f[1010];  // f[i]表示长度为i的字符串能构造的最大逆序对数

// 预计算不同长度字符串的最大逆序对数f[i]
int get_max(){ 
    // 步骤1：长度≤26时，最大逆序对是"zyx...a"这种完全逆序的情况，逆序对数为i*(i-1)/2
    // 递推：f[i] = f[i-1] + (i-1)（新增第i个字符，和前i-1个都构成逆序对）
    for(int i = 2; i <= 26; i ++) f[i] = f[i - 1] + i - 1; 
    
    int sum = 26;  // sum记录当前字符串的总字符数（初始26个不同字符）
    int vis[30] = {0};  // vis[ch]记录字符ch（0=a,1=b...）的出现次数
    for(int i = 0; i < 26; i ++) vis[i] = 1;  // 初始26个字符各1个
    
    // 步骤2：长度>26时，新增字符按a→b→c...循环（保证字典序小）
    // 循环条件：前一个长度的最大逆序对仍小于目标n，继续扩展长度
    for(int i = 27; f[i - 1] < n; i ++, sum ++){ 
        // 计算新增字符的编号：按a(0)、b(1)...z(25)循环
        int ch = (i % 26 - 1 + 26) % 26; 
        // 新增逆序对 = 总字符数 - 同字符数（因为同字符不产生逆序对）
        f[i] = f[i - 1] + sum - vis[ch]; 
        vis[ch] ++;  // 该字符出现次数+1
    }
}

// 全局变量：
int cnt[30];  // cnt[ch]：已确定位置中字符ch的出现次数
int vis[30];  // vis[ch]：后续待构造位置中，按最大逆序对构造时ch的出现次数

// 计算：选择字符ch时，能新增的逆序对数
int get_add(int ch){
    int add = 0;
    // 部分1：已确定字符中 < ch 的数量 → 这些字符和ch构成逆序对（ch在后面）
    // （vis是后续待构造的，可任意排列，所以全部算入）
    for(int i = 0; i < ch; i ++) add += vis[i]; 
    // 部分2：已确定字符中 > ch 的数量 + 后续待构造中 > ch 的数量
    // （cnt已确定位置，ch在前面，所以>ch的都和ch构成逆序对）
    for(int i = ch + 1; i < 26; i ++) add += cnt[i] + vis[i]; 
    return add;  // 返回新增逆序对总数
}

// 检查函数：
// id：当前构造到第id个位置；m：字符串总长度；ch：当前尝试选的字符；sum：已累计的逆序对数
// 返回值：选ch后，剩余位置按最大逆序对构造，能否让总逆序对数≥n
bool check(int id, int m, int ch, int sum){
    // 模拟剩余位置（id+1到m）按最大逆序对构造的过程
    for(int i = id + 1; i <= m; i ++){
        int maxadd = 0, ch1 = 0;  // maxadd：当前位置能新增的最大逆序对；ch1：对应字符
        // 枚举所有26个字符，找能新增最多逆序对的那个（最大构造策略）
        for(int j = 0; j < 26; j ++){ 
            int add = get_add(j);  // 计算选j的新增逆序对
            if(maxadd < add){  // 更新最大逆序对和对应字符
                maxadd = add;
                ch1 = j;
            }
        }
        vis[ch1] ++;    // 选中该字符，后续构造中该字符数+1
        sum += maxadd;  // 累计逆序对数
    }
    memset(vis, 0, sizeof vis);  // 重置vis数组（避免影响后续检查）
    return sum >= n;  // 总逆序对≥n则可行，返回true
}

// 构造最终字符串的核心函数（m是最短长度）
void solve(int m){
    int sum = 0;     // 已累计的逆序对数
    string ans;      // 最终答案字符串
    
    // 逐位置构造（第1位到第m位）
    for(int i = 1; i <= m; i ++){
        // 枚举当前位置的字符（从a(0)开始，保证字典序最小）
        for(int j = 0; j < 26; j ++){ 
            // 计算选字符j时新增的逆序对数
            int initadd = get_add(j);
            cnt[j] ++;       // 已确定字符j的数量+1
            sum += initadd;  // 累计逆序对数
            
            // 检查：选j后，剩余位置能否构造出≥n的逆序对
            if(check(i, m, j, sum)){
                ans += ('a' + j);  // 可行则加入答案，跳出循环
                break;
            }
            
            // 不可行则回溯：恢复cnt和sum
            cnt[j] --;       
            sum -= initadd;
        }
    }
    cout << ans;  // 输出最终字符串
}

int main(){

    cin >> n;          // 输入目标逆序对数V
    get_max();         // 预计算各长度的最大逆序对数f[i]
    
    // 找到能容纳n的最短长度m（第一个f[i]≥n的i）
    for(int i = 2; i <= n; i ++){
        if(f[i] >= n){
            solve(i);  // 构造长度为i的字符串
            break;
        }
    }
    return 0;
}