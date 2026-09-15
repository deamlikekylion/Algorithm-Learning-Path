#include<bits/stdc++.h>
using namespace std;

const int N = 1005, INF = 0x3f3f3f3f;
int n, m, s;
struct edge { int v, w; };
vector<edge> e[N];
int d[N], vis[N], pre[N];
// 优先队列：存储 (距离, 节点)，按距离从小到大排序
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

void dijkstra(int s) {
    // 节点是 1-based，因此初始化 1~n
    for (int i = 1; i <= n; i++) d[i] = INF;
    d[s] = 0;  q.push({0, s});
    while (q.size()) {
        auto t = q.top();  q.pop();
        int u = t.second;
        if (vis[u]) continue;
        vis[u] = 1;
        // 遍历 u 的所有邻接边，进行松弛操作
        for (auto ed : e[u]) {
            int v = ed.v, w = ed.w;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                pre[v] = u;
                // 推送“更新后的节点 v”到优先队列
                q.push({d[v], v}); 
            }
        }
    }
}

// 递归输出从 s 到 u 的路径
void dfs_path(int u) {
    if (u == s) {
        cout << u;
        return;
    }
    dfs_path(pre[u]);
    cout << " " << u;
}

int main() {
    cin >> n >> m >> s;
    // 读入 m 条边，构建邻接表
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        e[a].push_back({b, c});
    }
    dijkstra(s);
    // 输出每个节点的最短距离和路径
    for (int i = 1; i <= n; i++) {
        if (i == s) continue; // 跳过起点自身
        if (d[i] == INF) {
            cout << "从" << s << "到" << i << "不可达" << endl;
        } else {
            cout << "从" << s << "到" << i << "的最短距离：" << d[i] << "，最短路径为：";
            dfs_path(i);
            cout << endl;
        }
    }
    return 0;
}
