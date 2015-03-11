#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string removePadding(string token);
bool buyTickets(string* currentUser, string eventTitle,int tickets,string seller);
void subtractTickets(string eventTitle, int tickets,int currentTickets);
void subtractCredit(string* currentUser,int totalPrice);
string addPadding(string type, double token);
void dtfUpdater(string opCode,string user1,string str,string type,double credit,int tickets);
string addPadding(int token);

//asks for event title, number of tickets and sellers username
//calls the buyTickets funciton
void buy(string* currentUser) {
	string eventTitle;
	int tickets;
	string seller;
	bool confirm;

	if(currentUser[1] == "SS") {
		cout << "Error: Sell standard account cannot buy tickets." << endl;
		return;
	}
	string clear;
	getline(cin,clear);
	cout << "Enter event title: ";
	getline(cin,eventTitle);
	cout << "Enter number of tickets to purchase: ";
	if(cin >> tickets) {
	} else {
		cout << "Error: tickets must be entered as a number" << endl;
		cin.clear();
		return;
	}
	cout << "Enter sellers username: ";
	cin >> seller;

	buyTickets(currentUser,eventTitle,tickets,seller);
}

//reads through available tickets file line by line, uses the string.substr command
//and the text files structure to get the event title, seller username and number of 
//tickets from each line
//compares the event title, the ticket amount and the seller username of each line with
//what the user entered, if all match the total price is printed and the user is asked
//to confirm
//if the user enters yes then subtractTickets and subtractCredit are called
bool buyTickets(string* currentUser,string eventTitle,int tickets,string seller) {
	string titleCompare;
	string sellerCompare;
	string ticketsString;
	int ticketCompare;
	string price;
	double ticketPrice;
	string fileLine;
	double credit;

	ifstream inputfile("availableTickets.txt");

	while(!inputfile.eof()) {
		getline(inputfile, fileLine);
		titleCompare = fileLine.substr(0,18);
		sellerCompare = fileLine.substr(19,15);
		ticketsString = fileLine.substr(35,3);
		ticketCompare = stoi(ticketsString);
		//istringstream iss(fileLine);

		titleCompare = removePadding(titleCompare);
		sellerCompare = removePadding(sellerCompare);
		if((eventTitle == titleCompare) && (tickets <= ticketCompare) && (seller == sellerCompare)) {
			cout << ticketCompare << " Tickets available" << endl;
			string confirm;
			price = fileLine.substr(39,6);
			ticketPrice = stod(price);
			cout << "Event found: price per ticket -> " << ticketPrice 
				<< " Total price -> " << ticketPrice*tickets <<	endl;
			if(tickets > ticketCompare){
				cout << "Error: Ticket amount entered exceeds the amount of tickets available" << endl;
				return false;
			}
			credit = stod(currentUser[2]);
			if(tickets*ticketPrice > credit) {
				cout << "Error: Not enough credit to complete purchase" << endl;
				return false;
			}
			cout << "Do you want to complete this purchase (yes or no): ";
			cin >> confirm;
			if(confirm == "yes") {
				subtractTickets(eventTitle,tickets,ticketCompare);
				subtractCredit(currentUser,ticketPrice*tickets);
				inputfile.close();
				cout << "Purchase successful!" << endl;
				dtfUpdater("04",seller,eventTitle,"",ticketPrice,tickets);
				return true;
			} else if(confirm == "no") {
				cout << "Transaction cancelled" << endl;
				inputfile.close();
				return false;
			} else {
				inputfile.close();
				return false;
			}
		}
	}
	cout << "Error: Invalid purchase, ensure that event and seller name are correct, and that enough tickets are available" << endl;
}

//reads the available tickets file in line by line, checks if the event on each
//line matches the event that tickets were purchased for and if so uses string.replace
//to change the total amount of tickets to what it now should be.
//each line is then added to the file string
//once the end of the file is reached the available tickets file is cleared and 
//the file string is written to the text file
void subtractTickets(string eventTitle,int tickets,int currentTickets) {
	ifstream inputfile("availableTickets.txt");
	string fileLine;
	string file = "";

	while(!inputfile.eof()) {
		getline(inputfile, fileLine);
		//cout << fileLine;
		if (fileLine.find(eventTitle) != string::npos) {
			tickets = currentTickets - tickets;
			string ticketString = to_string(tickets); 
			ticketString = addPadding(tickets);
			fileLine.replace(35,3,ticketString);
			//cout << fileLine;
		}
		file += fileLine;
		file += "\n";
	}
	//cout << file << endl;
	inputfile.close();
	ofstream output("availableTickets.txt");
	output << file << endl;
	output.close();
}

//This function works in the same way as subtractTickets except
//it finds the current user and subtracts the amount they spent
//on this transaction from their credit, then clears the users text file
//and re-rwites it with the edited value
void subtractCredit(string* currentUser,int totalPrice) {
	ifstream inputfile("currentUsers.txt");
	string fileLine;
	string file = "";
	double balanceInt;
	string balanceString;

	while(!inputfile.eof()) {
		getline(inputfile,fileLine);
		if(fileLine.find(currentUser[0]) != string::npos) {
			balanceInt = stoi(currentUser[2]);
			balanceInt = balanceInt - totalPrice;
			balanceString = addPadding("credit", balanceInt);
			fileLine.replace(19,9,balanceString);
		}
		file += fileLine;
		file += "\n";
	}
	//cout << file << endl;
	inputfile.close();
	ofstream output("currentUsers.txt");
	output << file << endl;
	output.close();
}