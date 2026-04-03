#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;
int n,m,t,sum[N],cnt[N],mp[N],ans;
struct nod{
    int ti,id;
}a[N];

bool cmp(nod x,nod y){
    return x.ti<y.ti;
}

int main(){
    cin>>n>>m>>t;
    for(int i=1;i<=m;i++)  cin>>a[i].ti>>a[i].id;
    sort(a+1,a+1+m,cmp);
    for(int i=1;i<=m;i++){
        int ti=a[i].ti,id=a[i].id;
        if(cnt[id]){
            if(cnt[id]!=ti){
                sum[id]-=ti-cnt[id]-1;
                if(sum[id]<0)  sum[id]=0;
            }
            if(sum[id]<=3&&mp[id]==1)  mp[id]=0;  
            //注意减去衰减后先立即判断是否要移除再sum+2
            sum[id]+=2;
            if(sum[id]>5)  mp[id]=1;
            cnt[id]=ti;
        }else{
            sum[id]+=2;
            if(sum[id]>5)  mp[id]=1;
            cnt[id]=ti;
        }
    }
    for(int i=1;i<=n;i++){
        if(cnt[i]){
            if(cnt[i]!=t){
                sum[i]-=t-cnt[i];
                if(sum[i]<0)  sum[i]=0;
                if(sum[i]<=3&&mp[i]==1)  mp[i]=0;
            }
        }
        if(mp[i])  ans++;
    }
    cout<<ans;
    return 0;
}