#include<bits/stdc++.h>
using namespace std;

int main(){
    string s;  cin>>s;
    int n=s.size(),l=0,r=0,cnt=0;
    //[l,r]为好串则l<=i<=r,[i,r]共r-l+1都是好串
    //滑动窗口遍历r找最大的[l,r]累加r-l+1即可
    long long ans=0;       //要开long long
    for(int r=0;r<n;r++){  //遍历r
        if(r>0&&s[r]!=s[r-1]&&s[r]!=s[r-1]+1)  cnt++;
        //r>0时出现破坏点cnt就加一
        while(cnt>1){  //好串要求破坏点<=1,移动l减少破坏点满足即为最大[l,r]
            l++;
            if(s[l]!=s[l-1]&&s[l]!=s[l-1]+1)  cnt--;
            //如果l满足破坏点,现在l++已经去除了l-1,即[l,r]中破坏点减1,cnt--
        }
        ans+=(long long)r-l+1;
    }
    cout<<ans;
    return 0;
}