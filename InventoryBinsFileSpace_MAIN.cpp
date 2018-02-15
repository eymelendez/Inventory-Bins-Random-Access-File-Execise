// InventoryBinsFileSpace_MAIN.cpp

// Pag. 670 Random-Access File

// Use this baby to do the bins! Copy this and modify the descriptions. Also, there's some files that you need that are "removed" 
// but not deleted and you need them to create files, write, read files.
// Right-Click the Source Files and choose "existing items.

/* IMPORTANT NOTE: Page. 679 at the end says the following.

We assume that the program of Fig. 17.11 has been executed to create the file credit.dat
and that the program of Fig. 17.12 has been executed to insert the initialdata.
*/

#include<iomanip>
#include<iostream>
#include<fstream>
#include<cstdlib>


using namespace::std;
#include"InventoryBins.h" // ClientData class definition

int enterChoice();
void createTextFile(fstream &);
void updateRecord(fstream &);
void newRecord(fstream &);
void deleteRecord(fstream &);
void outputLine(ostream &, const InventoryBins &);

int getInventory(const char * const);

enum Choices { PRINT = 1, UPDATE, NEW, DELETE, END }; // Search for what is enum...

int main()
{
	// open file for reading and writing

	fstream inOutCredit("credit.dat", ios::in | ios::out | ios::binary);

	// exit program if fstream cannot open file
	if (!inOutCredit)
	{
		cout << "File cound not be opened" << endl;
		exit(1);
	} // end if.


	int choice; // store user choice

	// enable user to specify action
	while ((choice = enterChoice()) != END)
	{
		switch (choice)
		{
		case PRINT: // create text file from record file
			createTextFile(inOutCredit);
			break;

		case UPDATE: // update record
			updateRecord(inOutCredit);
			break;

		case NEW: // create record
			newRecord(inOutCredit);
			break;

		case DELETE: // delete existing record
			deleteRecord(inOutCredit);
			break;

		default: // display error if user does not select valid choice
			cout << "Incorrect choice" << endl;
			break;

		} // end switch

		inOutCredit.clear(); // reset end-of-file indicator
	} // end while


} // end main.

int enterChoice()
{
	// display available options

	cout << "\nEnter your choice" << endl
		<< "1 - store a formatted text file of account" << endl
		<< "	called \"print.txt\" for printing" << endl
		<< "2 - update a bin's stock" << endl
		<< "3 - add a new bin" << endl
		<< "4 - delete a bin" << endl
		<< "5 - end program\n? ";

	int menuChoice;
	cin >> menuChoice; // input menu selection from user
	return menuChoice;

} // end function enterChoice

  // create formatted text file for printing
void createTextFile(fstream & readFromFile)
{
	// create text file
	fstream outPrintFile("print.txt", ios::out);

	// exit program if ofstream cannot create file
	if (!outPrintFile)
	{
		cout << "File could not be created." << endl;
		exit(1);


	} // end if.

	outPrintFile << left << setw(10) << "Stock No." << setw(20) << "Description" 
				 << setw(11) << right << setw(10) << "Balance" << endl;

	// set file-position pointer to beginning of readFromFile
	readFromFile.seekg(0);

	// read first record from record file
	InventoryBins client;
	readFromFile.read(reinterpret_cast<char *> (&client), sizeof(InventoryBins));


	// copy all records from record file into text file
	while (!readFromFile.eof())
	{
		// write single record to text file
		if (client.getInventoryNumber() != 0)		// skip empty records
		{
			outputLine(outPrintFile, client);
			//outputLine(cout, client);
		}

		// read next record from record file
		readFromFile.read(reinterpret_cast<char *>(&client), sizeof(InventoryBins));

	} // end while

} // end function createTextFile


  // update balance in record
void updateRecord(fstream &updateFile)
{
	// obtain number of account to update
	int inventoryNumber = getInventory("Enter Bin's Number to update");

	// move file-position pointer to correct record in file
	updateFile.seekg((inventoryNumber - 1) * sizeof(InventoryBins));

	// read first record from file
	InventoryBins client;
	updateFile.read(reinterpret_cast<char *> (&client), sizeof(InventoryBins));

	// update record
	if (client.getInventoryNumber() != 0)
	{
		outputLine(cout, client); // display the record

		// request user to specify transaction
		cout << "\nEnter charge (+) or payment (-):	";
		double transaction; // charge or payment
		cin >> transaction;

		// update record balance
		while (transaction > 30 || transaction < 0)
		{
			cout << "ERROR, the bin's can't hold more than 30 stock or it can't "
				 << "accept NEGATIVE numbers. RE-ENTER THE VALUES: ";
			cin >> transaction;

		}

		double oldBalance = client.getStock();
		
		if ((oldBalance + transaction) > 30 || (oldBalance + transaction) < 0) 
		{
			cout << "Stock has surpassed the limit of 30 or reached a NEGATIVE NUMBER.\n";
			cout << "Returned stock to original state BEFORE transaction.";
			client.setStock(oldBalance - transaction);
			
			outputLine(cout, client); // display the record
		}
		else 
		{
			client.setStock(oldBalance + transaction);
			outputLine(cout, client); // display the record
		}
		

		// move file-position pointer to correct record in file
		updateFile.seekp((inventoryNumber - 1) * sizeof(InventoryBins));

		// write updated record over old record in file
		updateFile.write(reinterpret_cast<const char *> (&client), sizeof(InventoryBins));

	} // end if.
	else // display error if account does not exist
		cout << "Bin #" << inventoryNumber << " has no information." << endl;

} // end function updateRecord


  // create and insert record
void newRecord(fstream & insertInFile)
{
	// obtain number of account to create
	int inventoryNumber = getInventory("Enter new bin number: ");

	// move file-position pointer to correct record in file
	insertInFile.seekg((inventoryNumber - 1) * sizeof(InventoryBins));

	// read record from file
	InventoryBins client;
	insertInFile.read(reinterpret_cast<char *>(&client), sizeof(InventoryBins));

	// create record, if record does not previosly exist
	if (client.getInventoryNumber() == 0)
	{
		
		string description;
		double stock;

		// user enters last name, first name and balance
		cout << "Enter description, stock\n?";
		cin >> description;
		cin >> stock;

		while (stock > 30 || stock < 0) 
		{
			cout << "ERROR, the bin's can't hold more than 30 stock or it can't "
				 << "accept NEGATIVE numbers. RE-ENTER THE VALUES: ";
			cin >> stock;
		}

		// use values to populate account values
		client.setDescription(description);
		client.setStock(stock);
		client.setInventoryNumber(inventoryNumber);

		// move file-position pointer to correct record in file
		insertInFile.seekp((inventoryNumber - 1) * sizeof(InventoryBins));

		// insert record in file
		insertInFile.write(reinterpret_cast<const char *> (&client), sizeof(InventoryBins));

	} // end if
	else
		cout << "Bin #" << inventoryNumber
		<< " already contains information. " << endl;


} // end function newRecord

  // delete an existing record
void deleteRecord(fstream & deleteFromFile)
{
	// obtain number of account to delete
	int inventoryNumber = getInventory("Enter bin to delete");

	// move file-postion pointer to correct record in file
	deleteFromFile.seekg((inventoryNumber - 1) * sizeof(InventoryBins));

	// read record from file
	InventoryBins client;
	deleteFromFile.read(reinterpret_cast<char *>(&client), sizeof(InventoryBins));

	// delete record, if record exist in file
	if (client.getInventoryNumber() != 0)
	{
		InventoryBins blankClient; // created blank record

		// move file-position pointer to correct record in file
		deleteFromFile.seekp((inventoryNumber - 1) * sizeof(InventoryBins));

		// replace existing record with blank record
		deleteFromFile.write(reinterpret_cast<const char *>(&blankClient), sizeof(InventoryBins));

		cout << "Bin #" << inventoryNumber << "deleted.\n";

	} // end if
	else // display error if record does not exist
		cout << "Bin # " << inventoryNumber << " is empty.\n";

} // end deleteRecord

  // display single record
void outputLine(ostream &output, const InventoryBins &record)
{
	output << left << setw(10) << record.getInventoryNumber() << setw(16)
		   << record.getDescription() << setw(10) << right << record.getStock() << endl;


} // end function outputLine

int getInventory(const char * const prompt)
{
	int inventoryNumber;

	// obtain account-number value
	do
	{
		cout << prompt << " (1 - 100): ";
		cin >> inventoryNumber;

	} while (inventoryNumber < 1 || inventoryNumber > 100);

	return inventoryNumber;

} // end function getAccount


  // 9 de mayo de 2017 - SUCCESSFUL! SO BEAUTIFUL!