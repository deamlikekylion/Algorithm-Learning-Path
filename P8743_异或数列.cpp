#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;  cin>>t;
    while(t--){
        int n;  cin>>n;
        vector<int> x(n);
        for(int i=0;i<n;i++)  cin>>x[i];
        int ans=0;
        for(int k=19;k>=0;k--){
            int cnt1=0;
            for(int i : x)  if(i>>k&1)  cnt1++;
            if(cnt1%2==0)  continue;
            else if(cnt1==1)  ans=1;
            else{
                int cnt0=n-cnt1;
                if(cnt0%2==0)  ans=1;
                else  ans=-1;
            }
            break;
        }
        cout<<ans<<endl;
    }
    return 0;
}