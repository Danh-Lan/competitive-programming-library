#include <bits/stdc++.h>

using namespace std;

// source : 
// https://www.techiedelight.com/next-greater-element/
vector<int> findNGE(vector<int> const &input) {
    int n = input.size();
    vector<int> result(n, -1);
 
    stack<int> s;
 
    for (int i = 0; i < n; i++) {
        while (!s.empty() && input[s.top()] < input[i]) {
            result[s.top()] = input[i];
            s.pop();
        }

        s.push(i);
    }
 
    return result;
}

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
        int n, q; cin>>n>>q;
        vector<int> a(n);
        int pos[n];
        for (int i = 0; i < n; ++i) {
            cin>>a[i];
            --a[i];
            pos[a[i]] = i;
        }

        int val = 0;
        for (int i = 1; i < n; ++i) {
            if (a[i] > a[0]) break;
            val++;
        }

        vector<bool> big(n, false);
        int mx = a[0];
        for (int i = 1; i < n; ++i) {
            if (a[i] < mx) big[i] = false;
            else big[i] = true;

            mx = max(mx, a[i]);
        }

        vector<int> next = findNGE(a);

        for (int i = 0; i < q; ++i) {
            int par, k; cin>>par>>k;
            --par;
            if (k < par) {
                cout<<0<<endl;
                continue;
            }

            if (a[par] == n-1) {
                if (par > 1) cout<<max(0, k-(par-1))<<endl;
                else cout<<k<<endl;
            } else if (par > pos[n-1]) cout<<0<<endl;
            else {
                if (par == 0) {
                    cout<<min(k, val)<<endl;
                } else {
                    if (big[par] == false) cout<<0<<endl;
                    else {
                        if (pos[next[par]] != -1) {
                            int nxt_pos = pos[next[par]];
                            cout<<1 + min(k-par, nxt_pos-par-1)<<endl;
                        }
                    }
                }
            }
        }

    }

    return 0;
}