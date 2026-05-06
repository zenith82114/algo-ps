/*
 * Croatian Open Competition in Informatics, COCI 2011/2012, Contest #5 F. POPLOČAVANJE
 * BOJ 2809
 * JUNGOL 3723
 *
 * Aho-Corasick alg.
 * Date: 2022.2.9
 */

#include<bits/stdc++.h>
using namespace std;

class Trie {
    struct Node {
        char chr;
        int pos;
        bool is_entry = false;
        vector<int> chld;
        int prnt = -1, sufx = 0, dict = -1;
        Node(char c, int i) : chr(c), pos(i) {}
    };
    int V;
    vector<Node> nodes;
public:
    void init() {
        V = 1;
        nodes.emplace_back(0, 0);
        nodes[0].sufx = -1;
    }
    void add_entry(string& pattern) {
        int curr = 0;
        int P = pattern.length();
        for (int pos = 0; pos < P; ++pos) {
            int next = V;
            for (const int& i : nodes[curr].chld) {
                if (nodes[i].chr == pattern[pos]) {
                    next = i;
                    break;
                }
            }
            if (next == V) {
                nodes.emplace_back(pattern[pos], pos);
                nodes[curr].chld.emplace_back(V++);
                nodes.back().prnt = curr;
            }
            curr = next;
        }
        nodes[curr].is_entry = true;
    }
    void make_edges() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int curr = q.front(); q.pop();
            for (int& i : nodes[curr].chld)
                q.push(i);
            int temp = nodes[curr].prnt;
            while (temp > 0 && !nodes[curr].sufx) {
                temp = nodes[temp].sufx;
                for (int& i : nodes[temp].chld) {
                    if (nodes[i].chr == nodes[curr].chr) {
                        nodes[curr].sufx = i;
                        break;
                    }
                }
            }
            temp = nodes[curr].sufx;
            while (temp > 0 && !nodes[temp].is_entry)
                temp = nodes[temp].sufx;
            if (temp > 0)
                nodes[curr].dict = temp;
        }
    }
    void search(string& text, vector<pair<int, int>>& match) {
        int curr = 0;
        int T = text.length();
        for (int pos = 0; pos < T; ++pos) {
            int next = 0;
            while (!next) {
                for (int& i : nodes[curr].chld) {
                    if (nodes[i].chr == text[pos]) {
                        next = i;
                        break;
                    }
                }
                if (curr && !next)
                    curr = nodes[curr].sufx;
                else break;
            }
            curr = next;
            if (nodes[next].is_entry)
                match.emplace_back(pos, nodes[next].pos);
            while (nodes[next].dict > 0) {
                next = nodes[next].dict;
                match.emplace_back(pos, nodes[next].pos);
            }
        }
    }
} trie;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M; string text;
    cin >> N >> text >> M;
    trie.init();
    while (M--) {
        string pattern; cin >> pattern;
        trie.add_entry(pattern);
    }
    trie.make_edges();
    vector<pair<int, int>> v;
    trie.search(text, v);

    int l = N, cnt = N;
    for (auto rit = v.rbegin(); rit != v.rend(); ++rit) {
        int nr = rit->first;
        int nl = nr - rit->second;
        if (nl < l) {
            cnt -= (nr < l ? nr+1 : l) - nl;
            l = nl;
        }
    }

    cout << cnt << '\n';
    return 0;
}
