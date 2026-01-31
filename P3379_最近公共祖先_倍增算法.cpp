#include<bits/stdc++.h>
using namespace std;

const int N=5e5+5;
int n,m,s,dep[N],fa[N][20];  
//dep[i]为i点的深度,fa[i][j]为i点向上跳2^j的祖先节点,最多5e5个点,j取20即可(5e5<2^20)
vector<int> e[N];

void dfs(int u,int father){
	dep[u]=dep[father]+1;
	fa[u][0]=father;
	for(int i=1;i<=19;i++)  fa[u][i]=fa[fa[u][i-1]][i-1];  
	//倍增公式,u往上2^i层的祖先节点可有u往上2^i-1层的祖先节点往上跳2^i-1层得到
	//i从下到大遍历fa[u][i-1]值在fa[u][i]前已得到
	for(int v : e[u])  if(v!=father)  dfs(v,u);  //递归u的所有子节点
}

int lca(int u,int v){
	if(dep[u]<dep[v])  swap(u,v);  //保证u的层数更大,让u跳
	for(int i=19;i>=0;i--)  if(dep[fa[u][i]]>=dep[v])  u=fa[u][i];
	//i从大到小遍历,如果u跳2^i层后还未超过v就跳,否则不跳,最终让u跳到v的同一层
	//(因为任何数一定可以拆分成多个2的次方相加所以u一定可以跳到v的同一层)
	if(u==v)  return v;  //跳完后u等于v则v是u的祖先节点
	for(int i=19;i>=0;i--)  if(fa[u][i]!=fa[v][i])  u=fa[u][i],v=fa[v][i];
	//i从大到小遍历,当跳的层数很大时u,v的祖先节点一定相同,但不一定是最近的
	//为了让uv跳到最近公共祖先的下一层,所以只有跳完后祖先节点不同才能跳
	//此时一定在最近公共祖先下面,假设跳第j层时到最近公共祖先
	//则i>j时跳的祖先节点相等所以不跳,i<j的都可以跳
	//而从2^0加到2^j-1等于2^j-1,即最近公共祖先的下一层
	return fa[u][0];  //此时u的上一层就是最近公共祖先
}

int main(){
	cin>>n>>m>>s;  int a,b;  
	for(int i=0;i<n-1;i++){
		cin>>a>>b;
		e[a].push_back(b);
		e[b].push_back(a);
	}
	dfs(s,0);  //从根节点开始递归预处理fa数组(根节点以上的祖先节点为0)
    while(m--){
    	cin>>a>>b;
    	cout<<lca(a,b)<<endl;
	}
	return 0;
}
