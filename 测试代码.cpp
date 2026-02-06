#include<bits/stdc++.h>
using namespace std;
#define rep(x,y,z) for(int x=y;x<=z;x++)
typedef long long LL;
const int mod=1e9+7;
int n,m,a,b,oppo[7]={0,4,5,6,1,2,3};
bool st[7][7];

struct matrix{
    LL c[7][7];
    matrix(){memset(c,0,sizeof c);}
}A,res; 

matrix operator * (matrix &x,matrix &y){
    matrix t; 
    rep(i,1,6){ 
        rep(j,1,6){ 
            rep(k,1,6){ 
                t.c[i][j]=(t.c[i][j]+x.c[i][k]*y.c[k][j])%mod;
            }
        }
    }
    return t;
}

void fastpow(LL k){
    rep(i,1,6) res.c[1][i]=4;
    rep(i,1,6){ 
        rep(j,1,6){
            if(st[i][oppo[j]]) A.c[i][j]=0;
            else A.c[i][j]=4;
        }
    }
    while(k){
        if(k&1) res=res*A;
        A=A*A;
        k>>=1;
    }
}

int main(){
    cin>>n>>m;
    while(m--){
        cin>>a>>b;
        st[a][b]=st[b][a]=1;
    }
    fastpow(n-1);
    LL ans=0;
    rep(i,1,6) ans=(ans%mod+res.c[1][i]%mod)%mod;
    cout<<ans;
    return 0;
}