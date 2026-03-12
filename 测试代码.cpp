#include<bits/stdc++.h>
using namespace std;

// 定义全局变量，适配2e5的数据范围
int n, m;
// v_1/v_2 分别存储两棵树的邻接表
vector<int> v_1[200005], v_2[200005];
// c[i]/d[i] 分别表示第一棵树、第二棵树中节点i的权值
int c[200005], d[200005];
// vis_1/vis_2 标记节点是否已访问，避免重复遍历
bool vis_1[200005], vis_2[200005];

// 排序比较函数：对第一棵树的节点，按其权值c从小到大排序
inline bool cmp_1(const int &x, const int &y) {
    return c[x] < c[y];
}

// 排序比较函数：对第二棵树的节点，按其权值d从小到大排序
inline bool cmp_2(const int &x, const int &y) {
    return d[x] < d[y];
}

// 队列中存储的信息结构体：id_1/id_2表示当前遍历到两棵树的对应节点，dp表示当前公共前缀的长度
struct info {
    int id_1, id_2, dp;
};

signed main() {
    // 读取两棵树的节点总数n和m
    cin >> n >> m;

    // 读取第一棵树所有节点的权值（c[1]到c[n]）
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }

    // 读取第二棵树所有节点的权值（d[1]到d[m]）
    for (int i = 1; i <= m; i++) {
        cin >> d[i];
    }

    // 构建第一棵树的邻接表（n-1条边）
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        v_1[u].push_back(v);
        v_1[v].push_back(u);
    }

    // 构建第二棵树的邻接表（m-1条边）
    for (int i = 1; i < m; i++) {
        int p, q;
        cin >> p >> q;
        v_2[p].push_back(q);
        v_2[q].push_back(p);
    }

    // 对第一棵树每个节点的子节点，按权值从小到大排序（为后续双指针匹配做准备）
    for (int i = 1; i <= n; i++) {
        sort(v_1[i].begin(), v_1[i].end(), cmp_1);
    }

    // 对第二棵树每个节点的子节点，按权值从小到大排序
    for (int i = 1; i <= m; i++) {
        sort(v_2[i].begin(), v_2[i].end(), cmp_2);
    }

    // BFS队列，用于同步遍历两棵树，寻找公共前缀路径
    queue<info> q;
    // ans记录最长公共前缀的长度，初始化为0
    int ans = 0;

    // 特判：如果两棵树根节点（节点1）的权值不同，直接输出0（没有公共前缀）
    if (c[1] != d[1]) {
        cout << 0;
        return 0;
    }

    // 初始化BFS：从根节点开始，公共前缀长度为1（根节点权值相同）
    q.push({1, 1, 1});

    // 开始BFS遍历
    while (!q.empty()) {
        // 取出队头节点（当前遍历到的两棵树的对应节点状态）
        auto now = q.front();
        q.pop();

        // 更新最长公共前缀长度
        ans = max(ans, now.dp);

        // 标记当前节点已访问（防止走回头路/重复遍历）
        vis_1[now.id_1] = 1;
        vis_2[now.id_2] = 1;

        // 双指针i/j：分别指向第一棵树、第二棵树当前节点的子节点列表起始位置
        int i = 0, j = 0;
        // 同时遍历两个子节点列表，直到其中一个遍历完毕
        while (i < v_1[now.id_1].size() && j < v_2[now.id_2].size()) {
            // 取出第一棵树当前子节点的权值
            int val_1 = c[v_1[now.id_1][i]];
            // 取出第二棵树当前子节点的权值
            int val_2 = d[v_2[now.id_2][j]];

            if (val_1 < val_2) {
                // 第一棵树子节点权值更小，i后移找更大的值
                i++;
            } else if (val_1 > val_2) {
                // 第二棵树子节点权值更小，j后移找更大的值
                j++;
            } else if (val_1 == val_2) {
                // 找到权值相同的子节点，构成公共前缀的下一个节点
                // 前提：两个子节点都未被访问过（避免重复）
                if (vis_1[v_1[now.id_1][i]] == 0 && vis_2[v_2[now.id_2][j]] == 0) {
                    // 入队：公共前缀长度+1，继续遍历下一层
                    q.push({v_1[now.id_1][i], v_2[now.id_2][j], now.dp + 1});
                }
                // 双指针同时后移，继续寻找下一对权值相同的子节点
                i++;
                j++;
            }
        }
    }

    // 输出最终找到的最长公共前缀长度
    cout << ans;

    return 0;
}