#include <iostream>
#include <algorithm>

using namespace std;

struct Node{
    int data;
    Node* l;
    Node* r;
    int h;
    int balance;
    Node(int num) : data(num), l(nullptr), r(nullptr), h(1), balance(0){}
};

int height(Node* root){
    if(root == nullptr){
        return 0;
    }
    return root->h;
}

void update(Node* root){
    if(root == nullptr){
        return;
    }
    root->h = 1 + max(height(root->l), height(root->r));
    root->balance = height(root->r) - height(root->l);
}

Node* rightRotate(Node* root){
    Node* temp = root->l;
    root->l = temp->r;
    temp->r = root;

    update(root);
    update(temp);
    return temp;
}

Node* leftRotate(Node* root){
    Node* temp = root->r;
    root->r = temp->l;
    temp->l = root;

    update(root);
    update(temp);
    return temp;
}

Node* balanceTree(Node* root){
    update(root);

    if(root->balance == 2){
        if(root->r != nullptr && root->r->balance < 0){
            root->r = rightRotate(root->r);
        }
        return leftRotate(root);
    }

    if(root->balance == -2){
        if(root->l != nullptr && root->l->balance > 0){
            root->l = leftRotate(root->l);
        }
        return rightRotate(root);
    }

    return root;
}

Node* insert(Node* root, int num){
    if(root == nullptr){
        return new Node(num);
    }

    if(root->data >= num){
        root->l = insert(root->l, num);
    }else{
        root->r = insert(root->r, num);
    }

    return balanceTree(root);
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
        root = insert(root, temp);
    }

    cout << "АВЛ-дерево (число(баланс)): ";
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

    clear(root);
    return 0;
}
