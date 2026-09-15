#include<bits/stdc++.h>
using namespace std;
int n,ans=0;
int c[30]={0},p[30]={0},q[30]={0},pos[30]={0};  //p数组i+j最大为2n 

void print(){
	if(ans<=3){
		for(int i=1;i<=n;i++){
			if(i!=n)  printf("%d ",pos[i]);
			else  printf("%d",pos[i]);
		} 
	    cout<<endl;
	}
}

void dfs(int i){
	if(i>n){
		ans++;  print();  return;
	}
	for(int j=1;j<=n;j++){
		if(c[j]||p[i+j]||q[i-j+n])  continue;
		pos[i]=j;  c[j]=p[i+j]=q[i-j+n]=1;
		dfs(i+1);  c[j]=p[i+j]=q[i-j+n]=0;
	}
}

int main(){
	cin>>n;
	dfs(1);
	cout<<ans;
	return 0;
}







