#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool findUser(string username);

void refund(string* currentUser) {
	string user1;
	string user2;
	if (currentUser[1] == "AA") {
		cout << "Enter username of user to be refunded: ";
		cin >> user1;
		cout << "Enter username of the other user: ";
		cin >> user2;
		if((findUser(user1) == true) && findUser(user2) == true) {
			//todo addcredit to user1, remove creidt from user2
		} else {
			cout << "Error: both users must be existing users" << endl;
		}
	} else {
		cout << "Error: This action can only be preformed by an admin" << endl;
	}
}