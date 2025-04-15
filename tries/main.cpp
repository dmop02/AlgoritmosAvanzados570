// Alvaro Solano | 01643948
// Domingo Mora | A01783317
// Referencias: https://www.geeksforgeeks.org/trie-insert-and-search/
// https://replit.com/@ertello/Arbol-de-prefijos?error=overlimit#main.cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int ALPHABET_SIZE = 26;

// TrieNode
struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
};

// Clase Trie
class Trie {
private:
    TrieNode* root;

    TrieNode* getNode() {
        TrieNode* node = new TrieNode;
        node->isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            node->children[i] = nullptr;
        }
        return node;
    }

    void dfs(TrieNode* node, string path, vector<string>& result) {
        if (node->isEndOfWord) {
            result.push_back(path);
        }
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i]) {
                dfs(node->children[i], path + char(i + 'a'), result);
            }
        }
    }

    void deleteNode(TrieNode* node) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i]) {
                deleteNode(node->children[i]);
            }
        }
        delete node;
    }

public:
    Trie() {
        root = getNode();
    }

    ~Trie() {
        deleteNode(root);
    }

    void insert(const string& key) {
        TrieNode* pCrawl = root;
        for (char ch : key) {
            int index = ch - 'a';
            if (!pCrawl->children[index])
                pCrawl->children[index] = getNode();
            pCrawl = pCrawl->children[index];
        }
        pCrawl->isEndOfWord = true;
    }

    bool search(const string& key) {
        TrieNode* pCrawl = root;
        for (char ch : key) {
            int index = ch - 'a';
            if (!pCrawl->children[index])
                return false;
            pCrawl = pCrawl->children[index];
        }
        return pCrawl->isEndOfWord;
    }

    void printAll() {
        vector<string> result;
        dfs(root, "", result);
        for (const string& word : result) {
            cout << word << endl;
        }
    }

    void printWithPrefix(const string& prefix) {
        TrieNode* pCrawl = root;
        for (char ch : prefix) {
            int index = ch - 'a';
            if (!pCrawl->children[index])
                return;
            pCrawl = pCrawl->children[index];
        }
        vector<string> result;
        dfs(pCrawl, prefix, result);
        for (const string& word : result) {
            cout << word << endl;
        }
    }
};

int main() {
    int N;
    cin >> N;

    Trie trie;
    for (int i = 0; i < N; ++i) {
        string word;
        cin >> word;
        trie.insert(word);
    }

    int M;
    cin >> M;
    vector<string> queries(M);
    for (int i = 0; i < M; ++i) {
        cin >> queries[i];
    }

    string prefix;
    cin >> prefix;

    // 1. Palabras en orden lexicográfico
    trie.printAll();

    // 2. Resultado de las búsquedas
    for (const string& word : queries) {
        cout << (trie.search(word) ? "true" : "false") << endl;
    }

    // 3. Palabras con el prefijo dado
    trie.printWithPrefix(prefix);

    return 0;
}