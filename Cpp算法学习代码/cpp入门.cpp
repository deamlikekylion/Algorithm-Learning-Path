#include<iostream>
#include<cstring>  //如果想用C中函数，只需将C中头文件去.h后前加c即可 
#include<cmath>

using namespace std;  //std中含有cin,cut,endl函数，如果不提前声明，后面使用cin应该: std::cin 

struct stu{         //不用用typedef重命名 
	string name;
	int age;
};

int main()
{
	int n;
	cin >> n;
	cout << "hello world!" << '\n' << ++n << endl;  //endl等于\n,即换行 
	
	for(int i;i<n;i++){  //可直接在for循环中定义变量 
		cout << n << " ";  //" "相当于空格 
	} 
	cout << endl;
	
	bool flag1=true,flag2=false,flag3=-1,flag4=0;
	cout << flag1 << " " << flag2 << " " << flag3 << " " << flag4 << endl; //bool变量，输出1,0,1,0; 
	
	string s,s4;
	cin >> s;         //cin输入字符串不能带空格 
	getchar();        //除去换行 
	getline(cin,s4);  //getline(cin,s)输入字符串直接输入一行 
	cout << s << endl << s4 <<endl;
	string s1="hello",s2=" world!",s3=s1+s2;  //字符串拼接直接相加 
	cout << s3 << endl;
	cout << s3.length() <<endl;  //s.length()即为s3的长度
	string s5=s3.substr(2,3);  //s.substr(a,b)为从s第a个字符后面复制b个字符（不包括第a个） 
	string s6=s3.substr(4);    //s.substr(a)为从s第a个字符后面复制剩下所以字符（不包括第a个）
	cout << s5 << endl;
	cout << s6 << endl; 
	
	stu a[10]; //可直接声明结构不需在前面加struct 
	
	//&在cpp中增加了引用功能，见手机截图 
	
	return 0;
}