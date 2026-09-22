#include<bits/stdc++.h>
using namespace std;

int main(){
    string s;
    //法一:哈希集合unordered_set
    unordered_set<char> st;
    int l=0,mlen=0;
    for(int r=0;r<s.size();r++){
        while(st.count(s[r])){  //如果r已经存在,l一直右移并移出字符,直到没有重复(r不存在)  
            st.erase(s[l]);
            l++;
        }
        st.insert(s[r]);        //将新字符s[r]加入窗口
        mlen=max(mlen,r-l+1);   //更新最大长度
    }
    //法二:数组记下标
    /*unordered_set每次需要erase一个个吐出字符,
    更快的做法是用一个数组lastp[128]记录每个字符上一次出现的下标, 
    一旦遇到重复,l可以直接跳到重复字符的下一个位置,一步到位*/
    vector<int> lastp(128,-1);  
    //创建一个大小为128的动态数组,并把里面所有元素初始值设为-1(ASCII字符一共128个)
    for(int r=0;r<s.size();r++){
        char c=s[r];
        if(lastp[c]>=l)  l=lastp[c]+1;
        //只有字符c(s[r])出现过且在当前窗口内才会大于l(不存在时为初始值-1,不在窗口内时小于l)
        //l跳转到上一次c出现的位置的下一个
        lastp[c]=r;  //更新该字符最后出现的位置
        mlen=max(mlen,r-l+1);
    }
    return 0;
}
