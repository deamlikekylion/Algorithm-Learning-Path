#include<iostream>
#include<vector>  //使用vector必需的头文件 

using namespace std;  //vector也包含在std 

int main()
{
	vector <int> v;  //声明一个数组 
	v.resize(10);    //分配数组空间为10 
	vector <int> a(10);  //声明时直接分配10空间 
	for(int i=0;i<10;i++){  
		v[i]=i;      //数组下标表示和C语言一样 
	}
	for(int i=0;i<10;i++){
		cout << v[i] << " "; 
	}  
	cout << endl << v.size() << endl;  //v.size()表示v的长度，后面其他的也类似这样 
	 
	vector <int> b(10,2);   //将数组中的数全部初始化成2（一般是直接默认全部初始化为0） 
	for(int i=0;i<10;i++){
		cout << b[i] << " ";
	} 
	cout << endl;
	
	vector <int> c(10);     //迭代器 
	v.push_back(11);        //在数组后面添加元素 
	for(vector <int> :: iterator p=c.begin();p!=c.end();p++){  //p相当于指针，v.begin()是数组第一个元素位置，v.end()是最后一个元素后面一位 
		cout << *p << " ";                                    //正常可直接写auto p=c.begin() 
	} 
	 
	return 0;
}