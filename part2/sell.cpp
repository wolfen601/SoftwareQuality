#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool findEvent(string eventTitle);
void sellTickets(string* currenUser,string eventTitle,double price, int tickets);
string addPadding(string type,string username);
string addPadding(string type,int credit);
string addPadding(double token);
string removePadding(string token);

//asks user for event title, number of tickets to sell, and price of a ticket
//calls the findEvent function, if false is returned the sellTickets function
//is called
void sell(string* currentUser) {
	string eventTitle;
	double price;
	int tickets;

	string clear;
	getline(cin,clear);
	cout << "Enter event title: ";
	getline(cin,eventTitle);
	cout << "Enter number of tickets to sell: ";
	cin >> tickets;
	cout << "Enter the price of each ticket: ";
	cin >> price;

	if(findEvent(eventTitle) == true) {
		cout << "Error: Event title already exists" << endl;
	} else {
		sellTickets(currentUser,eventTitle,price,tickets);

	}
}

//adds the event info to the available tickets file
void sellTickets(string* currentUser,string eventTitle,double price,int tickets) {
	string priceString;
	string ticketString;
	string username;
	ofstream output("availableTickets.txt",ios_base::app);

	username = addPadding("username",currentUser[0]);
	eventTitle = addPadding("event",eventTitle);
	priceString = addPadding(price);
	ticketString = addPadding("tickets",tickets);

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