#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;
struct node{
    int x,y,t;
}a[N];
int fa[N],n,m;

int cmp(node a,node b){
    return a.t<b.t;
}

int find(int x){
    if(fa[x]==x)  return x;
    return fa[x]=find(fa[x]);
}

int main(){
    cin>>n>>m;
    if(n==1){
        cout<<0<<endl;  return 0;
    }
    for(int i=1;i<=m;i++){
        cin>>a[i].x>>a[i].y>>a[i].t;
    }
    sort(a+1,a+m+1,cmp);
    for(int i=1;i<=n;i++)  fa[i]=i;
    for(int i=1;i<=m;i++){
        int fx=find(a[i].x),fy=find(a[i].y);
        if(fx!=fy){
            fa[fx]=fy;  n--;
        }
        if(n==1){
            cout<<a[i].t;  return 0;
        }
    }
    cout<<"-1"<<endl;
    return 0;
}