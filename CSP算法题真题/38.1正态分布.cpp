#include<bits/stdc++.h>
using namespace std;

int main(){
	int k;  cin>>k;
	double u,o,n;
	while(k--){
		cin>>u>>o>>n;
		double m=(n-u)/o;
		int i=10*m;
		int j=(10*m-i)*10+1;
		cout<<i+1<<' '<<j<<endl;
	} 
	return 0;
}
