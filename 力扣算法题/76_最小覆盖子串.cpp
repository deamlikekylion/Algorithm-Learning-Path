#include<bits/stdc++.h>
using namespace std;

int main(){
    string s,t;
    vector<int> tn(128,0);  //统计t中各字符出现次数
    vector<int> wn(128,0);  //统计窗口中t中出现过的字符次数
                            //使用长度128初始全为0的数组充当哈希表,涵盖所有ASCII字符
    int num=0;              //t中不重复的字符次数(即有多少不同的字符)
    for(char c : t){
        if(tn[c]==0)  num++;
        tn[c]++;
    }
    int l=0,r=0,v=0;         //l,r为窗口两端,v为当前窗口中已经满足数量要求的字符种类数
    int f=0,minlen=INT_MAX;  //f,minlen记录最小覆盖子串的起始位置和长度(INT_MAX为int表示的最大整数,可直接用)
    while(r<s.size()){       //先向右滑动窗口,进入右移循环
        char c=s[r];
        r++;
        if(tn[c]>0){         //如果当前字符是t中的,更新窗口哈希表
            wn[c]++;
            if(wn[c]==tn[c])  v++;  //该字符的数量达标,v+1
        }
        while(v==num){       //当所有字符种类都达标时,开始收缩左边界找最短
            if(r-l<minlen){  //更新全局最短子串
                f=l;
                minlen=r-l;
            }
            char d=s[l];
            l++;             //窗口左移收缩
            if(wn[d]>0){     //如果移出的字符是t中的
                if(wn[d]==tn[d])  v--;  //移除后导致该字符数量不足,破坏了完全达标状态,将退出左收循环继续进入右移循环
                wn[d]--;     //更新窗口哈希表
            }
        }
    }
    string ans=s.substr(f,minlen);  //从s的最小覆盖子串起始位置f开始截取长度为minlen的子串为ans
    if(minlen==INT_MAX)  ans="";    //如果minlen没被更新过,说明没有合法子串,ans=""
    return 0;
}