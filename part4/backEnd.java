import java.io.*;

//Since our front end handles editing currency and ticket amount, the back end will handle
//combining the transaction file of multiple front end sessions to create a master 
//users file and tickets file that contain all users and events from all front ends.
//as well as ensuring that there are not multiple users or events with the same name
//after merging the transaction files
public class backEnd {
	public static void main(String[] args) {
		combine();
		readDTF();
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
	//if either opCode 1 or 3 is found, all other codes are handled in the front end
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
					writeUF(fileLine);
				} else if(opCode == 3) {
					writeTF(fileLine);
				}
			}

			reader.close();
		} catch(IOException e) {

		}
	}

	//Writes a new created user to the new current users file
	public static void writeUF(String fileLine) {
		try {
			FileWriter writer = new FileWriter("newCurrentUsers.txt",true);

			writer.write(fileLine+"\n");
			writer.close();
		} catch(IOException e) {

		}
	}

	//Writes a new event to the new available tickets file
	public static void writeTF(String fileLine) {
		try {
			FileWriter writer = new FileWriter("newAvailableTickets.txt",true);

			writer.write(fileLine+"\n");
			writer.close();
		} catch(IOException e) {

		}
	}
}