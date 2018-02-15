#include<iostream>
#include<fstream>
#include<cstdlib>

#include"InventoryBins.h"

using namespace::std;

int main()
{
	ofstream outCredit("credit.dat", ios::out | ios::binary);

	// exit program if ofstream could not open file

	if (!outCredit)
	{
		cout << "File could no tbe opened." << endl;
		exit(1);

	} // end if.

	InventoryBins blankClient; // constructor zeros out each data member

	// output 100 blank records to file

	for (int i = 0; i < 100; ++i)
	{
		outCredit.write(reinterpret_cast<const char *>(&blankClient), sizeof(InventoryBins));


	}


} // end main.