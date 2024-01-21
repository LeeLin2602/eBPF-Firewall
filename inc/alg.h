#include<iostream>
#include<map>
#include<vector>
#include<string>
#define print1d(x) {for(int v: x) {cout << v << " ";} cout << endl;}

using namespace std;


struct policy {
    int8_t allow = -1;
};

struct Trie {
    int rule;
    struct Trie* children[2] = {};
};

map<uint16_t, policy> rules[65536];

void add_rule(struct Trie* trie, string ip, int length, int port, int allow, int *cnt, int index = 0);

int check(struct Trie* trie, const string& ip, int port, int index = 0);
int compress_trie(struct Trie* root, vector<int>& compressed_array, int index = 0);
struct Trie* rebuildTrie(const vector<int>& compressed_array, int index = 0);
int check_on_compressed_trie(const vector<int>& compressed_array, string ip, int port, int index = 0, int stridx = 0);
