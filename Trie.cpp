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
// возвращает указатель на корневую вершину
Trie::TrieNode* Trie::getRoot()
{
    return root;
}

void Trie::setRoot(TrieNode* node)
{
    root = node;
}
// Возвращет новый узел с пустыми детьми
Trie::TrieNode* Trie::getNewNode(void)
{
    // Выделяем память под новый узел
    struct TrieNode* pNode = new TrieNode;

    // устанавливаем флаг конца слова в false
    pNode->isEndOfWord = false;
    // устанавливаем флаг"Посещен" слова в false
    pNode->isVizited = false;
    
    // инициализируем детей нулевым уазателем
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}


// Вставляет ключ в дерево, если его нет, 
// иначе если ключ явлется префксом узла дерева 
// помечает вкачестве литового т.е. конец слова
void Trie::insert(TrieNode* root, string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // вычисляем индекс в алфавите через смещение отнситьельно первой буквы
        int index = key[i] - 'a';

        // если указатель пустрой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    // помечаем последний узлел как лист, т.е. конец слова
    node->isEndOfWord = true;
}

// Возврашает true если ключ есть в дереве, иначе false 
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

// Вохвращает true если root имеет лист, иначе false 
bool Trie::isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// Рекурсивная функция удаления ключа из дерева 
Trie::TrieNode* Trie::remove(TrieNode* root, string key, int depth)
{
    // Если дерево пустое 
    if (!root)
        return nullptr;

    // если дошли до конца ключа 
    if (depth == key.size()) {

        // Этот узел больше не конец слова 
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // Если ключ не евляется префиксом, удаляем его
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // Если не дошли до конца ключа, рекурсивно вызываем для ребенка 
    // соответствующего символа 
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // Если у корня нет дочернего слова 
    // (удален только один его дочерний элемент), 
    // и он не заканчивается другим словом. 
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }

    // возвращаем новый корень
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


        prompts[0] = "Нет вариантов";
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
