#include<bits/stdc++.h>
using namespace std;

bool check(int x){
    for(int i=2;i*i<=x;i++){
        if(x%i==0)  return false;
    }
    return true;
}

int main(){
    int cnt=1;
    for(int i=3;;i++){
        if(check(i))  cnt++;
        if(cnt==2025){
            cout<<i;  break;
        }
    }
    return 0;
}