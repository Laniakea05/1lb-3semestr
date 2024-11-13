#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct ListTwo {
    string data; // Изменено с int на string
    ListTwo* next;
    ListTwo* previous;
};

// Добавление элемента в голову списка
void AddHead(ListTwo*& head, ListTwo*& tail, const string& value) {
    ListTwo* newListTwo = new ListTwo;
    newListTwo->data = value;
    newListTwo->next = head;
    newListTwo->previous = nullptr;
    if (head) { // не пуст ли список
        head->previous = newListTwo;
    } else {
        tail = newListTwo; // новый узел становится также хвостом списка
    }
    head = newListTwo;
}

// Добавление элемента в конец списка
void AddTail(ListTwo*& head, ListTwo*& tail, const string& value) {
    ListTwo* newListTwo = new ListTwo;
    newListTwo->data = value;
    newListTwo->next = nullptr;

    if (!head) { // проверяет, пуст ли список
        newListTwo->previous = nullptr; // так как у нового узла нет предыдущего узла
        head = newListTwo;
        tail = newListTwo;
    } else {
        newListTwo->previous = tail; // устанавливается в текущий хвост списка
        tail->next = newListTwo; // связывая текущий хвост с новым узлом.
        tail = newListTwo;
    }
}

// Удаление элемента из головы списка
void DelHead(ListTwo*& head, ListTwo*& tail) {
    if (!head) { // проверяет, пуст ли список
        return;
    }
    ListTwo* temp = head;
    head = head->next;
    if (head) { // Проверяет, не пуст ли список
        head->previous = nullptr; // если не пуст
    } else {
        tail = nullptr; // Если список пуст (head равен nullptr), то tail также устанавливается в nullptr.
    }
    delete temp;
}

// Удаление элемента с хвоста списка
void DelTail(ListTwo*& head, ListTwo*& tail) {
    if (!tail) { // пуст ли список
        return;
    }
    if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }
    ListTwo* temp = tail;
    tail = tail->previous;
    tail->next = nullptr;
    delete temp;
}

// Удаление элемента по значению
bool DelValue(ListTwo*& head, ListTwo*& tail, const string& value) {
    if (!head) {
        return false;
    }
    if (head->data == value) {
        DelHead(head, tail);
        return true;
    }
    ListTwo* temp = head;
    while (temp && temp->data != value) {
        temp = temp->next;
    }
    if (temp) {
        if (temp->next) { // Проверяет, имеется ли у удаляемого узла следующий узел.
            temp->next->previous = temp->previous; // Это связывает узел, идущий после удаляемого, с предыдущим узлом
        } else {
            tail = temp->previous;
        }
        if (temp->previous) { // Проверяет, имеется ли у удаляемого узла предыдущий узел
            temp->previous->next = temp->next; // Это связывает узел, идущий перед удаляемым, с следующим узлом
        }
        delete temp;
        return true;
    }
    return false;
}

// Поиск элемента по значению
ListTwo* FindValue(ListTwo*& head, const string& value) { // Функция возвращает указатель на структуру ListTwo
    ListTwo* temp = head;
    while (temp) {
        if (temp->data == value) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Вывод списка
void Print(ListTwo* head) {
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// Освобождение памяти
void DeleteList(ListTwo*& head, ListTwo*& tail) {
    while (head) {
        DelHead(head, tail);
    }
}

// Запись списка в файл
void WriteListToFile(ListTwo* head, const string& filename) { // const функция не может изменять строку с именем файла
    ofstream outFile(filename); // Создаётся объект outFile типа ofstream и открывается файл для записи
    if (!outFile.is_open()) {
        cout << "Can't open file" << endl;
        return;
    }
    ListTwo* temp = head;
    while (temp) {
        outFile << temp->data << endl;
        temp = temp->next;
    }
    outFile.close();
    cout << "File was written " << filename << endl;
}

// Чтение списка из файла
void ReadListFromFile(ListTwo*& head, ListTwo*& tail, const string& filename) { // Указатель на первый элемент списка передаётся по ссылке
    ifstream inFile(filename); // Создаётся объект inFile типа ifstream и открывается файл
    if (!inFile.is_open()) {
        cout << "Can't open file" << endl;
        return;
    }
    DeleteList(head, tail); // Удаляет все элементы существующего списка

    string value; // Хранение значения
    int count = 0;
    while (getline(inFile, value)) { // Читаем строки из файла
        AddTail(head, tail, value); // Добавляем в конец
        count++;
    }
    if (count > 0) {
        cout << count << " elements were read" << endl;
    } else {
        cout << "File is empty" << endl;
    }
    inFile.close();
}