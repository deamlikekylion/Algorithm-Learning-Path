#include<bits/stdc++.h>
using namespace std;

int a,b,c;  
string s,sa,sb,sc;
set<string> ans;
bool f[3];

bool check(int a,int b,int c){
    int ta;
    if(a>=60)  ta=1900+a;
    else  ta=2000+a;
    if(b>12||b==0||c==0)  return false;
    if(b==1||b==3||b==5||b==7||b==8||b==10||b==12){
        if(c>31)  return false;
    }else if(b!=2){
        if(c>30)  return false;
    }else{
        if((ta%100!=0&&ta%4==0)||(ta%400==0)){
            if(c>29)  return false;
        }else if(c>28)  return false;
    }
    return true;
}

int main(){
    cin>>s;  
    sa=s.substr(0,2);  sb=s.substr(3,2);  sc=s.substr(6,2);
    a=(s[0]-'0')*10+s[1]-'0';
    b=(s[3]-'0')*10+s[4]-'0';
    c=(s[6]-'0')*10+s[7]-'0';
    f[0]=check(a,b,c);  
    if(f[0]){
        string t;
        if(a>=60)  t+="19";
        else  t+="20";
        t+=sa+"-"+sb+"-"+sc;
        ans.insert(t);
    }
    f[1]=check(c,a,b);
    if(f[1]){
        string t;
        if(c>=60)  t+="19";
        else  t+="20";
        t+=sc+"-"+sa+"-"+sb;
        ans.insert(t);
    }  
    f[2]=check(c,b,a);
    if(f[2]){
        string t;
        if(c>=60)  t+="19";
        else  t+="20";
        t+=sc+"-"+sb+"-"+sa;
        ans.insert(t);
    }
    for(string i : ans)  cout<<i<<endl;
    return 0;
}