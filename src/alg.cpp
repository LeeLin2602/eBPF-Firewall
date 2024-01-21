#include <alg.h>

void add_rule(struct Trie* trie, string ip, int length, int port, int allow, int *cnt, int index) {
    if(rules[trie->rule][port].allow == !allow) return; // Conflict rule, discarding low-priority rule
    if(index == length) {
        rules[trie->rule][port].allow = allow;
        return;
    }
    int bit = ip[index] - '0';
    if(trie->children[bit] == NULL) {
        trie->children[bit] = new struct Trie;
        trie->children[bit]->rule = (*cnt)++;
    }
    add_rule(trie->children[bit], ip, length, port, allow, cnt, index + 1);
}

int check(struct Trie* trie, const string& ip, int port, int index) {
    if (!trie) return -1;
    if (index == ip.size()) { 
        return rules[trie->rule][port].allow;
    }
    int bit = ip[index] - '0';
    if (trie->children[bit]) {
        int result = check(trie->children[bit], ip, port, index + 1);
        return (result != -1) ? result : rules[trie->rule][port].allow;
    }
    return rules[trie->rule][port].allow;
}

int compress_trie(struct Trie* root, vector<int>& compressed_array, int index) {
    if (root == NULL) return index;

    int current_index = index;
    compressed_array.resize(max(compressed_array.size(), size_t(index + 3)));
    compressed_array[index] = root->rule;

    int next_index = index + 3; 
    int left_index = compress_trie(root->children[0], compressed_array, next_index);
    compressed_array[index + 1] = (root->children[0] != NULL) ? next_index : -1;

    next_index = left_index;
    int right_index = compress_trie(root->children[1], compressed_array, next_index);
    compressed_array[index + 2] = (root->children[1] != NULL) ? next_index : -1;

    return right_index;
}


struct Trie* rebuildTrie(const vector<int>& compressed_array, int index) {
    if (index == -1 || index >= compressed_array.size())
        return NULL;

    Trie* node = new Trie();
    node->rule = compressed_array[index];

    int leftIndex = compressed_array[index + 1];
    int rightIndex = compressed_array[index + 2];

    cout << index << ": " << compressed_array[index] << " " << leftIndex << " " << rightIndex << endl;

    if (leftIndex != -1)
        node->children[0] = rebuildTrie(compressed_array, leftIndex);
    if (rightIndex != -1)
        node->children[1] = rebuildTrie(compressed_array, rightIndex);

    return node;
}

int check_on_compressed_trie(const vector<int>& compressed_array, string ip, int port, int index, int stridx) {
    if (index == -1 || index >= compressed_array.size()) return -1; 
    if (stridx == ip.size()) {
        return rules[compressed_array[index]][port].allow; 
    }

    int bit = ip[stridx] - '0';

    int leftIndex = compressed_array[index + 1];
    int rightIndex = compressed_array[index + 2];

    if (bit == 0 && leftIndex != -1) {
        int result = check_on_compressed_trie(compressed_array, ip, port, leftIndex, stridx + 1);
        return (result != -1) ? result : rules[compressed_array[index]][port].allow;
    } else if (bit == 1 && rightIndex != -1) {
        int result = check_on_compressed_trie(compressed_array, ip, port, rightIndex, stridx + 1);
        return (result != -1) ? result : rules[compressed_array[index]][port].allow;
    }

    return rules[compressed_array[index]][port].allow;
}

