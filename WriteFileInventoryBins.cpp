// WriteFileInventoryBins.cpp

#include<iostream>
#include<fstream>
#include<cstdlib>

#include"InventoryBins.h"

using namespace::std;

int main()
{
	int inventoryNumber;
	string description;
	double stock;

	fstream outCredit("credit.dat", ios::in | ios::out | ios::binary);

	// exit program if stream cannot open file

	if (!outCredit)
	{
		cout << "File could not be opened." << endl;
		exit(1);

	}

	cout << "Enter bin number (1 to 100, 0 to end input)\n";

	// require user to specify account number

	InventoryBins client;
	cin >> inventoryNumber;

	//  user enters information, which is copied into file

	while (inventoryNumber > 0 && inventoryNumber <= 100)
	{
		// "user enters last name, first name and balance
		cout << "Enter description, stock? \n";
		cin >> description;
		cin >> stock;

		// set record accountNumber, lastName, firstName and balance values
		client.setInventoryNumber(inventoryNumber);
		client.setDescription(description);
		client.setStock(stock);

		// seek position in file of user-specified record
		outCredit.seekp((client.getInventoryNumber() - 1) * sizeof(InventoryBins));

		// write user-specified information in file
		outCredit.write(reinterpret_cast<const char *> (&client), sizeof(InventoryBins));

		// enable user to enter another account
		cout << "Enter stock No.\n?";
		cin >> inventoryNumber;

	} // end while


} // end main.