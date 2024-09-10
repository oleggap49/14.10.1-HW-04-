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
// возвращает указатель на корневую вершину
Trie::TrieNode* Trie::getRoot()
{
    return root;
}

// ¬озвращет новый узел с пустыми детьми
Trie::TrieNode* Trie::getNewNode(void)
{
    // ¬ыдел€ем пам€ть под новый узел
    struct TrieNode* pNode = new TrieNode;

    // устанавливаем флаг конца слова в false
    pNode->isEndOfWord = false;



    // инициализируем детей нулевым уазателем
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}


// ¬ставл€ет ключ в дерево, если его нет, 
// иначе если ключ €влетс€ префксом узла дерева 
// помечает вкачестве лиcтового т.е. конец слова
void Trie::insert(TrieNode* root, string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // вычисл€ем индекс в алфавите через смещение отнситьельно первой буквы
        int index = key[i] - 'a';

        // если указатель пустрой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    // помечаем последний узел как лист, т.е. конец слова
    node->isEndOfWord = true;
}


// рекурсивно добавл€ет букву в результат , пока не найдет признак конца слова
void Trie::getLetter(TrieNode* nd, const string key)
{
    TrieNode* node = nd;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        string res = key;
        if (node->isEndOfWord)          // выход из рекурсии
        {
            prompts[countPrompts] = res;
            countPrompts++;
            if (countPrompts > MAX_PROMPT_LIST_SIZE) countPrompts = 0; // защита от переполнени€ списка подсказок
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
// формирует список подсказок дл€ введенного ключа key
void Trie::getPrompts(TrieNode* root, string key)
{
    TrieNode* node = root;
    bool NotFound = false;
    for (int i = 0; i < key.length(); i++) // ищем, есть ли введенный ключ в дереве
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
        prompts[0] = "Ќет вариантов";
    }
    else
        getLetter(node, key);


}
// очистка списка подсказок
void Trie::deletePrompts()
{
    for (int i = 0; i < MAX_PROMPT_LIST_SIZE; i++)
        prompts[i] = "";
    countPrompts = 0;
}
