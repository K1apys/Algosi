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

Node* minNode(Node* root){
    while(root->l != nullptr){
        root = root->l;
    }
    return root;
}

Node* eraseMin(Node* root){
    if(root->l == nullptr){
        return root->r;
    }
    root->l = eraseMin(root->l);
    return balanceTree(root);
}

Node* erase(Node* root, int target){
    if(root == nullptr){
        return nullptr;
    }

    if(target < root->data){
        root->l = erase(root->l, target);
    }else if(target > root->data){
        root->r = erase(root->r, target);
    }else{
        Node* leftChild = root->l;
        Node* rightChild = root->r;
        delete root;

        if(rightChild == nullptr){
            return leftChild;
        }

        Node* minimum = minNode(rightChild);
        minimum->r = eraseMin(rightChild);
        minimum->l = leftChild;
        return balanceTree(minimum);
    }

    return balanceTree(root);
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

    cout << "Дерево до удаления: ";
    show(root);
    cout << endl;

    int target;
    cout << "Введите число для удаления: ";
    cin >> target;
    root = erase(root, target);

    cout << "Дерево после удаления: ";
    show(root);
    cout << endl;

    clear(root);
    return 0;
}
