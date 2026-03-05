#include<bits/stdc++.h>
using namespace std;
typedef long long ll;  //typedef要加;(注意与#define的区别,ll与long long的位置也相反)

int n;
vector<ll> t,numsa,numsb;

ll gcd(ll a,ll b){
    if(b==0)  return a;
    else  return gcd(b,a%b);
}

map<ll,ll> factorize(ll x){
    map<ll,ll> res;
    for(int i=2;i*i<x;i++){
        while(x%i==0){
            res[i]++;
            x/=i;
        }
    }
    if(x>1)  res[x]++;
    return res;
}

ll getmaxbase(vector<ll> &nums){
    if(nums.size()==1)  return nums[0];
    map<ll,ll> factors=factorize(nums[0]);
    ll maxbase=1;
    for(auto [p,e] : factors){
        bool valid=true;
        vector<ll> exps;  
        exps.push_back(e);
        for(int i=1;i<nums.size();i++){
            ll num=nums[i],cnt=0;
            while(num%p==0){
                cnt++;
                num/=p;
            }
            if(num!=1){
                valid=false;
                break;
            }
            exps.push_back(cnt);
        }
        if(valid){
            ll g=exps[0];
            for(ll e : exps)  g=gcd(g,e);
            maxbase=max(maxbase,(ll)pow(p,g));
        }
    }
    return maxbase;
}

int main(){
    cin>>n;  for(int i=0;i<n;i++)  cin>>t[i];  //vector也可以和数组一样读取元素
    sort(t.begin(),t.end());
    t.erase(unique(t.begin(),t.end()),t.end());
    n=t.size();
    for(int i=0;i<n-1;i++){
        ll x=t[i+1],y=t[i];
        ll g=gcd(x,y);
        ll a=x/g,b=y/g;
        numsa.push_back(a);
        numsb.push_back(b);
    }
    ll ra=getmaxbase(numsa);
    ll rb=getmaxbase(numsb);
    cout<<ra<<'/'<<rb<<endl;
    return 0;
}