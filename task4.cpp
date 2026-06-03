#include <iostream>
#include <string>
#include <climits>

using namespace std;

struct Node{
    int data;
    bool red;
    Node* l;
    Node* r;
    Node(int num, bool color) : data(num), red(color), l(nullptr), r(nullptr){}
};

bool isRedColor(string color){
    if(color == "R" || color == "r" || color == "red" || color == "Red" || color == "RED"){
        return true;
    }
    if(color == "к" || color == "К" || color == "красный" || color == "Красный"){
        return true;
    }
    return false;
}

void insert(Node* &root, int num, bool red){
    if(root == nullptr){
        root = new Node(num, red);
        return;
    }
    if(root->data >= num){
        insert(root->l, num, red);
    }else{
        insert(root->r, num, red);
    }
}

bool checkPositive(Node* root){
    if(root == nullptr){
        return true;
    }
    if(root->data <= 0){
        return false;
    }
    return checkPositive(root->l) && checkPositive(root->r);
}

bool checkSearchTree(Node* root, long long mn, long long mx){
    if(root == nullptr){
        return true;
    }
    if(root->data <= mn || root->data > mx){
        return false;
    }
    return checkSearchTree(root->l, mn, root->data) &&
           checkSearchTree(root->r, root->data, mx);
}

bool checkRedChildren(Node* root){
    if(root == nullptr){
        return true;
    }

    if(root->red){
        if(root->l != nullptr && root->l->red){
            return false;
        }
        if(root->r != nullptr && root->r->red){
            return false;
        }
    }

    return checkRedChildren(root->l) && checkRedChildren(root->r);
}

int blackHeight(Node* root){
    if(root == nullptr){
        return 1;
    }

    int left = blackHeight(root->l);
    int right = blackHeight(root->r);

    if(left == -1 || right == -1 || left != right){
        return -1;
    }

    if(root->red){
        return left;
    }else{
        return left + 1;
    }
}

bool checkRedBlack(Node* root){
    if(root == nullptr){
        return true;
    }
    if(root->red){
        return false;
    }
    if(!checkPositive(root)){
        return false;
    }
    if(!checkSearchTree(root, LLONG_MIN, LLONG_MAX)){
        return false;
    }
    if(!checkRedChildren(root)){
        return false;
    }
    return blackHeight(root) != -1;
}

void show(Node* root){
    if(root == nullptr){
        return;
    }
    show(root->l);
    cout << root->data << "(" << (root->red ? "R" : "B") << ") ";
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
    cout << "Введите количество узлов: ";
    cin >> n;

    cout << "Введите число и цвет узла (R или B):" << endl;
    for(int i = 0; i < n; i++){
        int num;
        string color;
        cin >> num >> color;
        insert(root, num, isRedColor(color));
    }

    cout << "Построенное дерево: ";
    show(root);
    cout << endl;

    if(checkRedBlack(root)){
        cout << "Свойства красно-черного дерева выполняются" << endl;
    }else{
        cout << "Свойства красно-черного дерева не выполняются" << endl;
    }

    clear(root);
    return 0;
}
