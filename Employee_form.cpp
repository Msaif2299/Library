#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

fstream f;
 
class Employee
{
private:
	class booksIssued
	{
	public:
		char LibraryID[100];
		char ISBN[13];
		time_t issueTime;
		booksIssued(){
			memset(&LibraryID,'\0',sizeof(LibraryID));
			memset(&ISBN,'\0',sizeof(ISBN));
		}
	};
	char employeeID[10];
	char membershipID[10];
	int bookCount;
	booksIssued Books[100];

public:
	Employee(){
		memset(&employeeID,'\0',sizeof(employeeID));
		memset(&membershipID,'\0',sizeof(membershipID));
		bookCount = 0;
		// addEmployee();

	}
	int getBookCount(){
		return bookCount;
	}
	
	char* getEmployeeID(){
		return employeeID;
	}

	char* getMemberID(){
		return membershipID;
	}

	booksIssued* getBooksIssued(){
		return Books;
	}

	// void alterEmployeeID(){
	// 	cin.get(employeeID,10);
	// }

	// void alterMembershipID(){
	// 	cin.get(membershipID,10);
	// }

	void addEmployee(Employee& obj){
		// char* temp = getMemberID();
		// cin.get(obj.employeeID,10);
		cin>>obj.employeeID;
		// cin.get(obj.membershipID,10);
		cin>>obj.membershipID;
		if(existingEmployee() == false){		//no existing ID of the employee
			f.open("EmployeeData.dat",ios::out|ios::app|ios::binary);
			f.write((char*)&obj,sizeof(obj));
			f.close();
			cout<<"Employee Added"<<endl;
		}
		else{
			cout<<"Already Registered."<<endl;
		}
	}

	void deleteEmployee(Employee& obj){
		fstream fin;
		fstream fout;
		Employee temp;
		fin.open("temp.dat",ios::in|ios::out|ios::binary);
		fout.open("EmployeeData.dat",ios::in|ios::out|ios::app|ios::binary);
		fin.seekg(0,ios::beg);
		while(fout.read((char*)&temp,sizeof(temp))){
			if(strcmpi(obj.getMemberID(),temp.getMemberID()) == 0){
				cout<<obj.employeeID<<" "<<temp.employeeID;
				continue;
			}
			else{
				fin.write((char*)&temp,sizeof(temp));
			}
		}
		fin.close();
		fout.close();
		remove("EmployeeData.dat");
		rename("temp.dat","EmployeeData.dat");

	}

	void addBook(Employee& b){
		int nBooks;
		cout<<"Number of books being issued: ";
		cin>>nBooks;
		while(nBooks--){
			// cout<<"1"<<endl;
		++bookCount;
		// cout<<"bookCount: "<<bookCount<<endl;
		int idx = bookCount - 1;
		cout<<"idx: "<<idx<<endl;
		cin>>b.Books[idx].LibraryID;
		cin>>b.Books[idx].ISBN;
		b.Books[idx].issueTime = time(NULL);
		}
		fstream ftemp;
		ftemp.open("temp.dat", ios::in | ios::out | ios::binary | ios::app);
		f.open("EmployeeData.dat", ios::in | ios::binary);
		Employee temp;
		while(f.read((char*)&temp,sizeof(temp))){

			if(strcmpi(b.getMemberID(),temp.getMemberID()) == 0){
				ftemp.write((char*)&b,sizeof(b));
				continue;
			}
			ftemp.write((char*)&temp,sizeof(temp));
		}
		f.close();
		ftemp.close();
		cout<<"Book added"<<endl;
		remove("EmployeeData.dat");
		rename("temp.dat","EmployeeData.dat");
		// cout<<bookCount<<endl;
	}

	bool existingEmployee(){
		Employee temp;
		f.open("EmployeeData.dat", ios::in | ios::binary);
		while(f.read((char*)&temp,sizeof(temp))){
				if(strcmpi(temp.employeeID,getEmployeeID()) == 0){
					f.close();
					return true;
				}
		}
		f.close();
		return false;

	}

	void showInfo(Employee& obj){
		cout<<"EmployeeID: "<<obj.employeeID<<endl;
		cout<<"MembershipID: "<<obj.membershipID<<endl;
		cout<<"Books issued: ";
		cout<<bookCount<<endl;
		for (int i = 0; i < bookCount; ++i)
		{
			cout<<"LibraryID:	"<<obj.Books[i].LibraryID<<endl;
			cout<<"ISBN:	"<<obj.Books[i].ISBN<<endl;
			struct tm* timeInfo;
			timeInfo = localtime(&obj.Books[i].issueTime);
			cout<<"Issued:	"<<asctime(timeInfo)<<endl;

		}
	}

	void showInformation(){
		f.open("EmployeeData.dat", ios::in | ios::binary);
		Employee temp;
		while(f.read((char*)&temp,sizeof(temp))){
			showInfo(temp);
		}
	}

	
};

int main(){
	// Employee e1,e2;
	// // e1.addEmployee(e1);
	// // e1.deleteEmployee(e1);
	// e1.addEmployee(e1);
	// e1.addBook(e1);
	// // e2.deleteEmployee(e1);
	// // cout<<"list is"<<endl;
	// e1.showInformation();

}