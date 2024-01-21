#include<iostream>
#include<string>
#include<alg.h>

using namespace std;

int main(){
    struct Trie* trie = new struct Trie;
    vector<int> compressed, compressed2;
	int cnt = 0;
    string ip; int length; int port; bool allow;
    while(cin >> ip >> length >> port >> allow) {
        if(ip == "-") break;
        cout << ip << " " << port << " " << allow << endl;
        add_rule(trie, ip, length, port, allow, &cnt);
    }
    cout << "------- Test Compress And Rebuild -------" << endl;
    compress_trie(trie, compressed);
    struct Trie* trie2;
    trie2 = rebuildTrie(compressed);
    compress_trie(trie2, compressed2);
    trie = rebuildTrie(compressed2);
    cout << "------- Test Firewall And Filter -------" << endl;
    while(cin >> ip >> port) {
        cout << "-----" << endl;
        cout << ip << " " << port << endl;
        cout << "ORIGINAL: " << check(trie, ip, port) << endl;
        cout << "REBUILD: " << check(trie2, ip, port) << endl;
        cout << "COMPRESSED: " << check_on_compressed_trie(compressed, ip, port) << endl;
    }
    return 0;
}

