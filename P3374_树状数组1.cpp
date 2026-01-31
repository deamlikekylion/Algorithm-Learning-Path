#include<bits/stdc++.h>
using namespace std;

const int N=5e5+5;
int n,m,s[N],op,x,y,k;
//s[N]为区间和

void change(int x,int k){  //向后修,点修改(将包含x的区间和s都加k)
    for(;x<=n;x+=x&-x)  s[x]+=k;  //x&-x取x的低位2次幂,x+x的低位2次幂=父下标(爬链)
}

int query(int x){  //向前查,前缀和
    int res=0;
    for(;x;x-=x&-x)  res+=s[x];
    return res;  //res为到x为止的前缀和
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)  cin>>k,  change(i,k);
    while(m--){
        cin>>op>>x;
        if(op==1)  cin>>k,  change(x,k);  //点修
        else  cin>>y,  cout<<query(y)-query(x-1)<<endl;  //区查,前缀和作差
    }
    return 0;
}