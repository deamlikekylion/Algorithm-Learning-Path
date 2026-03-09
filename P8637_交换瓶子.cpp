#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,m,ans=0,a[10005];  cin>>n;  m=n;
    for(int i=1;i<=n;i++)  cin>>a[i];
    while(m--){
        for(int i=1;i<=n;i++){
            if(a[i]!=i){
                swap(a[i],a[a[i]]);
                ans++;
            }
        }
    }
    cout<<ans;
    return 0;
}