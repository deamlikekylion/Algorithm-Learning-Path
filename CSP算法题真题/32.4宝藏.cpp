#include<bits/stdc++.h>
using namespace std;

const long long MOD=998244353;
struct MAT{
	long long a[2][2];
	MAT(){  //初始化 
		a[0][0]=a[0][1]=a[1][0]=a[1][1]=0;
	}
	MAT(long long a00,long long a01,long long a10,long long a11){  //赋值 
        a[0][0]=a00%MOD;  a[0][1]=a01%MOD;
        a[1][0]=a10%MOD;  a[1][1]=a11%MOD;
    }
};
struct Command{
	int v1;
	MAT mat; 
};
Command cmd[100005];  //记录指令 

MAT multiply(MAT res,MAT t){
	MAT tmp;  //不能直接用res 
	tmp.a[0][0]=(res.a[0][0]*t.a[0][0]+res.a[0][1]*t.a[1][0])%MOD;
	tmp.a[0][1]=(res.a[0][0]*t.a[0][1]+res.a[0][1]*t.a[1][1])%MOD;
	tmp.a[1][0]=(res.a[1][0]*t.a[0][0]+res.a[1][1]*t.a[1][0])%MOD;
	tmp.a[1][1]=(res.a[1][0]*t.a[0][1]+res.a[1][1]*t.a[1][1])%MOD;
	return tmp;
}

int main(){
	int n,m;  cin>>n>>m;
	for(int i=1;i<=n;i++){
		int t;  cin>>t;  cmd[i].v1=t;
		if(t==1||t==2){
			long long a,b,c,d;  cin>>a>>b>>c>>d;
			cmd[i].mat=MAT(a,b,c,d);
		}
	} 
	while(m--){
		int op;  cin>>op;
		if(op==1){
			int i,t;  cin>>i>>t;
			cmd[i].v1=t;
			if(t==1||t==2){
			    long long a,b,c,d;  cin>>a>>b>>c>>d;
			    cmd[i].mat=MAT(a,b,c,d);
		    }
		}else if(op==2){
			int l,r;  cin>>l>>r;
			deque<MAT> q;  
			stack<int> s;  //用栈记录最后插入的是头(1)还是尾(0) 
			for(int i=l;i<=r;i++){
				int t=cmd[i].v1;
				if(t==1){
					q.push_front(cmd[i].mat);
					s.push(1);
				}else if(t==2){
					q.push_back(cmd[i].mat);
					s.push(0);
				}else if(t==3){
					if(!s.empty()){
						int flag=s.top();  s.pop();
						if(flag)  q.pop_front();
						else  q.pop_back(); 
					}
				} 
			}
			MAT res=MAT(1,0,0,1);
			while(q.size()){
				MAT t=q.front();  q.pop_front();
				res=multiply(res,t);
			}
			cout<<res.a[0][0]<<' '<<res.a[0][1]<<' '
                <<res.a[1][0]<<' '<<res.a[1][1]<<endl;
		}
	}
	return 0;
}