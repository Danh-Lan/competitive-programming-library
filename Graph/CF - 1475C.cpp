// count total number of pair with first and second element not equal with each other

#include <bits/stdc++.h>
 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 

    int t = 1;
    cin>>t;
    for (int tt = 0; tt < t; ++tt)
    {
        int a, b, k; cin>>a>>b>>k;
        int boy[k], girl[k];
        map<int,int> mapBoy, mapGirl;
        for (int i = 0; i < k; ++i)
        {
            cin>>boy[i];
            mapBoy[boy[i]]++;
        }
        for (int i = 0; i < k; ++i)
        {
            cin>>girl[i];
            mapGirl[girl[i]]++;
        }
        if (a <= 1 || b <= 1 || k <= 1) cout<<0<<endl;
        else {
            long long ans = 0LL;
            for (int i = 0; i < k; ++i)
            {
                ans += 1LL*( k-1 - (mapBoy[boy[i]]-1) - (mapGirl[girl[i]]-1) ); 
            }
            cout<<ans/2LL<<endl;
        }
    }

    return 0;
}