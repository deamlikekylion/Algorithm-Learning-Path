#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,a,b,c,d,flag=0;  cin>>n;
    for(a=0;a<=sqrt(n);a++){
        for(b=0;b<=sqrt(n-a*a);b++){
            for(c=0;c<=sqrt(n-a*a-b*b);c++){
                d=sqrt(n-a*a-b*b-c*c);
                if(n==a*a+b*b+c*c+d*d){
                    flag=1;  break;
                }
            }
            if(flag)  break;
        }
        if(flag)  break;
    }
    int m[4]={a,b,c,d};
    sort(m,m+4);
    cout<<m[0]<<' '<<m[1]<<' '<<m[2]<<' '<<m[3];
    return 0;
}