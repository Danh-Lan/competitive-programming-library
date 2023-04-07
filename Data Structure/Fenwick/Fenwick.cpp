#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct Fenwick{
    int N;
    vector<T> Fen;
    Fenwick(int N): N(N), Fen(N+1, 0) {
    }
    void add (int i, T val) {
        i++;
        while (i <= N) {
            Fen[i] += val;
            i += i & -i;
        }
    }

    T sum (int i) {
        T ans = 0;
        while (i > 0) {
            ans += Fen[i];
            i -= i & -i;
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 
    
    int tt = 1; 
    cin>>tt;
    for (int test = 1; test <= tt; test++) {
        int n; cin>>n;
        string s; cin>>s;
        vector<int> pref(n+1);
        pref[0] = n;
        for (int i = 0; i < n; ++i)
        {
            if (s[i] == '-') pref[i+1] = pref[i] + 1;
            else pref[i+1] = pref[i] - 1;
        }
        vector<Fenwick<int>> BIT(3, Fenwick<int>(n*2 + 1));
        long long ans = 0;
        for (int i = 0; i <= n; ++i)
        {
            ans += BIT[pref[i] % 3].sum(pref[i] + 1);
            BIT[pref[i] % 3].add(pref[i], 1);
        }

        cout<<ans<<"\n";
    }

    return 0;
}

// 1660F2