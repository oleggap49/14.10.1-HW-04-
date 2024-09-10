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

    };
    string* prompts;        //������ �������� ���������
    Trie();
    ~Trie();
    TrieNode* getRoot();
    TrieNode* getNewNode(void);
    void insert(TrieNode*, string);
    void getLetter(TrieNode* root, string res);
    void getPrompts(TrieNode* root, string key);
    void deletePrompts();

private:
    TrieNode* root;
    int countPrompts;        //������� �������� ���������


};