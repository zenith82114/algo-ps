/*
 * ICPC, Regionals, Latin America,
 * Latin America Regional Contests 2012 C. Cellphone Typing
 * BOJ 5670 - trie
 * Date: 2021.8.19
 */

#include<iostream>
#include<iomanip>
#include<string>
using namespace std;
constexpr char EOS = '/';

class Trie {
    struct Node {
        char data;
        Node* sibl, * chld;
        Node(char c = 0)
            : data(c), sibl(nullptr), chld(nullptr) {}
        ~Node()	{
            if (sibl) delete sibl;
            if (chld) delete chld;
        }
        int count_branch(int base) {
            int cnt = 0;
            Node* cur = chld;
            while (cur) {
                if (cur->data == EOS)
                    cnt += base;
                Node* temp = cur->sibl;
                if (temp) base++;
                while (temp) {
                    if (temp->data == EOS)
                        cnt += base - 1;
                    else cnt += temp->count_branch(base);
                    temp = temp->sibl;
                }
                cur = cur->chld;
            }
            return cnt;
        }
    };
    Node root;
public:
    void insert(const string& s) {
        Node* cur = &root;
        for (auto it = s.begin(); it != s.end(); ++it) {
            char c = *it;
            if (cur->chld) {
                cur = cur->chld;
                while (cur->data != c && cur->sibl)
                    cur = cur->sibl;
                if (cur->data != c) {
                    cur->sibl = new Node(c);
                    cur = cur->sibl;
                }
            } else {
                cur->chld = new Node(c);
                cur = cur->chld;
            }
        }
    }
    int count_branch() {
        int cnt = 0;
        Node* temp = root.chld;
        while (temp) {
            cnt += temp->count_branch(1);
            temp = temp->sibl;
        }
        return cnt;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cout << fixed << setprecision(2);

    int N;
    while (cin >> N) {
        Trie T;
        for (int n = 0; n < N; ++n) {
            string s; cin >> s;
            s.push_back(EOS);
            T.insert(s);
        }
        cout << ((float)T.count_branch()) / N << '\n';
    }

    return 0;
}
