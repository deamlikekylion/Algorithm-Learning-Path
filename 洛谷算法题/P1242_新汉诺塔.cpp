#include<bits/stdc++.h>
using namespace std;

const int N=49094;  //最大移动步数存储容量(满足n≤18时的最坏情况)
struct uni{ 
	int x,y,z; 
}pa[2][N];  //存储两种移动策略的步骤:
            //x=盘子编号,y=起始柱,z=目标柱,pa[0]和pa[1]分别对应两种策略
int op;  //当前使用的策略索引(0或1),用于向pa[op]中记录步骤
int first[50],last[50];  //记录编号i盘子的初始位置first[i]和最终位置last[i]
int ans[2];  //两种策略移动步骤总数(ans[0]为策略0的步数,ans[1]为策略1的步数)

void mov(int x,int s,int y,int mid){  //将x到1以mid为中转站从s移到y(标准转移函数)
	if(x==0) return;
	mov(x-1,s,mid,y);  //先将x-1移到中转站mid(y作为此次移动的中转站)
	pa[op][++ans[op]]=(uni) {x,s,y};  //将x从s移到y
	mov(x-1,mid,y,s);  //将x-1从mid移到y(达到递归效果)
}

void merg(int x,int y){  //将1到x移到y
	if(x==0)  return;
	if(first[x]==y)  return merg(x-1,y);
	int mid=6-(first[x]+y);  //此处为y不是last[x]
	merg(x-1,mid);  //将比x小的盘先移到x的中转站
	pa[op][++ans[op]]=(uni) {x,first[x],y};  //将x从初始位置移到y
	mov(x-1,mid,y,first[x]);  //将比x小的盘从x的中转站移到y
    //merge函数最终目的将1到x全部移到y,但移x时将x-1先移到了x的中转站
    //最后用mov以x的初始位置为中转站将x-1从x的中转站移到y
}

void solv(int x,int s){  //将x到1盘从s移到最终位置
	if(x==0)  return;
	if(s==last[x])  return solv(x-1,s);
	int mid;
	for(int i=1;i<=3;++i){
		if(i!=s&&i!=last[x])  mid=i;
	}  //枚举找中转站
	mov(x-1,s,mid,last[x]);  //将比x小的盘从s移到中转站
	pa[op][++ans[op]]=(uni) {x,s,last[x]};
	solv(x-1,mid);  //将比x小的盘从中转站移到最终位置(达到递归效果)
}

void init(int x){  //将编号x盘子移到最终位置
	if(x==0) return;  //移完所以盘子结束
	if(first[x]==last[x]){ 
		return init(x-1);  //x移完移x-1
	}
	int mid=6-(first[x]+last[x]);  //中转站mid
	//6-(first[x]+last[x])即为中转站位置(结果即不是first[x]也不是last[x])
    //6是因为1+2+3=6,减去其他两个得到另一个
	op=0;
	merg(x-1,mid);  //将前x-1个盘子移到中转柱mid
	pa[op][++ans[op]]=(uni) {x,first[x],last[x]};  //移动x从初始柱到目标柱
	solv(x-1,mid);  //将前x-1个盘子从mid移到它们的目标位置
	//法一:将所有比x小的盘子先移到中转站,再将x移到最终位置
	op=1;
	merg(x-1,last[x]);  //先将前x-1个盘子移到x的目标柱
	pa[op][++ans[op]]=(uni) {x,first[x],mid};  //移动x从初始柱到中转柱mid
	mov(x-1,last[x],first[x],mid);  //将前x-1个盘子从x的目标柱移回x的初始柱
	pa[op][++ans[op]]=(uni) {x,mid,last[x]};  //移动x从mid到目标柱
	solv(x-1,first[x]);  //将前x-1个盘子从x的初始柱移到它们的目标位置
	//法二:将所有比x小的盘子先移到x的最终位置，再将x移到中转站
	//再将所有小盘移到x的初始位置,最后把x移到最终位置
}

void oput(int d){  //输出函数
	for(int i=1;i<=ans[d];++i){
		printf("move %d from %c to %c\n",
            pa[d][i].x,pa[d][i].y+64,pa[d][i].z+64);  
            //字符123加64等于字符ABC
	}
	cout<<ans[d];
}

int main(){
	int n,m,a;  cin>>n;
	for(int i=1;i<=3;++i){
		cin>>m;
		while(m--){
			cin>>a;  first[a]=i;
			//将1到n编号的盘子与柱子序号对应,a为1到n的编号,i为柱子序号
		}
	}
	for(int i=1;i<=3;++i){
		cin>>m;
		while(m--){
			cin>>a;  last[a]=i;
		}
	}
	init(n);
	//从大到小将盘子放到最终的位置,因为大的不能放小的上,所以要先确定大的
	oput(ans[0]>ans[1]);
	//输出
	return 0;
}
