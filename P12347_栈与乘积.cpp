#include<bits/stdc++.h>
using namespace std;

int Q,op,y,top,cnt,tz,zero[100005];
long long ans,x;    
//top为实际栈的栈顶指针(记录当前栈的元素个数/位置)
//cnt为有效数字栈(a数组)的栈顶指针,tz为0栈(zero数组)的栈顶指针
//zero为数组模拟栈:存储所有数字0在实际栈中的位置
//ans存储查询的乘积结果,x为入栈的数字
struct nod{         //结构体:存储非0非1的有效数字和它在实际栈中的位置
	long long val;  //数字的值
	int pos;        //该数字在实际栈中的位置(用于判断是否在查询区间内)
}a[100005];         //数组模拟栈:存储有效数字(非0非1)


int main(){
	cin>>Q; 
	while(Q--){ 
		cin>>op; 
		if(op==1){
			cin>>x;  top++;  //实际栈栈顶+1(无论数字是什么,实际栈都占位置)
			if(x==0){        //如果数字是0,存入0栈并记录它在实际栈的位置
				zero[++tz]=top;
			}else if(x!=1){  //如果数字不是1也不是0(有效数字),存入有效数字栈
				cnt++;          //有效数字栈栈顶+1
				a[cnt].val=x;   //存数值
				a[cnt].pos=top; //存该数字在实际栈的位置
			}
			//数字1:不做任何处理,不存栈(乘法无贡献,且耗时)
		}else if(op==2){
			if(top){  //栈非空才可以弹出
				if(top==zero[tz]){  //要弹出的是数字0(位置匹配0栈栈顶)
					top--;   //实际栈栈顶-1
					tz--;    //0栈栈顶-1(弹出0)
				}else if(top==a[cnt].pos){  //要弹出的是有效数字(非0非1)
					top--;   //实际栈栈顶-1
					cnt--;   //有效数字栈栈顶-1(弹出有效数字)
				}else{  //要弹出的是数字1(无存储,仅修改实际栈指针)
  					top--;
				}
			}
		}else if(op==3){
			cin>>y;
			if(y>top){  //栈内元素不足y个:输出ERROR
				cout<<"ERROR"<<endl;
			}else if(tz&&(top-zero[tz]+1)<=y){
            //查询区间内包含数字0:乘积直接为0
			//判断规则:0栈非空,且最靠近栈顶的0在查询的y个元素内
				cout<<0<<endl;
			}else{  //无0,计算有效数字的乘积
				ans=1;    //乘积初始化为1
				int t=0;  //计数器:遍历有效数字栈的偏移量
				//循环:从有效数字栈栈顶往回遍历有效数字,直到超出查询区间y
				while(top-a[cnt-t].pos+1<=y) {
					ans*=a[cnt-t].val;
					if(ans>=4294967296)  break;
					t++;
				}
				if(ans>=4294967296)  cout<<"OVERFLOW"<<endl;
				else  cout<<ans<<endl;
			}
		}
	}
	return 0;
}