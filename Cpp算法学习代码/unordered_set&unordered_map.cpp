#include<iostream>
#include<unordered_set>  //注意头文件不是set和map 
#include<unordered_map>

using namespace std;

int main()
{
	unordered_set <int> s;          //处了不会自动排序之外，其他的和set以及map没有区别       
	unordered_map <string,int> m;   //unordered_set和unordered_map输出没有规律 
	                                //这个垃圾编译器好像用不了 
	s.insert(1);
	s.insert(7);
	s.insert(5);
	
	m["hafkaf"]=4;
	m["ahdabd"]=5;
	m["shab"]=8;
	
	for(auto p=s.begin();p!=s.end();p++){
		cout << *p << endl;
	}
	
	for(auto p=m.begin();p!=m.end();p++){
		cout << p->first << " " << p->second << endl;
	}
	
	return 0;
}