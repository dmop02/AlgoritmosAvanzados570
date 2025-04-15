// Como base se uso el codigo del profesor encontrado en una carpeta de sharepoint que lleva a un archivo de replit: https://replit.com/@ertello/Arreglo-de-sufijos?error=overlimit#main.cpp 
// Tambien se puede utilizar como referencia las siguients paginas : https://usaco.guide/adv/suffix-array?lang=cpp , https://www.geeksforgeeks.org/suffix-array-set-2-a-nlognlogn-algorithm/?ref=next_article_top 
// Alvaro Solano | 01643948
// Domingo Mora | A01783317
#include <iostream>
#include <map>
#include <vector>
using namespace std;

// O(n log n)
vector<pair<string, int>> createSuffixArray(string S) {
  string T = S + "$";
  int n = T.length();
  map<string, int> Map;
  vector<pair<string, int>> suffix;
  string sub = "";
  for (int i = n - 1; i >= 0; i--) {
    sub = T[i] + sub;
    Map[sub] = i;
  }
  for (auto x : Map)
    suffix.push_back(make_pair(x.first, x.second));
  return suffix;
}
//0(n)
vector<int> createPrefixArray(string S, vector<pair<string, int>> sa) {
  string T = S + "$";
  int n = T.length();
  vector<int> lcp(n, 0);
  vector<int> invSuffix(n, 0);
  for (int i = 0; i < n; i++) {
    invSuffix[sa[i].second] = i;
  }
  int k = 0;
  for (int i = 0; i < n; i++) {
    if (invSuffix[i] == n - 1) {
      k = 0;
      continue;
    }
    int j = sa[invSuffix[i] + 1].second;
    while (i + k < n && j + k < n && T[i + k] == T[j + k])
      k++;
    lcp[invSuffix[i]] = k;
    if (k > 0)
      k--;
  }
  return lcp;
}
// 0(n)
int main() {
  string texto;
  getline(cin, texto);
  cout << "texto: " << texto << endl;
  cout << "Arreglo de sufijos" << endl;
  vector<pair<string, int>> suffixArray(createSuffixArray(texto));
  
  for (int i = 0; i < (int)suffixArray.size(); i++)
    cout << suffixArray[i].first << " " << suffixArray[i].second + 1 << endl;
  cout << endl;
  
  cout << "Arreglo de prefijos" << endl;
  vector<int> prefixArray(createPrefixArray(texto, suffixArray));
  for (int i = 0; i < (int)prefixArray.size() - 1; i++)
    cout << i << "\t" << prefixArray[i] << endl;
  cout << endl;
  return 0;
}

