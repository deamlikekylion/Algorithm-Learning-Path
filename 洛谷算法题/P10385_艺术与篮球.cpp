#include<bits/stdc++.h>
using namespace std;

int main(){
    int ans=0;
    int a[10]={13,1,2,3,5,4,4,2,2,2};
    for(int y=2000;y<=2023;y++){
        int n1=0,ty=y; 
        while(ty!=0){
            n1+=a[ty%10];
            ty/=10;
        }
        for(int m=1;m<=12;m++){
            int n2,D;
            if(m<10)  n2=13+a[m];
            else  n2=a[1]+a[m%10];
            if(m==1||m==3||m==5||m==7||m==8||m==10||m==12)  D=31;
            else if(m==4||m==6||m==9||m==11)  D=30;
            else if((y%4==0&&y%100!=0)||(y%400==0))  D=29;
            else  D=28;
            if(n1+n2>50){
                ans+=D;
                continue;
            }
            for(int d=1;d<=D;d++){
                int n3;
                if(d<10)  n3=13+a[d];
                else if(d<20)  n3=a[1]+a[d%10];
                else if(d<30)  n3=a[2]+a[d%10];
                else  n3=a[3]+a[d%10];
                if(n1+n2+n3>50)  ans++;
            }
        }
    }
    int n1=a[2]+a[0]+a[2]+a[4];
    for(int m=1;m<=4;m++){
        int n2=13+a[m],D;
        if(m==1||m==3)  D=31;
        else if(m==2)  D=29;
        else  D=13;
        for(int d=1;d<=D;d++){
            int n3;
            if(d<10)  n3=13+a[d];
            else if(d<20)  n3=a[1]+a[d%10];
            else if(d<30)  n3=a[2]+a[d%10];
            else  n3=a[3]+a[d%10];
            if(n1+n2+n3>50)  ans++;
        }
    }
    cout<<ans;
    return 0;
}