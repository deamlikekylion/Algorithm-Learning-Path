#include<bits/stdc++.h>
using namespace std;

int n,t,t1,t2,a,b,c;

int cal(){
    int h,m,s;
    scanf("%d:%d:%d",&h,&m,&s);  //用scanf读取更简单
    t1=h*3600+m*60+s;            //全部转换成秒方便计算
    scanf("%d:%d:%d",&h,&m,&s);  
    t2=h*3600+m*60+s;
    char c;
    while((c=getchar())!='\n'&&c!='\r'){  //'\r'回车(光标回行首),'\n'换行(光标移下一行)
        if(c=='('){
            c=getchar();  //这时读入的是加号
            c=getchar();  //这时读入的是数字
            t2+=(c-'0')*24*3600;
        }
    }
    return t2-t1;
}

int main(){
    cin>>n;
    while(n--){
        t=(cal()+cal())/2;
        a=t/3600;  b=(t%3600)/60;  c=(t%3600)%60;  //将秒再转化成“时分秒”的形式
        printf("%02d:%02d:%02d\n",a,b,c);  //用printf输出更简单,%02d表示输出不足两位前补0
    }
    return 0;
}