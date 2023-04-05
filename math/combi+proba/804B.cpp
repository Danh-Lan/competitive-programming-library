#include <bits/stdc++.h>
 
using namespace std;

const long long MOD = 1e9+7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 

    int test = 1;
    //cin>>test;
    for (int tt = 0; tt < test; ++tt)
    {
        string s; cin>>s;
        long long leng = 0LL;
        long long ans = 0LL;
        for (int i = s.length()-1; i >= 0 ; --i)
        {
            if (s[i] == 'b') {
                leng++;
            } else {
                if (leng != 0) {
                    ans = (ans+leng) % MOD;
                    leng = (2LL*leng) % MOD;
                }
            }
        }

        cout<<ans<<endl;
    }

    return 0;
}