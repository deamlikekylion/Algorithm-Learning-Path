#include<iostream>
#include<map>  //使用map必需的头文件

using namespace std;  //map也包含在std

int main()
{
	map <string,int> m;  //声明键值对map（此处键是string类型，值是int类型） 
	
	m["hello"]=4;        //此处相当于赋值   
	m["world"]=3;
	m["ilovewuhan"]=2;
	m["ha"]=1;
	
	cout << "hello : " << m["hello"] << endl;
	
	for(map <string,int> :: iterator p=m.begin();p!=m.end();p++){  //map会根据键的大小从小到大排序（此处键为字符串，按照字符串大小） 
		cout << p->first << " : " << p->second << endl;  //此处可看出map类似于结构体 
	}                                               //迭代器          
	
	cout << m.size() << endl;  //m的长度，即含的元素个数，4个 
	
	return 0;
}