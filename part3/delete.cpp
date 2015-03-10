#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void removeUser(string username);
void removeSales(string username);
string* findUser(string username);
void dtfUpdater(string opCode,string user1,string str,string type,double credit,int tickets);

//checks if user has permission to delete
//checks if the logged in user is the one being deleted
//calls removeUser and removeSales functions
void remove(string* currentUser) {
	string username;
	string* deleteUser;

	if(currentUser[1] != "AA") {
		cout << "Error: This action can only be preformed by an admin" << endl;
		return;
	}

	cout << "Enter the username of the account you want to delete: ";
	cin >> username;
	deleteUser = findUser(username);
	if (username == currentUser[0]) {
		cout << "Error: Cannot delete the currently logged in user" << endl;
	} else {
		cout << "Account successfully deleted." << endl;
		removeUser(username);
		removeSales(username);
		double credit = stod(deleteUser[2]);
		dtfUpdater("02",username,"",deleteUser[1],credit,0);
	}
}

//reads in currentUsers line by line, if the line contains
//the username to be deleted that line is not copied into the file
//string all other lines are copied into the file string
//the text file is cleared and the file string is written to it
void removeUser(string username) {
	ifstream inputfile("currentUsers.txt");
	string fileLine;
	string file = "";
	while(!inputfile.eof()) {
		getline(inputfile,fileLine);
		if(fileLine.find(username) != string::npos) {

		} else {
			file += fileLine;
			file += "\n";
		}
	}
	inputfile.close();
	ofstream output("currentUsers.txt");
	output << file;
}

//this function will work similarly reading through the available
//tickets file, if the event was created by the user being deleted
//that line will be skipped while all other lines are copied
void removeSales(string username) {

}