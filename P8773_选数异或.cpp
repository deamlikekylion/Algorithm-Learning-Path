#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5,A=1<<20;
int n,m,x,a[N],last[A],f[N];

int main(){
    cin>>n>>m>>x;
    for(int i=1;i<=n;i++)  cin>>a[i];
    for(int i=1;i<=n;i++){
        int b=a[i]^x;
        f[i]=max(f[i-1],last[b]);
        last[a[i]]=i;
    }
    while(m--){
        int l,r;  cin>>l>>r;
        if(f[r]>=l)  cout<<"yes"<<endl;
        else  cout<<"no"<<endl;
    }
    return 0;
}