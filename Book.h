#pragma once
#include <string>
using namespace std;
class Book
{
	string ISBN, publisher, libraryID, title, author;
	bool isIssued;
	int edition;
	float price;
	void bookEdit(Book);
public:
	Book() {
		ISBN = "";
		isIssued = false;
		publisher = "";
		libraryID = "";
		title = "";
		author = "";
		edition = 0;
		price = 0.00;
	}

	void setISBN(string);
	void setPublisher(string);
	void setlibraryID(string);
	void setTitle(string);
	void setAuthor(string);
	void setEdition(int);
	void setPrice(float);
	void setIssue(bool);

	string getISBN() const;
	string getPublisher() const;
	string getlibraryID() const;
	string getTitle() const;
	string getAuthor() const;
	int getEdition() const;
	float getPrice() const;
	bool isBookIssued() const;

	void setBookAttributes(string, string, string, string, string, int, float);

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
	~Book();
};

