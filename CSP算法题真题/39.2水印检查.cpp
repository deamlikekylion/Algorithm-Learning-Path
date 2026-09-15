#include<bits/stdc++.h>
using namespace std;

int n,l,a[210][210];

int check(int i,int j,int k){
    if(a[i][j]>=k){
        int m=a[i][j],t=0;
        for(int b=i;b<=i+4;b++){
            for(int c=j;c<=j+8;c++){
                if(b==i){
                    if(a[b][c]<k){
                        t=1;  break;
                    }else{
                        m=min(m,a[b][c]);
                    }
                }else if(b==i+1){
                    if(c==j+1||c==j+2||c==j+4||c==j+5||c==j+7){
						if(a[b][c]>=k){
							t=1;  break;
						}
					}else if(a[b][c]<k){
						t=1;  break;
					}else{
						m=min(m,a[b][c]);
					}
                }else if(b==i+2){
                    if(c==j+1||c==j+2||c==j+8){
						if(a[b][c]>=k){
							t=1;  break;
						}
					}else if(a[b][c]<k){
						t=1;  break;
					}else{
						m=min(m,a[b][c]);
					}
                }else if(b==i+3){
                    if(c==j+1||c==j+2||c==j+3||c==j+4||c==j+7||c==j+8){
						if(a[b][c]>=k){
							t=1;  break;
						}
					}else if(a[b][c]<k){
						t=1;  break;
					}else{
						m=min(m,a[b][c]);
					}
                }else{
                    if(c==j+7||c==j+8){
						if(a[b][c]>=k){
							t=1;  break;
						}
					}else if(a[b][c]<k){
						t=1;  break;
					}else{
						m=min(m,a[b][c]);
					}
                }
            }
            if(t)  break;
        }
        if(!t)  return m;
    }
    return 0;
}

int main(){
    cin>>n>>l;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
        }
    }
    for(int k=1;k<=l-1;k++){
        for(int i=1;i+4<=n;i++){
            for(int j=1;j+8<=n;j++){
                int k1=check(i,j,k);
                if(k1){
                    cout<<k<<endl;
                    if(k1!=k){
                        for(int p=k+1;p<=k1;p++){
                            cout<<p<<endl;
                        }
                    }
                    k=k1;
                }
            }
        }
    }
}