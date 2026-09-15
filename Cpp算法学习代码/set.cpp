#include<iostream>
#include<set>  //使用set必需的头文件 

using namespace std;  //set也包含在std

int main()
{
	set <int> s;  //声明集合set(类似vector) 
	s.insert(2);  //在集合中插入元素（不开重复） 
	s.insert(3);
	s.insert(1);
	
	for(set <int> :: iterator p=s.begin();p!=s.end();p++){   //迭代器遍历，p,s.end()等是指针 
		cout << *p << " ";                  //输入set中的元素会自动从小到大排序 
	}
	cout << endl;
	
	cout << ( s.find(2) != s.end() ) << endl;  //如果能找到则输出1，否则输出0 
	cout << ( s.find(4) != s.end() ) << endl;
	
	s.erase(1);  //删除集合中的元素 
	cout << ( s.find(1) != s.end() ) << endl;  //1被删除后无法找到，输出0 
	
	return 0;
}