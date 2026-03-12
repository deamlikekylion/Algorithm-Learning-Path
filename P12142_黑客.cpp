#include<bits/stdc++.h>
using namespace std;

const int mod=1000000007,N=5e5+5;
int n,m,nm,sum,ans,a[N];

bool havenum(int num){
    int l=1,r=sum,t;
    while(l<=r){
        int mid=(l+r)/2;
        if(a[mid]<num){
            l=mid+1;  t=mid;
        }else  r=mid-1;
    }
}

int main(){
    cin>>sum;  
    for(int i=1;i<=sum;i++)  cin>>a[i];
    sort(a+1,a+1+sum);  nm=sum-2;
    for(int i=1;i*i<=nm;i++){
        int j=nm/i;
        if(i*j==nm){
            int l=1,r=sum,t;
            while(l<=r){
                int mid=(l+r)/2;
                if(a[mid]<j){
                    l=mid+1;  t=mid;
                }else  r=mid-1;
            }
        }
    }
    return 0;
}