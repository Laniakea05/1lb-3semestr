#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct Node {
    string key;
    string value;
    Node* next;
};

class Hash{
    public:
        static const int size=10;
        Node* table[size];

        Hash();
        void addtoh(const string& key, const string& value);
        string geth(const string& key);
        void delh(const string& key);
        void printh();
        void clearH();
        void writetofile(const string& filename);
        void readfromFile(const string& filename);
    private:
        int hashf(const string& key);

};