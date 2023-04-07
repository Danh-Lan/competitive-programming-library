// LEARN DSU

#include<bits/stdc++.h>

using namespace std;

const long long N=5e5+5,mod=1e9+7;
long long a[N],b[N],c[N],pre[N],sz[N];

long long find(long long x){
    return (x==pre[x])?x:(pre[x]=find(pre[x]));   
}
void merge(long long x,long long y) {
    x=find(x);y=find(y);
    if(x==y) return;
    pre[x]=y;c[y]+=c[x];sz[y]+=sz[x];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 

    long long q;cin>>q;
    while(q--){
        long long n,ans=1;cin>>n;
        for(long long i=1;i<=n;i++){
            pre[i]=i;c[i]=0;sz[i]=1;
        }
        for(long long i=1;i<=n;i++){
            cin>>a[i];
        }
        for(long long i=1;i<=n;i++){
            cin>>b[i];
        }
        for(long long i=1;i<=n;i++){
            long long x;cin>>x;
            if(x>0) c[x]=1;
        }
        for(long long i=1;i<=n;i++){
            merge(a[i],b[i]);
        }
        for(long long i=1;i<=n;i++){
            if(i==find(i)){
                if(c[i]>0) continue;
                else{
                    if(sz[i]>1) ans*=2,ans%=mod;
                }
            }
        }
        cout<<ans<<"\n";
    }
    
    return 0;
}