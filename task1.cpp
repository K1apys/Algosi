#include <iostream>
#include <algorithm>

using namespace std;

struct Node{
    int data;
    Node* l;
    Node* r;
    int balance;
    Node(int num) : data(num), l(nullptr), r(nullptr), balance(0){}
};

int height(Node* root){
    if(root == nullptr){
        return 0;
    }
    return 1 + max(height(root->l), height(root->r));
}

void updateBalance(Node* root){
    if(root == nullptr){
        return;
    }
    updateBalance(root->l);
    updateBalance(root->r);
    root->balance = height(root->r) - height(root->l);
}

bool find(Node* root, int target){
    if(root == nullptr){
        return false;
    }else if(root->data == target){
        return true;
    }else if(root->data > target){
        return find(root->l, target);
    }else{
        return find(root->r, target);
    }
}

void insert(Node* &root, int num){
    if(root == nullptr){
        root = new Node(num);
        return;
    }
    if(root->data >= num){
        insert(root->l, num);
    }else{
        insert(root->r, num);
    }
    root->balance = height(root->r) - height(root->l);
}

Node* minNode(Node* root){
    while(root != nullptr && root->l != nullptr){
        root = root->l;
    }
    return root;
}

void erase(Node* &root, int target){
    if(root == nullptr){
        return;
    }

    if(target < root->data){
        erase(root->l, target);
    }else if(target > root->data){
        erase(root->r, target);
    }else{
        if(root->l == nullptr){
            Node* temp = root->r;
            delete root;
            root = temp;
        }else if(root->r == nullptr){
            Node* temp = root->l;
            delete root;
            root = temp;
        }else{
            Node* temp = minNode(root->r);
            root->data = temp->data;
            erase(root->r, temp->data);
        }
    }

    if(root != nullptr){
        root->balance = height(root->r) - height(root->l);
    }
}

void show(Node* root){
    if(root == nullptr){
        return;
    }
    show(root->l);
    cout << root->data << "(" << root->balance << ") ";
    show(root->r);
}

void clear(Node* root){
    if(root == nullptr){
        return;
    }
    clear(root->l);
    clear(root->r);
    delete root;
}

int main(){
    Node* root = nullptr;

    int n;
    cout << "Введите количество элементов: ";
    cin >> n;

    cout << "Введите элементы дерева: ";
    for(int i = 0; i < n; i++){
        int temp;
        cin >> temp;
        insert(root, temp);
    }
    updateBalance(root);

    cout << "Симметричный обход (число(баланс)): ";
    show(root);
    cout << endl;

    int target;
    cout << "Введите число для поиска: ";
    cin >> target;
    if(find(root, target)){
        cout << "Число найдено" << endl;
    }else{
        cout << "Число не найдено" << endl;
    }

    int num;
    cout << "Введите число для добавления: ";
    cin >> num;
    insert(root, num);
    updateBalance(root);
    cout << "После добавления: ";
    show(root);
    cout << endl;

    cout << "Введите число для удаления: ";
    cin >> num;
    erase(root, num);
    updateBalance(root);
    cout << "После удаления: ";
    show(root);
    cout << endl;

    clear(root);
    return 0;
}
