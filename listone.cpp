#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct ListOne {
    string data; // Изменено с int на string
    ListOne* next; // Указатель на следующий узел
};

// Добавление элемента в начало списка
void AddHead(ListOne*& head, const string& value) {
    ListOne* newListOne = new ListOne; // Создаем новый узел
    newListOne->data = value; // Помещаем в новый узел значение
    newListOne->next = head; // Устанавливаем указатель на старый узел
    head = newListOne; // Голова теперь указывает на новый узел
}

// Добавление элемента в конец списка
void AddTail(ListOne*& head, const string& value) {
    ListOne* newListOne = new ListOne;
    newListOne->data = value;
    newListOne->next = nullptr; // Устанавливаем next в nullptr

    if (!head) { // Если список пуст
        head = newListOne; // Новый узел становится головой
    } else {
        ListOne* temp = head; // Временный указатель на голову
        while (temp->next) { // Двигаемся по списку до последнего узла
            temp = temp->next;
        }
        temp->next = newListOne; // Связываем новый узел с последним узлом
    }
}

// Удаление элемента из головы списка
void DelHead(ListOne*& head) {
    if (!head) {
        return;
    }
    ListOne* temp = head; // Временный указатель на голову
    head = head->next; // Изменяем голову на второй узел
    delete temp; // Удаляем старую голову
}

// Удаление элемента из конца списка
void DelTail(ListOne*& head) {
    if (!head) {
        return;
    }
    if (!head->next) { // Если только один узел
        delete head; // Удаляем голову
        head = nullptr; // Сбрасываем голову
        return;
    }

    ListOne* temp = head;
    while (temp->next->next) { // Двигаемся до узла перед последним
        temp = temp->next;
    }
    delete temp->next; // Удаляем последний узел
    temp->next = nullptr; // Обнуляем указатель на следующий узел
}

// Удаление по значению
bool DelValue(ListOne*& head, const string& value) {
    if (!head) {
        return false;
    }
    if (head->data == value) { // Если значение в голове совпадает
        DelHead(head); // Удаляем голову
        return true;
    }

    ListOne* temp = head;
    while (temp->next && temp->next->data != value) { // Ищем узел для удаления
        temp = temp->next;
    }

    if (temp->next) { // Если узел найден
        ListOne* del = temp->next; // Узел для удаления
        temp->next = temp->next->next; // Связываем предшествующий узел с узлом после удаляемого
        delete del; // Удаляем узел
        return true;
    }

    return false;
}

// Поиск элемента по значению
ListOne* FindValue(ListOne*& head, const string& value) {
    ListOne* temp = head;
    while (temp) { // Проходим по списку
        if (temp->data == value) {
            return temp; // Возвращаем узел, если найден
        }
        temp = temp->next;
    }
    return nullptr; // Если не найден
}

// Вывод списка
void Print(ListOne*& head) {
    ListOne* temp = head; // Используем временный указатель для обхода
    while (temp) {
        cout << temp->data << " "; // Выводим данные узла
        temp = temp->next;
    }
    cout << endl;
}

// Освобождение памяти
void DeleteList(ListOne*& head) {
    while (head) {
        DelHead(head);
    }
}

// Запись в файл
void WriteToFileListOne(ListOne* head, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Can't open file" << endl;
        return;
    }
    ListOne* temp = head;
    while (temp) {
        outFile << temp->data << endl; // Записываем значение в файл
        temp = temp->next;
    }
    outFile.close();
    cout << "File was written " << filename << endl;
}

// Чтение списка из файла
void ReadFromFileListOne(ListOne*& head, const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Can't open file" << endl;
        return;
    }
    DeleteList(head); // Удаляем старые данные перед загрузкой новых

    string value; // Хранение значения
    int count = 0; // Подсчет считанных значений
    while (getline(inFile, value)) { // Читаем строки из файла
        AddTail(head, value); // Добавляем в конец
        count++;
    }
    if (count > 0) {
        cout << "File was read" << endl;
    } else {
        cout << "File is empty" << endl;
    }

    inFile.close();
}
