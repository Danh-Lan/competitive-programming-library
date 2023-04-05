#include <bits/stdc++.h>
 
using namespace std;

struct Fenwick {
    int n; vector<int> t;
    Fenwick() {}
    Fenwick(int _n) {
        n = _n; t.assign(n + 1, 0);
    }
    int query(int i) {
        int ans = 0;
        for (; i >= 1; i -= (i & -i)) ans += t[i];
        return ans;
    }
    void upd(int i, int val) {
        if (i <= 0) return;
        for (; i <= n; i += (i & -i)) t[i] += val;
    }
    void upd(int l, int r, int val) {
        upd(l, val);
        upd(r + 1, -val);
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 
 
    int test = 1;
    cin>>test;
    for (int tt = 0; tt < test; ++tt)
    {
        string s; cin>>s;
        int q; cin>>q;

        Fenwick fEven(s.length()/2+1), fOdd(s.length()/2+1);
        for (int i = 0; i < s.length(); i += 2)
        {
            if (s[i] == '[' || s[i] == ']') fEven.upd(i/2+1, 1);
        }
        for (int i = 1; i < s.length(); i += 2)
        {
            if (s[i] == '[' || s[i] == ']') fOdd.upd(i/2+1, 1);
        }

        for (int i = 0; i < q; ++i)
        {
            int l, r; cin>>l>>r;
            int diff;
            if (l % 2 == 1) diff = abs(fEven.query((l+1)/2, r/2)-fOdd.query((l+1)/2, r/2));
            else diff = abs(fEven.query(l/2 + 1, r/2 + 1)-fOdd.query(l/2, r/2));
            cout<<diff<<endl;
        }
    }

    return 0;
}
