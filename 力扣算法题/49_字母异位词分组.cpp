#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<string> strs;
    unordered_map<string,vector<string>> mp;  
    //定义哈希表:key是排序后的特征串,value是同一组的所有原字符串
    //map<key,value>按key排序,unordered_map不排序更快,mp[key]=value
    for(const string& s : strs){  //遍历每个字符串进行归类
    //遍历套板:const auto& i : s,其中const意味着不能修改i,&直接引用元素不需拷贝,更快(const也可不加)
        string t=s;
        sort(t.begin(),t.end());  //排序得到该组唯一的key,vector排序用begin(),end()
        mp[t].push_back(s);       
        //如果key(t)不存在,会自动创建一个空的vector<string>然后把原字符串(s)push进去
        //mp[t]是vector,可用push_back()添加元素
        //还可以用insert()插入元素,下标[]只能用来修改元素不能添加元素
    }
    vector<vector<string>> ans;
    for(auto& p : mp){            //map相当于pair<key,value>  
        ans.push_back(p.second);  //p.second为mp.value,就是归好类的一组vector<string>,与ans的元素类型符合
    }
    return 0;
}
