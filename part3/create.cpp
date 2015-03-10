#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//from login: check if user already exists
string* findUser(string username);
void dtfUpdater(string opCode,string user1,string str,string type,double credit,int tickets);
string addPadding(string type,string username);
string addPadding(string type,double token);

//Asks user for a new username and account type, checks if the username is valid
//and and not already being used.
//writes the user name, account type and balance of 0 to the current users file
//as well as logs the transaction in the daily transaction file
void create(string* currentUser) {
	string username;
	string credit;
	string type;
	int len;
	string* userExists;

	if (currentUser[1] != "AA") {
		cout << "Error: Not an admin, cannot create accounts." << endl;
		return;
	}

	cout << "Enter username of new account: ";
	cin >> username;

	userExists = findUser(username);
	len = username.length();
	if(len > 15) {
		cout << "Error: username exceeds 15 characters" << endl;
		return;
	} else if(len < 3) {
		cout << "Error: username must be at least 3 characters" << endl;
		return;
	} else if(username.find("-") != std::string::npos) {
		cout << "Error: username cannot contain dashes '-'" << endl;
		return;
	} else if(userExists[0] != "--error--") {
		cout << "Error: user already exists" << endl;
		return;
	} 
	cout << "Enter account type: ";
	cin >> type;

	ofstream output("currentUsers.txt",ios_base::app);

	username = addPadding("username",username);
	credit = addPadding("credit",0);
	output << endl << username << " " << type << " " << credit;
	output.close();

	//double balance = 0;
	dtfUpdater("01",username,"",type,0,0);
	cout << "Account successfully created!" << endl;
}