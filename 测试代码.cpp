#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+10;
int num,ans;
int fa[100100];
int find(int x)//并查集中的查询操作
{
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
int main()
{
	int n;
	cin>>n;
	for (int i=1;i<100100;i++)//所有数最开始都应指向它本身
	{
		fa[i]=i;
	}
	int a;
	for (int i=1;i<=n;i++)
	{
		cin>>a;
		a=find(a);//查询这个数
		fa[a]=find(a)+1;//修改它的父节点
		cout<<a<<" ";
	}
	return 0;
}

