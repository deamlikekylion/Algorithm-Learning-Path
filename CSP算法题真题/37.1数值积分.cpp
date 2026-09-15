#include<bits/stdc++.h>
using namespace std;
int main(){
    int b,c,l,r;  cin>>b>>c>>l>>r;
    long long s=0;
    if(l%2==1)  l++;
	for(int i=l;i<=r;i+=2){
		s+=i*i+i*b+c;
	} 
	cout<<s*2;
	return 0;  
}
