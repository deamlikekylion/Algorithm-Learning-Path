#include<bits/stdc++.h>
using namespace std;

string s;       //存储输入的正则表达式
int idx;        //全局索引,记录当前遍历到的字符位置

int dfs(){      //递归函数
    int ans=0;  //ans为每个括号内的最大长度,存储一个括号内遍历过的分支中的最大长度
    int tem=0;  //tem遇到新的分支时清零记录新分支的长度,即作为临时变量记录分支长度
    while(idx<(int)s.size()){        //遍历字符,直到字符串结束或遇到右括号)
        char c=s[idx];  idx++;  //获取当前字符并后移索引
        if(c=='x'){             //遇到x当前分支长度+1
            tem++;
        }else if(c=='('){       //遇到(递归计算括号内的长度,结果加到当前分支
            tem+=dfs();
        }else if(c==')'){       //遇到)结束当前括号内的计算,返回分支最大值
            ans=max(ans,tem);
            return ans;
        }else if(c=='|'){       //遇到|
            ans=max(ans,tem);   //用ans存储当前括号内遍历过的分支的最大长度
            tem=0;              //清零tem用来继续记录新分支的长度
        }
    }
    ans=max(ans,tem);           //遍历到字符串末尾,返回所有分支的最大值
    return ans;
}

int main(){
    cin>>s;
    cout<<dfs();
    return 0;
}