// 14.10.1 (HW-04).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
 
#include "Trie.h"
 
int main()
{
    setlocale(LC_ALL, "");
    Trie tr;
    tr.insert(tr.getRoot(), "abcd");
    tr.insert(tr.getRoot(), "ablum");
    tr.insert(tr.getRoot(), "arbor");


    char letter;
    string key  = "";
     do
    {
        cout << "Введите символ:"<< endl;
        cin >> letter;
        if (letter == 'q') break;
        key += string{ letter };
        cout << key << endl << "___________________"<< endl;

        tr.getPrompts(tr.getRoot(), key, tr.prompts );
        for (int i = 0; i < MAX_PROMPT_LIST_SIZE; i++)
            cout << tr.prompts[i] <<" " <<endl; 
        tr.deletePrompts(tr.prompts);
     } while (letter != 'q');


     
   /* string key = "aplum";
    cout << "Ключ " << key;
   if( tr.search(tr.getRoot(), key ))
       cout << " найден." << endl;
   else cout << " не найден." << endl;

   string res = tr.getWord(tr.getRoot());
   cout << res << endl;
  //  tr.setRoot(tr.remove(tr.getRoot(), res, 5));
    
       res  = tr.getWord(tr.getRoot());
   cout << res  << endl;
  */   
}

