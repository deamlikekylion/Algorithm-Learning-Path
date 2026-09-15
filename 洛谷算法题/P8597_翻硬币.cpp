#include<bits/stdc++.h>
using namespace std;
int main(){
    string a,b;  cin>>a>>b;
    int cnt=0;
    if(a==b)  cout<<cnt;
    else{
        int n=a.length();
        for(int i=0;i<n;i++){
            if(a[i]!=b[i]){
                a[i]==b[i];
                if(a[i+1]=='*')  a[i+1]='o';
                else  a[i+1]='*';
                cnt++;
            }
            if(a==b)  break;
        }
    }
    cout<<cnt;
    return 0;
}