// ReadFileInventoryBins.cpp

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdlib>

#include"InventoryBins.h"

using namespace::std;

void outputLine(ostream &, const InventoryBins &); // prototype

int main()
{
	ifstream inCredit("credit.dat", ios::in | ios::binary);

	// exit program if ifstream cannot open file

	if (!inCredit)
	{
		cout << "file could not be opened." << endl;
		exit(1);
	} // end if.

	cout << left << setw(10) << "Stock No." << setw(16)
		<< "Description" << left << setw(10) << right << "Stock" << endl;

	InventoryBins client; // create record

    // read first record from file
	inCredit.read(reinterpret_cast<char *>(&client), sizeof(InventoryBins));

	// read all records from file

	while (inCredit && !inCredit.eof())
	{
		// display record
		if (client.getInventoryNumber() != 0)
		{
			outputLine(cout, client);
		}

		// read next from file
		inCredit.read(reinterpret_cast<char *> (&client), sizeof(InventoryBins));

	} // end while


} // end main.

void outputLine(ostream &output, const InventoryBins &record)
{
	output << left << setw(10) << record.getInventoryNumber()
		<< setw(16) << record.getDescription()
		<< setw(10) << right << record.getStock() << endl;


} // end function outputLine