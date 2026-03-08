#include<iostream>
using namespace std;

int t,t1,t2;
int cal(){ //计算飞行时间 
	int h,m,s;
	scanf("%d:%d:%d",&h,&m,&s);
	t1=h*3600+m*60+s; //转换为秒数 
	scanf("%d:%d:%d",&h,&m,&s);
	t2=h*3600+m*60+s;
	char c;
	while((c=getchar())!='\n' && c!='\r'){ //输入（+1）的部分
		if(c=='('){
			c=getchar(); //这时读入的是加号
			c=getchar(); //这时读入的是数字
			t2+=(c-'0')*86400; //累加天数，同样换算成秒 
		}
	}
	return t2-t1;
}
int main(){
	cin>>t;
	while(t--){
		int ans=(cal()+cal())/2,a,b,c;
		a=ans/3600,ans%=3600; b=ans/60,ans%=60; c=ans; //将秒再转化成“时分秒”的形式
		printf("%02d:%02d:%02d\n",a,b,c);
	}
	return 0;
}
