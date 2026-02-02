#include<bits/stdc++.h>
using namespace std;

long long n,a[500005],b[500005],t[500005],cnt[500005],ans;
map<long long,int>m;
long long lowbit(long long x)
{
    return x&(-x);
}
long long getsum(long long x)
{
    long long sum=0;
    while(x)
    {
        sum+=t[x];
        x-=lowbit(x);
    }
    return sum;
}
void update(long long x,long long y)
{
    while(x<=500000)
    {
        t[x]+=y;
        x+=lowbit(x);
    }
}
int main()
{
    scanf("%lld",&n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld",&a[i]);
        b[i]=a[i];
    }
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++)
    {
        m[b[i]]=i;
    }
    for(int i=1;i<=n;i++)
    {
        a[i]=m[a[i]];
    }
    for (int i = 1; i <= n; i++)
    {
        update(a[i],1);//数字可以是0，所以要加1
        cnt[i]+=(i-getsum(a[i])); //统计前面比它大的数字
    }
    memset(t,0,sizeof(t));
    for (int i = n; i >= 1; i--)
    {
        update(a[i],1);
        cnt[i]+=getsum(a[i]-1); //统计后面比它小的数字
    }
    for(int i=1;i<=n;i++)
    {
    	ans+=(cnt[i]+1)*cnt[i]/2;//算出这个数字的代价
    }
    printf("%lld",ans);
    return 0;
}
