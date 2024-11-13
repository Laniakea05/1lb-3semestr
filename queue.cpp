#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct NodeQue { // Представляет узел в очереди
    string data; // Изменено с int на string
    NodeQue* next;
};

struct Queue { // Представляет очередь
    NodeQue* head; // Реализует основную функциональность очереди
    NodeQue* tail; // В Queue будут определены методы для добавления элементов в очередь

    Queue() {
        head = nullptr;
        tail = nullptr;
    }
};

// Добавление элемента в очередь
void AddToQueue(Queue& queue, const string& value) { // Изменено с int на string
    NodeQue* newNode = new NodeQue; // Новый узел
    newNode->data = value;
    newNode->next = nullptr;

    if (!queue.head) { // Пустая ли очередь
        queue.head = newNode;
        queue.tail = newNode;
    } else {
        queue.tail->next = newNode;
        queue.tail = newNode;
    }
}

// Удаление элемента из очереди
string DelFromQueue(Queue& queue) { // Изменено с int на string
    if (!queue.head) { // Если queue.head равен nullptr, значит, очередь пуста.
        cout << "Queue is empty" << endl;
        return ""; // Возвращаем пустую строку
    }

    NodeQue* temp = queue.head; // Создается указатель temp, который копирует адрес первого элемента очереди
    string value = temp->data; // Сохраняем значение
    queue.head = queue.head->next;

    if (!queue.head) { // Проверяется, стала ли очередь пустой после удаления первого элемента
        queue.tail = nullptr; // Если очередь стала пустой
    }
    delete temp;
    return value; // Возвращаем значение
}

// Вывод очереди
void PrintQueue(const Queue& queue) {
    NodeQue* temp = queue.head;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Освобождение памяти
void DeleteQueue(Queue& queue) {
    while (queue.head) {
        DelFromQueue(queue);
    }
}

// Запись в файл
void WriteToFile(const Queue& queue, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Can't open file" << endl;
        return;
    }

    NodeQue* temp = queue.head;
    while (temp) {
        outFile << temp->data << endl; // Записываем строку в файл
        temp = temp->next;
    }
    outFile.close();
}

// Чтение очереди из файла
void ReadQueueFromFile(Queue& queue, const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Can't open file" << endl;
        return;
    }

    DeleteQueue(queue);

    string value; // Изменено с int на string
    int count = 0;
    while (getline(inFile, value)) { // Читаем строки из файла
        AddToQueue(queue, value); // Добавляем в очередь
        count++;
    }
    if (count > 0) {
        cout << count << " elements were read" << endl;
    } else {
        cout << "File is empty" << endl;
    }

    inFile.close();
}
