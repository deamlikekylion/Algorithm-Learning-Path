#include<bits/stdc++.h>
using namespace std;

int S,D,N;
string huffmancode;  //初始的哈夫曼树序列化字符串
vector< pair<string,string> > Stable;  //静态表格
vector< pair<string,string> > Dtable;  //动态表格

struct node{      //哈夫曼树节点结构
    char data;    //存储字符数据(仅叶子节点有效)
    node* left;   //左子节点指针
    node* right;  //右子节点指针
    node(char d) : data(d), left(nullptr), right(nullptr) {}  //构造函数,用于创建叶子节点(带有字符数据)
    node() : data('\0'), left(nullptr), right(nullptr) {}     //构造函数,用于创建内部节点(无字符数据)
};

//const string&引用s不用拷贝s,且函数内部不能修改s
node* rebuild(const string& s,int& index){  //根据序列化字符串递归重建哈夫曼树
    if(index>=s.length())  return nullptr;  //索引越界,返回空指针
    if(s[index]=='1'){  //如果当前字符是1,则是一个叶子节点
        index++;
        char ch=s[index++];
        return new node(ch);  //创建并返回叶子节点(new的用法可问AI)  
    }else if(s[index]=='0'){
        index++;
        node* nod=new node();         //创建内部节点
        nod->left=rebuild(s,index);   //递归构建左子树
        nod->right=rebuild(s,index);  //递归构建右子树
        return nod;                   //返回内部节点
    }
    return nullptr;
}

void destroytree(node* root){  //递归销毁哈夫曼树，释放内存
    if(!root)  return;
    destroytree(root->left);
    destroytree(root->right);
    delete root;
}

string hextobinary(const string& hexstr){  //将十六进制字符串转换为二进制字符串
    static const string hexmap[]={         //十六进制字符到4位二进制字符串的映射表
        "0000","0001","0010","0011","0100","0101","0110","0111",
        "1000","1001","1010","1011","1100","1101","1110","1111"
    };
    string res;            //存储转换结果
    for(char c : hexstr){  //根据字符是数字还是字母,从映射表中获取对应的二进制字符串
        res += isdigit(c) ? hexmap[c-'0'] : hexmap[c-'a'+10];
    }
    return res;
}

string huffmandecode(node* root,const string& binarystr){  //使用哈夫曼树对二进制字符串进行解码
    string res;      //存储解码结果
    node* cur=root;  //cur为当前遍历到的哈夫曼树节点,初始为根节点
    for(char bit : binarystr){ 
        cur = (bit=='0' ? cur->left : cur->right);  //根据二进制位移动到左子节点(0)或右子节点(1)
        if(!cur->left&&!cur->right){                //如果当前节点是叶子节点(无左右子节点)
            res+=cur->data;  //将叶子节点的字符加入结果
            cur=root;        //重置当前节点到根节点,准备下一个字符的解码
        }
    }
    return res;
}

string work(string s,node* huffmantree){  //处理输入字符,判断是否需要进行哈夫曼解码
    //s:待处理的原始字符串,huffmanTree:哈夫曼树的根节点指针
    if(s.empty())  return s;  //空字符串直接返回
    if(s[0]!='H')  return s;  //如果字符串不是以'H'开头,不需要解码直接返回
    else if(s.size()>=2&&s[0]=='H'&&s[1]=='H')  return s.substr(1);
           //如果字符串以"HH"开头,则为转义字符,去掉第一个'H'
    else{  //字符串以'H'开头且不是转义字符则需要进行哈夫曼解码
        if(s.size()<3)  return s;                  //长度不足无法解码，返回原始字符串
        char c1=s[s.size()-2],c2=s[s.size()-1];    //提取最后两个字符，作为补零数量（十进制数字）
        if(!isdigit(c1)||!isdigit(c2))  return s;  //最后两个字符不是数字，返回原始字符串
        int cnt=10*(c1-'0')+c2-'0';                //计算补零数量
        string hexdata=s.substr(1,s.size()-3);     //提取中间的十六进制数据部分(去掉开头的'H'和结尾的两位数字)
        string binarystr=hextobinary(hexdata);     //将十六进制数据转换为二进制字符串
        if(cnt>0&&binarystr.size()>=cnt){          //去掉二进制字符串末尾因十六进制转换而添加的补零
            binarystr=binarystr.substr(0,binarystr.size()-cnt);
        }
        return huffmandecode(huffmantree,binarystr);  // 对处理后的二进制字符串进行哈夫曼解码
    }
}

void insertDtable(const string &k,const string &v){  //向动态表格中插入新条目
    Dtable.insert(Dtable.begin(),{k,v});     //从开头插入
    if(Dtable.size()>D)  Dtable.pop_back();  //删除尾部
}

pair<string,string> getentry(int index){   //根据索引从静态表格或动态表格中获取条目
    if(index<=S)  return Stable[index-1];  //索引在静态表格范围内
    else{                                  //索引在动态字典范围内
        int idx=index-S-1;
        if(idx>=0&&idx<Dtable.size())  return Dtable[idx];
    }
    return {"", ""};                       //索引无效,返回空键值对
}

int main(){
    cin>>S>>D;
    for(int i=0;i<S;i++){  //读取S个静态表格条目,存入STable
        string k,v;  cin>>k>>v;
        Stable.emplace_back(k,v);
    }
    cin>>huffmancode;  int index=0;                //读取哈夫曼树的序列化字符串
    node* huffmantree=rebuild(huffmancode,index);  //重建哈夫曼树
    for(auto [k,v] : Stable){   //预处理静态表格中的所有条目,对键和值进行work处理(解码)
        k=work(k,huffmantree);
        v=work(v,huffmantree);
    }
    cin>>N;
    while(N--){
        int op;  cin>>op;
        if(op==1){  //操作1:表格引用指令,直接根据索引查询并输出
            int idx;  cin>>idx;
            auto entry=getentry(idx);
            cout<<entry.first<<": "<<entry.second<<endl;
        }else if(op==2){  //操作2:字面量并索引指令,处理后插入动态表格
            int idx;  cin>>idx;
            if(idx==0){   //idx=0:直接读取键和值,处理后插入动态表格
                string k,v;  cin>>k>>v;
                k=work(k,huffmantree);
                v=work(v,huffmantree);
                cout<<k<<": "<<v<<endl;
                insertDtable(k,v);
            }else{        //idx≠0:根据索引获取键,读取新值并处理,插入动态表格
                string v;  cin>>v;  v=work(v,huffmantree);
                string k=getentry(idx).first;
                cout<<k<<": "<<v<<endl;
                insertDtable(k,v);
            }
        }else if(op==3){  //操作3:字面量不索引指令,仅处理并输出,不插入动态表格
            int idx;  cin>>idx;
            if(idx==0){   //idx=0:直接读取键和值,处理后输出
                string k,v;  cin>>k>>v;
                k=work(k,huffmantree);
                v=work(v,huffmantree);
                cout<<k<<": "<<v<<endl;
            }else{        //idx≠0:根据索引获取键,读取新值并处理,输出
                string v;  cin>>v;  v=work(v,huffmantree);
                string k=getentry(idx).first;
                cout<<k<<": "<<v<<endl;
            }
        }
    }
    destroytree(huffmantree);  //销毁哈夫曼树,释放内存
    return 0;
}