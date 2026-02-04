#include<bits/stdc++.h>		//懒人万能头文件
#define int long long		//宏定义省事
using namespace std;
const int P = 1e9 + 7;		//记得取模
int n , m , k , ans;
int a[55][55];
int dx[2] = {1 , 0};		//两种方向
int dy[2] = {0 , 1};
int mem[55][55][15][15];		//记忆数组

int dfs(int x , int y , int num , int maxn)		//x与y记录当前行列坐标，num记录当前已拿的物品总数，maxn记录当前物品最大值
{
	if(x > n || y > m)	return 0;		//越界了就直接返回0
	if(mem[x][y][maxn][num] != -1)	return mem[x][y][maxn][num];		//如果mem数组的值不为-1就直接返回
	int cnt = 0;		//记录方案数
	if(x == n && y == m)
	{
		if(num == k || num == k - 1 && a[n][m] > maxn)
			++ cnt , cnt %= P;
	}
	else
	{
		for(int i = 0;i < 2;i ++)		//枚举两种方向
		{
			int xx = x + dx[i];
			int yy = y + dy[i];
			cnt += dfs(xx , yy , num , maxn);
			if(a[x][y] > maxn)		//能否拿格子上的物品
				cnt += dfs(xx , yy , num + 1, a[x][y]);
		}
	}
	mem[x][y][maxn][num] = cnt % P;		//记录当前情况的值
	return mem[x][y][maxn][num];		//直接返回即可
}	

signed main()
{
	memset(mem , -1 , sizeof(mem));		//不要忘了初始化
	cin >> n >> m >> k;		//输入
	for(int i = 1;i <= n;i ++)		//还是输入
		for(int j = 1;j <= m;j ++)
			cin >> a[i][j];
	cout << dfs(1 , 1 , 0 , -1) % P;		//这次是输出
	return 0;
}
