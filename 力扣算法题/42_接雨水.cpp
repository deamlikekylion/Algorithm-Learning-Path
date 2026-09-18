#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<int> height;
    int n=height.size(),ans=0;
    int l=0,r=n-1,lmax=0,rmax=0;
    while(l<r){                    //双指针从两端遍历
        lmax=max(lmax,height[l]);  //lmax为l左边最高的柱子
        rmax=max(rmax,height[r]);  //rmax为r右边最高的柱子
        //对于第i个柱子,i接水量为min(i左边最高的柱子,i右边最高的柱子)-i的高度
        //所以可以通过遍历每一个柱子接水量累加得总接水量
        if(lmax<rmax){
            ans+=lmax-height[l];   
            //对于第l个柱子,l左边最高的柱子=lmax,l右边最高的柱子目前不知道
            //但lmax<rmax,则lmax<l右边最高的柱子(因为rmax<=l右边最高的柱子)
            l++;  //l列处理完继续向右遍历
        }else{
            ans+=rmax-height[r];
            //对于第r个柱子,r右边最高的柱子=rmax,r左边最高的柱子目前不知道
            //但rmax<=lmax,则rmax<=r左边最高的柱子(因为lmax<=r左边最高的柱子)
            r--;  //r列处理完继续向左遍历
        }
    }
    return 0;
}