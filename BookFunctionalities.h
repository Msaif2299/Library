#pragma once
#include "Book.h"
void addBooks() {
	cout << "Book Addition to the Library Database";
	cout << "\n";	//Add the option of going back instantly
	Book temp;
	bool done = false;
	char ch;
	while (!done) {
		temp.getItemsFromUser();
		cout << "Press G to enter more or any other key to exit!";
		ch = getchar();
		if (ch == 'g' || ch == 'G')
			continue;
		else
			done = true;
	}
}