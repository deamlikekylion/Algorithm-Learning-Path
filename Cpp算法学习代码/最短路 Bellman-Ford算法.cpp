#include<bits/stdc++.h>
using namespace std;

const int N = 1005, INF = 0x3f3f3f3f;
int n, m, s;
struct edge { int v, w; };
vector<edge> e[N];
int d[N], pre[N];

bool bellmanford(int s) {
    memset(d, INF, sizeof(d));  d[s] = 0;
    bool flag;
    for(int i = 1; i <= n; i++){
    	flag = false;
    	for(int u = 1; u <= n; u++){
    		if(d[u] == INF)  continue;
    		for(auto ed : e[u]){
    			int v = ed.v, w = ed.w;
    			if(d[v] > d[u] + w){
    				d[v] = d[u] + w;
    				pre[v] = u; 
    				flag = true;
				}
			}
		}
		if (!flag)  break;
	}
	return flag;
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
    int t=bellmanford(s);
    if (!t) {
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
	} else {
		cout<<"存在负环！"<<endl; 
	}
    return 0;
}