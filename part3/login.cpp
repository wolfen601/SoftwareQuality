#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

string* findUser(string username);
string removePadding(string token);

//function asks user to enter their existing username, then calls the findUser function
//if the function does not return null the currentUser vector is returned to the main
//file so the current users information can be used in other functions
//sets the username as '--error--' if the username is not found
string* login() {
	string username;
	string* currentUser = new string[3];

	cout << "Enter username: ";
	cin >> username;
	currentUser = findUser(username);

	if (currentUser[0] != "--error--")
	{
		cout << currentUser[0] << " " << currentUser[1] << " " << currentUser[2] << endl;
		return currentUser;
	} else {
		return currentUser;
	}
}

//Reads the currentUsers.txt file line by line and tokenizes each line
//at the space, if the first token of the line(the username) mathes the
//entered username then the username, account type and account balance
//are stored in the currentUsers vector and returned to the login function 
//otherwise NULL is returned
string* findUser(string username) {
	string* currentUser = new string[3];
	ifstream inputfile("currentUsers.txt");
	string fileLine;
	string token;

	while(!inputfile.eof()) {
		getline(inputfile, fileLine);
		istringstream iss(fileLine);

		for (int i = 0; i < 3; ++i) {
			getline(iss,token,' ');
			token = removePadding(token);
			currentUser[i] = token;
		}

		if (username == currentUser[0]) {
			inputfile.close();
			return currentUser;
		}
	}
	inputfile.close();
	currentUser[0] = "--error--";
	return currentUser;
}