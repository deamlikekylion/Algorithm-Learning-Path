#include<bits/stdc++.h>
using namespace std;

string mp[6]={
    "102022",
    "222022",
    "222200",
    "222222",
    "221221",
    "202212"
};
int row_0[6],row_1[6],col_0[6],col_1[6];  
//row_0[i],row_1[i]分别记录第i行0和1的数量,col_0[j],col_1[j]分别记录第j列0和1的数量
unordered_set <string> rows,cols;
//rows,cols分别记录填满后每行每列的字符串情况
bool found=false;
//用于找到解后返回
string ans; 

void dfs(int r,int c){
    if(found)  return;           //找到解后返回
    if(r==6){                    //所有行遍历完了,即全部填满了
        for(int j=0;j<6;j++){    //检查每列是否唯一
            string col;
            for(int i=0;i<6;i++)  col+=mp[i][j];
            if(cols.count(col))  return;  //出现重复立即返回
            cols.insert(col);    //记录新的不重复列情况
        }
        for(int i=0;i<6;i++){    //检查符合,将棋盘赋值ans
            for(int j=0;j<6;j++)  ans+=mp[i][j]; 
        }
        cout<<ans<<endl;         //输出解
        found=true;              //found赋值true使所有dfs递归结束
        return;
    }
    if(c==6){                    //列c=6即当前行遍历完了
        string row=mp[r];        //检查每行是否唯一,将当前行情况赋值给row
        if(rows.count(row))  return;  //出现重复立即返回
        rows.insert(row);        //记录新的不重复行情况
        dfs(r+1,0);              //dfs下一行
        rows.erase(row);         //回溯时恢复,删除之前记录的行情况
        return;
    }
    if(mp[r][c]!='2'){           //跳过填充过的位置
        dfs(r,c+1);
        return;
    }
    if(row_0[r]<3&&col_0[c]<3){  //要求0和1数量相等即每行每列0和1为3
        mp[r][c]='0';            //填0
        row_0[r]++;  col_0[c]++;
        if(!(r>=2&&mp[r-2][c]==mp[r][c]&&mp[r-1][c]==mp[r][c])
         &&!(c>=2&&mp[r][c-2]==mp[r][c]&&mp[r][c-1]==mp[r][c])){  
        //满足不连续重复三个相同的
            dfs(r,c+1);          //dfs该行下一个
        }
        mp[r][c]='2';            //回溯时恢复(注意回溯在if外面,因为修改是在if之前)
        row_0[r]--;  col_0[c]--;
    }
    if(row_1[r]<3&&col_1[c]<3){
        mp[r][c]='1';            //填1
        row_1[r]++;  col_1[c]++;
        if(!(r>=2&&mp[r-2][c]==mp[r][c]&&mp[r-1][c]==mp[r][c])
         &&!(c>=2&&mp[r][c-2]==mp[r][c]&&mp[r][c-1]==mp[r][c])){
            dfs(r,c+1);
        }
        mp[r][c]='2';
        row_1[r]--;  col_1[c]--;
    }
    return;                      //显式return不加也行,void函数会自动结束返回
}

int main(){
    for(int i=0;i<6;i++){        //记录初始时每行每列0和1的数量
        for(int j=0;j<6;j++){
            if(mp[i][j]=='0'){
                row_0[i]++;  col_0[j]++;
            }else if(mp[i][j]=='1'){
                row_1[i]++;  col_1[j]++;
            }
        }
    }
    dfs(0,0);
    return 0;
}