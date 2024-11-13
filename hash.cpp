#include <iostream>  // Подключение библиотеки для ввода-вывода
#include <fstream>   // Подключение библиотеки для работы с файлами
#include <iomanip>   // Подключение библиотеки для управления форматированием вывода
#include "hash.h"    // Подключение заголовочного файла, содержащего объявления класса Hash и структуры Node

using namespace std;

// Конструктор класса Hash
Hash::Hash(){
    // Инициализация массива table размером size
    for(int i=0; i<size; i++){
        table[i]=nullptr;  // Устанавливаем все элементы массива в nullptr, чтобы обозначить пустые ячейки
    }
}

// Хеш-функция для вычисления индекса по ключу
int Hash::hashf(const string& key){
    int hash=0;  // Инициализация переменной для хранения хеш-значения
    for (int i=0; i<key.length(); i++){
        hash+=key[i];  // Суммируем ASCII-коды символов строки ключа
    }
    return hash%size;  // Возвращаем индекс, используя оператор остатка для ограничения размера
}

// Добавление элемента в хеш-таблицу
void Hash::addtoh(const string& key, const string& value){
    int index=hashf(key);  // Вычисляем индекс для ключа
    Node* newNode= new Node{key, value, nullptr};  // Создаем новый узел с указанным ключом и значением

    if(!table[index]) {  // Если ячейка по вычисленному индексу пуста
        table[index]=newNode;  // Сохраняем новый узел в таблице
    } else {  // Если ячейка уже содержит узел, начинаем обход связного списка
        Node* temp=table[index];  // Указатель на текущий узел
        while (temp) {
            if (temp->key==key) {  // Если найден узел с таким же ключом
                temp->value=value;  // Обновляем его значение
                delete newNode;  // Удаляем новый узел, так как он не нужен
                return;  // Выходим из функции
            }
            if (!temp->next) {  // Если достигнут конец списка
                temp->next=newNode;  // Добавляем новый узел в конец цепочки
                return;  // Выходим из функции
            }
            temp=temp->next;  // Переходим к следующему узлу
        }
    }
}

// Получение значения по ключу
string Hash::geth(const string& key){
    int index=hashf(key);  // Вычисляем индекс для ключа
    Node* temp=table[index];  // Указатель на первый узел в списке
    while(temp) {  // Проходим по списку
        if (temp->key==key) {  // Если ключ найден
            return temp->value;  // Возвращаем соответствующее значение
        }
        temp=temp->next;  // Переходим к следующему узлу
    }
    return "Key no find";  // Если ключ не найден, возвращаем сообщение
}

// Удаление значения по ключу
void Hash::delh(const string& key){
    int index=hashf(key);  // Вычисляем индекс для ключа
    Node* temp=table[index];  // Указатель на текущий узел
    Node* previous=nullptr;  // Указатель на предыдущий узел

    while(temp) {  // Проходим по списку
        if (temp->key==key) {  // Если ключ найден
            if (previous) {  // Если узел не первый в списке
                previous->next=temp->next;  // Пропускаем удаляемый узел
            } else {
                table[index]=temp->next;  // Если узел первый, обновляем указатель в таблице
            }
            delete temp;  // Удаляем узел
            return;  // Выходим из функции
        }
        previous=temp;  // Обновляем указатель на предыдущий узел
        temp=temp->next;  // Переходим к следующему узлу
    }
    cout<<"Key no find to delete"<<endl;  // Если ключ не найден, выводим сообщение
}

// Вывод всех элементов таблицы
void Hash::printh(){
    for (int i=0; i<size; i++){  // Проходим по всему массиву таблицы
        if (table[i]) {  // Если ячейка не пуста
            Node* temp=table[i];  // Указатель на первый узел в списке
            while (temp) {  // Проходим по списку
                cout<<"{"<<temp->key<<" : "<<temp->value<<"}";  // Выводим ключ и значение
                temp=temp->next;  // Переходим к следующему узлу
            }
            cout<<endl;  // Переход на новую строку после вывода всех узлов в ячейке
        }
    }
}

// Освобождение памяти
void Hash::clearH(){
    for (int i=0; i<size; i++){  // Проходим по всему массиву таблицы
        Node* temp=table[i];  // Указатель на первый узел в списке
        while(temp){  // Проходим по списку
            Node* temps=temp;  // Сохраняем указатель на текущий узел для удаления
            temp=temp->next;  // Переходим к следующему узлу
            delete temps;  // Удаляем текущий узел
        }
        table[i]=nullptr;  // Обновляем ячейку на пустую
    }
}

// Запись в файл
void Hash::writetofile(const string& filename){
    ofstream outFile(filename);  // Открываем файл для записи
    if (!outFile.is_open()){  // Проверяем, удалось ли открыть файл
        cout<<"Can't open file"<<endl;  // Если нет, выводим сообщение
        return;  // Выходим из функции
    }

    for (int i=0; i<size; i++){  // Проходим по всему массиву таблицы
        Node* temp=table[i];  // Указатель на первый узел в списке
        while(temp){  // Проходим по списку
            outFile<<temp->key<<" "<<temp->value<<endl;  // Записываем ключ и значение в файл
            temp=temp->next;  // Переходим к следующему узлу
        }
    }

    outFile.close();  // Закрываем файл
}

// Чтение из файла
void Hash::readfromFile(const string& filename){
    ifstream inFile(filename);  // Открываем файл для чтения
    if (!inFile.is_open()){  // Проверяем, удалось ли открыть файл
        cout<<"Can't open file"<<endl;  // Если нет, выводим сообщение
        return;  // Выходим из функции
    }

    clearH();  // Очищаем хеш-таблицу перед загрузкой данных

    string key, value;  // Переменные для хранения ключа и значения
    while(inFile>>key>>value){  // Читаем пары ключ-значение из файла
        addtoh(key, value);  // Добавляем их в хеш-таблицу
    }

    inFile.close();  // Закрываем файл
}
