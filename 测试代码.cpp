#include<bits/stdc++.h>
using namespace std;
string maze[30]; //存放迷宫 
int vis[30][50]; //是否访问过 
char ans[1000]; //答案序列 
queue<int> que; 
int next_x[4] = {1, 0, 0, -1}; 
//注意x，y的顺序，D<L<R<U搜出来的必定字典序最小
int next_y[4] = {0, -1, 1, 0}; 
//{x, y} = {1, 0}表示向下 ,{0, -1}左,{0, 1}右,{-1, 0}上 
int DLRU[4] = {'D', 'L', 'R', 'U'};
int flag = 0; //用于dfs中 
void bfs(int x, int y){
	que.push(x);
	que.push(y);
	vis[x][y] = 1;
	while(!que.empty()){
		int current_x = que.front();
		que.pop();
		int current_y = que.front();
		que.pop();
		if(current_x == 29 && current_y == 49) //如果走到了终点就退出循环 
			break;
		for(int i = 0; i < 4; i++){ //这里是判断四个方向是否可到达 
			int next_step_x = current_x + next_x[i];
			int next_step_y = current_y + next_y[i];
			if(next_step_x < 30 && next_step_x >= 0 && next_step_y < 50 
				&& next_step_y >= 0){ //不能越界 
				if(maze[next_step_x][next_step_y] == '0') //如果是0代表可达 
					if(vis[next_step_x][next_step_y] == 0){ 
						//判断这个点有没有访问过，等于0代表没有访问过 
						que.push(next_step_x);
						que.push(next_step_y);
						vis[next_step_x][next_step_y] = 
						vis[current_x][current_y] + 1; 
						//当前节点vis值等于上一层+1，这样方便后面寻找走的路径 
					}
			}
		}
	}
}
void dfs(int index, int x, int y){
	//这里深搜是从终点开始，所以要按照字典序最小，那么方向顺序就和正向相反，就是URLD 
	if(flag == 1) return; //如果找到了第一个答案序列，不进行下面的搜索 
	if(index == 1){
		flag = 1; // 用来判断是否搜到第一个答案，如果搜到了接下来的搜索就不用干了 
		for(int i = 2; i <= vis[29][49]; i++)
			cout<<ans[i];
		cout<<endl;
		return;
	}
	for(int i = 3; i >= 0; i--){ //顺序要相反 
		int pre_x = x + next_x[i];
		int pre_y = y + next_y[i];
		if(pre_x < 30 && pre_x >= 0 && pre_y < 50 && pre_y >= 0){
			if(vis[pre_x][pre_y] + 1 == vis[x][y]){
				ans[index] = DLRU[3 - i]; 
				dfs(index - 1, pre_x, pre_y);
				ans[index] = ' ';
			}
		}
	}
}
int main(){
	freopen("maze.txt", "r", stdin);
	for(int i = 0; i < 30; i++)
		cin>>maze[i];
	bfs(0, 0);
	dfs(vis[29][49], 29, 49);
	for(int i = 0; i < 30; i++){
		for(int j = 0; j < 50; j++){
//			cout<<vis[i][j]<<" ";
			printf("%3d ", vis[i][j]);
		}
		cout<<endl;
	}
	return 0;
}
