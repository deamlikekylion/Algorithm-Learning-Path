#include<bits/stdc++.h>
using namespace std;

// 全局变量定义
int sum;                // 输入的总数字个数（即n*m + 2）
int scale;              // 矩阵元素的总个数 = sum - 2（即n*m）
int x;                  // 临时变量，存储输入的每个数字
long long bucket[500007]; // 计数桶，bucket[i]表示数字i出现的次数
long long jc[500007] = {1}; // jc[i]表示i! mod 1e9+7，初始化jc[0]=1
long long invjc[500007] = {}; // invjc[i]表示(i!)的逆元 mod 1e9+7
long long ans = 0;      // 最终答案，累加所有合法情况的结果
const long long mod = 1000000007ll; // 模数，题目要求答案对1e9+7取余

// 快速幂函数：计算a^b mod mod，用于求逆元
long long qpow(long long a, long long b)
{
	long long res = 1; // 结果初始化为1
	while(b) // 快速幂核心循环，b>0时继续
	{
		if(b & 1) // 如果b的二进制最后一位是1，乘上当前的a
			res = res * a % mod;
		a = a * a % mod; // a平方，处理下一位
		b >>= 1; // b右移一位（等价于b//2）
	}
	return res;
}

// 求x在模mod下的逆元（费马小定理）
long long inv(long long x)
{
	// mod是质数，逆元 = x^(mod-2) mod mod
	return qpow(x, mod - 2);
}

int main()
{
	// 第一步：读取输入总个数，计算矩阵元素总数scale
	cin >> sum;
	scale = sum - 2; // scale = n*m，因为sum = n*m + 2

	// 第二步：预处理阶乘数组jc[0...5e5]
	for(long long i = 1; i <= 500000; i++)
	{
		jc[i] = jc[i - 1] * i % mod; // 递推计算i! = (i-1)! * i mod mod
	}

	// 第三步：预处理阶乘的逆元数组invjc[0...5e5]
	for(int i = 0; i <= 500000; i++)
	{
		invjc[i] = inv(jc[i]); // invjc[i] = (i!)^(-1) mod mod
	}

	// 第四步：读取所有输入数字，统计每个数字的出现次数（桶排序）
	for(int i = 1; i <= sum; i++)
	{
		cin >> x;
		bucket[x]++; // 数字x的计数+1
	}

	// 第五步：枚举所有可能的矩阵行数n，寻找合法的(n,m)组合
	for(int i = 1; i <= scale; i++)
	{
		// 合法条件：
		// 1. i是scale的约数（即m=scale/i是整数，满足n*m=scale）
		// 2. 数字i（行数n）在输入中存在（bucket[i]>0）
		// 3. 数字scale/i（列数m）在输入中存在（bucket[scale/i]>0）
		if(scale % i == 0 && bucket[i] && bucket[scale / i])
		{
			int n = i, m = scale / i; // 当前枚举的行数n，列数m

			// 临时扣除n和m的计数（因为这两个数是矩阵的行列数，不属于矩阵元素）
			bucket[n]--;
			bucket[m]--;

			// 计算当前(n,m)对应的合法矩阵数：scale! / (k1! * k2! * ... * kt!)
			// 其中ki是剩余数字的出现次数，模意义下除法=乘逆元
			long long now = jc[scale]; // 先取scale!
			for(int j = 1; j <= 500000; j++)
				if(bucket[j]) // 如果数字j有剩余，乘上(ki!)的逆元
					now = now * invjc[bucket[j]] % mod;

			// 累加当前情况的结果到总答案
			ans = (ans + now) % mod;

			// 恢复n和m的计数（避免影响后续枚举）
			bucket[n]++;
			bucket[m]++;
		}
	}

	// 第六步：输出最终答案
	cout << ans << endl;
	return 0;
}