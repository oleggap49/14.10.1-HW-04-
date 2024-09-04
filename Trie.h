#pragma once
#include <string>
using namespace std;

const int ALPHABET_SIZE = 26;
const  int MAX_PROMPT_LIST_SIZE = 5;
class Trie 
{
public:
 struct TrieNode              // ��������� ����� ������ 
 {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;       // isEndOfWord - true, ���� ���� �������� ������ �����
    bool isVizited;
 };
 string* prompts;        //������ �������� ���������
 int coutPrompts;        //������� �������� ���������
 Trie();
 ~Trie();
 TrieNode* getRoot();
 void setRoot(TrieNode* root);
 TrieNode* getNewNode(void);
 void insert(TrieNode*, string);
 bool search(TrieNode*, string);
 bool isEmpty(TrieNode* root);
 TrieNode* remove(TrieNode* root, string key, int depth);
 void getWord(TrieNode* root, string res, string* prompts );
 void getPrompts(TrieNode* root, string key, string* prompts);
 void deletePrompts(  string* prompts);
 //char getLetter(TrieNode*, string  );
 
private:
    TrieNode* root;
};