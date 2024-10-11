#include<iostream>
#include<string>
#include "CircularLinkedList.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;


int main() {
	CS273::CircLinkedList<string> myList;
	myList.push_back("Matt");
	myList.push_back("Susanna");
	myList.push_back("Theresa");

	cout << myList.front() << endl;
	cout << myList.back() << endl << endl;

	CS273::CircLinkedList<string>::iterator it = myList.begin();
	for (int i = 0; i < myList.size(); ++i) {
		cout << *it << endl;
		++it;
	}
	--it;

	myList.insert(it, "Abigail");
	cout << myList.front() << endl << endl;

	it = myList.begin();
	for (int i = 0; i < myList.size(); ++i) {
		cout << *it << endl;
		++it;
	}
	--it;
	cout << *it << endl << endl;
	myList.erase(it);
	cout << myList.back() << endl;

	return 0;
}