#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<string.h>

using namespace std;

class Book
{
	char ISBN[13], publisher[100], libraryID[100], title[100], author[100];
	bool isIssued;
	int edition;
	float price;
	void bookEdit(Book);
public:
	Book() {
		strcpy_s(ISBN, "");
		isIssued = false;
		strcpy_s(publisher, "");
		strcpy_s(libraryID, "");
		strcpy_s(title, "");
		strcpy_s(author, "");
		edition = 0;
		price = 0.00;
	}

	void setISBN(const char[]);
	void setPublisher(const char[]);
	void setlibraryID(const char[]);
	void setTitle(const char[]);
	void setAuthor(const char[]);
	void setEdition(int);
	void setPrice(float);
	void setIssue(bool);

	const char* getISBN() const;
	const char* getPublisher() const;
	const char* getlibraryID() const;
	const char* getTitle() const;
	const char* getAuthor() const;
	int getEdition() const;
	float getPrice() const;
	bool isBookIssued() const;

	void setBookAttributes(const char[], const char[], const char[], const char[], const char[], int, float);

	void getAllAttributes() const;

	void getItemsFromUser();
	void getAllBooks();

	void editBook();
	Book searchBookByTitle();
	Book searchBookByAuthor();
	Book searchBookByPublisher();
	Book searchBookByLibraryID();
	Book searchBookByISBN();

	void deleteBookByLibraryID(Book);
	void addBooks();
	void removeBook();

	~Book();
};

void Book::addBooks() {
	cout << "Book Addition to the Library Database";
	cout << "\n";	//Add the option of going back instantly
	Book temp;
	//bool done = false;
	char ch;
	do {
		temp.getItemsFromUser();
		cout << "Press G to enter more or any other key to exit!";
		cin >> ch;
	} while (ch == 'g' || ch == 'G');
}

void Book::removeBook() {
	Book book1, book2;
	bool deleted = false;
	char ch = 'd';
	do {
		book1.searchBookByLibraryID();
		if (book1.getlibraryID() == "") {
			cout << "Book not found. Please check the ID again.\n Enter F to try again. Enter any other key to exit: ";
			cin >> ch;
		}
		else {
			book2.deleteBookByLibraryID(book1);
			deleted = true;
		}
	} while (ch == 'f' || ch == 'F');
	if (deleted)
		cout << "Successfully Deleted!\n";
}


int checkInput();

void modifyPrint(vector<Book> items) {
	vector<Book>::iterator it;
	int count = 0;
	for (auto it = items.begin(); it != items.end(); it++) {
		cout << '\n' << count + 1 << "." << "Title: " << it->getTitle() << "\n";
		cout << "  " << "Author: " << it->getAuthor() << '\n';
		cout << "  " << "Publisher: " << it->getPublisher() << '\n';
		cout << "  " << "Is Issued: ";
		if (it->isBookIssued())
			cout << "Yes\n";
		else
			cout << "No\n";
		cout << "  " << "Edition: " << it->getEdition() << '\n';
		cout << "  " << "ISBN: " << it->getISBN() << '\n';
		cout << "  " << "Library ID: " << it->getlibraryID() << '\n';
		cout << "  " << "Price: " << it->getPrice() << '\n';
		count++;
	}
}

bool existingLibIDChecker(string libraryID) {
	fstream f;
	f.open("Books.dat", ios::in | ios::binary);
	Book book;
	while (f.read((char*)&book, sizeof(book))) {
		if (_strcmpi(book.getlibraryID(), libraryID.c_str()) == 0) {
			f.close();
			return true;
		}
	}
	f.close();
	return false;
}

Book resultChecker(vector<Book> items) {
	vector<Book>::size_type option;
	Book empty;
	char ch;
	if (items.size() == 0) {
		cout << "No book found!\n";
		return empty;
	}
	cout << "Enter the number of the book you wish to choose: ";
	do {
		cout << "\nEnter the option: ";
		option = checkInput();
		if (option > items.size() || option <= 0) {
			cout << "Wrong number! Press F to try again or press any other key to exit!\n";
			cin >> ch;
		}
		else {
			cout << "Chosen Book is: \n";
			items[option - 1].getAllAttributes();
			cout << "\n Continue? Press F to try again! Or press anything else to continue!\n";
			cin >> ch;
			if (ch != 'f' || ch != 'F')
				return items[option - 1];
		}
	} while (ch == 'f' || ch == 'F');
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
			cout << "Please enter only digits.\nEnter again: ";
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
			string::iterator i;
			for (auto i = input.begin(); i != input.end(); i++)
				if (*i < 48 || *i > 58)
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

void Book::setAuthor(const char author[]) {
	strcpy_s(this->author,author);
}

void Book::setEdition(int edition) {
	this->edition = edition;
}

void Book::setISBN(const char ISBN[]) {
	strcpy_s(this->ISBN, ISBN);
}

void Book::setlibraryID(const char libraryID[]) {
	strcpy_s(this->libraryID, libraryID);
}

void Book::setPrice(float price) {
	this->price = price;
}

void Book::setPublisher(const char publisher[]) {
	strcpy_s(this->publisher, publisher);
}

void Book::setTitle(const char title[]) {
	strcpy_s(this->title, title);
}

const char* Book::getAuthor() const {
	return author;
}

const char* Book::getPublisher() const {
	return publisher;
}

bool Book::isBookIssued() const {
	return isIssued;
}

const char* Book::getISBN() const {
	return ISBN;
}

const char* Book::getlibraryID() const {
	return libraryID;
}

int Book::getEdition() const {
	return edition;
}

const char* Book::getTitle() const {
	return title;
}

float Book::getPrice() const {
	return price;
}

void Book::setBookAttributes(const char title[], const char author[], const char publisher[], const char ISBN[], const char libraryID[], int edition, float price) {
	setAuthor(author);
	setTitle(title);
	setPublisher(publisher);
	setISBN(ISBN);
	setlibraryID(libraryID);
	setEdition(edition);
	setPrice(price);
}

void Book::getAllAttributes() const {
	cout << "Title: " << title << "\n";
	cout << "Author: " << author << "\n";
	cout << "Edition: " << edition << "\n";
	cout << "Publisher: " << publisher << "\n";
	cout << "Issue State: ";
	if (isIssued == true)
		cout << "Issued\n";
	else
		cout << "Not Issued\n";
	cout << "ISBN: " << ISBN << "\n";
	cout << "Library ID: " << libraryID << "\n";
	cout << "Price: " << price << "\n\n";
}

void Book::getItemsFromUser() {
	string publisher, author, title, ISBN, libraryID;
	int edition;
	float price;
	cout << "Enter the title: ";
	cin >> ws;
	getline(cin, title);
	cout << "Enter the Author: ";
	cin >> ws;
	getline(cin, author);
	cout << "Enter the edition number: ";
	edition = checkInput();
	cout << "Enter the publisher name: ";
	cin >> ws;
	getline(cin, publisher);
	cout << "Enter the ISBN number: ";
	ISBN = ISBNChecker();
	bool existing = true;
	while (true) {
		cout << "Enter the library ID: ";
		cin >> libraryID;
		existing = existingLibIDChecker(libraryID);
		if (existing) {
			cout << "The entered library ID already exists! \nPlease go to edit or press f to try again!\nOr enter any other key to exit!";
			char ch;
			cin >> ch;
			if (ch == 'f' || ch == 'F')
				continue;
			else
				return;
		}
		else
			break;
	}
	cout << "Enter the price: ";
	cin >> price;
	cout << "\n";
	setBookAttributes(title.c_str(), author.c_str(), publisher.c_str(), ISBN.c_str(), libraryID.c_str(), edition, price);
	fstream f;
	f.open("Books.dat", ios::app | ios::binary | ios::out);
	f.write((char*)this, sizeof(*this));
	f.close();
}

void Book::setIssue(bool isIssued) {
	this->isIssued = isIssued;
}

Book Book::searchBookByAuthor() {
	string author;
	cout << "Enter the author's name: ";
	cin >> ws;
	getline(cin, author);
	fstream f;
	Book temp, temp1;
	vector<Book> results;
	f.open("Books.dat", ios::binary | ios::in);
	while (f.read((char*)&temp, sizeof(temp))) {
		temp1 = temp;
		if(_strcmpi(temp1.getAuthor(), author.c_str()) == 0)
			results.push_back(temp);
	}
	f.close();
	modifyPrint(results);
	*this = resultChecker(results);
	return *this;
}

Book Book::searchBookByISBN() {
	string ISBN;
	cout << "Enter the ISBN: ";
	ISBN = ISBNChecker();
	fstream f;
	Book temp, temp1;
	vector<Book> results;
	f.open("Books.dat", ios::binary | ios::in);
	while (f.read((char*)&temp, sizeof(temp))) {
		temp1 = temp;
		if (_strcmpi(temp1.getISBN(), ISBN.c_str()) == 0)
			results.push_back(temp);
	}
	f.close();
	modifyPrint(results);
	*this = resultChecker(results);
	return *this;
}

Book Book::searchBookByLibraryID() {
	string libraryID;
	cout << "Enter the library ID: ";
	cin >> ws;
	getline(cin, libraryID);
	fstream f;
	Book temp, temp1;
	vector<Book> results;
	f.open("Books.dat", ios::binary | ios::in);
	while (f.read((char*)&temp, sizeof(temp))) {
		temp1 = temp;
		if (_strcmpi(temp1.getlibraryID(), libraryID.c_str()) == 0)
			results.push_back(temp);
	}
	f.close();
	modifyPrint(results);
	*this = resultChecker(results);
	return *this;
}

Book Book::searchBookByPublisher() {
	string publisher;
	cout << "Enter the publisher's name: ";
	cin >> ws;
	getline(cin, publisher);
	fstream f;
	Book temp, temp1;
	vector<Book> results;
	f.open("Books.dat", ios::binary | ios::in);
	while (f.read((char*)&temp, sizeof(temp))) {
		temp1 = temp;
		if (_strcmpi(temp1.getPublisher(), publisher.c_str()) == 0)
			results.push_back(temp);
	}
	f.close();
	modifyPrint(results);
	*this = resultChecker(results);
	return *this;
}

Book Book::searchBookByTitle() {
	string title;
	cout << "Enter the title: ";
	cin >> ws;
	getline(cin, title);
	fstream f;
	Book temp, temp1;
	vector<Book> results;
	f.open("Books.dat", ios::binary | ios::in);
	while (f.read((char*)&temp, sizeof(temp))) {
		temp1 = temp;
		if (_strcmpi(temp1.getTitle(),title.c_str()) == 0)
			results.push_back(temp);
	}
	f.close();
	modifyPrint(results);
	*this = resultChecker(results);
	return *this;
}

void Book::editBook() {
	Book result;
	int option;
	char ch = 'e';
	do {
		do {
			cout << "Search book by?\n1.Title\n2.Author\n3.Publisher\n4.ISBN\n5.Library ID\nEnter the option: ";
			option = checkInput();
			switch (option) {
			case 1: {
				string newTitle;
				cout << "Enter the new title: ";
				cin >> ws;
				getline(cin, newTitle);
				result = searchBookByTitle();
				result.setTitle(newTitle.c_str());
				if (result.getlibraryID() != "")
					bookEdit(result);
				break;
			}
			case 2: {
				string newAuthor;
				cout << "Enter the new author: ";
				cin >> ws;
				getline(cin, newAuthor);
				result = searchBookByAuthor();
				result.setAuthor(newAuthor.c_str());
				if (result.getlibraryID() != "")
					bookEdit(result);
				break;
			}
			case 3: {
				string newPublisher;
				cout << "Enter the new publisher: ";
				cin >> ws;
				getline(cin, newPublisher);
				result = searchBookByPublisher();
				result.setPublisher(newPublisher.c_str());
				if (result.getlibraryID() != "")
					bookEdit(result);
				break;
			}
			case 4: {
				string newISBN;
				cout << "Enter the new ISBN: ";
				newISBN = ISBNChecker();
				result = searchBookByISBN();
				result.setISBN(newISBN.c_str());
				if (result.getlibraryID() != "")
					bookEdit(result);
				break;
			}
			case 5: {
				string newLibraryID;
				char ch;
				bool existing;
				while (true) {
					cout << "Enter the new library ID: ";
					cin >> ws;
					getline(cin, newLibraryID);
					existing = existingLibIDChecker(newLibraryID);
					if (existing) {
						cout << "The entered library ID already exists!\nPress f to try again or press any other key to end.\nEnter your option: ";
						cin >> ch;
						if (ch == 'f' || ch == 'F')
							continue;
						else
							break;
					}
					break;
				}
				if (existing)
					break;
				result = searchBookByLibraryID();
				result.setlibraryID(newLibraryID.c_str());
				if (result.getlibraryID() != "")
					bookEdit(result);
				break;
			}
			default:
				cout << "Wrong Option!\n";
				cout << "Press F to try again or press any other key to go back!";
				cin >> ch;
			}
		} while (ch == 'F' || ch == 'f');
		cout << "Press F to search again. Otherwise press any other key to exit this option.";
		cin >> ch;
	} while (ch == 'F' || ch == 'f');
}

void Book::bookEdit(Book book) {
	fstream fin, fout;
	fin.open("Books.dat", ios::in | ios::binary);
	fout.open("Temp.dat", ios::out | ios::trunc | ios::binary);
	Book temp, temp1;
	while (fin.read((char*)&temp, sizeof(temp))) {
		temp1 = temp;
		if (_strcmpi(temp1.getlibraryID(),book.getlibraryID()) == 0)
			fout.write((char*)&book, sizeof(book));
		else
			fout.write((char*)&temp1, sizeof(temp1));
	}
	fin.close();
	fout.close();
	remove("Books.dat");
	rename("Temp.dat", "Books.dat");
}

void Book::deleteBookByLibraryID(Book book) {
	fstream fin, fout;
	fin.open("Books.dat", ios::in | ios::binary);
	fout.open("Temp.dat", ios::out | ios::trunc | ios::binary);
	Book temp, temp1;
	while (fin.read((char*)&temp, sizeof(temp))) {
		temp1 = temp;
		if (_strcmpi(temp1.getlibraryID(),book.getlibraryID()) == 0)
			continue;
		fout.write((char*)&temp1, sizeof(temp1));
	}
	fin.close();
	fout.close();
	remove("Books.dat");
	rename("Temp.dat", "Books.dat");
}

void Book::getAllBooks() {
	fstream f;
	f.open("Books.dat", ios::in | ios::binary);
	Book temp, temp1;
	while (f.read((char*)&temp, sizeof(temp))) {
		temp1 = temp;
		temp1.getAllAttributes();
	}
	f.close();
}

Book::~Book()
{
}
