#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5,K=1e3+5;
int n,k,a[N],b[K][3],ans;  
//b[r][3]表示%k余数为r的最大的三个数(因为题目要求三个数之和,所以同余的最多取三个即可)

bool cmp(int x,int y){  //降序排序自定义函数
    return  x>y;
}

int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++)  cin>>a[i];
    sort(a+1,a+1+n,cmp);  //降序排序,后面b[r]先存入的就是最大的
    for(int i=1;i<=n;i++){
        int r=a[i]%k;
        for(int j=0;j<3;j++){
            if(b[r][j]==0){  //b数组初始化为0,而a数组不为0,可用来判断是否存入了数字
                b[r][j]=a[i];
                break;
            }
        }
    }
    //三个数和为k的倍数,则它们对k的余数和只有0,k,2k三种情况,枚举余数r1,r2可由sum得r3
    for(int sum=0;sum<=2*k;sum+=k){
        for(int r1=0;r1<k;r1++){
            for(int r2=0;r2<k;r2++){
                int r3=sum-r1-r2;
                if(r3<0||r3>k)  continue;  //检查r3要在余数范围内
                int x1,x2,x3;  //即满足要求的三个数
                x1=b[r1][0];   //x1取余数r1中的最大值
                if(r1==r2&&r1==r3){  //讨论r1,r2,r3的五种情况取其他较大的两个数
                    x2=b[r1][1];  x3=b[r1][2];
                }else if(r1==r2&&r1!=r3){
                    x2=b[r1][1];  x3=b[r3][0];
                }else if(r1==r3&&r1!=r2){
                    x2=b[r2][0];  x3=b[r1][1];
                }else if(r1!=r2&&r2==r3){
                    x2=b[r2][0];  x3=b[r2][1];
                }else{
                    x2=b[r2][0];  x3=b[r3][0];
                }
                if(x1!=0&&x2!=0&&x3!=0){    //检查三个数是否存在
                    ans=max(ans,x1+x2+x3);  //取最大三个数的和
                }
            }
        }
    }
    cout<<ans;
    return 0;
}