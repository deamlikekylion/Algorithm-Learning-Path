#include<bits/stdc++.h>
using namespace std;

int main(){
	int n;  scanf("%d",&n);
	int a[1005],k[1005],ans[1005];
	memset(ans,0x3f3f3f,sizeof(ans));
	//ans[i]：到达第i格所需的最少跳跃次数（初始化为较大值表示不可达）	
	for(int i=1;i<=n;i++)  scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)  scanf("%d",&k[i]);
	priority_queue <int> q;
	q.push(1);  ans[1]=0; 
	//优先队列（默认大顶堆），用于存储待处理的格子位置
    //此处用优先队列是为了优先处理更靠前的位置（非严格意义上的贪心） 
	while(!q.empty()){
		int now=q.top();
		q.pop();  
		if(now+k[now]>=n){  //再跳1步即可到达终点，直接输出结果
			cout<<ans[now]+1;
			return 0;
		}
		for(int i=1;i<=k[now];i++){
			int next=now+i;
			next-=a[next];  //进行题目要求的后退操作得到最终位置 	
			if(ans[next]<ans[now]+1)  continue;  
			//剪枝：如果到达next格的已知最少步数<=当前计算的步数（ans[now]+1）
            //说明无需更新，直接跳过（保证ans[next]始终存储最小值） 
			ans[next]=ans[now]+1;  //更新到达next格的最少步数（当前路径更优） 
			q.push(next);          //将更新后的格子加入队列，等待处理其后续跳跃 
		}
	}
	cout<<-1;
	return 0;
}