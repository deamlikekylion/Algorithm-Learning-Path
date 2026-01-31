#include<bits/stdc++.h>
using namespace std;
int n,a[70],nxt[70],vis[70]={0},sum,cnt,len,m,flag; 

//now:现在正在拼第now个长棍(原始棍),last:上一个用来拼目前长棍的短棍,rest:目前长棍还需拼的长度
void dfs(int now,int last,int rest){  
	int i;
	if(!rest){  //目前长棍拼完了
		if(now==m){  //达到了原始棍数可满足并返回
			flag=1;  return;
		}
		for(i=1;i<=cnt;i++){  //找还没用的短棍中的最长棍
			if(!vis[i])  break;  
		}
		vis[i]=1;
		dfs(now+1,i,len-a[i]);  //递归拼下一个长棍
		vis[i]=0;
		if(flag)  return;  //可满足层层返回退出
	}
	int l=last+1,r=cnt,mid;
	while(l<r){  //二分找第一个小于等于rest的棍长a[l]
		mid=(l+r)>>1;
		if(a[mid]<=rest)  r=mid;
		else  l=mid+1;
	}
	for(i=l;i<=cnt;i++){
		if(!vis[i]){
			vis[i]=1;
			dfs(now,i,rest-a[i]);  //拼接短棍i
			vis[i]=0;
			if(flag)  return;  //可满足则返回退出
			if(rest==a[i]||rest==len)  return;
			i=nxt[i];  //nxt[i]为长度等于a[i]的最大编号,nex[i]+1为下一个较短长度的编号
			if(i==cnt)  return;  //遍历完都不满足返回
		}
	}
}

int main(){
	cin>>n;
	int num;  cnt=0;
	for(int i=1;i<=n;i++){
		cin>>num;
		if(num>50)  continue;
		a[++cnt]=num;
		sum+=num;  
	}
	sort(a+1,a+1+cnt,greater<int>());  //降序排序,先合并长棍
	nxt[cnt]=cnt;
	for(int i=cnt-1;i>0;i--){  //长度相同的nxt等于编号最大的棍编号
		if(a[i]==a[i+1])  nxt[i]=nxt[i+1];  //长度相同的nxt值相同
		else  nxt[i]=i;
	}
	for(len=a[1];len<=sum/2;len++){  //枚举可能的原始长度
		if(sum%len!=0)  continue;    //原始棍数为整数
		m=sum/len;  flag=0;  vis[1]=1;  //m为原始棍数,falg该长度标记是否可满足
		dfs(1,1,len-a[1]);   vis[1]=0;  //vis递归后重置为0
		if(flag){
			cout<<len<<endl;
			return 0;
		}
	}
	cout<<sum<<endl;  //枚举到超过总长度一半都不满足则原始棍只可能为1根 
	return 0;
}
