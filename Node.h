#ifndef __NODE_H__
#define __NODE_H__
#include <iostream>

using namespace std;

class Node {
 private:
   string val;
   int count;
    
 public:
   Node(string);
   string getValue(); //return the string attribute of a node
   void increment(); //increment the count attribute
   void decrement(); //decrement the count attribute
   int getCount(); // return the count value

   Node *left;
   Node *right;
};
#endif