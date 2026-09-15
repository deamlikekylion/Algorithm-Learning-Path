#include<bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

// 快速幂函数，计算 (base^exp) % mod
long long quick_pow(long long base, int exp, int mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) { // 若exp为奇数，乘上当前base
            result = (result * base) % mod;
        }
        base = (base * base) % mod; // base平方
        exp >>= 1; // exp除以2
    }
    return result;
}

int main(){
    int n,m;  cin>>n>>m;
    unordered_set<int> hash; // 存储井号的位置
    for (int i=0;i<m;++i) {
        int a;  cin>>a;
        hash.insert(a);
    }
    
    // 收集所有可能的"ccf"和"cspark"起始位置
    vector<int> ccf,cspark;
    int l=1,i=1;
    while(i<=n){
    	if(hash.count(i)){
    		int size=i-l;
    		if(size/3)  for(int j=l;j<=i-3;j++)  ccf.push_back(j);
			if(size/6)  for(int j=l;j<=i-6;j++)  cspark.push_back(j);
			l=++i;
		}else if(i==n){
			int size=n+1-l;
    		if(size/3)  for(int j=l;j<=n+1-3;j++)  ccf.push_back(j);
			if(size/6)  for(int j=l;j<=n+1-6;j++)  cspark.push_back(j); 
			break;
		}else  i++;
	}
	
	// 自由位置数：总可填位置 - ccf占用 - cspark占用
    int free = (n - m) - 9; 
    long long pow = 0;
    if (free > 0) {
        pow = quick_pow(26, free , MOD);
    } else if (free == 0) {
        pow = 1; // 26^0 = 1
    } else {
        pow = 0; // 自由位置为负，无法容纳ccf和cspark，贡献为0
    }

    long long total = 0;
    // 遍历所有有效(ccf起始, cspark起始)对，满足ccf在cspank前
    for (int i : ccf) {
        for (int j : cspark) {
            if (i + 2 < j) { // ccf的结束位置(i+2)在cspark起始位置(j)之前
                total = (total + pow) % MOD;
            }
        }
    }
    
    // 容斥原理去重 
   
   
   
   	// 输出结果 
    cout << total << endl;

    return 0;
}