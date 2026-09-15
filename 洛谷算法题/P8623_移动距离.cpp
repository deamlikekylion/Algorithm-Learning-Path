#include<bits/stdc++.h>
using namespace std;
int main(){
    int w,m,n;  cin>>w>>m>>n;
    int a=m/w,b=n/w,c=m%w,d=n%w;
    if(c){
        if(a%2)  c=w-m%w+1;
    }else{
        a--;  
        if(a%2) c=1;
        else c=w; 
    }
    if(d){
        if(b%2)  d=w-n%w+1;
    }else{
        b--;  
        if(b%2) d=1;
        else d=w; 
    }
    int ans=abs(a-b)+abs(c-d);
    cout<<ans;
    return 0;
}