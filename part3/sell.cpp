#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool findEvent(string eventTitle);
void sellTickets(string* currenUser,string eventTitle,double price, int tickets);
string addPadding(string type,string username);
string addPadding(int credit);
string addPadding(string type,double token);
string removePadding(string token);
void dtfUpdater(string opCode,string user1,string str,string type,double credit,int tickets);

//asks user for event title, number of tickets to sell, and price of a ticket
//calls the findEvent function, if false is returned the sellTickets function
//is called
void sell(string* currentUser) {
	string eventTitle;
	double price;
	int tickets;
	//string clear;

	if(currentUser[1] == "BS") {
		cout << "Error: Buy standard users cannot sell tickets" << endl;
		return;
	}

	//getline(cin,clear);
	cout << "Enter event title: ";
	//getline(cin,eventTitle);
	cin >> eventTitle;
	if(eventTitle.length() > 25) {
		cout << "Error: max character limit of 25 exceeded" << endl;
		return;
	}else if(findEvent(eventTitle) == true) {
		cout << "Error: Event title already exists" << endl;
		return;
	}

	cout << "Enter number of tickets to sell: ";
	if(cin >> tickets) {

	} else {
		cout << "Error: tickets must be entered as a number" << endl;
		cin.clear();
		return;
	}
	if(tickets > 100) {
		cout << "Error: max number of tickets exceeded" << endl;
		return;
	}

	cout << "Enter the price of each ticket: ";
	if (cin >> price) {

	} else {
		cout << "Error: price must be entered as number" << endl;
		cin.clear();
		return;
	}
	if (price > 999.99) {
		cout << "Error: max price on each ticket exceeded" << endl;
		return;
	}
	sellTickets(currentUser,eventTitle,price,tickets);
	dtfUpdater("03",currentUser[0],eventTitle,"",price,tickets);
}

//adds the event info to the available tickets file
void sellTickets(string* currentUser,string eventTitle,double price,int tickets) {
	string priceString;
	string ticketString;
	string username;
	ofstream output("availableTickets.txt",ios_base::app);

	username = addPadding("username",currentUser[0]);
	eventTitle = addPadding("event",eventTitle);
	priceString = addPadding("price",price);
	ticketString = addPadding(tickets);

	//priceString = to_string(price);

	output << endl << eventTitle << " " << username << " "
		<< ticketString << " " << priceString;

	output.close();
	cout << "Ticket successfully registered!" << endl;
}

//reads through the available tickets file line by line
//uses substr to grab the event title from a line and compares
//it to the title entered by the user
//returns true if an event with the same name is found
//and false is the entered name is unique
bool findEvent(string eventTitle) {
	string titleCompare;
	string fileLine;

	ifstream inputfile("availableTickets.txt");

	while(!inputfile.eof()) {
		getline(inputfile,fileLine);
		titleCompare = fileLine.substr(0,18);

		titleCompare = removePadding(titleCompare);
		if (eventTitle == titleCompare) {
			inputfile.close();
			return true;
		}
	}
	inputfile.close();
	return false;
}