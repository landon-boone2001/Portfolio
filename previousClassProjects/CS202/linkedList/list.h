#ifndef LIST_H
#define LIST_H
#include <cstdio>

//start of Node class
class Node {
	public:
		Node(int);
		int data;
		Node *next;
};
//end of Node class

//start of List class
class List {
	private:
		Node *head;
		Node *newNode(int);
		int count;
	public:
		List();
		~List();
		void addNode(int);
		int empty();
		int getCount();
		Node *getHead();
        int getDigit(int);
		void print();
};
//end of List class




#endif