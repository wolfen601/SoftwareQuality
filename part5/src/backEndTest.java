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

	@Test
	public void testBuy() {
		fail("Not yet implemented");
	}

	@Test
	public void testRefund() {
		fail("Not yet implemented");
	}

	@Test
	public void testAddcredit() { //admin---------- AA 000010.00
		fail("Not yet implemented");
	}

}
