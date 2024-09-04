#include "Trie.h"

using namespace std;
Trie::Trie()
{
    root = getNewNode();
    prompts = new string[MAX_PROMPT_LIST_SIZE];
    coutPrompts = 0;
    deletePrompts(prompts);
}
Trie::~Trie()
{
    if (root != nullptr)
    {
        delete root; 
        delete[] prompts;
    }
}
// ���������� ��������� �� �������� �������
Trie::TrieNode* Trie::getRoot()
{
    return root;
}

void Trie::setRoot(TrieNode* node)
{
    root = node;
}
// ��������� ����� ���� � ������� ������
Trie::TrieNode* Trie::getNewNode(void)
{
    // �������� ������ ��� ����� ����
    struct TrieNode* pNode = new TrieNode;

    // ������������� ���� ����� ����� � false
    pNode->isEndOfWord = false;
    // ������������� ����"�������" ����� � false
    pNode->isVizited = false;
    
    // �������������� ����� ������� ���������
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}


// ��������� ���� � ������, ���� ��� ���, 
// ����� ���� ���� ������� �������� ���� ������ 
// �������� ��������� �������� �.�. ����� �����
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

    // �������� ��������� ����� ��� ����, �.�. ����� �����
    node->isEndOfWord = true;
}

// ���������� true ���� ���� ���� � ������, ����� false 
bool Trie::search(struct TrieNode* root, string key)
{
    struct TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;

        node = node->children[index];
    }

    return (node != nullptr && node->isEndOfWord);
}

// ���������� true ���� root ����� ����, ����� false 
bool Trie::isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// ����������� ������� �������� ����� �� ������ 
Trie::TrieNode* Trie::remove(TrieNode* root, string key, int depth)
{
    // ���� ������ ������ 
    if (!root)
        return nullptr;

    // ���� ����� �� ����� ����� 
    if (depth == key.size()) {

        // ���� ���� ������ �� ����� ����� 
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // ���� ���� �� �������� ���������, ������� ���
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // ���� �� ����� �� ����� �����, ���������� �������� ��� ������� 
    // ���������������� ������� 
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // ���� � ����� ��� ��������� ����� 
    // (������ ������ ���� ��� �������� �������), 
    // � �� �� ������������� ������ ������. 
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }

    // ���������� ����� ������
    return root;
}

/*string Trie::getWord1(TrieNode* root)
{
    TrieNode* node = root;
    string res = "";
   
        for (int i = 0; i < ALPHABET_SIZE; i++)
            while (!node->isEndOfWord)
            if (node->children[i])
            {
                bool viz = node->children[i]->isVizited;
               // if (!node->children[i]->isVizited)
                if (!viz)
                {
                    char ch = 'a' + i;
                    res += string{ ch };
                   //    node->isVizited = true;              
                    node = node->children[i];

                }
            }
    return res;
}
*/
void Trie::getWord(TrieNode* nd, string res, string* prompts )
{
    TrieNode* node = nd;
      
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->isEndOfWord)
        {
            prompts[coutPrompts] = res;
            coutPrompts++;
            return;
        }
        if (node->children[i])
             //if (!node->children[i]->isVizited)
        {
            char ch = 'a' + i;
            res += string{ ch };
           // node->isVizited = true;
            
            getWord(node->children[i], res,prompts );
        }
    }
    
}

void Trie::getPrompts(TrieNode* root, string key, string* prompts)
{
    TrieNode* node = root;
    bool NotFound = false;
    for (int i = 0; i < key.length(); i++)
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
        deletePrompts(prompts);


        prompts[0] = "��� ���������";
    }
    else
       // for (int i = 0; i < MAX_PROMPT_LIST_SIZE; i++)
        {
        int np = 0;
            string res = key;
         getWord(node, res, prompts );
    }
        
}
void Trie::deletePrompts(string* prompts)
{
    for (int i = 0;i < MAX_PROMPT_LIST_SIZE;i++)
        prompts[i] = "";
}
