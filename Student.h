#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
using namespace std;

fstream f;

class Student
{
private:
	class booksIssued
	{
	public:
		char LibraryID[100];
		char ISBN[13];
		time_t issueTime;
		booksIssued() {
			memset(&LibraryID, '\0', sizeof(LibraryID));
			memset(&ISBN, '\0', sizeof(ISBN));
		}
	};
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

	void addStudent(Student& obj) {
		// char* temp = getMemberID();
		// cin.get(obj.employeeID,10);
		cout << "Enter Student ID" << endl;
		cin >> obj.studentID;
		// cin.get(obj.membershipID,10);
		cout << "Enter Membership ID" << endl;
		cin >> obj.membershipID;
		if (existingStudent() == false) {		//no existing ID of the employee
			f.open("StudentData.dat", ios::out | ios::app | ios::binary);
			f.write((char*)&obj, sizeof(obj));
			f.close();
			cout << "Student Added" << endl;
		}
		else {
			cout << "Already Registered." << endl;
		}

		cout << endl;
	}

	void deleteStudent(Student& obj) {
		fstream fin;
		fstream fout;
		Student temp;
		fin.open("temp.dat", ios::in | ios::out | ios::binary);
		fout.open("StudentData.dat", ios::in | ios::out | ios::app | ios::binary);
		fin.seekg(0, ios::beg);
		while (fout.read((char*)&temp, sizeof(temp))) {
			if (strcmpi(obj.getMemberID(), temp.getMemberID()) == 0) {
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

	void addBook(Student& b) {


		int nBooks;
		cout << "*** WARNING: A student cannot have more than 5 books issued at the same time ****" << endl;
		cout << "Number of books being issued: ";
		cin >> nBooks;
		if (nBooks <= 5 && bookCount <= 5)
		{

			while (nBooks--) {
				// cout<<"1"<<endl;
				++bookCount;
				// cout<<"bookCount: "<<bookCount<<endl;
				int idx = bookCount - 1;
				cout << "idx: " << idx << endl;
				cout << "Enter book Library ID:";
				cin >> b.Books[idx].LibraryID;
				cout << "Enter ISBN code:";
				cin >> b.Books[idx].ISBN;
				b.Books[idx].issueTime = time(NULL);
			}
			fstream ftemp;
			ftemp.open("temp.dat", ios::in | ios::out | ios::binary | ios::app);
			f.open("StudentData.dat", ios::in | ios::binary);
			Student temp;
			while (f.read((char*)&temp, sizeof(temp))) {

				if (strcmpi(b.getMemberID(), temp.getMemberID()) == 0) {
					ftemp.write((char*)&b, sizeof(b));
					continue;
				}
				ftemp.write((char*)&temp, sizeof(temp));
			}
			f.close();
			ftemp.close();
			cout << "Book added" << endl;
			remove("StudentData.dat");
			rename("temp.dat", "StudentData.dat");
			// cout<<bookCount<<endl;

		}


		else {

			cout << "LIMIT REACHED" << endl;
		}

		cout << endl;

	}

	bool existingStudent() {
		Student temp;
		f.open("StudentData.dat", ios::in | ios::binary);
		while (f.read((char*)&temp, sizeof(temp))) {
			if (strcmpi(temp.studentID, getStudentID()) == 0) {
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
			timeInfo = localtime(&obj.Books[i].issueTime);
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

