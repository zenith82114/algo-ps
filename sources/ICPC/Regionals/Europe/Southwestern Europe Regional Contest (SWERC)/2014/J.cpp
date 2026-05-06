/*
 * ICPC, Regionals, Europe, Southwestern Europe Regional Contest,
 * SWERC 2014 J. The Big Painting
 * BOJ 10538 - Aho-Corasick, KMP
 * Date: 2025.4.1
 */

#include<bits/stdc++.h>
using namespace std;

int a[2000][2000] {};
int b[2000] {};
int ff[2000] {};

class Trie {
    struct Node {
        Node *chld[2];
        Node *prnt, *fail;
        int chr, pid;
        Node(int c): chld(), prnt(0), fail(0), chr(c), pid(-1) {}
    };
    Node *root;
    int count;
public:
    void init() {
        root = new Node(-1);
        count = 0;
    }
    int insert(const string& pattern) {
        Node *cur = root;
        for (const char& p : pattern) {
            int chr = p == 'o'? 0 : 1;
            Node *&nxt = cur->chld[chr];
            if (!nxt) {
                nxt = new Node(chr);
                nxt->prnt = cur;
            }
            cur = nxt;
        }
        if (cur->pid == -1) cur->pid = ++count;
        return cur->pid;
    }
    void build() {
        queue<Node *> q;
        for (auto tmp : root->chld) if (tmp) {
            tmp->fail = root;
            q.emplace(tmp);
        }
        while (!q.empty()) {
            Node *cur = q.front(); q.pop();
            if (cur->chld[0]) q.emplace(cur->chld[0]);
            if (cur->chld[1]) q.emplace(cur->chld[1]);

            Node *tmp = cur->prnt;
            while (tmp != root && !cur->fail) {
                tmp = tmp->fail;
                cur->fail = tmp->chld[cur->chr];
            }
            if (!cur->fail) cur->fail = root;
        }
    }
    vector<pair<int, int> > search(const string& text) {
        vector<pair<int, int> > matches;
        Node *cur = root;

        for (int i = 0; i < (int)text.size(); ++i) {
            int chr = text[i] == 'o'? 0 : 1;
            while (cur != root && !cur->chld[chr]) cur = cur->fail;
            if (cur->chld[chr]) cur = cur->chld[chr];
            if (cur->pid != -1) matches.emplace_back(i, cur->pid);
        }
        return matches;
    }
} trie;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int hp, wp, hm, wm; cin >> hp >> wp >> hm >> wm;

    trie.init();
    for (int i = 0; i < hp; ++i) {
        string p; cin >> p;
        b[i] = trie.insert(p);
    }
    trie.build();

    for (int i = 0; i < hm; ++i) {
        string t; cin >> t;
        auto matches = trie.search(t);
        for (const auto& [j, pid] : matches) a[i][j] = pid;
    }

    for (int i = 1, j = 0; i < hp; ++i) {
        while (j && b[i] != b[j]) j = ff[j - 1];
        if (b[i] == b[j]) ++j;
        ff[i] = j;
    }

    int ans = 0;
    for (int col = wp - 1; col < wm; ++col) {
        for (int i = 0, j = 0; i < hm; ++i) {
            while (j && a[i][col] != b[j]) j = ff[j - 1];
            if (a[i][col] == b[j]) ++j;
            if (j == hp) ++ans, j = ff[j - 1];
        }
    }

    cout << ans;
    return 0;
}
