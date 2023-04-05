#include <bits/stdc++.h>
 
using namespace std;

const long long MOD = 1000000007;

long long modPow(long long a, long long x, long long p) {
    long long res = 1;
    while(x > 0) {
        if( x % 2 != 0) {
            res = (res * a) % p;
        }
        a = (a * a) % p;
        x /= 2;
    }
    return res;
}

long long modInverse(long long a, long long p) {
    return modPow(a, p-2, p);
}
long long modBinomial(long long n, long long k, long long p) {
    long long numerator = 1;
    for (int i=0; i<k; i++) {
        numerator = (numerator * (n-i) ) % p;
    }

    long long denominator = 1;
    for (int i=1; i<=k; i++) {
        denominator = (denominator * i) % p;
    }

    return ( numerator* modInverse(denominator,p) ) % p;
}

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
        int n, k; cin>>n>>k;
        map<int,int> freq;
        for (int i = 0; i < n; ++i)
        {
            int num; cin>>num;
            freq[num]++;
        }

        vector<pair<int,int>> vec;
        for (auto it : freq) {
            vec.push_back({it.first, it.second});
        }
        sort(vec.rbegin(), vec.rend());

        long long ans = 1LL;
        int idx = 0;
        while (k > 0) {
            ans = ans%MOD * modBinomial(vec[idx].second, min(vec[idx].second, k), MOD) % MOD;
            k -= min(k, vec[idx].second);
            ++idx;
        }

        cout<<ans<<endl;
    }

    return 0;
}