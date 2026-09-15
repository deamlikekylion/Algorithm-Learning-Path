#include<bits/stdc++.h>
using namespace std;
int h[10005]={0};
queue<int> mem;
int main()
{
	int m,n;  scanf("%d %d",&m,&n);
	int cnt=0;
	while(n--){
		int word;  scanf("%d",&word);
		if(!h[word]){
			++cnt;
			mem.push(word);
			h[word]=1;
			while(mem.size()>m){
				h[mem.front()]=0;
				mem.pop();
			}
		}
	}
	cout<<cnt;
	return 0;
}
