#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string* findUser(string username);
string addPadding(string type,double token);
void dtfUpdater(string opCode,string user1,string str,string type,double credit,int tickets);

//user inputs the username to add credit to if the current user is an admin
//otherwise credit will be added to the current account
int addcredit(string* currentUser,int session) {
	string username;
	double credit;
	string* userInfo;
	if (currentUser[1] == "AA") {
		cout << "Enter the user you want to add credit to: ";
		cin >> username;
		userInfo = findUser(username);
		if (userInfo[0] != username) {
			cout << "Error: User must be existing user" << endl;
			return session;
		}
	} else {
		userInfo = currentUser;
	}
	cout << "Enter the amount of credit to add: ";
	cin >> credit;
	if (session+credit > 1000) {
		cout << "Error: Can only add 1000 dollars of credit at once" << endl;
		return session;
	}
	double balance;
	balance = stod(userInfo[2]);
	if(balance+credit > 999999.99) {
		cout << "Error: Transaction causes you to exceed to max credit limit" << endl;
		return session;
	}

	ifstream inputfile("currentUsers.txt");
	string balanceString;
	string fileLine;
	string file = "";
	//finds user, updates their credit, rewrites the textfile
	while(!inputfile.eof()) {
		cin.clear();
		getline(inputfile,fileLine);
		if(fileLine.find(userInfo[0]) != string::npos) {
			balance = stoi(userInfo[2]);
			balance = balance + credit;
			balanceString = addPadding("credit",balance);
			fileLine.replace(19,9,balanceString);
		}
		file += fileLine;
		file += "\n";
	}
	inputfile.close();
	ofstream output("currentUsers.txt");
	output << file;
	output.close();

	cout << "Credit added successfully" << endl;

	session += credit;
	if (currentUser[1] == "AA") {
		dtfUpdater("06",username,"",userInfo[1],credit,0);
	} else {
		dtfUpdater("06",currentUser[0],"",currentUser[1],credit,0);
	}
	return session;
}