#include<bits/stdc++.h>
using namespace std;

const int N=1e4+5;
int n,m,fa[N],sum[N],cha[N];
//fa为并查集父数组
//sum[i]表示i节点的总信息值,开始只对一个连通块的根节点有效,
//即sum[根]表示整个连通块的总信息值,非根节点最后由sum[根]-cha[i]得到
//cha[i]表示i节点与其父节点fa[i]的sum差值,即cha[i]=sum[fa[i]]-sum[i]

int find(int x){             //带路径压缩的并查集查找函数
    if(fa[x]==x)  return x;  //递归终止条件,x是根节点,直接返回自身
    else{
        int fx=find(fa[x]);  //递归查找父节点的根节点,注意要先更新父节点的路径再更新cha!
        cha[x]+=cha[fa[x]];  //路径压缩核心:更新x到根的差值=x到父节点的差值+父节点到根的差值
	                         //(路径压缩后x会直接指向根,因此需要先计算父节点到根的差值,再累加到x)
                             //(先计算父节点到根的差值由上一步先递归查找父节点的根节点完成)
        return fa[x]=find(fx);  //路径压缩:将x直接指向根节点fx,减少后续查找次数
    }
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)  fa[i]=i;  //并查集初始化
    while(m--){
        int op,x,y;  cin>>op>>x>>y;
        if(op==1){
            int fx=find(x),fy=find(y);
            if(fx!=fy){                            //x,y不在一个连通块则合并fy到fx
                if(sum[fx]<sum[fy])  swap(fx,fy);  //合并fy到fx保证sum[fx]>sum[fy]
                cha[fy]=sum[fx]-sum[fy];           //使得cha[fy]大于0
                fa[fy]=fx;                         //将fy的父节点设为fx完成两个连通块的合并
            }
        }else{
            int fx=find(x);  sum[fx]+=y;  
            //在节点x发送大小为y的信息即整个连通块整体加y,整个连通快节点的cha不变只需要根的sum加y
        }
    }
    for(int i=1;i<=n;i++){      //输出每个节点的最终信息值
        int fi=find(i);         //再次查找根节点,确保路径压缩完成,cha[i]是i到根(父节点)的总差值
        sum[i]=sum[fi]-cha[i];  //节点i的信息值=根节点的信息值-i到根节点的差值
        cout<<sum[i]<<' ';
    }
    return 0;
}