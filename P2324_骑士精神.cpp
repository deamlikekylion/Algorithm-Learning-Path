#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
int t,flag,mp[7][7];  //mp存储棋盘
int dx[8]={1,1,-1,-1,2,-2,2,-2};
int dy[8]={2,-2,2,-2,1,1,-1,-1};
const int goal[7][7]={
    {0,0,0,0,0,0},    //第0行无意义,下标从1开始
    {0,1,1,1,1,1},
    {0,0,1,1,1,1},
    {0,0,0,2,1,1},
    {0,0,0,0,0,1},
    {0,0,0,0,0,0}
};

int evaluate(){       //评估函数:计算当前棋盘与目标棋盘的差异度,用于剪枝
    int cnt=0;
    for(int i=1;i<=5;i++){
        for(int j=1;j<=5;j++){
            if(mp[i][j]!=goal[i][j])  cnt++;  //统计不同位置的数量
        }
    }
    return cnt;
}

//A*算法:dfs+启发式剪枝(dep:当前移动步数;x,y:当前空位的坐标;maxdep:允许的最大步数)
void A_star(int dep,int x,int y,int maxdep){  
    if(dep==maxdep){                //达到最大步数限制,检查是否达成目标
        if(!evaluate())  flag=1;    //差异度为0,找到目标状态
        return;
    }
    for(int i=0;i<8;i++){
        int tx=x+dx[i],ty=y+dy[i];
        if(tx<1||tx>5||ty<1||ty>5)  continue;
        swap(mp[x][y],mp[tx][ty]);  //交换空位与骑士的位置(模拟移动)
        int eva=evaluate();         //计算移动后的差异度
        if(eva+dep<=maxdep)  A_star(dep+1,tx,ty,maxdep);
        //启发式剪枝:当前步数+差异度<=最大步数,才能继续递归搜索
        swap(mp[x][y],mp[tx][ty]);  //回溯,恢复棋盘状态
    }
}

int main(){
    cin>>t;  int sx,sy;  char c;
    while(t--){
        flag=0;                                 //初始化标记
        for(int i=1;i<=5;i++){
            for(int j=1;j<=5;j++){
                cin>>c;
                if(c=='*'){
                    mp[i][j]=2;  sx=i;  sy=j;
                }else  mp[i][j]=c-'0';
            }
        }
        if(!evaluate()){                        //检查初始状态是否就是目标状态
            cout<<'0'<<endl;  continue;
        }
        for(int maxdep=1;maxdep<=15;maxdep++){  //枚举最大步数(1到15)
            A_star(0,sx,sy,maxdep);             //移动空位找目标状态
            if(flag){                           //找到目标状态
                cout<<maxdep<<endl;
                goto end;                       //跳转到标签,处理下一组测试用例
            }
        }
        cout<<"-1"<<endl;                       //15步内未找到目标
        end:;                                   //标签,用于跳出循环
    }
    return 0;
}