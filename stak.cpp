#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct NodeS{
    string data;
    NodeS* next;
};

struct Stak{
    NodeS* head=nullptr;
};


//добавление элемента в стек
void Push(Stak* stak, const string& data){
    NodeS* temp=new NodeS{data, nullptr};//сразу же присвоить полям data и next нового узла значения data и nullptr 
    temp->next=stak->head;//Указатель next нового узла устанавливается в адрес текущей головы стека, хранящийся в stak->head.
    stak->head=temp;// stak->head перемещается на новый узел, делая его новой головой стека. 
}

//удаление элемента из стека
string Pop(Stak* stak){
    if (stak->head==nullptr){
        cout<<"stak is empty"<<endl;
        return " ";
    }

    NodeS* temp=stak->head;
    string data=temp->data;// Сохраняем данные удаляемого элемента
    stak->head=stak->head->next; // Обновляем голову стека
    delete temp;
    return data;// Возвращаем данные
}


//вывод элементов стека
void PrintStak(Stak* stak){
    if (stak->head==nullptr){
        cout<<"stak is empty"<<endl;
        return;
    }

    NodeS* temp=stak->head;
    while(temp){// Вывод элементов от верхнего к нижнему
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
}


//освобождение памяти
void FreeStak(Stak* stak){
    while(stak->head){
        Pop(stak);
    }
}


//запись стека в файл
void WriteToFile(const Stak& stak, const string& filename){
    ofstream outFile(filename);
    if(!outFile.is_open()){
        cout<<"Can't open file"<<endl;
        return;
    }

    NodeS* temp=stak.head;
    while(temp){
        outFile<<temp->data<<endl;
        temp=temp->next;
    }
    outFile.close();
}

//чтение из файла
void ReadFromFile(Stak& stak, const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Can't open file" << endl;
        return;
    }

    // Очищаем существующий стек
    FreeStak(&stak);

    string value;
    int count=0;
    while(inFile>>value){
        Push(&stak, value);
        count++;
    }
    if(count>0){
        cout<<count<<" elements was read"<<endl;
    } else {
        cout<<"File is empty"<<endl;
    }
    

    inFile.close();
}
