#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,ans;  cin>>n;  ans=n;
    while(n>=3){
        ans++; n-=3;  n++;
    }
    cout<<ans<<endl;
    return 0;
}