#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//user inputs the username to add credit to if the current user is an admin
//otherwise credit will be added to the current account
void addcredit(string* currentUser) {
	string username;
	int credit;
	if (currentUser[1] == "AA") {
		cout << "Enter the user you want to add credit too: ";
		cin >> username;
	}
	cout << "Enter the amount of credit to add: ";
	cin >> credit;

	//todo actually update the credit
}