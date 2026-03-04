#include <bits/stdc++.h>
using namespace std;

// 全局变量定义
int n;                      // 树的节点数量
int a[100005];              // a[i] 存储第i个节点的和谐值（点权）
long long dp[100005];
// dp[u]：以u为根的子树中，包含u的最大权值连通子图的和（必须选u）
                            // 注意开long long：点权绝对值≤1e6，n≤1e5，总和可能达1e11，超出int范围
vector<int> adj[100005];    // 邻接表：存储树的边，adj[u]存储u的所有邻接节点

/**
 * @brief 深度优先搜索（后序遍历），计算每个节点的dp值
 * @param u 当前遍历的节点
 * @param fa u的父节点（避免回边遍历）
 */
void dfs(int u, int fa) {
    // 初始化dp[u]：只选当前节点u，和为u的点权
    dp[u] = a[u];
    
    // 遍历u的所有邻接节点v
    for(int v : adj[u]) {
        // 如果v是父节点，跳过（避免走回头路，保证只遍历子树）
        if(v == fa) continue;
        
        // 递归遍历子节点v，父节点设为u
        dfs(v, u);
        
        // 状态转移核心：
        // 如果子节点v的dp[v]为正，说明选v的子树能增加总和，就加上；
        // 如果dp[v]为负，加了会让总和变小，所以加0（等价于不选v的子树）
        // 0ll是long long类型的0，保证和dp[v]（long long）类型匹配
        dp[u] += max(dp[v], 0ll);
    }
}

int main() {
    // 输入节点数量n
    scanf("%d", &n);
    
    // 输入每个节点的和谐值（点权），节点编号从1到n
    for(int i = 1; i <= n; i++) 
        scanf("%d", &a[i]);
    
    // 输入n-1条边，构建邻接表（树的无向边）
    for(int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);  // u的邻接表加入v
        adj[v].push_back(u);  // v的邻接表加入u
    }
    
    // 从根节点1开始DFS，父节点设为0（0不是有效节点，避免冲突）
    dfs(1, 0);
    
    // 计算答案：
    // 1. 遍历dp[1]到dp[n]，找到最大的dp值（所有以u为根的最优连通子图）
    // 2. 与0ll比较：如果所有dp[u]都是负数，选空集（和为0）更优
    // max_element返回区间内最大值的迭代器，*取值；%lld对应long long类型输出
    printf("%lld", max(*max_element(dp + 1, dp + n + 1), 0ll));
    
    return 0;
}