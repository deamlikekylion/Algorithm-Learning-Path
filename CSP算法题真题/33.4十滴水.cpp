#include<bits/stdc++.h>
using namespace std;

struct Node{
	int pos,water,pre,next;
}nodes[300005];

int cmp(Node a,Node b){
	return a.pos<b.pos;
}

int main(){
	int c,m,n,cnt;  cin>>c>>m>>n;  cnt=m;
	for(int i=0;i<m;i++)  cin>>nodes[i].pos>>nodes[i].water;
	sort(nodes,nodes+m,cmp);  //按照pos升序排序(因为可能有无水的格子所以i与pos不是相等的)
    for(int i=0;i<m;i++){
    	nodes[i].pre=(i==0)?-1:i-1;
    	nodes[i].next=(i==m-1)?-1:i+1;
	}
	while(n--){
		int p;  cin>>p;
		int l=0,r=m-1,idx=-1;
		while(l<=r){  //二分查找nodes[idx]的pos为p
			int mid=(l+r)/2;
			if(nodes[mid].pos==p){
				idx=mid;  break;
			}else if(nodes[mid].pos<p)  l=mid+1;
			else r=mid-1;
		}
		nodes[idx].water++;  queue<int> q;
		if(nodes[idx].water>=5)  q.push(idx);
		while(!q.empty()){
			int u=q.front();  q.pop();
			if(nodes[u].water<5)  continue;
			nodes[u].water=0;  cnt--;
			int l=nodes[u].pre,r=nodes[u].next;
			if(l!=-1){
				nodes[l].next=r;  //删除已经爆开的格子u,保证后面爆开的格子pre,next的格子都有水 
				nodes[l].water++;
				if(nodes[l].water>=5)  q.push(l);
			}
			if(r!=-1){
				nodes[r].pre=l;   //删除已经爆开的格子u  
				nodes[r].water++;
				if(nodes[r].water>=5)  q.push(r);
			}
		}
		cout<<cnt<<endl;
	}
	return 0;
}



















