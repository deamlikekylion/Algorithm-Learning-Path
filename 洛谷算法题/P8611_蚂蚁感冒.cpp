#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,x[55],l=0,r=0,sum=0;  cin>>n;
    for(int i=1;i<=n;i++)  cin>>x[i];
    for(int i=2;i<=n;i++){
        if(abs(x[i])<abs(x[1])&&x[i]>0) l++;
        if(abs(x[i])>abs(x[1])&&x[i]<0) r++;
    }
    if(x[1]<0){
        if(l==0)  sum=1;
        else  sum=l+r+1;
    }else{
        if(r==0)  sum=1;
        else  sum=l+r+1;
    }
    cout<<sum;
    return 0;
}