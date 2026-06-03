#include <iostream>

using namespace std;

struct Node{
    int data;
    bool red;
    Node* l;
    Node* r;
    Node* parent;
    Node(int num) : data(num), red(true), l(nullptr), r(nullptr), parent(nullptr){}
};

Node* NIL = nullptr;

void initNil(){
    NIL = new Node(0);
    NIL->red = false;
    NIL->l = NIL;
    NIL->r = NIL;
    NIL->parent = NIL;
}

void leftRotate(Node* &root, Node* x){
    Node* y = x->r;
    x->r = y->l;

    if(y->l != NIL){
        y->l->parent = x;
    }

    y->parent = x->parent;

    if(x->parent == NIL){
        root = y;
    }else if(x == x->parent->l){
        x->parent->l = y;
    }else{
        x->parent->r = y;
    }

    y->l = x;
    x->parent = y;
}

void rightRotate(Node* &root, Node* x){
    Node* y = x->l;
    x->l = y->r;

    if(y->r != NIL){
        y->r->parent = x;
    }

    y->parent = x->parent;

    if(x->parent == NIL){
        root = y;
    }else if(x == x->parent->r){
        x->parent->r = y;
    }else{
        x->parent->l = y;
    }

    y->r = x;
    x->parent = y;
}

void fixInsert(Node* &root, Node* node){
    while(node->parent->red){
        if(node->parent == node->parent->parent->l){
            Node* uncle = node->parent->parent->r;

            if(uncle->red){
                node->parent->red = false;
                uncle->red = false;
                node->parent->parent->red = true;
                node = node->parent->parent;
            }else{
                if(node == node->parent->r){
                    node = node->parent;
                    leftRotate(root, node);
                }
                node->parent->red = false;
                node->parent->parent->red = true;
                rightRotate(root, node->parent->parent);
            }
        }else{
            Node* uncle = node->parent->parent->l;

            if(uncle->red){
                node->parent->red = false;
                uncle->red = false;
                node->parent->parent->red = true;
                node = node->parent->parent;
            }else{
                if(node == node->parent->l){
                    node = node->parent;
                    rightRotate(root, node);
                }
                node->parent->red = false;
                node->parent->parent->red = true;
                leftRotate(root, node->parent->parent);
            }
        }
    }
    root->red = false;
}

void insert(Node* &root, int num){
    Node* node = new Node(num);
    node->l = NIL;
    node->r = NIL;
    node->parent = NIL;

    Node* parent = NIL;
    Node* cur = root;

    while(cur != NIL){
        parent = cur;
        if(num <= cur->data){
            cur = cur->l;
        }else{
            cur = cur->r;
        }
    }

    node->parent = parent;

    if(parent == NIL){
        root = node;
    }else if(num <= parent->data){
        parent->l = node;
    }else{
        parent->r = node;
    }

    fixInsert(root, node);
}

Node* search(Node* root, int target){
    while(root != NIL){
        if(root->data == target){
            return root;
        }else if(target < root->data){
            root = root->l;
        }else{
            root = root->r;
        }
    }
    return NIL;
}

Node* minNode(Node* root){
    while(root->l != NIL){
        root = root->l;
    }
    return root;
}

void transplant(Node* &root, Node* u, Node* v){
    if(u->parent == NIL){
        root = v;
    }else if(u == u->parent->l){
        u->parent->l = v;
    }else{
        u->parent->r = v;
    }
    v->parent = u->parent;
}

void fixDelete(Node* &root, Node* x){
    while(x != root && !x->red){
        if(x == x->parent->l){
            Node* brother = x->parent->r;

            if(brother == NIL){
                x = x->parent;
            }else if(brother->red){
                brother->red = false;
                x->parent->red = true;
                leftRotate(root, x->parent);
            }else{
                if(!brother->l->red && !brother->r->red){
                    brother->red = true;
                    x = x->parent;
                }else{
                    if(!brother->r->red){
                        brother->l->red = false;
                        brother->red = true;
                        rightRotate(root, brother);
                        brother = x->parent->r;
                    }
                    brother->red = x->parent->red;
                    x->parent->red = false;
                    brother->r->red = false;
                    leftRotate(root, x->parent);
                    x = root;
                }
            }
        }else{
            Node* brother = x->parent->l;

            if(brother == NIL){
                x = x->parent;
            }else if(brother->red){
                brother->red = false;
                x->parent->red = true;
                rightRotate(root, x->parent);
            }else{
                if(!brother->r->red && !brother->l->red){
                    brother->red = true;
                    x = x->parent;
                }else{
                    if(!brother->l->red){
                        brother->r->red = false;
                        brother->red = true;
                        leftRotate(root, brother);
                        brother = x->parent->l;
                    }
                    brother->red = x->parent->red;
                    x->parent->red = false;
                    brother->l->red = false;
                    rightRotate(root, x->parent);
                    x = root;
                }
            }
        }
    }
    x->red = false;
}

void erase(Node* &root, int target){
    Node* z = search(root, target);
    if(z == NIL){
        return;
    }

    Node* y = z;
    Node* x;
    bool yWasRed = y->red;

    if(z->l == NIL){
        x = z->r;
        transplant(root, z, z->r);
    }else if(z->r == NIL){
        x = z->l;
        transplant(root, z, z->l);
    }else{
        y = minNode(z->r);
        yWasRed = y->red;
        x = y->r;

        if(y->parent == z){
            x->parent = y;
        }else{
            transplant(root, y, y->r);
            y->r = z->r;
            y->r->parent = y;
        }

        transplant(root, z, y);
        y->l = z->l;
        y->l->parent = y;
        y->red = z->red;
    }

    delete z;

    if(!yWasRed){
        fixDelete(root, x);
    }
}

void show(Node* root){
    if(root == NIL){
        return;
    }
    show(root->l);
    cout << root->data << "(" << (root->red ? "R" : "B") << ") ";
    show(root->r);
}

void clear(Node* root){
    if(root == NIL){
        return;
    }
    clear(root->l);
    clear(root->r);
    delete root;
}

int main(){
    initNil();
    Node* root = NIL;

    int n;
    cout << "Введите количество элементов: ";
    cin >> n;

    cout << "Введите элементы дерева: ";
    for(int i = 0; i < n; i++){
        int temp;
        cin >> temp;
        insert(root, temp);
    }

    cout << "Красно-черное дерево: ";
    show(root);
    cout << endl;

    int target;
    cout << "Введите число для удаления: ";
    cin >> target;
    erase(root, target);

    cout << "После удаления: ";
    show(root);
    cout << endl;

    clear(root);
    delete NIL;
    return 0;
}
