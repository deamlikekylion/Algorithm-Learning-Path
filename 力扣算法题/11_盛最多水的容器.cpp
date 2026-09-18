#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<int> height;
    int n=height.size(),i=0,j=n-1,maxa=0;  //初始选两端最宽,后面向中间靠拢
    while(i<j){
        int h=min(height[i],height[j]);
        maxa=max(maxa,h*(j-i));
        //核心剪枝:只要新板的高度<=当前短板h,容水量必然变小,跳过选下一个
        while(i<j&&height[i]<=h)  i++;
        while(i<j&&height[j]<=h)  j--;
    }
    return 0;
}