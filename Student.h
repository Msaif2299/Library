#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <string.h>
#include"Books.h"
#include"Employee.h"
using namespace std;


class Student
{
private:
	
	char studentID[10];
	char membershipID[10];
	int bookCount;
	booksIssued Books[100];

public:
	Student() {
		memset(&studentID, '\0', sizeof(studentID));
		memset(&membershipID, '\0', sizeof(membershipID));
		bookCount = 0;
		// addEmployee();

	}
	int getBookCount() {
		return bookCount;
	}

	char* getStudentID() {
		return studentID;
	}

	char* getMemberID() {
		return membershipID;
	}

	booksIssued* getBooksIssued() {
		return Books;
	}

	// void alterEmployeeID(){
	// 	cin.get(employeeID,10);
	// }

	// void alterMembershipID(){
	// 	cin.get(membershipID,10);
	// }

	int yearExtractor() {
		return (int)(studentID[0] - '0') + (int)(studentID[1] - '0') * 10 + (int)(studentID[2] - '0') * 100 + (int)(studentID[3] - '0') * 1000;
	}

	bool addStudent() {
		cout << "Enter Student ID" << endl;
		cin >> this->studentID;
		cout << "Enter Membership ID" << endl;
		cin >> this->membershipID;
		if (existingStudent() == false) {		//no existing ID of the employee
			if (f.is_open()) {
				f.open("StudentData.dat", ios::out | ios::app | ios::binary);
				f.write((char*)this, sizeof(*this));
				f.close();
				cout << "Student Added" << endl;
				return true;
			}
			else
				cout << "File unable to open!" << endl;
		}
		return false;
		cout << endl;
	}

	void deleteStudent(Student& obj) {
		fstream fin;
		fstream fout;
		Student temp;
		fin.open("temp.dat", ios::in | ios::out | ios::binary);
		fout.open("StudentData.dat", ios::in | ios::out | ios::app | ios::binary);
		if (fin.is_open() && fout.is_open()) {
			fin.seekg(0, ios::beg);
			while (fout.read((char*)&temp, sizeof(temp))) {
				if (_strcmpi(obj.getMemberID(), temp.getMemberID()) == 0) {
					cout << obj.studentID << " " << temp.studentID;
					continue;
				}
				else {
					fin.write((char*)&temp, sizeof(temp));
				}
			}
			fin.close();
			fout.close();
			remove("StudentData.dat");
			rename("temp.dat", "StudentData.dat");
		}
		else
			cout << "File could not be opened!" << endl;

	}

	void addBook(Student& b, const char LibraryID[], const char ISBN[]) {


		int nBooks;
		cout << "*** WARNING: A student cannot have more than 5 books issued at the same time ****" << endl;
		cout << "Number of books being issued: ";
		cin >> nBooks;
		if ((nBooks + bookCount) <= 5)
		{
			
			while (nBooks--) {
				// cout<<"1"<<endl;
				++bookCount;
				// cout<<"bookCount: "<<bookCount<<endl;
				int idx = bookCount - 1;
				cout << "idx: " << idx << endl;
				strcpy_s(b.Books[idx].LibraryID, LibraryID);
				strcpy_s(b.Books[idx].ISBN, ISBN);
				b.Books[idx].issueTime = time(NULL);
			}
			fstream ftemp;
			ftemp.open("temp.dat", ios::in | ios::out | ios::binary | ios::app);
			f.open("Student.dat", ios::in | ios::binary);
			Employee temp;
			while (f.read((char*)&temp, sizeof(temp))) {

				if (_strcmpi(b.getMemberID(), temp.getMemberID()) == 0) {
					ftemp.write((char*)&b, sizeof(b));
					continue;
				}
				ftemp.write((char*)&temp, sizeof(temp));
			}
			f.close();
			ftemp.close();
			cout << "Book added" << endl;
			remove("Student.dat");
			rename("temp.dat", "Student.dat");
		}


		else {

			cout << "LIMIT REACHED" << endl;
		}

		cout << endl;

	}

	void returnIssuedBooks(string libraryID) {
		booksIssued empty;
		int temp;
		vector<booksIssued> newList;
		for (int i = 0; i < bookCount; i++)
			if (_strcmpi(Books[i].LibraryID, libraryID.c_str()) == 0)
				temp = i;
		for (int i = 0; i < bookCount; i++)
			if (temp == i)
				continue;
			else if (i == bookCount - 1)
				newList.push_back(empty);
			else
				newList.push_back(Books[i]);
		for (int i = 0; i < bookCount; i++)
			Books[i] = newList[i];
		bookCount--;
	}

	bool existingStudent() {
		Student temp;
		f.open("StudentData.dat", ios::in | ios::binary);
		while (f.read((char*)&temp, sizeof(temp))) {
			if (_strcmpi(temp.studentID, getStudentID()) == 0) {
				f.close();
				return true;
			}
		}
		f.close();
		return false;

	}

	void showInfo(Student& obj) {
		cout << "StudentID: " << obj.studentID << endl;
		cout << "MembershipID: " << obj.membershipID << endl;
		cout << "Books issued: ";
		cout << bookCount << endl;
		for (int i = 0; i < bookCount; ++i)
		{
			cout << "LibraryID:	" << obj.Books[i].LibraryID << endl;
			cout << "ISBN:	" << obj.Books[i].ISBN << endl;
			struct tm* timeInfo;
			timeInfo = localtime_s(&obj.Books[i].issueTime);
			cout << "Issued:	" << asctime(timeInfo) << endl;

		}
	}

	void showInformation() {
		f.open("StudentData.dat", ios::in | ios::binary);
		Student temp;
		while (f.read((char*)&temp, sizeof(temp))) {
			showInfo(temp);
		}

		cout << endl;
	}


};

