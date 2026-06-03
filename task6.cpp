#include <iostream>

using namespace std;

struct Node{
    int data;
    Node* l;
    Node* r;
    Node* parent;
    Node(int num) : data(num), l(nullptr), r(nullptr), parent(nullptr){}
};

void rotateLeft(Node* &root, Node* x){
    Node* y = x->r;
    if(y == nullptr){
        return;
    }

    x->r = y->l;
    if(y->l != nullptr){
        y->l->parent = x;
    }

    y->parent = x->parent;
    if(x->parent == nullptr){
        root = y;
    }else if(x == x->parent->l){
        x->parent->l = y;
    }else{
        x->parent->r = y;
    }

    y->l = x;
    x->parent = y;
}

void rotateRight(Node* &root, Node* x){
    Node* y = x->l;
    if(y == nullptr){
        return;
    }

    x->l = y->r;
    if(y->r != nullptr){
        y->r->parent = x;
    }

    y->parent = x->parent;
    if(x->parent == nullptr){
        root = y;
    }else if(x == x->parent->r){
        x->parent->r = y;
    }else{
        x->parent->l = y;
    }

    y->r = x;
    x->parent = y;
}

void splay(Node* &root, Node* x){
    if(x == nullptr){
        return;
    }

    while(x->parent != nullptr){
        Node* p = x->parent;
        Node* g = p->parent;

        if(g == nullptr){
            if(x == p->l){
                rotateRight(root, p);
            }else{
                rotateLeft(root, p);
            }
        }else if(x == p->l && p == g->l){
            rotateRight(root, g);
            rotateRight(root, p);
        }else if(x == p->r && p == g->r){
            rotateLeft(root, g);
            rotateLeft(root, p);
        }else if(x == p->r && p == g->l){
            rotateLeft(root, p);
            rotateRight(root, g);
        }else{
            rotateRight(root, p);
            rotateLeft(root, g);
        }
    }
}

Node* find(Node* &root, int target){
    Node* cur = root;
    Node* last = nullptr;

    while(cur != nullptr){
        last = cur;
        if(cur->data == target){
            splay(root, cur);
            return root;
        }else if(target < cur->data){
            cur = cur->l;
        }else{
            cur = cur->r;
        }
    }

    if(last != nullptr){
        splay(root, last);
    }
    return nullptr;
}

void insert(Node* &root, int num){
    if(root == nullptr){
        root = new Node(num);
        return;
    }

    Node* cur = root;
    Node* parent = nullptr;

    while(cur != nullptr){
        parent = cur;
        if(num <= cur->data){
            cur = cur->l;
        }else{
            cur = cur->r;
        }
    }

    Node* node = new Node(num);
    node->parent = parent;

    if(num <= parent->data){
        parent->l = node;
    }else{
        parent->r = node;
    }

    splay(root, node);
}

Node* maxNode(Node* root){
    while(root != nullptr && root->r != nullptr){
        root = root->r;
    }
    return root;
}

void erase(Node* &root, int target){
    find(root, target);

    if(root == nullptr || root->data != target){
        return;
    }

    Node* leftChild = root->l;
    Node* rightChild = root->r;
    delete root;

    if(leftChild == nullptr){
        root = rightChild;
        if(root != nullptr){
            root->parent = nullptr;
        }
        return;
    }

    leftChild->parent = nullptr;
    root = leftChild;

    Node* mx = maxNode(root);
    splay(root, mx);

    root->r = rightChild;
    if(rightChild != nullptr){
        rightChild->parent = root;
    }
}

void show(Node* root){
    if(root == nullptr){
        return;
    }
    show(root->l);
    cout << root->data << " ";
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

    cout << "Splay-дерево: ";
    show(root);
    cout << endl;

    int target;
    cout << "Введите число для поиска: ";
    cin >> target;
    if(find(root, target) != nullptr && root->data == target){
        cout << "Число найдено и поднято в корень" << endl;
    }else{
        cout << "Число не найдено" << endl;
    }

    cout << "Текущий корень: ";
    if(root != nullptr){
        cout << root->data << endl;
    }else{
        cout << "дерево пусто" << endl;
    }

    cout << "Введите число для добавления: ";
    cin >> target;
    insert(root, target);
    cout << "После добавления, корень: " << root->data << endl;

    cout << "Введите число для удаления: ";
    cin >> target;
    erase(root, target);

    cout << "После удаления: ";
    show(root);
    cout << endl;

    clear(root);
    return 0;
}
