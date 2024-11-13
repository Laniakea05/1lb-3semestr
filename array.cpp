#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

struct Array {
    string* data; // указатель на массив строк
    int size;
    int capacity; // максимальный размер
};

// создание массива с нужной ёмкостью
void CreateArray(Array& arr, int capac) {
    arr.data = new string[capac];
    arr.size = 0;
    arr.capacity = capac;
}

// добавление элемента в конец массива
void Add(Array& arr, const string& value) {
    if (arr.size == arr.capacity) {
        string* newdata = new string[arr.capacity * 2];
        for (int i = 0; i < arr.size; i++) { // Копирует элементы из старого массива в новый массив.
            newdata[i] = arr.data[i];
        }
        delete[] arr.data;
        arr.data = newdata; // Указатель data структуры Array направляется на новый массив.
        arr.capacity *= 2;
    }
    arr.data[arr.size] = value; // Новый элемент value добавляется в конец массива.
    arr.size++; // Обновляется текущий размер массива.
}

// добавление элемента по индексу
void AddIndex(Array& arr, int index, const string& value) {
    if (index < 0 || index > arr.size) {
        cerr << "index out of array bounds" << endl;
        return;
    }
    if (arr.size >= arr.capacity) {
        string* newdata = new string[arr.capacity * 2];
        for (int i = 0; i < arr.size; i++) {
            newdata[i] = arr.data[i];
        }
        delete[] arr.data;
        arr.data = newdata;
        arr.capacity *= 2;
    }
    for (int i = arr.size; i > index; i--) { // Элементы массива, начиная с индекса arr.size 
        arr.data[i] = arr.data[i - 1]; // и до индекса index, сдвигаются на одну позицию вправо
    }
    arr.data[index] = value;
    arr.size++;
}

// получение элемента по индексу
string Getin(const Array& arr, int index) {
    if (index < 0 || index >= arr.size) {
        cerr << "index out of array bounds" << endl;
        return "";
    }
    return arr.data[index];
}

// удаление элемента по индексу
void Delin(Array& arr, int index) {
    if (index < 0 || index >= arr.size) {
        cerr << "index out of array bounds" << endl;
        return;
    }
    for (int i = index; i < arr.size - 1; i++) {
        arr.data[i] = arr.data[i + 1];
    }
    arr.size--;
}

// замена элемента по индексу
void Setin(Array& arr, int index, const string& value) {
    if (index < 0 || index >= arr.size) {
        cerr << "index out of array bounds" << endl;
        return;
    }
    arr.data[index] = value;
}

// освобождение памяти
void DeleteArray(Array& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

// вывод элементов массива
void Print(const Array& arr) {
    for (int i = 0; i < arr.size; i++) {
        cout << arr.data[i] << " ";
    }
    cout << endl;
}

// длина массива
int Length(const Array& arr) {
    return arr.size;
}

// запись в файл
void WriteArrayToFile(const Array& arr, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Can't open file" << endl;
        return;
    }
    for (int i = 0; i < arr.size; i++) {
        outFile << arr.data[i] << endl;
    }
    outFile.close();
    cout << "File was written " << filename << endl;
}

// чтение из файла
void ReadArrayFromFile(Array& arr, const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Can't open file" << endl;
        return;
    }

    // Очищаем существующий массив
    DeleteArray(arr);

    string value;
    int count = 0;
    while (getline(inFile, value)) { // Чтение строки
        Add(arr, value);
        count++;
    }
    if (count > 0) {
        cout << count << " elements were read" << endl;
    } else {
        cout << "File is empty" << endl;
    }

    inFile.close();
    cout << "File was read " << filename << endl;
}
