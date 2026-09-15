#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,m,sum=0,a[1005],b[1005],c[1005];
    cin>>n;
    for(int i=0;i<n;i++)  cin>>a[i];
    for(int i=0;i<n;i++)  cin>>b[i];    
    for(int i=0;i<n;i++)  cin>>c[i];    
    cin>>m;
    int t1=0,t2=0,t3=0;
    while(m--){
        int x1,x2,x3;  cin>>x1>>x2>>x3;
        t1=(t1+x1)%n;  t2=(t2+x2)%n;
        t3=(t3+x3)%n;
        int y1=a[t1],y2=b[t2],y3=c[t3];
        if(y1==y2&&y2==y3){
            sum+=200;  continue;
        }else if(y1==y2||y1==y3||y2==y3){
            sum+=100;  continue;
        }else if(y2==y1+1&&y3==y1+2){
            sum+=200;  continue;
        }else{
            int y[3];  
            y[0]=y1,y[1]=y2,y[2]=y3;
            sort(y,y+3);
            if(y[1]==y[0]+1&&y[2]==y[0]+2){
                sum+=100;  continue;
            }
        }  
    }
    cout<<sum<<endl;
    return 0;
}