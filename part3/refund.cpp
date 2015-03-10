#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string* findUser(string username);
string addPadding(string type,double token);
void dtfUpdater(string opCode,string user1,string str,string type,double credit,int tickets);

//Checks if current user is an admin, asks for names of both users.
//checks if users exist, removes credit from user2 and adds it to user1
void refund(string* currentUser) {
	string user1;
	string user2;
	string* user1Info;
	string* user2Info;
	double credit;
	if (currentUser[1] == "AA") {
		cout << "Enter username of user to be refunded: ";
		cin >> user1;
		cout << "Enter username of the other user: ";
		cin >> user2;

		user1Info = findUser(user1);
		user2Info = findUser(user2);
		if((user1 != user1Info[0]) || (user2 != user2Info[0])) {
			cout << "Error: both users must be existing users" << endl;
			return;
		}

		cout << "Enter the amount to refund: "; 
		if(cin >> credit) {
			
		} else {
			cout << "Error: Amount must be a number" << endl;
		}

		double balance;
		balance = stod(user2Info[2]);
		if (balance < credit) {
			cout << "Error: User does not have enough credit to refund" << endl;
			return;
		}

		ifstream inputfile("currentUsers.txt");
		string balanceString;
		string fileLine;
		string file = "";
		//finds both users, updates their credit, rewrites the textfile
		while(!inputfile.eof()) {
			cin.clear();
			getline(inputfile,fileLine);
			if(fileLine.find(user1Info[0]) != string::npos) {
				balance = stoi(user1Info[2]);
				balance = balance + credit;
				balanceString = addPadding("credit",balance);
				fileLine.replace(19,9,balanceString);
			}
			if(fileLine.find(user2Info[0]) != string::npos) {
				balance = stoi(user2Info[2]);
				balance = balance - credit;
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

		cout << "Credit refunded successfully" << endl;
		dtfUpdater("05",user1Info[0],user2Info[0],"",credit,0);
	} else {
		cout << "Error: This action can only be performed by an admin" << endl;
	}
}