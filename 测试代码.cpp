#include <bits/stdc++.h>  // 万能头文件，包含所有C++标准库
using namespace std;

// 变量定义
long long n;             // 数组长度
long long a[100010];     // 原数组
long long p[100010];     // 前缀异或和数组 p[0]~p[n]
int w[25][2];            // 统计每一位0/1的个数：w[k][0]=第k位0的数量，w[k][1]=第k位1的数量
long long ans = 0;       // 最终答案（用long long防止溢出）

int main()
{
	// 1. 输入数组长度n
	scanf("%lld",&n);
	
	// 2. 输入原数组a[1]~a[n]
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	
	// 3. 计算前缀异或和数组
    // p[0] = 0（全局变量默认初始化为0）
    // p[i] = 前i个数的异或和
    for(int i=1;i<=n;i++)
		p[i] = p[i-1] ^ a[i];
	
	// 4. 统计每一位二进制上0和1的数量
	// 遍历所有前缀异或值：p[0] ~ p[n]
    for(int i=0;i<=n;i++){
        // 遍历0~20位（题目说a[i]≤2^20，只需算这21位）
        for(int k=0;k<=20;k++){
	        // (p[i]>>k)&1：取出p[i]的第k位二进制数字（0或1）
	        int bit = (p[i] >> k) & 1;
	        w[k][bit]++;  // 对应位数的计数器+1
		}
	}
	
	// 5. 计算每一位的贡献，累加得到答案
	for(int k=0;k<=20;k++){
	    // 第k位贡献 = 0的个数 × 1的个数 × 2^k
	    ans += (long long)w[k][0] * w[k][1] * (1 << k);
	}
	
	// 6. 输出最终答案
	printf("%lld",ans);
	return 0;
}