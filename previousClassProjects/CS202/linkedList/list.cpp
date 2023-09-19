#include "list.h"
#include <string>
#include <iostream>

//start of Node functions
Node::Node(int i) {
	data = i;
	next = NULL;
}
//end of Node functions

//start of List functions
List::List() {
	head = NULL;
	count = 0;
}

//copied Dr. Emrich's function
List::~List() {
	if (!empty()) { // follow the links, clobbering as we go
		Node *p = head;

		while (p != NULL) {
			Node *next = p->next; // retrieve this node's "next" before we clobber it
			delete p;
			p = next;
		}
	}
}

//helper function to create a new node
Node *List::newNode(int i) {
	Node *node = new Node(i);
	node->next = NULL;
	return node;
}

//copied Dr. Emrich's function
void List::addNode(int i) {
	//...
        Node * nn = newNode(i);
    if (getCount() == 0) {

        head = nn;
    }
    else {
        Node * p = head; 
        while (p->next != NULL)  {
            p = p->next; // go to end of list
        } 
        p->next = nn;
        nn->next = NULL;
        
    }
    List::count++;
    
}

int List::empty() {
	//... 
    if (getCount() == 0){
        return true;
    }
    else {
        return false;
    }
}

int List::getCount() {
    return count;
	//...
}

Node *List::getHead() {
	//...
    return head;
}
// returns digit from node in order to easily add in the sumList function
int List::getDigit(int i) {
    int digit;
    
    Node * digitFind =head;
    int j = 0;
   while (digitFind != NULL) {
        Node * digitFindNext = digitFind->next;
        if (j == i) {
            digit = digitFind->data;
        }
        digitFind = digitFindNext;
        j++;
    }
    return digit;
}

void List::print() {
	if (!empty()) {
        std::string output;
		while (head != NULL) {
			Node *next = head->next; 
            output += std::to_string( head->data);
            head = next;
		}   
    std::cout << output << std::endl;
	} 
    
    else {
		printf("empty\n");
	}
}
//end of List functions