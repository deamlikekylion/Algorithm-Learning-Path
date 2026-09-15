#include<bits/stdc++.h>
using namespace std; 

//dp[i][j]：前i个仓库，总花费为j时，能获得的最大净收益
int dp[1005][40005];
//a[i]：存储第i个仓库的所有货物的价值
vector <int> a[1005];
//b[i]：第i个仓库的基本费用；c[i]：第i个仓库的计件费用系数
int b[1005], c[1005];

//自定义比较函数，用于将货物价值降序排序
bool dcmp(int a, int b){
    return a > b;
}

int main(){
    int n, m, v;  cin >> n >> m >> v;
    memset(dp, 0, sizeof(dp));
    
    // 读取每个仓库的基本费用b[j]和计件费用系数c[j]
    for(int i = 1; i <= n; i++){
        cin >> b[i] >> c[i];
    }
    
    // 读取每个货物的价值和所属仓库，按仓库分组存入a数组
    for(int i = 1; i <= m; i++){
        int val, t;  // val：货物价值；t：所属仓库
        cin >> val >> t;
        t++;  // 使仓库编号从1开始（与数组索引对应）
        a[t].push_back(val);
    }
    
    // 对每个仓库的货物按价值降序排序，这样选k个时优先选价值高的，净收益增长更快
    for(int i = 1; i <= n; i++){
        sort(a[i].begin(), a[i].end(), dcmp);
    }
    
    //分组背包DP：处理每个仓库作为一组，组内选0~k个货物
    for(int i = 1; i <= n; i++){  // 遍历每个仓库（第i个仓库）
        for(int j = 0; j <= 40000; j++){  // 遍历所有可能的总花费j
            //状态转移1：不选第i个仓库的货物，继承前i-1个仓库的状态
            dp[i][j] = dp[i-1][j];
            int sum = 0;  // 记录当前仓库选k个货物的总价值
            //枚举选k个货物（k从1到该仓库货物数量）
            for(int k = 0; k < a[i].size(); k++){
                //选k+1个货物时的总成本：基本费用b[i] + 计件费用c[i]*(k+1)
                int cost = b[i] + c[i] * (k + 1);
                if(cost > j)  break;  
				//成本超过当前总花费j，无法选k+1个，跳出循环
                sum += a[i][k];  
				//累加前k+1个货物的价值（因为已降序，前k+1个是价值最高的k+1个）
                //状态转移2：选第i个仓库的k+1个货物，
				//净收益 = 前i-1个仓库花费j-cost时的净收益 + 当前sum-cost
                dp[i][j] = max(dp[i][j], dp[i-1][j-cost] + sum-cost);
            }
        }
    }
    
    // 寻找满足净收益≥v的最小花费
    int ans;
    for(int i = 0; i <= 40000; i++){
        if(dp[n][i] >= v){  // 找到第一个总花费i，使得前n个仓库花费i时净收益≥v
            ans = i;
            break;
        }
    }
    cout << ans;  // 输出最小花费
    return 0;	
}