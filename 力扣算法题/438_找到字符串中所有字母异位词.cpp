#include<bits/stdc++.h>
using namespace std;

int main(){
    string s,p;
    vector<int> ans;
    int s_len=s.size(),p_len=p.size();
    if(s_len<p_len)  return 0;  //特判,如果s比p还短,不可能包含p的异位词(实际return ans)
    vector<int> countP(26, 0);
    vector<int> countS(26, 0);  
    //因为题目只有小写英文字母,直接用两个大小为26的vector<int>:
    //countP:记录目标串p的词频;countS:记录当前窗口里26个字母的词频
    for(int i=0;i<p_len;i++){              //统计p和s初始窗口(长度为 p_len)的词频
        countP[p[i]-'a']++;
        countS[s[i]-'a']++;
    }
    if(countS==countP)  ans.push_back(0);  //检查第0个窗口是否匹配
    for(int i=0;i<s_len-p_len;i++){        //开始滑动窗口:每次右边进一个，左边出一个
        countS[s[i]-'a']--;                //左边移出字符s[i]
        countS[s[i+p_len]-'a']++;          //右边加入新字符s[i+p_len]
        if(countS==countP)  ans.push_back(i+1);  
        //两个vector可以直接用==判断是否相等,如果当前窗口的词频与p一致,记录起始下标(新窗口起点是i+1)
    }
    return 0;
}