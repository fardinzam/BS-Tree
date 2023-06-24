#include "Node.h"

Node::Node(string val) {
    this->val = val;
    count = 1;
    left = nullptr;
    right = nullptr;
}

//return the string attribute of a node
string Node::getValue() {
    return val;
}

//increment the count attribute
void Node::increment() {
    count++;
}

//decrement the count attribute
void Node::decrement() {
    if(count == 0)
        throw exception(); // "Decrement when count is 0!"
    count--;
}

int Node::getCount() {
    return count;
}