#include<bits/stdc++.h>
using namespace std;

int main(){
    string s;  cin>>s;
    int n=s.size(),l=0,r=n-1,sum=0;
    while(l<r){
        while(s[l]!='A'&&l<r)  l++;
        while(s[r]!='B'&&l<r)  r--;
        if(l>=r)  break;
        l++;  r--;  sum+=2;
    }
    cout<<n-sum;
    return 0;
}