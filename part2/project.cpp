#include <iostream>
#include <string>

using namespace std;

string* login();
void create(string* currentUser);
void buy(string* currentUser);
void logout();
void sell(string* currentUser);
void dtfUpdater(string opCode,string username,string type_user2,int credit);
void remove(string* currentUser);
void refund(string* currentUser);
void addcredit(string* currentUser);

//Compile program using the included makefile which compiles all files with c++11 enabled
// >>make
// >>./a.out
int main() {
	string* currentUser = new string[3];
	string command;
	string username;
	bool loggedIn = false;
	//TODO admin check for create and remove
	//Daily Transaction file updates

	//Enter command loop that only accepts login or quit
	//if login is accepted the loggedIn boolean is set to true
	//and the program enters the inner while loop
	while(true) {
		cout << "Enter a command: ";
		cin >> command;
		if (command == "login") {
			currentUser = login();
			if (currentUser[0] != "--error--") {
				cout <<"Log in successful!" << endl;
				loggedIn = true;
			} else {
				cout << "Log in failed, user not found" << endl;;
			}
		}  else if(command == "quit") {
			break;
		}
		//Command loop for a user when logged in, that accepts other commands
		while(loggedIn == true) {
			cout << "Enter a command: ";
			cin >> command;
			if (command == "create") {
				create(currentUser);
			} else if(command == "buy") {
				buy(currentUser);
			} else if(command == "sell") {
				sell(currentUser);
			} else if(command == "delete") {
				remove(currentUser);
			} else if(command == "addcredit") {
				addcredit(currentUser);
			} else if(command == "refund") {
				refund(currentUser);
			} else if(command == "logout") {
				//converts users credit to int and calls dtfUpdater
				//sets loggedIn boolean to false so the program returns
				//to the outer while loop
				int credit = stoi(currentUser[2]);
				dtfUpdater("00",currentUser[0],currentUser[1],credit);
				loggedIn = false;
				cout << currentUser[0] << " has been logged out successfully" << endl;
			}
		}
	}
}
