#include<bits/stdc++.h>  // 万能头文件，包含所有常用STL库
using namespace std;

int n;                  // 输入的数字个数
long long t[200];       // 存储输入的原始数字（数组大小200，适配题目N<100的限制）
long long a[200];       // 存储相邻数字化简后的分子
long long b[200];       // 存储相邻数字化简后的分母

// 递归函数：尝试将相邻的两个比值（a[i]/b[i] 和 a[i+1]/b[i+1]）化为同底数的幂次
// 核心思路：通过不断相除，让a[i]和a[i+1]相等、b[i]和b[i+1]相等，从而找到公共底数
void d(int i) {
	// 递归终止条件：如果当前分子和下一个分子相等，无需继续处理
	if(a[i]==a[i+1]) return;
	
	// 情况1：当前分子大于下一个分子 → 不断除以下一个分子，直到相等
	if(a[i]>a[i+1]) {
		while(a[i]>a[i+1]) a[i]/=a[i+1];  // 分子相除，试图让a[i]缩小到和a[i+1]相等
		while(b[i]>b[i+1]) b[i]/=b[i+1];  // 分母同步相除，保持比值不变
		d(i);  // 递归继续处理（可能一次相除还不相等）
		return;
	}
	
	// 情况2：当前分子小于下一个分子 → 不断除以下一个分子，直到相等
	if(a[i]<a[i+1]) {
		while(a[i]<a[i+1]) a[i+1]/=a[i];  // 下一个分子相除，试图缩小到和当前分子相等
		while(b[i]<b[i+1]) b[i+1]/=b[i];  // 分母同步相除，保持比值不变
		d(i);  // 递归继续处理
		return;
	}
}

// 自定义最大公约数（gcd）函数：递归实现欧几里得算法
long long c(long long x,long long y) {
	if(x%y==0) return y;          // x能被y整除，最大公约数是y
	if(y%x==0) return x;          // y能被x整除，最大公约数是x
	if(x<y) return c(y%x,x);      // x<y时，递归计算y%x和x的gcd
	if(x>y) return c(x%y,y);      // x>y时，递归计算x%y和y的gcd
}

int main() {
	// 步骤1：输入数字个数和原始数字
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%lld",&t[i]);  // 用scanf读入long long，避免cin的效率问题
	
	// 步骤2：对原始数字升序排序（等比数列需有序才能计算相邻比值）
	sort(t+1,t+n+1);
	
	// 步骤3：手动去重（逻辑有缺陷，会漏判连续重复）
	for(int i=1;i<n;i++) {
		if(t[i]==t[i+1]) {  // 发现相邻重复数字
			// 将重复位置后的数字整体前移一位，覆盖重复值
			for(int j=i+1;j<=n;j++) {
				t[j]=t[j+1];
			}
			n--;  // 数字个数减1（去重后总数减少）
		}
	}
	
	// 步骤4：计算相邻数字的最简比值（分子存a[i]，分母存b[i]）
	for(int i=1;i<n;i++) {
		// 化简t[i+1]/t[i]为最简分数：分子=大数/gcd，分母=小数/gcd
		a[i]=t[i+1]/c(t[i+1],t[i]);
		b[i]=t[i]/c(t[i+1],t[i]);
	}
	
	// 步骤5：递归化简所有相邻比值，试图找到公共底数
	for(int i=1;i<n-1;i++) d(i);
	
	// 步骤6：输出最后一个比值（认为是最大公比）
	cout<<a[n-1]<<"/"<<b[n-1];
	return 0;
}