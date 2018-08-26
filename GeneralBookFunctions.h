#pragma once
#include"Book.h"
#include<vector>

void modifyPrint(vector<Book> items) {
	for (int i = 0; i < items.size(); i++) {
		cout << '\n' << i + 1 << "." << "Title: " << items[i].getTitle() << "\n";
		cout << "  " << "Author: " << items[i].getAuthor() << '\n';
		cout << "  " << "Publisher: " << items[i].getPublisher() << '\n';
		cout << "  " << "Is Issued: ";
		if (items[i].isBookIssued())
			cout << "Yes\n";
		else
			cout << "No\n";
		cout << "  " << "Edition: " << items[i].getEdition() << '\n';
		cout << "  " << "ISBN: " << items[i].getISBN() << '\n';
		cout << "  " << "Library ID: " << items[i].getlibraryID() << '\n';
		cout << "  " << "Price: " << items[i].getPrice() << '\n';
	}
}

Book resultChecker(vector<Book> items) {
	cout << "Enter the number of the book you wish to choose: ";
	int option;
	char ch;
	do {
		cin >> option;
		if (option > items.size()) {
			cout << "Wrong number! Press F to try again or press any other key to exit!\n";
			ch = getchar();
		}
		else {
			cout << "Chosen Book is: \n";
			items[option - 1].getAllAttributes();
			cout << "\n Continue? Press F to try again! Or press anything else to continue!\n";
			ch = getchar();
			if (ch != 'f' || ch != 'F')
				return items[option - 1];
		}
	} while (ch == 'f' || ch == 'F');
	Book empty;
	return empty;
}

int checkInput() {
	int value;
	bool valid = false;
	while (!valid) {
		valid = true;
		cin >> value;
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "Please enter only digits.";
			valid = false;
		}
	}
	return value;
}

string ISBNChecker() {
	string input;
	bool wrongSize = false;
	while (!wrongSize) {
		cin >> ws;
		getline(cin, input);
		wrongSize = true;
		if (input.size() == 13 || input.size() == 10) {
			for (int i = 0; i < input.size(); i++)
				if (input[i] < 48 || input[i] > 58)
					wrongSize = false;
			if (!wrongSize)
				cout << "ISBN cannot consist of anything other than digits. Please try again.";
		}
		else {
			cout << "The ISBN can be only 10 digits or 13 digits long. Please try again.";
			wrongSize = false;
		}
	}
	return input;
}