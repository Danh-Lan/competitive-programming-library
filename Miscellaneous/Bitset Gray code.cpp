#include<bits/stdc++.h>
 
using namespace std;

void GreyCode(int n) {
    for (int i = 0; i < (1 << n); i++) {
        int val = (i ^ (i >> 1));
         
        // Using bitset
        bitset<32> r(val);
         
        // Converting to string
        string s = r.to_string();
        cout << s.substr(32 - n) << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
 
    int tt = 1; 
    //cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int n; cin >> n;
        GreyCode(n);
    }
 
    return 0;
}