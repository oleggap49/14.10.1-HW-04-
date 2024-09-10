#include "Trie.h"

using namespace std;
Trie::Trie()
{
    root = getNewNode();
    prompts = new string[MAX_PROMPT_LIST_SIZE];

    deletePrompts();
}
Trie::~Trie()
{
    if (root != nullptr)
        delete root;

    delete[] prompts;
}
// ���������� ��������� �� �������� �������
Trie::TrieNode* Trie::getRoot()
{
    return root;
}

// ��������� ����� ���� � ������� ������
Trie::TrieNode* Trie::getNewNode(void)
{
    // �������� ������ ��� ����� ����
    struct TrieNode* pNode = new TrieNode;

    // ������������� ���� ����� ����� � false
    pNode->isEndOfWord = false;



    // �������������� ����� ������� ���������
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}


// ��������� ���� � ������, ���� ��� ���, 
// ����� ���� ���� ������� �������� ���� ������ 
// �������� ��������� ��c������ �.�. ����� �����
void Trie::insert(TrieNode* root, string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // ��������� ������ � �������� ����� �������� ������������ ������ �����
        int index = key[i] - 'a';

        // ���� ��������� �������, �.�. ����� � ����� ��������� ���
        // ������� ����� ����
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    // �������� ��������� ���� ��� ����, �.�. ����� �����
    node->isEndOfWord = true;
}


// ���������� ��������� ����� � ��������� , ���� �� ������ ������� ����� �����
void Trie::getLetter(TrieNode* nd, const string key)
{
    TrieNode* node = nd;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        string res = key;
        if (node->isEndOfWord)          // ����� �� ��������
        {
            prompts[countPrompts] = res;
            countPrompts++;
            if (countPrompts > MAX_PROMPT_LIST_SIZE) countPrompts = 0; // ������ �� ������������ ������ ���������
            return;

        }
        if (node->children[i])

        {
            char ch = 'a' + i;
            res += string{ ch };

            getLetter(node->children[i], res);
        }
    }

}
// ��������� ������ ��������� ��� ���������� ����� key
void Trie::getPrompts(TrieNode* root, string key)
{
    TrieNode* node = root;
    bool NotFound = false;
    for (int i = 0; i < key.length(); i++) // ����, ���� �� ��������� ���� � ������
    {
        int index = key[i] - 'a';
        if (!node->children[index])
        {
            NotFound = true;
            break;
        }
        node = node->children[index];
    }
    if (NotFound)
    {
        deletePrompts();
        prompts[0] = "��� ���������";
    }
    else
        getLetter(node, key);


}
// ������� ������ ���������
void Trie::deletePrompts()
{
    for (int i = 0; i < MAX_PROMPT_LIST_SIZE; i++)
        prompts[i] = "";
    countPrompts = 0;
}
