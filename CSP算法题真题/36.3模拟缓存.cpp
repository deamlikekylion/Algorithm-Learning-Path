#include<bits/stdc++.h>
using namespace std;

using pii=pair<int,int>;  
//定义pair<int,int>类型别名，用于存储（时间戳，内存块号）

int main(){
    int n,N,q;  cin>>n>>N>>q;  
	//n：每组的缓存行数；N：组数；q：操作次数
    vector<set<pii>> g(N);  
	//模拟N个组，每组是一个set，存储（时间戳q，内存块号a），
	//set自动按时间戳升序排列
    vector<pii> ans;  
	//存储输出结果，每个元素是（操作类型，内存块号）
    map<int,int> tim,mod;  
	//tim：记录内存块最后一次访问的时间戳q；mod：标记内存块是否为“修改过”

    while(q--){  //处理q次操作
        int op,a;  cin>>op>>a;  
		//op：操作类型（0或1，1表示修改内存块）；a：要访问的内存块号
        int id=(a/n)%N;  
		//计算内存块a所属的组号：组号=(内存块号/每组缓存行数)%组数

        //在组id中查找是否存在内存块a
		//（通过lower_bound找时间戳对应的位置，判断是否有该内存块）
        auto it=g[id].lower_bound({tim[a],0});
        //lower_bound找第一个>=的，tim[a]为时间戳，每次赋值q（第57行）
		//g[id].second存内存块号，即a，一定>=0 
        if(it!=g[id].end()&&it->second==a){  
		    //如果找到且该位置的内存块号是a，说明缓存命中
            g[id].erase(it);  
			//先删除旧的记录(为了更新时间戳)
            tim[a]=q;  //更新内存块a的最后访问时间戳为当前操作次数q
            g[id].insert({tim[a],a});  
			//插入新的记录，时间戳为当前操作次数q（越新的时间戳越小）
            if(op==1)  mod[a]=1;  
			//如果是修改操作，标记该内存块为脏块（需要写回）
        }else{  //缓存未命中，需要替换
            if(g[id].size()<n){  //组内还有空闲缓存行
                ans.push_back({0,a});  //记录“加载”操作（类型0，加载内存块a）
                tim[a]=q;  //更新内存块a的最后访问时间戳为当前操作次数q
                g[id].insert({tim[a],a});  //将内存块a加入该组，时间戳为tim[a]
                if(op==1)  mod[a]=1;  //如果是修改操作，标记为脏块
            }else{  //组内没有空闲缓存行，需要替换
                auto tmp=g[id].rbegin()->second;  
				//取组内时间戳最大的（最久未使用的）内存块号
				//s.rbegin()指向最后一个，set升序排序 
                if(mod[tmp]){  //如果该内存块是脏块（被修改过）
                    ans.push_back({1,tmp});  //记录“写回”操作
                    mod[tmp]=0;  //清除脏块标记
                }
                //删除组内时间戳对应tmp的记录（因为要被替换）
                g[id].erase(g[id].lower_bound({tim[tmp],tmp}));
                ans.push_back({0,a});  //加载新的内存块a
                tim[a]=q;  //更新内存块a的最后访问时间戳为当前操作次数q
                g[id].insert({tim[a],a});  //将a加入组，时间戳为tim[a]
                if(op==1)  mod[a]=1;  //如果是修改操作，标记a为脏块
            }
        }
    }

    //遍历输出所有操作结果
    for(auto it : ans){
        cout<<it.first<<" "<<it.second<<endl;
    }
    return 0; 
}