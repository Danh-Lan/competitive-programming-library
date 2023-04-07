#include <bits/stdc++.h>

using namespace std;

struct TrieNode {
    TrieNode* left;
    TrieNode* right;
    TrieNode() {
        this->left = NULL;
        this->right = NULL;
    }
};
 
void insert(TrieNode* cur, long long num) {
    for (int i = 30; i >= 0; i--) {
        if ((num & (1 << i))) {
            if (cur->right == NULL)
                cur->right = new TrieNode();
            cur = cur->right;
        } else {
            if (cur->left == NULL)
                cur->left = new TrieNode();
            cur = cur->left;
        }
    }
}
int gt_mx_xor(TrieNode* cur, int num) {
    int res = 0;
    for (int i = 30; i >= 0; i--) {
        if ((num & (1 << i))) {
            // need to go zero
            if (cur->left) {
                cur = cur->left;
                res |= (1 << i);
            } else if (cur->right) {
                cur = cur->right;
            }
        } else {
            // need to go one
            if (cur->right) {
                cur = cur->right;
                res |= (1 << i);
            } else if (cur->left) {
                cur = cur->left;
            }
        }
    }
    return res;
}
int get_last_bit(int n) {
    if (n == 0) assert(false);
    for (int i = 30; i >= 0; i--) {
        if (n & (1 << i)) return i;
    }
    return -1;
}
vector<pair<int, vector<int>>> map_to_pair(map<int, vector<int>>& mp) {
    vector<pair<int, vector<int>>> res;
    for (auto it : mp) {
        res.push_back({it.first, it.second});
    }
    return res;
}
bool diff_in_first_bit(int a, int b) {
    return (a & 1) != (b & 1) && (a >> 1 == b >> 1);
}
 
tuple<int, int, int> get_max_xor(vector<int> a, vector<int> b, int k) {
    TrieNode* root = new TrieNode();
    for (int i = 0; i < a.size(); i++) {
        insert(root, a[i]);
    }
    int indx = -1;
    for (int j = 0; j < b.size(); j++) {
        if (gt_mx_xor(root, b[j]) >= k) {
            indx = j;
            break;
        }
    }
    for (int i = 0; i < a.size() && indx != -1; i++) {
        if ((a[i] ^ b[indx]) >= k) return {a[i], b[indx], (a[i] ^ b[indx])};
    }
    return {-1, -1, -1};
}
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    map<int, int> get_indx;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        get_indx[v[i]] = i + 1;
    }
    if (k == 0) {
        cout << n << "\n";
        for (int i = 1; i <= n; i++) cout << i << " ";
        cout << "\n";
        return;
    }
    int last_bit = get_last_bit(k);
    map<int, vector<int>> groups_tmp;
    for (int i = 0; i < n; i++) { 
        // ex ~(1LL<<...) has the form 11..111(1)0...0
        groups_tmp[v[i] & (~((1ll << last_bit) - 1))].push_back(v[i]);
    }
 
    vector<pair<int, vector<int>>> groups = map_to_pair(groups_tmp);
    n = groups.size();
    vector<int> res;
    for (int i = 0; i < n; i++) {
        // try to take two elements from these groups
        if (i + 1 < n && diff_in_first_bit(groups[i].first >> last_bit, groups[i + 1].first >> last_bit)) {
            int g1 = groups[i].first >> last_bit, g2 = groups[i+1].first >> last_bit;
            int f, s, val;
            tie(f, s, val) = get_max_xor(groups[i].second, groups[i + 1].second, k);
            if (val >= k) {
                res.push_back(f);
                res.push_back(s);
            } else {
                res.push_back(groups[i].second.back());
            }
            i++;
        } else {
            // take any number from that group
            res.push_back(groups[i].second.back());
        }
    }
    if (res.size() < 2)
        cout << "-1\n";
    else {
        cout << res.size() << "\n";
        for (int i = 0; i < res.size(); i++) {
            cout << get_indx[res[i]] << " ";
        }
        cout << "\n";
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
    //cin>>tt;
    for (int test = 1; test <= tt; test++) {
        solve();
    }

    return 0;
}