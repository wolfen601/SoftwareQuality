import java.io.*;

//copies all old users and events to the new files, then reads
//the merged daily transaction file to apply the transactions
//create and sell are implemented
public class backEnd {
	public static void main(String[] args) {
		//combine();

		try {
			FileWriter clearUsers = new FileWriter("newCurrentUsers.txt");
			clearUsers.write("");
			FileWriter clearTickets = new FileWriter("newAvailableTickets.txt");
			clearTickets.write("");

			clearTickets.close();
			clearUsers.close();
		} catch(IOException e) {

		}

		copyOldFiles();
		readDTF();
	}

	//preserves the events and users from the oldCurrentUsers and oldAvailableTickets
	//files copies them to the new files
	public static void copyOldFiles() {
		try {
			FileReader oldUsers = new FileReader("oldCurrentUsers.txt");
			FileReader oldTickets = new FileReader("oldAvailableTickets.txt");
			BufferedReader oldUsersReader = new BufferedReader(oldUsers);
			BufferedReader oldTicketsReader = new BufferedReader(oldTickets);
			FileWriter writeUsers = new FileWriter("newCurrentUsers.txt",true);
			FileWriter writeTickets = new FileWriter("newAvailableTickets.txt",true);

			String fileLine;
			while((fileLine = oldUsersReader.readLine()) != null) {
				writeUsers.write(fileLine+"\n");
			}

			while((fileLine = oldTicketsReader.readLine()) != null) {
				writeTickets.write(fileLine+"\n");
			}

			oldTicketsReader.close();
			oldUsersReader.close();
			writeTickets.close();
			writeUsers.close();
		} catch(IOException e) {

		}
	}

	//Combines all files in the directory named dailyTransactionFile(n).txt
	//where n is the number of the file (dailyTransactionFile1.txt etc)
	//creates the mergedDailyTransactionFile.txt
	/*public static void combine() {
		try {
			String fileLine,countString,fileName;
			String str = "dailyTransactionFile";
			int count = 1;
			fileName = str + "1.txt";
		
			while(true) {
				File file = new File(fileName);
				if(file.exists() == true) {
					FileReader f = new FileReader(file);
					BufferedReader reader = new BufferedReader(f);
					//System.out.println(fileName);
					FileWriter writer = new FileWriter("mergedDailyTransactionFile.txt",true);

					while((fileLine = reader.readLine()) != null) {
						writer.write(fileLine+"\n");
					}

					writer.close();
					reader.close();
					count++;
					countString = Integer.toString(count);
					countString += ".txt";
					fileName = str + countString;
				} else {
					break;
				}
			}
		} catch(IOException e) {

		}
	}*/

	//Reads through the merged daily transaction file and checks the opCode that
	//is stored at the start of each line. Calls the appropriate write function
	public static void readDTF() {
		try {
			FileReader file = new FileReader("mergedDailyTransactionFile.txt");
			BufferedReader reader = new BufferedReader(file);

			String line;
			String str;
			String fileLine;
			while((line = reader.readLine()) != null) {
				str = line.substring(0,2);
				fileLine = line.replace(line.substring(0,3),"");

				int opCode = Integer.parseInt(str);
				if (opCode == 1) {			//create
					create(fileLine);
				} else if(opCode == 2) {	//delete
					delete(fileLine);
				} else if(opCode == 3) {	//sell
					sell(fileLine);
				} else if(opCode == 6) { 	//addcredit
					addcredit(fileLine);
				}
			}

			reader.close();
		} catch(IOException e) {

		}
	}

	//Writes a new created user to the new current users file, checks the 
	//oldCurrentUsers file logs an error if the user already exists
	public static void create(String fileLine) {
		try {
			String line;
			String username;
			boolean userExists = false;
			FileReader oldUsers = new FileReader("oldCurrentUsers.txt");
			BufferedReader oldUsersReader = new BufferedReader(oldUsers);
			FileWriter writer = new FileWriter("newCurrentUsers.txt",true);	



			//check if user already exists in old users file
			while((line = oldUsersReader.readLine()) != null) {
				username = line.substring(0,15);
				if(username.equals(fileLine.substring(0,15))) {
					userExists = true;
					System.out.println("Error: Create failed, user already exists");
				}
			}
			if (userExists == false) {
				writer.write(fileLine+"\n");
			}

			oldUsersReader.close();
			writer.close();
		} catch(IOException e) {

		}
	}

	//checks if the user exists in the new users file
	//if the user exists the file is rewritten without that user
	public static void delete(String fileLine) {
		try {
			String line;
			String username;
			String file = "";
			boolean userExists = false;

			FileReader fileName = new FileReader("newCurrentUsers.txt");
			BufferedReader reader = new BufferedReader(fileName);

			//write lines to the file string, check if user exists
			while((line = reader.readLine()) != null) {
				username = line.substring(0,15);
				if (username.equals(fileLine.substring(0,15)) != true) {
					
					file += line;
					file += "\n";
				} else {
					userExists = true;
				}
			}
			reader.close();

			//rewrite file
			if(userExists == true) {
				FileWriter writer = new FileWriter("newCurrentUsers.txt");
				writer.write(file);
				writer.close();
			} else {
				System.out.println("Error: Delete failed, user does not exist");
			}
		} catch(IOException e) {

		}
	}

	//Writes a new event to the new available tickets file, checks if 
	//event already exists in old tickets
	public static void sell(String fileLine) {
		try {
			String line;
			String eventName;
			boolean eventExists = false;
			FileReader oldTickets = new FileReader("oldAvailableTickets.txt");
			BufferedReader oldTicketsReader = new BufferedReader(oldTickets);
			FileWriter writer = new FileWriter("newAvailableTickets.txt",true);	

			//check if event already exists in old tickets file
			while((line = oldTicketsReader.readLine()) != null) {
				eventName = line.substring(0,18);
				if(eventName.equals(fileLine.substring(0,18))) {
					eventExists = true;
					System.out.println("Error: Sell failed, event already exists");
				}
			}
			if (eventExists == false) {
				writer.write(fileLine+"\n");
			}

			oldTicketsReader.close();
			writer.close();
		} catch(IOException e) {

		}
	}

	//removes tickets from the event, removes credit from users account
	public static void buy() {

	}

	//will subtract credit from the first user and add credit
	//to the second user
	public static void refund() {

	}

	//finds the user specified in the daily transaction file
	//adds the amount of credit to their account and rewrites the users
	//file
	public static void addcredit(String fileLine) {
		try {
			String line,username, temp;
			String creditString = "";
			String file = "";
			double credit,addedCredit;
			int len;
			FileReader fileName = new FileReader("newCurrentUsers.txt");
			BufferedReader reader = new BufferedReader(fileName);

			//check if event already exists in old tickets file
			while((line = reader.readLine()) != null) {
				username = line.substring(0,15);
				if(username.equals(fileLine.substring(0,15))) { //if usernames are equal
					//retrieve credit and amount to be added
					credit = Double.parseDouble(line.substring(19,28));
					addedCredit = Double.parseDouble(fileLine.substring(19,28));
					credit = credit + addedCredit;
					temp = Double.toString(credit);

					//add padding
					len = temp.length();
					len = 9 - len;
					for (int i = 0; i<len ;i++ ) {
						creditString += "0";
					}

					//convert to string and write to file string
					creditString += temp;
					line = line.replace(line.substring(19,28),creditString);
					file += line;
					file += "\n";
				} else {
					//make no changes to other lines
					file += line;
					file += "\n";
				}
			}

			//rewrite file
			FileWriter writer = new FileWriter("newCurrentUsers.txt");	
			writer.write(file);
			reader.close();
			writer.close();
		} catch(IOException e) {

		}
	}
}