#include<bits/stdc++.h>
using namespace std;

const int N = 1005, INF = 0x3f3f3f3f;
int n, m, d[N][N], p[N][N]; // p[i][j] 记录 i->j 的中间节点

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // 核心：松弛操作（更新最短距离 + 记录中间节点）
                if (d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j]; // 修正：实际更新最短距离
                    p[i][j] = k;                 // 记录 i->j 的中间节点为 k
                }
            }
        }
    }
}

// 递归输出 i->j 的中间路径（不含起点 i 和终点 j）
void path(int i, int j) {
    if (p[i][j] == 0) return; // 无中间节点，直接返回
    int k = p[i][j];
    path(i, k);     // 先输出 i->k 的中间路径
    cout << " " << k; // 输出中间节点 k
    path(k, j);     // 再输出 k->j 的中间路径
}

int main() {
    cin >> n >> m;
    // 初始化距离矩阵和前驱矩阵
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            d[i][j] = (i == j) ? 0 : INF; // 自身到自身距离为 0，否则为 INF
            p[i][j] = 0; // 初始无前驱节点
        }
    }
    // 读入边
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        d[a][b] = c;
    }

    floyd(); // 先调用 Floyd 算法计算最短路径

    // 输出每个起点 i 到终点 j 的结果
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue; // 跳过自身到自身的情况
            if (d[i][j] == INF) {
                cout << "从" << i << "到" << j << "不可达！" << endl;
            } else {
                cout << "从" << i << "到" << j << "的最短距离为：" << d[i][j];
                cout << "，最短路径为：" << i;
                path(i, j); // 输出中间路径
                cout << " " << j << endl;
            }
        }
    }
    return 0;
}




















