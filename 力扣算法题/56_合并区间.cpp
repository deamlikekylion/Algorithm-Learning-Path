#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<vector<int>> intervals;
    sort(intervals.begin(),intervals.end());          //按照区间的左端点从小到大排序,
                                                      //C++的sort对vector,pair,string的排序规则是默认按照第一个元素的字典序
    vector<vector<int>> ans;
    for(const auto& cur : intervals){
        if(ans.empty()||cur[0]>ans.back()[1]){        //如果ans为空,或者当前区间的左端点>上一个区间的右端点.说明不重叠
            ans.push_back(cur);                       //不重叠加入ans
        }else{                                       
            ans.back()[1]=max(ans.back()[1],cur[1]);  //重叠时合并,更新上一区间的右端点(.back()返回容器最后一个元素,且可以进行修改)
        }
    }
    return 0;
}