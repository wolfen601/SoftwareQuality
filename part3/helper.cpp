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
string addPadding(int token) {
	string temp;
	string creditString = "";
	temp = to_string(token);
	int len = temp.length();

	len = 3 - len;

	for (int i = 0; i < len; ++i) {
		creditString += "0";
	}
	creditString += temp;
	return creditString;
}

//adds leading zeros but takes a double as an argument
//for number values that need decimal places
//uses string.erase to remove all but 2 decimal places
string addPadding(string type,double token) {
	string temp;
	string priceString = "";
	temp = to_string(token);
	int len;
	temp.erase(temp.length()-4,temp.length());
	len = temp.length();
	if(type == "price") {
		len = 6 - len;
	} else if(type == "credit") {
		len = 9 - len;
	}

	for (int i = 0; i < len; ++i) {
		priceString += "0";
	}
	priceString += temp;
	return priceString;
}

//updates the daily transaction file
//if statement determines how the data is written based on what data is in the transaction
//whether a transaction log has 1 or 2 users etc..
void dtfUpdater(string opCode,string user1,string str,string type,double credit,int tickets) {
	ofstream output("dailyTransactionFile.txt",ios_base::app);
	string creditString;
	string ticketString;
	output << endl << opCode << " ";
	if((opCode == "01") || (opCode == "02") || (opCode == "06") || (opCode == "00")) {
		user1 = addPadding("username",user1);
		output << user1 << " " << type << " ";
		creditString = addPadding("credit",credit);
		output << creditString;
	} else if(opCode == "05") {
		user1 = addPadding("username",user1);
		str = addPadding("username",str);
		creditString = addPadding("credit",credit);
		output << user1 << " " << str << " " << creditString;
	} else if((opCode == "03") || (opCode == "04")) {
		str = addPadding("event",str);
		user1 = addPadding("username",user1);
		creditString = addPadding("price",credit);
		ticketString = addPadding(tickets);
		output << str << " " << user1 << " " << ticketString
			<< " " << creditString;
	}
	output.close();
}