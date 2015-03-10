#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void search() {
	string search;
	cout << "Enter event name or seller username to search: ";
	string clear;
	getline(cin,clear);
	getline(cin,search);

	ifstream inputfile("availableTickets.txt");
	string fileLine;
	while(!inputfile.eof()) {
		getline(inputfile,fileLine);
		if(fileLine.find(search) != string::npos) {
			cout << fileLine << endl;
		}
	}
}