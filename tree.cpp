
#include <iostream>
#include <fstream>
#include <queue>
#include <iomanip>

using namespace std;

// Структура узла дерева
struct NodeT {
    int data;
    NodeT* left;
    NodeT* right;

    NodeT(int data) : data(data), left(nullptr), right(nullptr) {}
};

// Структура дерева
struct FullBinaryTree {
    NodeT* root;

    // Конструктор
    FullBinaryTree() : root(nullptr) {}

    // Добавление элемента
    void insert(int data) {
        if (root == nullptr) {
            root = new NodeT(data);
            return;
        }

        queue<NodeT*> q;
        q.push(root);

        while (!q.empty()) {
            NodeT* current = q.front();
            q.pop();

            if (current->left == nullptr) {
                current->left = new NodeT(data);
                return;
            } else if (current->right == nullptr) {
                current->right = new NodeT(data);
                return;
            } else {
                q.push(current->left);
                q.push(current->right);
            }
        }
    }

    // Поиск элемента
    NodeT* search(int data) {
        if (root == nullptr) {
            return nullptr;
        }

        queue<NodeT*> q;
        q.push(root);

        while (!q.empty()) {
            NodeT* current = q.front();
            q.pop();

            if (current->data == data) {
                return current;
            }

            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }

        return nullptr;
    }

    // Проверка на Full Binary Tree
    bool isFull() {
        if (root == nullptr) {
            return true; 
        }

        queue<NodeT*> q;
        q.push(root);

        while (!q.empty()) {
            NodeT* current = q.front();
            q.pop();

            // Если узел имеет только один ребенок, то дерево не полное
            if ((current->left != nullptr && current->right == nullptr) ||
                (current->left == nullptr && current->right != nullptr)) {
                return false;
            }

            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }

        return true;
    }

    // Вывод дерева
    void printTree(NodeT* node, int indent = 0) const {
        if (node != nullptr) {
            if (node->right) {
                printTree(node->right, indent + 4);
            }
            if (indent) {
                cout << setw(indent) << ' ';
            }
            if (node->right) cout << " /\n" << setw(indent) << ' ';
            cout << node->data << "\n ";
            if (node->left) {
                cout << setw(indent) << ' ' << " \\\n";
                printTree(node->left, indent + 4);
            }
        }
    }

    // Публичный метод для вызова printTree
    void printTreeStructure() const {
        printTree(root);
    }

    // Освобождение памяти
    void clear() {
        if (root != nullptr) {
            queue<NodeT*> q;
            q.push(root);

            while (!q.empty()) {
                NodeT* current = q.front();
                q.pop();

                if (current->left != nullptr) {
                    q.push(current->left);
                }
                if (current->right != nullptr) {
                    q.push(current->right);
                }

                delete current;
            }
        }
        root = nullptr;
    }

    // Чтение из файла
    void readFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile.is_open()) {
            cout << "Can't open file" << endl;
            return;
        }

        int data;
        while (inFile >> data) {
            insert(data);
        }

        inFile.close();
    }

    // Запись в файл
    void writeToFile(const string& filename) {
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cout << "Can't open file" << endl;
            return;
        }

        printLevelOrder(outFile); // Используем printLevelOrder для записи
        outFile.close();
    }

private:
    // Вспомогательная функция для вывода дерева в файл
    void printLevelOrder(ofstream& outFile) {
        if (root == nullptr) {
            return;
        }

        queue<NodeT*> q;
        q.push(root);

        while (!q.empty()) {
            NodeT* current = q.front();
            q.pop();

            outFile << current->data << " ";

            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
        outFile << endl;
    }
};

