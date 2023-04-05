#include <bits/stdc++.h>

using namespace std;

vector<long long> t, lazy;
int n, k;
 
void push(int v, int vl, int vr) {
    t[v] += lazy[v];
    if (vl != vr) {
        lazy[2*v+1] += lazy[v];
        lazy[2*v+2] += lazy[v];
    }
    lazy[v] = 0;
}
 
void update(const int l, const int r, const long long val, int vl = 0, int vr = k - 1, int v = 0) {
    push(v, vl, vr);
    if(vl > r || l > vr) return;
    if(l <= vl && vr <= r) {
        lazy[v] += val;
        push(v, vl, vr);
        return;
    }
    int vm = (vl + vr) / 2;
    update(l, r, val, vl, vm, 2*v+1);
    update(l, r, val, vm+1, vr, 2*v+2);
    t[v] = min(t[2*v+1], t[2*v+2]);
}
 
long long get(const int l, const int r, int vl = 0, int vr = k - 1, int v = 0) {
    push(v, vl, vr);
    if(vl > r || l > vr) return LONG_LONG_MAX;
    if(l <= vl && vr <= r) return t[v];
    int vm = (vl + vr) / 2;
    auto L = get(l, r, vl, vm, 2*v+1);
    auto R = get(l, r, vm+1, vr, 2*v+2);
    return min(L, R);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int tt = 1; 
    //cin>>tt;
    for (int test = 1; test <= tt; test++) {
        cin>>n;
        k = 1;
        while (k < n) k <<= 1;
        t.resize(2*k - 1);
        lazy.resize(2*k - 1);
        for (int i = 0; i < n; ++i) {
            int x; cin>>x;
            update(i, i, x);
        }

        int q; cin>>q;
        while (q--) {
            int l, r; cin>>l>>r;
            string str; getline(cin, str);
            if (!str.empty()) {
                int x = stoi(str);
                if (l > r) {
                    update(l, n-1, x);
                    update(0, r, x);
                } else update(l, r, x);
            } else {
                if (l > r) cout<<min(get(0, r), get(l, n-1))<<endl;
                else cout<<get(l, r)<<endl;
            }
        }
    }

    return 0;
}