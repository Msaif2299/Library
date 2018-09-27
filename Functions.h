#pragma once
#include"Books.h"
#include"Employee.h"
#include"Student.h"

void AddBookToLibrary() {
	Book b;
	b.addBooks();
}

void AddUserToDatabase() {
	while (true) {
		cout << "What kind of user would you like to create? \n1. Student \n2.Employee\nEnter: ";
		int option;
		cin >> option;
		switch (option) {
		case 1:
			Student s;
			while (!s.addStudent()) {
				char ch;
				cout<<"\n The student already exists! \nWould you like to try again? Press F to try again. Press any other key to exit! \n Enter: ";
				cin >> ch;
				if (ch == 'f' || ch == 'F')
					break;
			}
			break;

		case 2: {
			Employee e;
			while (!e.addEmployee(e)) {
				char ch;
				cout << "\n The employee already exists! \nWould you like to try again? Press F to try again. Press any other key to exit! \n Enter: ";
				cin >> ch;
				if (ch == 'f' || ch == 'F')
					break;
			}
		}
			break;

		default:
			cout << "\nWrong option entered!";
		}
		char ch;
		cout << "\nDo you wish to enter again? \nPress F to enter again! Or any other key to exit!\nEnter: ";
		cin >> ch;
		if (ch == 'f' || ch == 'F')
			continue;
		else
			break;
	}
}

void IssueBook() {
	while (true) {
		cout << "To issue a book: \nEnter the type of user:\n1.Student\n2.Employee\nEnter: ";
		int option;
		cin >> option;
		switch (option) {
		case 1:
		{
			string membershipID;
			cout << "Enter the membership ID: ";
			cin >> ws;
			getline(cin, membershipID);
			break;
			Student e, temp, empty;
			fstream f;
			f.open("Student.dat", ios::in | ios::binary);
			while (f.read((char*)&temp, sizeof(temp))) {
				e = temp;
				if (_strcmpi(e.getMemberID(), membershipID.c_str()) == 0)
					break;
			}
			if (_strcmpi(e.getMemberID(), empty.getMemberID()) == 0)
				cout << "\nThis student does not exist!";
			else
				while (true) {
					Book b;
					b.searchBookByLibraryID();
					if (_strcmpi(b.getlibraryID(), "") == 0)
						cout << "\nThis library ID does not exist!";
					else {
						e.addBook(e, b.getlibraryID(), b.getISBN());
						cout << "\nBook successfully added!";
					}
					cout << "Do you wish to add more books?\nPress F to add more books. \nPress any other key to exit!\nEnter: ";
					char ch;
					cin >> ch;
					if (ch == 'f' || ch == 'F')
						continue;
					else
						break;
				}
		}
			break;
		case 2: {
			string membershipID;
			cout << "Enter the membership ID: ";
			cin >> ws;
			getline(cin, membershipID);
			break;
			Employee e, temp, empty;
			fstream f;
			f.open("Employee.dat", ios::in | ios::binary);
			while (f.read((char*)&temp, sizeof(temp))) {
				e = temp;
				if (_strcmpi(e.getMemberID(), membershipID.c_str()) == 0)
					break;
			}
			if (_strcmpi(e.getMemberID(), empty.getMemberID()) == 0)
				cout << "\nThis employee does not exist!";
			else
				while (true) {
					Book b;
					b.searchBookByLibraryID();
					if (_strcmpi(b.getlibraryID(), "") == 0)
						cout << "\nThis library ID does not exist!";
					else {
						e.addBook(e, b.getlibraryID(), b.getISBN());
						cout << "\nBook successfully added!";
					}
					cout << "Do you wish to add more books?\nPress F to add more books. \nPress any other key to exit!\nEnter: ";
					char ch;
					cin >> ch;
					if (ch == 'f' || ch == 'F')
						continue;
					else
						break;
				}
		}
		default:
			cout << "Wrong option entered!\n";
		}
		cout << "\nDo you wish to issue more books? Press F to continue issuing or any other key to exit!\nEnter: ";
		char ch;
		cin >> ch;
		if (ch == 'f' || ch == 'F')
			continue;
		else
			break;
	}
}


void ReturnBooks() {
	while (true) {
		cout << "To return a book: \nEnter the type of user:\n1.Student\n2.Employee\nEnter: ";
		int option;
		cin >> option;
		switch (option) {
		case 1: {
			booksIssued *tempBooks;
			cout << "Enter the membership ID: ";
			string membershipID;
			cin >> ws;
			getline(cin, membershipID);
			Student e, empty, temp;
			fstream f;
			f.open("Student.dat", ios::in | ios::binary);
			while (f.read((char*)&temp, sizeof(temp))) {
				e = temp;
				if (_strcmpi(membershipID.c_str(), temp.getMemberID()) == 0)
					break;
			}
			f.close();
			if (_strcmpi(e.getMemberID(), empty.getMemberID()) == 0)
				cout << "\nThe student does not exist!";
			else
				while (true) {
					tempBooks = e.getBooksIssued();
					cout << "Enter the library ID of the issued book: ";
					string libraryID;
					cin >> ws;
					getline(cin, libraryID);
					int bookCount = e.getBookCount();
					bool flag = false;
					for(int i = 0; i < bookCount; i++)
						if (_strcmpi((tempBooks + i)->LibraryID, libraryID.c_str()) == 0)
							flag = true;
					if (flag) {
						e.returnIssuedBooks(libraryID);
						Book tempBook, tempBook1;
						f.open("Books.dat", ios::in | ios::binary);
						while (f.read((char*)&tempBook, sizeof(tempBook))) {
							tempBook1 = tempBook;
							if (_strcmpi(tempBook1.getlibraryID(), libraryID.c_str()) == 0)
								break;
						}
						tempBook1.setIssue(false);
						f.close();
						f.open("Books.dat", ios::in | ios::binary);
						fstream ftemp;
						Book tempBook2;
						ftemp.open("Temp.dat", ios::trunc | ios::out | ios::binary);
						while (f.read((char*)&tempBook, sizeof(tempBook))) {
							tempBook2 = tempBook;
							if (_strcmpi(tempBook2.getlibraryID(), libraryID.c_str()) == 0)
								ftemp.write((char*)&tempBook1, sizeof(tempBook1));
							else
								ftemp.write((char*)&tempBook2, sizeof(tempBook2));
						}
						f.close();
						ftemp.close();
						remove("Books.dat");
						rename("Temp.dat", "Books.dat");
						cout << "\nBook successfully returned!";
					}
					else
						cout << "\nNo such book found!";
					cout << "\nDo you wish to return another book for the same user? \nPress F to return another book\nPress any other key to exit!\nEnter: ";
					char ch;
					cin >> ch;
					if (ch == 'f' || ch == 'F')
						continue;
					else
						break;
				
				}
		}
			break;
		case 2: {
			booksIssued *tempBooks;
			cout << "Enter the membership ID: ";
			string membershipID;
			cin >> ws;
			getline(cin, membershipID);
			Employee e, empty, temp;
			fstream f;
			f.open("Employee.dat", ios::in | ios::binary);
			while (f.read((char*)&temp, sizeof(temp))) {
				e = temp;
				if (_strcmpi(membershipID.c_str(), temp.getMemberID()) == 0)
					break;
			}
			f.close();
			if (_strcmpi(e.getMemberID(), empty.getMemberID()) == 0) {
				cout << "\nThe employee does not exist!";
			}
			else
				while (true) {
					tempBooks = e.getBooksIssued();
					cout << "Enter the library ID of the issued book: ";
					string libraryID;
					cin >> ws;
					getline(cin, libraryID);
					int bookCount = e.getBookCount();
					bool flag = false;
					for (int i = 0; i < bookCount; i++)
						if (_strcmpi((tempBooks + i)->LibraryID, libraryID.c_str()) == 0)
							flag = true;
					if (flag) {
						e.returnIssuedBooks(libraryID);
						Book tempBook, tempBook1;
						f.open("Books.dat", ios::in | ios::binary);
						while (f.read((char*)&tempBook, sizeof(tempBook))) {
							tempBook1 = tempBook;
							if (_strcmpi(tempBook1.getlibraryID(), libraryID.c_str()) == 0)
								break;
						}
						tempBook1.setIssue(false);
						f.close();
						f.open("Books.dat", ios::in | ios::binary);
						fstream ftemp;
						Book tempBook2;
						ftemp.open("Temp.dat", ios::trunc | ios::out | ios::binary);
						while (f.read((char*)&tempBook, sizeof(tempBook))) {
							tempBook2 = tempBook;
							if (_strcmpi(tempBook2.getlibraryID(), libraryID.c_str()) == 0)
								ftemp.write((char*)&tempBook1, sizeof(tempBook1));
							else
								ftemp.write((char*)&tempBook2, sizeof(tempBook2));
						}
						f.close();
						ftemp.close();
						remove("Books.dat");
						rename("Temp.dat", "Books.dat");
						cout << "\nBook successfully returned!";
					}
					else
						cout << "\nNo such book found!";
					cout << "\nDo you wish to return another book for the same user? \nPress F to return another book\nPress any other key to exit!\nEnter: ";
					char ch;
					cin >> ch;
					if (ch == 'f' || ch == 'F')
						continue;
					else
						break;
				}
			break;
		}
		default:
			cout << "\nWrong option!";
		}
		cout << "Do you wish to return a book for another user?\nPress F to return another book \nPress any other key to exit!\nEnter: ";
		char ch;
		cin >> ch;
		if (ch == 'f' || ch == 'F')
			continue;
		else
			break;
	}
}


void searchBook() {
	Book b;
	while (true) {
		cout << "To search a book: \n1.By Title\n2.By Author\n3.By Publisher\n4.By ISBN\n5.By Library ID\nEnter your choice: ";
		int option;
		cin >> option;
		switch (option) {
		case 1:
			b.searchBookByTitle();
			break;
		case 2:
			b.searchBookByAuthor();
			break;
		case 3:
			b.searchBookByPublisher();
			break;
		case 4:
			b.searchBookByISBN();
			break;
		case 5:
			b.searchBookByLibraryID();
			break;
		default:
			cout << "\nWrong option!";
		}
		cout << "\nDo you wish to search again? \nPress F to search again.\nPress any other key to exit searching\nEnter: ";
		char ch;
		cin >> ch;
		if (ch == 'F' || ch == 'f')
			continue;
		else
			break;
	}
	while (true) {
		cout << "\nWhat do you wish to do with the searched book?\n1.Nothing\n2.Edit\n3.Delete";
		b.getAllAttributes();
		cout << "\nEnter your option: ";
		bool nothing = false;
		int option;
		cin >> option;
		switch (option) {
		case 1:
			nothing = true;
			break;
		case 2:
			b.editBook();
			break;
		case 3:
			b.removeBook();
			nothing = true;
			break;
		default:
			cout << "\nWrong option!";
		}
		if (nothing)
			break;
		cout << "Do you wish to do something else with the selected book?\nPress F to continue \nPress any other key to exit\nEnter: ";
		char ch;
		cin >> ch;
		if (ch == 'f' || ch == 'F')
			continue;
		else
			break;
		nothing = false;
	}
}



void ArchiveUsers() {
	time_t now = time(NULL);
	tm tstruct;
	tstruct = *localtime_s(&now);
	if ((tstruct.tm_mday == 27) && (tstruct.tm_mon == 6)) {
		fstream fout, fin, ftemp;
		fout.open("Archived.dat", ios::out | ios::app | ios::binary);
		fin.open("Student.dat", ios::in | ios::binary);
		ftemp.open("Temp.dat", ios::out | ios::trunc | ios::binary);
		Student temp, s;
		while (fin.read((char*)&temp, sizeof(temp))) {
			s = temp;
			if ((s.yearExtractor() - tstruct.tm_year - 1900) >= 4) {
				fout.write((char*)&s, sizeof(temp));
			}
			else
				ftemp.write((char*)&s, sizeof(s));
		}
		fin.close();
		ftemp.close();
		fout.close();
		remove("Students.dat");
		rename("Temp.dat", "Students.dat");
	}
}
