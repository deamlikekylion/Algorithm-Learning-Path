#include<bits/stdc++.h>
using namespace std;

int n,ans;
string s;

int main(){
    cin>>s;  n=s.size();
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(s[j]>s[i])  continue;
            else if(s[j]<s[i])  ans++;
            else{
                int x=i+1,y=j-1;
                while(x<y){
                    if(s[y]>s[x])  break;
                    else if(s[y]<s[x]){
                        ans++;  break;
                    }else{
                        x++;  y--;
                    }
                }
            }
        }
    }
    cout<<ans;
    return 0;
}