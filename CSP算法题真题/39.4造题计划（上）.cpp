#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// ========== 常量定义（适配题目数据范围） ==========
const int MAXN = 2e5 + 5;  // 题目中节点数n的上限（2×10^5 +5）
const int LOG = 20;        // 倍增层数（2^20 > 2e5，足够覆盖树的最大深度）

// ========== 全局变量（关联题目概念） ==========
vector<int> adj[MAXN];     // 树的邻接表：存储树的边（对应题目中的“n个结点的树”）
int depth[MAXN];           // 节点的深度：用于后续计算LCA和路径长度
int up[LOG][MAXN];         // 倍增LCA数组：up[k][u]表示u向上跳2^k步的祖先（快速求LCA）
int a[MAXN];               // 节点的权值：对应题目中“编号为i的点有权值a_i”（0~n-1的排列）
int pos[MAXN];             // 权值→节点的映射：pos[v] = u 表示“权值v对应的节点是u”（因为权值是排列，唯一对应）
int s[MAXN], t[MAXN];      // 点集直径端点：s[mid]/t[mid]是“权值0~mid的所有节点”构成的点集的直径（最远两点）


// ========== BFS预处理：父节点+深度 ==========
// 作用：避免递归栈溢出，初始化每个节点的直接父节点（up[0][u]）和深度
// （后续求LCA必须依赖深度和父节点信息）
void bfs(int root, int n) {
    queue<int> q;
    q.push(root);          // 根节点入队（这里选节点1为根）
    up[0][root] = 0;       // 根节点无父节点，标记为0
    depth[root] = 0;       // 根节点深度设为0
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {  // 遍历u的所有邻接节点
            if (v != up[0][u]) { // 排除父节点，避免回边
                up[0][v] = u;         // 记录v的直接父节点是u
                depth[v] = depth[u] + 1; // v的深度=父节点深度+1
                q.push(v);            // v入队，继续BFS遍历子节点
            }
        }
    }
}


// ========== 预处理倍增LCA数组 ==========
// 作用：基于直接父节点（up[0]），构建“跳2^k步的祖先”数组，为快速查询LCA做准备
// （LCA是计算“两点路径”的核心工具）
void preprocess_lca(int root, int n) {
    bfs(root, n);  // 先通过BFS初始化up[0]和depth
    for (int k = 1; k < LOG; ++k) { // 递推构建各层倍增数组
        for (int u = 1; u <= n; ++u) {
            // 核心递推式：跳2^k步 = 先跳2^(k-1)步，再跳2^(k-1)步
            up[k][u] = up[k-1][up[k-1][u]];
        }
    }
}


// ========== 计算两点的最近公共祖先（LCA） ==========
// 作用：找到u和v的最深公共祖先，是计算“两点路径”的基础
int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v); // 保证u的深度≥v，方便统一处理
    
    // 第一步：将u提升到与v相同的深度
    for (int k = LOG-1; k >= 0; --k) {
        if (depth[u] - (1 << k) >= depth[v]) { // 跳2^k步后深度仍≥v
            u = up[k][u];
        }
    }
    if (u == v) return u; // 提升后u==v，说明v是u的祖先
    
    // 第二步：u和v同时向上跳，直到父节点相同（此时父节点就是LCA）
    for (int k = LOG-1; k >= 0; --k) {
        if (up[k][u] != up[k][v]) {
            u = up[k][u];
            v = up[k][v];
        }
    }
    return up[0][u]; // 最终u、v的直接父节点就是LCA
}


// ========== 计算两点的路径长度（边数） ==========
// 作用：基于LCA计算u到v的路径长度，同时用于判断“节点是否在路径上”
int get_dist(int u, int v) {
    int ancestor = lca(u, v);
    // 公式：u到v的路径长度 = u到LCA的深度 + v到LCA的深度
    return depth[u] + depth[v] - 2 * depth[ancestor];
}


// ========== 预处理：权值0~mid的点集的直径端点 ==========
// 核心逻辑（服务于mex查询）：
// mex是“最小未出现的自然数”，即mex=k ⇨ 0~k-1都在路径上，k不在路径上。
// 要判断“0~mid的权值是否都在路径上”，只需判断“0~mid对应的点集的直径”是否在路径上
//（树的性质：直径在路径上则整个点集都在路径上）。

//代码里的s[mid]和t[mid]不是整棵树的直径，而是 **“权值 0~mid 的节点构成的子集” 的直径 **（局部直径），
//也就是：在 “权值为 0、1、2…mid 的这些节点” 中，找两个距离最远的节点，这两个节点就是这个点集的直径端点，
//它们的路径就是点集直径。

void preprocess_st(int n) {
    s[0] = pos[0]; // 初始：权值0对应的节点，直径是自己
    t[0] = pos[0];
    for (int mid = 1; mid < n; ++mid) {
        int u = pos[mid];          // 当前加入的节点（权值mid对应的节点）
        int sm_prev = s[mid-1];    // 前一个点集（0~mid-1）的直径左端点
        int tm_prev = t[mid-1];    // 前一个点集的直径右端点
        
        // 计算三个关键距离：原直径长度、原左端点到新节点、原右端点到新节点
        int d1 = get_dist(sm_prev, tm_prev);
        int d2 = get_dist(sm_prev, u);
        int d3 = get_dist(tm_prev, u);
        
        // 新点集的直径是“原直径端点、新节点”三者中的最远对（树的直径性质）
        if (d2 >= d1 && d2 >= d3) {
            s[mid] = sm_prev;
            t[mid] = u;
        } else if (d3 >= d1 && d3 >= d2) {
            s[mid] = tm_prev;
            t[mid] = u;
        } else {
            s[mid] = sm_prev;
            t[mid] = tm_prev;
        }
    }
}


// ========== 主函数：处理题目输入、预处理、查询 ==========
int main() {
    ios::sync_with_stdio(false); // 加速cin/cout（适配大数据量）
    cin.tie(0);
    
    int n, m;
    cin >> n >> m; // 输入节点数n、查询数m（对应题目输入）
    
    // 输入每个节点的权值，并建立“权值→节点”的映射pos
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pos[a[i]] = i; // 因为权值是0~n-1的排列，每个权值对应唯一节点
    }
    
    // 输入树的n-1条边，构建邻接表
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // 预处理LCA（为后续路径查询做准备）
    preprocess_lca(1, n);
    // 预处理各mid对应的点集直径（为快速判断“0~mid是否在路径上”做准备）
    preprocess_st(n);
    
    // 处理m次查询（对应题目中的m条限制）
    while (m--) {
        int x, y;
        cin >> x >> y; // 输入查询的两个节点x、y
        
        // 二分查找：找到最大的mid，使得“权值0~mid的所有节点都在x-y路径上”
        // 最终mex就是mid+1（因为mid是最大的满足“0~mid都在路径上”的数）
        int low = 0, high = n;
        while (low < high) {
            int mid = (low + high) / 2;
            if (mid >= n) { // 边界处理：mid超过n则收缩上界
                high = mid;
                continue;
            }
            
            int sm = s[mid]; // 权值0~mid的点集的直径左端点
            int tm = t[mid]; // 权值0~mid的点集的直径右端点
            int d_xy = get_dist(x, y); // x到y的路径长度
            
            // 判断sm是否在x-y路径上：x→sm的距离 + sm→y的距离 = x→y的总距离
            int d_xsm = get_dist(x, sm);
            int d_smy = get_dist(sm, y);
            bool s_in = (d_xy == d_xsm + d_smy);
            
            // 判断tm是否在x-y路径上（同理）
            int d_xtm = get_dist(x, tm);
            int d_tmy = get_dist(tm, y);
            bool t_in = (d_xy == d_xtm + d_tmy);
            
            // 若直径的两个端点都在路径上，则整个点集（0~mid）都在路径上
            if (s_in && t_in) {
                low = mid + 1; // 尝试找更大的mid
            } else {
                high = mid; // 收缩上界，找更小的mid
            }
        }
        
        // 输出mex值（low是最大的满足“0~low-1都在路径上”的数，故mex=low）
        cout << low << '\n';
    }
    
    return 0;
}