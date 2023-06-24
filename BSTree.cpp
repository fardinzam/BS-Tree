#include "BSTree.h"

BSTree::BSTree( ) {
    root = nullptr;
}

BSTree::~BSTree() {
    del(root);
}
void BSTree::del(Node* ptr) { // destructor helper function
    if(!ptr)
        return;
    del(ptr->left);
    del(ptr->right);
    delete ptr;
}

void BSTree::insert(const string& key) {
    if(!root){ // base case: empty tree
        Node* newNode = new Node(key);
        root = newNode;
        return;
    }

    Node* ptr = root; // previous node
    Node* prevPtr = nullptr;
    while(ptr) {
        prevPtr = ptr; //saves previous node
        if(ptr->getValue() > key)
            ptr = ptr->left;
        else if(ptr->getValue() < key)
            ptr = ptr->right;
        else if(ptr->getValue() == key){ // duplicate key
            ptr->increment();
            return;
        }
    }
    //if tree is traversed and key is in the leaf nodes
    Node* newNode = new Node(key);
    if(prevPtr->getValue() > key)
        prevPtr->left = newNode;
    else
        prevPtr->right = newNode;
}


void BSTree::remove(const string& key) {
    remove(nullptr, root, key);
}
void BSTree::remove(Node* parent, Node* ptr, const string& key) {
    if(!ptr) 
        return;
    if(ptr->getValue() > key) // target node is on the left
        return remove(ptr, ptr->left, key);
    if(ptr->getValue() < key) // target node is on the right
        return remove(ptr, ptr->right, key);
    // we have arrived at target node
    //  case: count > 1
    if(ptr->getCount() > 1) {
        ptr->decrement();
        return;
    }
    //  case: no children
    if(!ptr->left && !ptr->right) { 
        if(parent) {
            if(parent->left == ptr) parent->left = nullptr;
            else parent->right = nullptr;
        }
        else root = nullptr;
        delete ptr;
        return;
    }
    //  case: one child
    if (!ptr->left || !ptr->right) {
        if(ptr->right) {
            if(ptr->right->left) {
                Node* rc = ptr->right;
                Node* lc = rc->left;
                rc->left = lc->right;
                lc->right = rc;
                parent->left = lc;
            }
            else {
                if(parent) {
                    if(parent->left == ptr)
                        parent->left = ptr->right;
                    else
                        parent->right = ptr->right;
                }
                else {
                    root = ptr->right;
                }
            }
        }
        else {
            if(parent) {
                if(parent->left == ptr) parent->left = ptr->left;
                else parent->right = ptr->left;
            }
            else {
                root = ptr->left;
            }
        }
        delete ptr;
        return;
    }
    //   case: two children
    //   find the node to replace ptr with: rightmost child of left subtree
    Node* n = ptr->left;
    Node* prevN = ptr;
    while(n->right) {
        prevN = n;
        n = n->right;
    }
    if(prevN->right == n) { // if we actually went all the way to the right
        prevN->right = n->left;
        n->left = ptr->left;
    }
    else{ // account for zybooks
        Node* rightMostN = n->left;
        Node* prevNn = n;
        if(rightMostN){
            while(rightMostN->right){
                prevNn = rightMostN;
                rightMostN = rightMostN->right;
            }
            if(rightMostN != n->left){
                prevNn->right = rightMostN->left;
                rightMostN->left = n->left;
                n->left = rightMostN;

            }
        }
    }
    n->right = ptr->right;
    //   replace ptr with n
    if(parent) {
        if(parent->left == ptr) parent->left = n;
        else parent->right = n;
    }
    else root = n;
    //   delete ptr
    delete ptr;	
}

bool BSTree::search(const string& key) const { //needs work
    return search(root, key);
}
bool BSTree::search(Node* ptr, const string& key) const {//needs work
    if(!ptr)
        return false;
    if(ptr->getValue() == key)
        return true;
    if(ptr->getValue() > key)
        return search(ptr->left, key);
    return search(ptr->right, key);
}

string BSTree::largest() const {
    //find rightmost node
    Node* ptr = root;
    if(!ptr)
        return "";
    while(ptr->right) {
        ptr = ptr->right;
    }
    return ptr->getValue();
}

string BSTree::smallest() const {
    //find leftmost node
    Node* ptr = root;
    if(!ptr)
        return "";
    while(ptr->left) {
        ptr = ptr->left;
    }
    return ptr->getValue();
}

int BSTree::height(const string& key) const {
    if (search(key)){ // if this key exists, find its height
        Node* n = root;
        while(n->getValue() != key){
            if(n->getValue() < key)
                n = n->right;
            else
                n = n->left;
        }
        return height(n);
    }
    return -1;
}
int BSTree::height(Node* ptr) const {
    if(!ptr)
        return -1;
    return 1 + max(height(ptr->left), height(ptr->right));
}

void BSTree::inOrder() const {
    inOrder(root);
}
void BSTree::inOrder(Node* ptr) const {
    if(!ptr) 
        return;
    inOrder(ptr->left);
    cout << ptr->getValue() << "(" << ptr->getCount() << ")" << ", ";
    inOrder(ptr->right);
}

void BSTree::preOrder() const {
    preOrder(root);
}
void BSTree::preOrder(Node *ptr) const {
    if(ptr) {
        cout << ptr->getValue() << "(" << ptr->getCount() << ")" << ", ";
        preOrder(ptr->left);
        preOrder(ptr->right);
    }
}

void BSTree::postOrder() const {
    postOrder(root);
}
void BSTree::postOrder(Node *ptr) const {
    if(ptr) {
        postOrder(ptr->left);
        postOrder(ptr->right);
        cout << ptr->getValue() << "(" << ptr->getCount() << ")" << ", ";
    }
}