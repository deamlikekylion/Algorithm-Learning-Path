#include<bits/stdc++.h>
using namespace std;

const int N=5e5+5;
int n,m,s[N],a[N],op,x,y,k;
//s[N]为差分的区间和

void change(int x,int k){  //向后修,点修改(将包含x的区间和s都加k)
    for(;x<=n;x+=x&-x)  s[x]+=k;  //x&-x取x的低位2次幂,x+x的低位2次幂=父下标(爬链)
}

int query(int x){  //向前查,前缀和
    int res=0;
    for(;x;x-=x&-x)  res+=s[x];
    return res;  //res为到x为止修改值的差分前缀和
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)  cin>>a[i];
    while(m--){
        cin>>op>>x;
        if(op==1){  //区修,差分修改
            cin>>y>>k;
            change(x,k);
            change(y+1,-k);
        }else  cout<<a[x]+query(x)<<endl;  //点查,原值加修改值差分前缀和
    }
    return 0;
}