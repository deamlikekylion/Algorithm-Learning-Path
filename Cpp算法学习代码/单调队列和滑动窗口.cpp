#include<bits/stdc++.h>
using namespace std;
int a[10005];
deque<int> q;
int main()
{
	int n,m;  scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)  scanf("%d",&a[i]);
	//通过单调(双端)队列滑动长度为k-1的窗口维护其最左端为k-1区间内最小h的序号(队列存h的序号)  
	for(int i=1;i<=n;i++){
		while(!q.empty()&&a[q.back()]>a[i]){
			q.pop_back();
		}
		//如果最右端的值大于当前的值就去除当前的最右端,因为它不可能成为该区间的最小值了
        //(当前的值比它少),维护了队列的单调性(从左往右单增),所以队列里不一定有k-1个元素
		q.push_back(i);
		if(i>=m){
			while(!q.empty()&&q.front()<=i-m){
				q.pop_front();
			}
			//i为最右端,窗口区间为[i-(k-1)+1,i],最左端(q.front())<=i-(k-1)的都要去除
			printf("%d ",a[q.front()]);
			//取每次最左端(每个区间最小值)
		}
	}
	printf("\n");
	while(!q.empty()){
		q.pop_front();
	}
	for(int i=1;i<=n;i++){
		while(!q.empty()&&a[q.back()]<a[i]){
			q.pop_back();
		}
		q.push_back(i);
		if(i>=m){
			while(!q.empty()&&q.front()<=i-m){
				q.pop_front();
			}
			printf("%d ",a[q.front()]);
		}
	}
	printf("\n");
	return 0;
}
