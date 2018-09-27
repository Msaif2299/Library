#include<iostream>
#include<fstream>
#include<Windows.h>
#include"Functions.h"
using namespace std;

int main() {
	ArchiveUsers();
	while (true) {
		cout << "Enter the option you wish to execute:";
		cout << "\n1.Add users\n2.Issue books to users\n3.Return books from users\n4.Search books\n5.Add Books\nEnter your option: ";
		int option;
		cin >> option;
		switch (option) {
		case 1:
			AddUserToDatabase();
			break;
		case 2:
			IssueBook();
			break;
		case 3:
			ReturnBooks();
			break;
		case 4:
			searchBook();
			break;
		case 5:
			AddBookToLibrary();
			break;
		default:
			cout << "Wrong option entered! Please try again!\n";
			Sleep(2000);
		}
		system("CLS");
		cout << "\nDo you wish to exit? Press F to exit. Press any other key to continue!";
	}
	return 0;
}