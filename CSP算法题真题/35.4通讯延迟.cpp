#include<bits/stdc++.h>  
using namespace std;

const long long INF = 0x3f3f3f3f3f3f3f3fLL;
const int N = 5005;

// 边结构体：表示图中的一条边
struct edge {
    int from;  // 边的起点
    int to;    // 边的终点
    long long w;  // 边的权重（此处为通讯延迟）
    edge(int a, int b, long long c) : from(a), to(b), w(c) {}
    // 构造函数：初始化边的起点、终点和权重
};

// 邻接表：e[i]存储所有从节点i出发的边
vector<edge> e[N];

// 节点结构体：用于优先队列中存储节点及其当前最短距离
struct node {
    int id;         // 节点编号
    long long n_dis;  // 从起点到该节点的当前最短距离
    // 构造函数：初始化节点编号和当前距离
    node(int b, long long c) : id(b), n_dis(c) {}
    // 重载小于号：使优先队列成为小根堆（距离小的节点优先出队）
    bool operator<(const node& a) const {
        return n_dis > a.n_dis;  // 注意：优先队列默认是大根堆，这里反转比较结果
    }
};

int n, m;  // n：节点数量；m：基站数量
long long dis[5005];  // dis[i]：从起点（节点1）到节点i的最短距离
bool done[5005];  // done[i]：标记节点i是否已确定最短距离（避免重复处理）

// Dijkstra算法：求解从起点（节点1）到所有其他节点的最短距离
void dijkstra() {
    int s = 1;  // 起点为节点1
    // 初始化：所有节点的最短距离设为无穷大，且未处理
    for (int i = 1; i <= n; i++) {
        dis[i] = INF;
        done[i] = 0;  // 0表示未处理，1表示已处理
    }
    dis[s] = 0;  // 起点到自身的距离为0

    // 优先队列（小根堆）：用于每次选择当前距离最小的节点
    priority_queue<node> q;
    q.push(node(s, dis[s]));  // 起点入队

    // 处理队列中的节点，直到队列为空
    while (!q.empty()) {
        node u = q.top();  // 取出当前距离最小的节点
        q.pop();  // 弹出队列

        if (done[u.id]) continue;  // 若该节点已确定最短距离，跳过
        done[u.id] = 1;  // 标记为已处理

        // 遍历当前节点的所有邻接边，更新可达节点的最短距离
        for (int i = 0; i < e[u.id].size(); i++) {
            edge y = e[u.id][i];  // 当前边（从u.id到y.to）
            if (done[y.to]) continue;  // 若目标节点已处理，跳过

            // 松弛操作：若通过当前边到达y.to的距离更短，则更新
            if (dis[y.to] > y.w + u.n_dis) {
                dis[y.to] = y.w + u.n_dis;  // 更新最短距离
                q.push(node(y.to, dis[y.to]));  // 将更新后的节点入队
            }
        }
    }
}

int main() {
    cin >> n >> m;  // 读取节点数量n和基站数量m

    for (int i = 1; i <= n; i++) e[i].clear();
    // 初始化邻接表（清空每个节点的边列表）

    map<pair<long long, long long>, int> dian;
    int cnt = 1;  // 节点编号计数器（从1开始）
    // 用map存储节点坐标与编号的映射：键为坐标(x,y)，值为节点编号（1~n）
	   
    for (int i = 0; i < n; i++) {  // 读取n个节点的坐标，并分配编号
        long long x, y;
        scanf("%lld %lld", &x, &y);  // 读取节点坐标
        dian[{x, y}] = cnt++;  // 为该坐标分配唯一编号（1,2,...,n）
    }

    // 处理m个基站
    while (m--) {
        long long x, y, r, d;
        scanf("%lld %lld %lld %lld", &x, &y, &r, &d);
        // 读取基站信息：x,y为基站坐标，r为覆盖半径（正方形范围），d为通讯延迟
		 
        vector<int> nodes;  // 存储当前基站覆盖的所有节点编号

        auto it = dian.lower_bound({x - r, y - r});
        // 查找覆盖范围内的节点：利用map的有序性，缩小查找范围
        // lower_bound({x - r, y - r})：找到第一个x坐标 >= x-r的节点
        
        // 遍历x坐标在[x-r, x+r]范围内的节点
        while (it != dian.end() && it->first.first <= x + r) {
            // 检查y坐标是否在[y-r, y+r]范围内（确保在正方形覆盖区）
            if (it->first.second >= y - r && it->first.second <= y + r) {
                nodes.push_back(it->second);  // 加入覆盖节点列表
            }
            it++;  // 继续检查下一个节点
        }

        // 若覆盖的节点数 >= 2，则在这些节点间建立双向边（通讯是双向的）
        int t = nodes.size();
        if (t >= 2) {
            // 只处理i < j的情况，避免重复添加边（i->j和j->i各加一次）
            for (int i = 0; i < t; i++) {
                for (int j = i + 1; j < t; j++) {
                    // 添加从nodes[i]到nodes[j]的边，权重为d
                    e[nodes[i]].push_back(edge(nodes[i], nodes[j], d));
                    // 添加从nodes[j]到nodes[i]的边，权重为d（双向）
                    e[nodes[j]].push_back(edge(nodes[j], nodes[i], d));  
                }
            }
        }
    }

    // 调用Dijkstra算法计算最短路径
    dijkstra();

    // 输出结果：若节点n不可达（距离仍为INF），输出"Nan"；否则输出最短距离
    if (dis[n] >= INF) cout << "Nan" << endl;
    else cout << dis[n] << endl;

    return 0;
}