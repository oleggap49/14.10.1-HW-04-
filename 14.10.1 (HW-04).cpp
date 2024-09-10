/ 14.10.1 (HW - 04).cpp : Этот файл содержит функцию "main".Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include "Trie.h"

int main()
{
    setlocale(LC_ALL, "");
    Trie tr;
    //формируем дерево
    tr.insert(tr.getRoot(), "abrek");
    tr.insert(tr.getRoot(), "absent");
    tr.insert(tr.getRoot(), "akter");
    tr.insert(tr.getRoot(), "akula");
    tr.insert(tr.getRoot(), "balkon");
    tr.insert(tr.getRoot(), "bidon");

    char letter;
    string key = "";
    do
    {
        cout << "Введите символ:" << endl;
        cin >> letter;
        if (letter == 'q') break;
        //последовательно вводим буквы ключа
        key += string{ letter };
        cout << key << endl << "___________________" << endl;
        // для введенного ключа ищем подсказки
        tr.getPrompts(tr.getRoot(), key);
        for (int i = 0; i < MAX_PROMPT_LIST_SIZE; i++)   //   выдаем список найденных подсказок
            cout << tr.prompts[i] << " " << endl;
        // чистим список подсказок для следующего цикла
        tr.deletePrompts();
    } while (letter != 'q');

}

