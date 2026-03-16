#include<bits/stdc++.h>
using namespace std;

int g(int x){  //小于等于x的奇数个数 
    if(!x)  return 0;
    return (x+1)/2;
}

int f(int x){  //小于等于x的4的倍数个数
    return x/4;
}

int main(){
    int l,r,ans;  cin>>l>>r;
    ans=g(r)-g(l-1)+f(r)-f(l-1);
    /*x=(y−z)*(y+z),可知x满足可以拆成2个奇偶性相同的数(y-z和
    y+z)的乘积;如果是奇数,直接拆成1和它本身即可,即y-z=1,y+z=x;
    如果是偶数,因为要拆成2个偶数(两个偶数相乘才可能为偶数),所以
    应是4的倍数,此时一种拆分为拆成2和x除以2,即y-z=2,y+z=x/2;
    所以,答案为l到r中奇数和4的倍数的个数.*/
    cout<<ans;
    return 0;
}