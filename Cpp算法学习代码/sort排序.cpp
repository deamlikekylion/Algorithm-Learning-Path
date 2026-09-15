#include<bits/stdc++.h>
using namespace std;
bool my_less(int i,int j)  {return (i<j);}
bool my_greater(int i,int j)  {return (i>j);}
int main(){
	int a[]={3,6,5,8,7,2,4,9};
	sort(a,a+4);                 //升序排序前四个数 
	sort(a,a+7);                 //升序排序整个数组 
	sort(a,a+7,less<int>());     //
	sort(a,a+7,my_less);         //
	sort(a,a+7,greater<int>());  //降序排序整个数组
	sort(a,a+7,my_greater);      //
	return 0;
}