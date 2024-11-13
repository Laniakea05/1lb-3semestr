#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include "array.cpp"
#include "hash.cpp"
#include "queue.cpp"
#include "stak.cpp"
#include "listone.cpp"
#include "listtwo.cpp"
#include "tree.cpp"

using namespace std;

void ArrayCommands(Array& arr) {
    string command;
    while (true) {
        cout << " >> ";
        cin >> command;

        // добавление в конец
        if (command == "AADD") {
            string value;
            cin.ignore(); // игнорируем предыдущий символ новой строки
            getline(cin, value); // считываем строку с пробелами

            bool exists = false;
            for (int i = 0; i < arr.size; i++) {
                if (arr.data[i] == value) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                Add(arr, value);
                WriteArrayToFile(arr, "array.txt");
            } else {
                cout << "Value already exists" << endl;
            }
        } else if (command == "AADDIN") {
            int index;
            string value;
            cin >> index;
            cin.ignore(); // игнорируем предыдущий символ новой строки
            getline(cin, value); // считываем строку

            if (index >= 0 && index <= Length(arr)) {
                AddIndex(arr, index, value);
                WriteArrayToFile(arr, "array.txt");
            } else {
                cout << "Index out of range" << endl;
            }
        } else if (command == "AGETIN") {
            int index;
            cin >> index;
            if (index >= 0 && index < Length(arr)) {
                cout << "Element at index " << index << ": " << Getin(arr, index) << endl;
            } else {
                cout << "Index out of range" << endl;
            }
        } else if (command == "ADELIN") {
            int index;
            cin >> index;
            if (index >= 0 && index < Length(arr)) {
                Delin(arr, index);
                WriteArrayToFile(arr, "array.txt");
            } else {
                cout << "Index out of range" << endl;
            }
        } else if (command == "ASETIN") {
            int index;
            string value;
            cin >> index;
            cin.ignore(); // игнорируем предыдущий символ новой строки
            getline(cin, value); // считываем строку

            if (index >= 0 && index < Length(arr)) {
                Setin(arr, index, value);
                WriteArrayToFile(arr, "array.txt");
            } else {
                cout << "Index out of range" << endl;
            }
        } else if (command == "ALEN") {
            cout << "Array size: " << Length(arr) << endl;
        } else if (command == "APRINT") {
            Print(arr);
        } else if (command == "EXIT") {
            break;
        } else {
            cout << "Unknown command" << endl;
        }
    }
}



void ListOneCommands(ListOne*& list, const string& filename) {
    string command;
    while (true) {
        cout << ">> ";
        cin >> command;

        if (command == "LAHEAD") {
            string value; // Изменено с int на string
            cin >> value;
            AddHead(list, value);
            WriteToFileListOne(list, filename);
        } else if (command == "LATAIL") {
            string value; // Изменено с int на string
            cin >> value;
            AddTail(list, value);
            WriteToFileListOne(list, filename);
        } else if (command == "LDHEAD") {
            if (list) {
                DelHead(list);
                WriteToFileListOne(list, filename);
            } else {
                cout << "List is empty" << endl; // Исправлено сообщение
            }
        } else if (command == "LDTAIL") {
            if (list) {
                DelTail(list);
                WriteToFileListOne(list, filename);
            } else {
                cout << "List is empty" << endl; // Исправлено сообщение
            }
        } else if (command == "LDVAL") {
            string value; // Изменено с int на string
            cin >> value;
            if (DelValue(list, value)) {
                WriteToFileListOne(list, filename);
            } else {
                cout << "Value not found" << endl; // Исправлено сообщение
            }
        } else if (command == "LFIND") {
            string value; // Изменено с int на string
            cin >> value;
            if (FindValue(list, value)) {
                cout << "Value found" << endl; // Исправлено сообщение
            } else {
                cout << "Value not found" << endl; // Исправлено сообщение
            }
        } else if (command == "LPRINT") {
            cout << "List: ";
            Print(list);
        } else if (command == "EXIT") {
            break;
        } else {
            cout << "Command not found" << endl; // Исправлено сообщение
        }
    }
}


void StakCommands(Stak& stak){
    string command;
    while(true){
        cout<< ">>";
        cin>>command;

        if(command=="SPUSH"){
            string value;
            cin>>value;
            Push(&stak, value);
            WriteToFile(stak,"STAk.txt");
        } else if (command=="SPOP"){
            string value=Pop(&stak);
            if (!value.empty()){
                WriteToFile(stak, "STAK.txt");
            } else {
                cout<<"Stek pust"<<endl;
            }
        } else if (command=="SPRINT"){
            cout<<"Stak :";
            PrintStak(&stak);
        } else if (command=="EXIT"){
            break;
        } //else{
           // cout<<"No find command"<<endl;
        //}
    }
}

void ListSecCommands(ListTwo*& head, ListTwo*& tail, const string& filename) {
    string command;
    while (true) {
        cout << " >> ";
        cin >> command;

        if (command == "LSADDHEAD") {
            string value; // Изменено с int на string
            cin >> value;
            AddHead(head, tail, value);
            WriteListToFile(head, filename);
        } else if (command == "LSADDTAIL") {
            string value; // Изменено с int на string
            cin >> value;
            AddTail(head, tail, value);
            WriteListToFile(head, filename);
        } else if (command == "LSDELHEAD") {
            if (head) {
                DelHead(head, tail);
                WriteListToFile(head, filename);
            } else {
                cout << "List is empty" << endl; // Исправлено сообщение
            }
        } else if (command == "LSDELTAIL") {
            if (tail) {
                DelTail(head, tail);
                WriteListToFile(head, filename);
            } else {
                cout << "List is empty" << endl; // Исправлено сообщение
            }
        } else if (command == "LSDELVAL") {
            string value; // Изменено с int на string
            cin >> value;
            if (DelValue(head, tail, value)) {
                WriteListToFile(head, filename);
            } else {
                cout << "Value not found" << endl; // Исправлено сообщение
            }
        } else if (command == "LSFINDV") {
            string value; // Изменено с int на string
            cin >> value;
            if (FindValue(head, value)) {
                cout << "Value found: " << value << endl; // Исправлено сообщение
            } else {
                cout << "Value not found" << endl; // Исправлено сообщение
            }
        } else if (command == "LSPRINT") {
            cout << "List: ";
            Print(head);
        } else if (command == "EXIT") {
            break;
        } else {
            cout << "Command not found" << endl; // Исправлено сообщение
        }
    }
}


void QueueCommands(Queue& queue) {
    string command;
    while (true) {
        cout << ">> ";
        cin >> command;

        if (command == "QADDQUE") {
            string value; // Изменено с int на string
            cin >> value; // Читаем строку
            AddToQueue(queue, value);
            WriteToFile(queue, "QUEUE.txt");
        } else if (command == "QDELQUE") {
            string value = DelFromQueue(queue); // Изменено с int на string
            if (!value.empty()) { // Проверяем, не пустая ли строка
                WriteToFile(queue, "QUEUE.txt");
            } else {
                cout << "Queue is empty" << endl;
            }
        } else if (command == "QPRINT") {
            cout << "Queue: ";
            PrintQueue(queue);
        } else if (command == "EXIT") {
            break;
        } else {
            cout << "Command not found" << endl;
        }
    }
}


void HashCommands(Hash& hashtable){
    string command;
    while(true){
        cout<<" >> ";
        cin>>command;

        if (command=="HADD"){
            string key, value;

            cin>>key;
            cin>>value;
            hashtable.addtoh(key, value);
            hashtable.writetofile("HASH.txt");
        } else if(command=="HGET"){
            string key;
            cin>>key;
            string result=hashtable.geth(key);
            if(!result.empty()){
                cout<<"Znachenie : "<<result<<endl;
            } else {
                cout<<"Znachenie no find"<<endl;
            }
        } else if(command=="HDEL"){
            string key;
            cin>>key;
            hashtable.delh(key);
            hashtable.writetofile("HASH.txt");
        } else if (command=="HPRINT"){
            cout<<"Hash-table : "<<endl;
            hashtable.printh();
        } else if (command=="EXIT"){
            break;
        } else {
            cout<<"Commanda no find"<<endl;
        }
    }
}

void TreeCommands(FullBinaryTree& tree) {
    string command;
    while (true) {
        cout << " >> ";
        cin >> command;

        if (command == "TADD") {
            int value;
            cin >> value;
            tree.insert(value);
            tree.writeToFile("TREE.txt"); // Запись дерева в файл
        } else if (command == "TSEARCH") {
            int value;
            cin >> value;
            NodeT* result = tree.search(value);
            if (result) {
                cout << "Znachenie : " << result->data << endl;
            } else {
                cout << "Znachenie no find" << endl;
            }
        } else if (command == "TPRINT") {
            cout << "Tree structure: " << endl;
            tree.printTreeStructure();
        } else if (command == "TCLEAR") {
            tree.clear();
            cout << "Tree cleared." << endl;
        } else if (command == "EXIT") {
            break;
        } else {
            cout << "Command not found" << endl;
        }
    }
}



int main(){
    Array arr;
    CreateArray(arr, 10);
    FullBinaryTree tree;
    Hash hashtable;
    ListOne* list=nullptr;
    ListTwo* head=nullptr;
    ListTwo* tail=nullptr;
    Queue queue;
    Stak stak;

    while(true){
        string command;
        cout<< ">> ";
        cin>>command;

        if(command=="ARRAY"){
            ArrayCommands(arr);
        } else if (command=="HASH"){
            HashCommands(hashtable);
        } else if (command=="LISTONE"){
            ListOneCommands(list, "LISTONE.txt");
        } else if (command=="LISTTWO"){
            ListSecCommands(head, tail, "LISTTWO.txt");
        } else if (command=="QUEUE"){
            QueueCommands(queue);
        } else if (command=="STAK"){
            StakCommands(stak);
        } else if(command=="TREE"){
            TreeCommands(tree);
        } else if (command=="EXIT"){
            break;
        } else {
            cout<<"Commanda no find"<<endl;
        }
    }

    DeleteArray(arr);
    hashtable.clearH();
    DeleteList(list);
    DeleteList(head, tail);
    DeleteQueue(queue);
    FreeStak(&stak);

    return 0;

}


