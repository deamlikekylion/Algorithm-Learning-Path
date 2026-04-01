// 包含所有C++标准库，比赛快速写法
#include <bits/stdc++.h>
using namespace std;

// 核心：数据范围极大(1e12)，必须用long long，宏定义简化代码
#define int long long
// 数组最大长度，N最大1e5，开2e5足够
const int maxn = 200000 + 10;

// n:数组长度 m:已知条件数 q:查询数
int n, m, a, b, s;
// par[]: 并查集父节点数组
// val[]: 核心！带权并查集的权值，val[x]表示 sum[x] - sum[根节点]
int par[maxn], val[maxn];

// 并查集初始化：父节点指向自己，权值初始为0
// l=0, r=n：前缀和下标从0到n
void init(int l, int r)
{
    for(int i = l; i <= r; i++) 
        par[i] = i, val[i] = 0;
}

// 带权并查集的查找函数（带路径压缩）
// 返回x的根节点，同时更新val[x]为x到根节点的真实权值
int find(int x)
{
    // 如果x是根节点，直接返回
    if(par[x] == x) 
        return x;
    else
    {
        // 递归找到x的根节点
        int root = find(par[x]);
        // 路径压缩：更新x到根节点的权值
        // 原val[x]是x到父节点的距离，val[par[x]]是父节点到根节点的距离
        // 相加后就是x直接到根节点的距离
        val[x] += val[par[x]];
        // 路径压缩：直接让x的父节点指向根节点
        return par[x] = root;
    }
}

// 主函数，因为#define int long long，所以主函数必须用signed
signed main()
{
    // 输入：数组长度n，已知条件数m，查询数q
    cin >> n >> m;
    int q;
    cin >> q;

    // 初始化并查集：前缀和下标 0 ~ n
    init(0, n);

    // 处理M个已知的部分和条件
    for(int i = 1; i <= m; i++)
    {
        // 输入：区间[l, r]，和为s
        scanf("%lld%lld%lld", &a, &b, &s); 
        // 关键转化：区间[l,r]和 = sum[r] - sum[l-1] = s
        // 所以把a = l-1，对应前缀和sum[a]
        a--;

        // 查找a和b的根节点
        int t1 = find(a);
        int t2 = find(b);

        // 如果两个节点不在同一个集合，合并
        if(t1 != t2)
        {
            // 合并：让t2的父节点指向t1
            par[t2] = t1;
            // 核心公式：推导合并后的权值
            // 已知 sum[b] - sum[a] = s
            // sum[b] = val[b] + sum[t2]
            // sum[a] = val[a] + sum[t1]
            // 代入得：val[b]+sum[t2] - (val[a]+sum[t1]) = s
            // 因为sum[t1]=0（根节点），整理得：val[t2] = s + val[a] - val[b]
            val[t2] = -val[b] + s + val[a];
        }
    }

    // 处理Q个查询
    while(q--)
    {
        // 输入查询区间[l, r]
        scanf("%d%d", &a, &b); 
        // 同样转化为 sum[r] - sum[l-1]
        a--;

        // 查找根节点
        int t1 = find(a);
        int t2 = find(b);

        // 根节点不同 → 无法推导，输出UNKNOWN
        if(t1 != t2)
            cout << "UNKNOWN\n";
        // 根节点相同 → 可以推导，区间和 = val[b] - val[a]
        // 因为val[b]=sum[b]-sum[root]，val[a]=sum[a]-sum[root]，相减后就是sum[b]-sum[a]
        else
            cout << val[b] - val[a] << '\n';
    }

    return 0;
}