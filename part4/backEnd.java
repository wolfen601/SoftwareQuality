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
	public static void combine() {
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
	}

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
				if (opCode == 1) {
					create(fileLine);
				} else if(opCode == 3) {
					sell(fileLine);
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

	//Writes a new event to the new available tickets file, checks if 
	//event already exists in old tickets
	public static void sell(String fileLine) {
		try {
			String line;
			String username;
			boolean eventExists = false;
			FileReader oldTickets = new FileReader("oldAvailableTickets.txt");
			BufferedReader oldTicketsReader = new BufferedReader(oldTickets);
			FileWriter writer = new FileWriter("newAvailableTickets.txt",true);	

			//check if event already exists in old tickets file
			while((line = oldTicketsReader.readLine()) != null) {
				username = line.substring(0,18);
				if(username.equals(fileLine.substring(0,18))) {
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
}