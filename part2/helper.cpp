#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

//removes the dashes from usernames and event titles after being read in from
//text files
string removePadding(string token) {
	char rem[] = "-";

	for (int i = 0; i < 2; i++) {
		token.erase(remove(token.begin(),token.end(),rem[i]),token.end());
	}
	return token;
}

//adds dashes to usernames and event titles to be written
//into text files
//calculates the number of dashes needed based on the max length
//of the text field specified in the project doc
string addPadding(string type,string token) {
	int len = token.length();
	if (type == "username") {
		len = 15 - len;
	} else if(type == "event") {
		len = 18 - len;
	}
	for (int i = 0; i < len; ++i) {
		token += "-";
	}
	return token;
}

//converts integers to strings so leading zeros can be added
//(with an int leading zeros are removed)
//to credit ticket numbers or price values
string addPadding(string type,int token) {
	string temp;
	string creditString = "";
	temp = to_string(token);
	int len = temp.length();

	if(type == "credit") {
		len = 9 - len;
	} else if(type == "tickets") {
		len = 3 - len;
	} else if(type == "price") {
		len = 3 - len;
	}

	for (int i = 0; i < len; ++i) {
		creditString += "0";
	}
	creditString += temp;
	return creditString;
}

//adds leading zeros but takes a double as an argument
//for number values that need decimal places
//uses string.erase to remove all but 2 decimal places
string addPadding(double token) {
	string temp;
	string priceString = "";
	temp = to_string(token);
	temp.erase(5,9);
	int len = temp.length();

	len = 6 - len;

	for (int i = 0; i < len; ++i) {
		priceString += "0";
	}
	priceString += temp;
	return priceString;
}

//updates the daily transaction file
//if statement determines how the data is written based on what data is in the transaction
//whether a transaction log has 1 or 2 users etc..
void dtfUpdater(string opCode,string username,string type_user2,int credit) {
	ofstream output("dailyTransactionFile.txt",ios_base::app);
	if((opCode == "01") || (opCode == "02") || (opCode == "06") || (opCode == "00")) {
		string creditString;
		output << opCode << " ";
		username = addPadding("username",username);
		output << username << " " << type_user2 << " ";
		creditString = addPadding("credit",credit);
		output << creditString << endl;
	}
	output.close();
}