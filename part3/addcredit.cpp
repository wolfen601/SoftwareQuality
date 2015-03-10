#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string* findUser(string username);
string addPadding(string type,double token);

//user inputs the username to add credit to if the current user is an admin
//otherwise credit will be added to the current account
int addcredit(string* currentUser,int session) {
	string username;
	int credit;
	string* userInfo;
	if (currentUser[1] == "AA") {
		cout << "Enter the user you want to add credit too: ";
		cin >> username;
		userInfo = findUser(username);
		if (userInfo[0] != username) {
			cout << "Error: User must be existing user" << endl;
			return session;
		}
	}
	cout << "Enter the amount of credit to add: ";
	cin >> credit;
	if (session+credit > 1000) {
		cout << "Error: Can only add 1000 dollars of credit at once" << endl;
		return session;
	}
	int balanceInt;
	balanceInt = stoi(userInfo[2]);
	if(balanceInt+credit > 999999.99) {
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
			balanceInt = stoi(userInfo[2]);
			balanceInt = balanceInt + credit;
			balanceString = addPadding("credit",balanceInt);
			fileLine.replace(19,9,balanceString);
		}
		file += fileLine;
		file += "\n";
	}
	ofstream output("currentUsers.txt");
	output << file;

	cout << "Credit added asuccessfully" << endl;

	session += credit;
	return session;
}