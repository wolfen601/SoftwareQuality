import static org.junit.Assert.*;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.PrintStream;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;


public class backEndTest {
	//reads the output stream
	private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
	private backEnd tester = new backEnd();
	//set the output stream
	@Before
	public void setUpStreams() {
	    System.setOut(new PrintStream(outContent));
	}
	//cleans up the output stream
	@After
	public void cleanUpStreams() {
	    System.setOut(null);
	}
	//testMain
	@Test 
	public void testMain() {
		String[] args = {""};
		backEnd.main(args);
	}
	//test that the new current users file is made
	@Test 
	public void testNewFile1() {
		File testUsers = new File("newCurrentUsers.txt");
		assertTrue("File does not exist.", testUsers.exists());
	}
	//test that the new available tickets file is made
	@Test 
	public void testNewFile2() {
		File testTickets = new File("newAvailableTickets.txt");
		assertTrue("File does not exist.", testTickets.exists());
	}
	//test that the old users file exists
	@Test 
	public void testOldFiles1() {
		File testOldUsers = new File("oldCurrentUsers.txt");
		assertTrue("File does not exist.", testOldUsers.exists());
	}
	//test that the old tickets file exists
	@Test 
	public void testOldFiles2() {
		File testOldTickets = new File("oldAvailableTickets.txt");
		assertTrue("File does not exist.", testOldTickets.exists());
	}
	//test that there is a merged daily transaction to read
	@Test 
	public void testReadDTF() {
		File testDTF = new File("mergedDailyTransactionFile.txt");
		assertTrue("File does not exist.", testDTF.exists());
	}
	//test that the user cannot be created if it exists
	@Test
	public void testCreateExisting() {
		backEnd.create("user----------- BS 000000.00");
		assertEquals("Error: Create failed, user already exists\r\n", outContent.toString());
	}
	//test that the user can be created 
	@Test
	public void testCreate() {
		backEnd.create("user3---------- BS 000000.00");
		assertEquals("", outContent.toString());
	}
	//test the user exists to delete
	@Test
	public void testDeleteExisting() {
		backEnd.create("user3---------- BS 000000.00");
		backEnd.delete("user3---------- BS 000000.00");
		assertEquals("", outContent.toString());
	}
	//test that a non existing user cannot be deleted
	@Test
	public void testDelete() {
		backEnd.delete("user6---------- BS 000000.00");
		assertEquals("Error: Delete failed, user does not exist\r\n", outContent.toString());
	}
	//test that an event cannot be sold with the same name as an existing one
	@Test
	public void testSellExisting() {
		backEnd.sell("RandomEvent------- admin---------- 012 012.00");
		assertEquals("Error: Sell failed, event already exists\r\n", outContent.toString());
	}
	//test that the event can be sold
	@Test
	public void testSell() {
		backEnd.sell("RandomEvent2------ admin---------- 012 012.00");
		assertEquals("", outContent.toString());
	}
	//test that the event must exist to be bought
	@Test
	public void testBuy() {
		backEnd.buy("RandomEvent9------- admin---------- 002 005.00");
		assertEquals("Error: Buy failed, event does not exist\r\n", outContent.toString());
	}
	//test that the transaction buy succeeds
	@Test
	public void testBuyExisting() {
		backEnd.buy("RandomEvent------- admin---------- 002 012.00");
		assertEquals("", outContent.toString());
	}
	//test that the buyer is refunded money from seller
	@Test
	public void testRefund() {
		backEnd.refund("admin---------- user1---------- 000100.00");
		assertEquals("", outContent.toString());
	}
	//test that add credit passes
	@Test
	public void testAddCredit() {
		backEnd.addcredit("admin---------- AA 000010.00");
		assertEquals("", outContent.toString());
	}
	//test that add credit fails on maximum amount
	@Test
	public void testAddCreditMax() {
		for(int i = 0; i < 2; i++){
			backEnd.addcredit("admin---------- AA 999999.00");
		}
		assertEquals("Error: Add credit failed, exceeds maximum amount\r\n", outContent.toString());
	}
	//test that credit adds padding
	@Test
	public void testAddPaddingCredit() {
		assertEquals("Error: Padding not added properly", "000100.00", backEnd.addPadding("credit", 0, 100));
	}
	//test that other tickets adds padding
	@Test
	public void testAddPadding() {
		assertEquals("Error: Padding not added properly", "097", backEnd.addPadding("tickets", 97, 0));
	}
	//test that nothing happens for padding
	@Test
	public void testAddPaddingNothing() {
		assertEquals("Error: Nothing was suppose to happen", "NOTHING HAPPENED", backEnd.addPadding("", 0, 0));
	}
	//test that add padding loop runs zero times
	@Test
	public void testLoopRunsZero() {
		assertEquals("Error: Padding not added properly", "100", backEnd.addPadding("tickets", 100, 0));
	}
	//test that add padding loop runs one time
	@Test
	public void testLoopRunsOnce() {
		assertEquals("Error: Padding not added properly", "090", backEnd.addPadding("tickets", 90, 0));
	}
	//test that add padding loop runs two times
	@Test
	public void testLoopRunsTwice() {
		assertEquals("Error: Padding not added properly", "009", backEnd.addPadding("tickets", 9, 0));
	}
}
