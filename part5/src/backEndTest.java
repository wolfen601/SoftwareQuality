import static org.junit.Assert.*;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.PrintStream;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;


public class backEndTest {
	private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
	
	@Before
	public void setUpStreams() {
	    System.setOut(new PrintStream(outContent));
	}

	@After
	public void cleanUpStreams() {
	    System.setOut(null);
	}
	
	@Test 
	public void testNewFile1() {
		File testUsers = new File("newCurrentUsers.txt");
		assertTrue("File does not exist.", testUsers.exists());
	}
	@Test 
	public void testNewFile2() {
		File testTickets = new File("newAvailableTickets.txt");
		assertTrue("File does not exist.", testTickets.exists());
	}

	@Test 
	public void testOldFiles1() {
		File testOldUsers = new File("oldCurrentUsers.txt");
		assertTrue("File does not exist.", testOldUsers.exists());
	}
	@Test 
	public void testOldFiles2() {
		File testOldTickets = new File("oldAvailableTickets.txt");
		assertTrue("File does not exist.", testOldTickets.exists());
	}

	@Test 
	public void testReadDTF() {
		File testDTF = new File("mergedDailyTransactionFile.txt");
		assertTrue("File does not exist.", testDTF.exists());
	}

	@Test
	public void testCreateExisting() {
		backEnd.create("user----------- BS 000000.00");
		backEnd.create("user----------- BS 000000.00");
		assertEquals("Error: Create failed, user already exists", outContent.toString());
	}
	
	@Test
	public void testCreate() {
		backEnd.create("user3---------- BS 000000.00");
		assertEquals("", outContent.toString());
	}

	@Test
	public void testDeleteExisting() {
		backEnd.delete("user----------- BS 000000.00");
		assertEquals("", outContent.toString());
	}
	
	@Test
	public void testDelete() {
		backEnd.delete("user6---------- BS 000000.00");
		assertEquals("Error: Delete failed, user does not exist", outContent.toString());
	}

	@Test
	public void testSellExisting() {
		backEnd.sell("RandomEvent------- admin---------- 012 012.00");
		backEnd.sell("RandomEvent------- admin---------- 012 012.00");
		assertEquals("Error: Sell failed, event already exists", outContent.toString());
	}
	
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
