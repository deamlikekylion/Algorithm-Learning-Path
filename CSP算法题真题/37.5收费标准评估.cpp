#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

vector<ll> a;               // 存储每个节点的权值
vector<vector<int>> graph;  // 用邻接表表示树（无向图）
int root;                   // 当前树的根节点

// 深度优先搜索（DFS），计算节点的两个关键值
// u 当前节点，parent 父节点（避免回退遍历）
// pair<ll, ll> 第一个值f：包含u的最大连通和（必须包含u，可连接正权子树）
// 第二个值g：u所在子树中的最大连通和（可以是子树中任意符合条件的连通区域）
pair<ll, ll> dfs(int u, int parent) {
    ll f = a[u];  // f初始值为当前节点的权值（至少包含自身）
    ll g = a[u];  // g初始值暂定为f（后续会与子树的g比较）
    ll sum_positive = 0;  // 累加所有正的子节点f值（只连接能增加总和的子树）
    vector<ll> children_g;  // 存储所有子节点的g值（用于后续更新当前节点的g）

    // 遍历当前节点的所有邻接节点（子节点）
    for (int v : graph[u]) {
        // 跳过父节点（避免循环遍历）
        if (v == parent) continue;
        
        // 递归计算子节点v的f和g
        pair<ll, ll> t = dfs(v, u);
        ll f_v = t.first;  // 子节点v的f值
        ll g_v = t.second; // 子节点v的g值

        // 若子节点的f值为正，则加入总和（连接该子树能增大当前节点的f）
        sum_positive += max(0LL, f_v);
        // 记录子节点的g值，用于后续更新当前节点的g
        children_g.push_back(g_v);
    }

    // 更新当前节点的f值：自身权值 + 所有正的子节点f值之和
    f += sum_positive;

    // 更新当前节点的g值：取自身f值和所有子节点g值中的最大值
    // （因为子树的最大连通区域可能在某个子节点的子树中，而非包含当前节点）
    g = f;  // 先以自身f为候选
    for (ll g_child : children_g) {
        if (g_child > g) {
            g = g_child;
        }
    }

    return {f, g};
}

// 计算当前根节点的基础值（包含根的最大连通和），return 根节点的f值
ll get_basic() {
    pair<ll, ll> t = dfs(root, -1);  // 从根节点开始DFS，父节点设为-1（无父节点）
    ll f = t.first;
    return f;
}

// 查询以u为根的子树中的最大连通和，u 子树的根节点
// return 子树中的最大连通和（即u的g值）
ll query_subtree(int u) {
    pair<ll, ll> t = dfs(u, -1);  // 从u开始DFS，视u为根（父节点设为-1）
    ll g = t.second;
    return g;
}

int main() {
    // 优化输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;  // n：节点数；m：操作数
    cin >> n >> m;

    // 初始化节点权值（1-based索引，节点编号从1开始）
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 初始化树的邻接表（1-based索引）
    graph.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {  // 树有n-1条边
        int u, v;
        cin >> u >> v;
        // 无向图，双向添加边
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // 初始根节点为1，输出初始根的基础值
    root = 1;
    cout << get_basic() << endl;

    // 处理m个操作
    for (int i = 0; i < m; i++) {
        int type;  // 操作类型
        cin >> type;

        if (type == 1) {
            // 操作1：查询以u为根的子树中的最大连通和
            int u;
            cin >> u;
            cout << query_subtree(u) << endl;
        } else if (type == 2) {
            // 操作2：修改节点u的权值为a_val，输出新的根基础值
            int u, a_val;
            cin >> u >> a_val;
            a[u] = a_val;  // 更新权值
            cout << get_basic() << endl;
        } else if (type == 3) {
            // 操作3：更改根节点为u，输出新根的基础值
            int u;
            cin >> u;
            root = u;  // 更新根节点
            cout << get_basic() << endl;
        } else if (type == 4) {
            // 操作4：修改树结构（删除边a-b，添加边c-d），输出新的根基础值
            int a, b, c, d;
            cin >> a >> b >> c >> d;

            // 从邻接表中删除边a-b（双向删除）
            // 删除a的邻接表中的b
            for (auto it = graph[a].begin(); it != graph[a].end(); it++) {
                if (*it == b) {
                    graph[a].erase(it);
                    break;
                }
            }
            // 删除b的邻接表中的a
            for (auto it = graph[b].begin(); it != graph[b].end(); it++) {
                if (*it == a) {
                    graph[b].erase(it);
                    break;
                }
            }

            // 添加新边c-d（双向添加）
            graph[c].push_back(d);
            graph[d].push_back(c);

            // 输出修改后根的基础值
            cout << get_basic() << endl;
        }
    }

    return 0;
}
