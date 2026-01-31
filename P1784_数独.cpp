#include<bits/stdc++.h>
using namespace std;

int sd[10][10];  //sd[i][j]记录i,j处的数字,空为0
bool h[10][10],l[10][10],fz[10][10]; 
//h[i][j],l[i][j]保证第i行第i列的数字j不重复,eg:i,j处填2后,h[i][2]=l[j][2]=true
//fz[i][j]保证第i个方阵内的数字j不重复,eg:i,j处填2后,fz[(i-1)/3*3+(j-1)/3+1][2]=true

void dfs(int x,int y){
    if(sd[x][y]){
        if(x==9&&y==9){  //全部填完输出结束
            for(int i=1;i<=9;i++){	
  		        for(int j=1;j<=9;j++){
                    cout<<sd[i][j]<<" ";
                }
		        cout<<endl;
	        }
            exit(0);  //注意,此处用exit(0)结束程序,用return的话不会退出所有dfs函数
        }else if(y==9)  dfs(x+1,1);  //先深搜列,当x行处列搜完(y=9)搜下一行
        else  dfs(x,y+1);
    }else{  //x,y处为0,填充数字
        for(int i=1;i<=9;i++){
            if((!h[x][i])&&(!l[y][i])&&(!fz[(x-1)/3*3+(y-1)/3+1][i])){  //判断重复
                sd[x][y]=i; 
				h[x][i]=l[y][i]=fz[(x-1)/3*3+(y-1)/3+1][i]=true;  //标记
				if(x==9&&y==9){  //同上
                    for(int i1=1;i1<=9;i1++){	
  		                for(int j1=1;j1<=9;j1++){
                            cout<<sd[i1][j1]<<" ";
                        }
		            cout<<endl;
	                }
                    exit(0);
                }else if(y==9)  dfs(x+1,1);
				else  dfs(x,y+1); 
				sd[x][y]=0; 
				h[x][i]=l[y][i]=fz[(x-1)/3*3+(y-1)/3+1][i]=false;  //恢复标记
            }
        }
    }
}

int main(){
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            int t;  cin>>t;  sd[i][j]=t;
            if(t)  h[i][t]=l[j][t]=fz[(i-1)/3*3+(j-1)/3+1][t]=true;
            //t非0,填充了数字进行标记
        }
    }
    dfs(1,1);
    return 0;
}