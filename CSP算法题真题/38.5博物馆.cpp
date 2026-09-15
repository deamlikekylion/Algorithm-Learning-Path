#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

// 常量定义：最大节点数和最大边数
const int MAXN = 1e5 + 5;  // 节点数上限（10^5 + 5）
const int MAXM = 2e5 + 5;  // 边数上限（2*10^5 + 5）

// 全局变量
int n, m, q;               // n：节点数；m：边数；q：查询数
vector<int> G[MAXN];       // 邻接表：存储图的边（G[u]为u的相邻节点列表）
int dfn[MAXN];             // dfn[u]：节点u的发现时间（DFS遍历顺序编号）
int low[MAXN];             // low[u]：u能回溯到的最早发现时间的节点编号
int timestamp;             // 时间戳：用于记录dfn的编号
bool is_cut[MAXN];         // 标记节点是否为割点（articulation point）
int sz[MAXN];              // sz[u]：以u为根的子树大小（包含u本身）
int dfn_in[MAXN];          // 节点u进入DFS的时间戳（同dfn[u]，用于子树范围判断）
int dfn_out[MAXN];         // 节点u离开DFS的时间戳（子树遍历结束时的时间）
vector<pair<int, int>> cut_children[MAXN];  
// 割点u的子节点信息：(子节点v, 子树v的大小)

/**
 * Tarjan算法：用于查找图中的割点，并计算子树大小、时间戳等信息
 * @param u 当前遍历的节点
 * @param fa 父节点（-1表示根节点）
 */
void tarjan(int u, int fa) {
    // 初始化当前节点的发现时间和最早回溯时间
    dfn[u] = low[u] = ++timestamp;  // 时间戳递增
    dfn_in[u] = timestamp;          // 记录进入时间（与dfn一致）
    sz[u] = 1;                      // 子树大小初始为1（自身）
    int child = 0;                  // 记录子节点数量（用于根节点判断割点）

    // 遍历u的所有相邻节点
    for (int v : G[u]) {
        if (v == fa) continue;  // 跳过父节点，避免重复访问

        if (!dfn[v]) {  // v未被访问过（树边）
            child++;    // 子节点数量+1
            tarjan(v, u);  // 递归遍历子节点v

            // 回溯时更新当前节点的子树大小和low值
            sz[u] += sz[v];  // u的子树大小包含v的子树
            low[u] = min(low[u], low[v]);  // 用v的low值更新u的low值

            // 判断u是否为割点：
            // 1. 非根节点：若子节点v的low值 >= u的dfn值，
			// 说明v无法回溯到u的祖先，u是割点
            if (low[v] >= dfn[u] && fa != -1) {
                is_cut[u] = true;
                // 记录割点u的子节点v及其子树大小（用于后续查询）
                cut_children[u].emplace_back(v, sz[v]);
            }

            // 2. 根节点：若子节点数量 > 1，则根节点是割点（删除后子树分离）
            if (fa == -1 && child > 1) {
                is_cut[u] = true;
                cut_children[u].emplace_back(v, sz[v]);
            }
        } else {  // v已被访问过（回边）
            // 用v的发现时间更新u的low值（回边能回溯到更早的节点）
            low[u] = min(low[u], dfn[v]);
        }
    }
    dfn_out[u] = timestamp;  // 记录离开时间（子树遍历结束）
}

int main() {
    ios::sync_with_stdio(false);  // 关闭输入输出同步，加速cin/cout
    cin.tie(0);

    // 读入图的基本信息
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);  // 无向图，双向添加边
        G[v].push_back(u);
    }

    // 初始化时间戳并执行Tarjan算法（以节点1为根）
    timestamp = 0;
    tarjan(1, -1);  // 根节点的父节点为-1

    // 处理q个查询
    while (q--) {
        int c;  // 当前查询包含的节点数量
        cin >> c;
        vector<int> S(c);  // 存储查询中的节点集合
        vector<bool> in_S(n + 1, false);  // 标记节点是否在S中（加速查询）
        for (int i = 0; i < c; i++) {
            cin >> S[i];
            in_S[S[i]] = true;
        }

        // 提取S中所有节点的dfn_in，并排序（用于后续子树范围查询）
        vector<int> S_dfn;
        for (int node : S) {
            S_dfn.push_back(dfn_in[node]);
        }
        sort(S_dfn.begin(), S_dfn.end());

        long long ans = 0;  // 存储当前查询的答案
        // 遍历所有节点，计算每个节点对答案的贡献
        for (int x = 1; x <= n; x++) {
            if (!is_cut[x]) {  // 非割点的情况
                // 贡献为：S中节点总数 - 若x在S中则减1（自身不贡献）
                ans += c - (in_S[x] ? 1 : 0);
            } else {  // 割点的情况
                // cnt0：S中不在割点x任何子树内的节点数（即属于x的"父部分"）
                int cnt0 = c - (in_S[x] ? 1 : 0);
                int max_cnt = 0;  // 记录S中在x的子树内的最大节点数

                // 遍历割点x的所有子节点（每个子节点对应一个被x分割的子树）
                for (auto &p : cut_children[x]) {
                    int y = p.first;  // 子节点y
                    // 子树y的dfn范围：[dfn_in[y], dfn_out[y]]
                    int l = dfn_in[y], r = dfn_out[y];
                    // 查找S_dfn中落在[l, r]范围内的节点数量
					//（即子树y中的S节点数）
                    int left_idx = lower_bound(S_dfn.begin(), 
					S_dfn.end(), l) - S_dfn.begin();
                    int right_idx = upper_bound(S_dfn.begin(), 
					S_dfn.end(), r) - S_dfn.begin();
                    int count = right_idx - left_idx;  // 子树y中的S节点数

                    cnt0 -= count;  // 从cnt0中减去该子树的节点数
					//（这些节点属于子树而非父部分）
                    if (count > max_cnt) {
                        max_cnt = count;  // 更新最大子树节点数
                    }
                }

                // 比较父部分节点数和最大子树节点数，取较大值作为割点x的贡献
                if (cnt0 > max_cnt) {
                    max_cnt = cnt0;
                }
                ans += max_cnt;
            }
        }
        cout << ans << '\n';  // 输出当前查询的答案
    }

    return 0;
}