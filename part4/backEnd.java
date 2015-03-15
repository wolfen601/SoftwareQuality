import java.io.*;

public class backEnd {
	public static void main(String[] args) {
		combine();
		readDTF();
	}

	public static void combine() {

	}

	public static void readDTF() {
		try {
			FileReader file = new FileReader("dailyTransactionFile.txt");
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
				}
				System.out.println(opCode);
			}

			reader.close();
		} catch(IOException e) {

		}
	}

	public static void writeUF(String fileLine) {
		try {
			FileWriter writer = new FileWriter("currentUsers.txt");

			writer.write(fileLine);
			writer.close();
		} catch(IOException e) {

		}
	}

	public void writeTF() {

	}
}