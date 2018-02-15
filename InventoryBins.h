// InventoryBins.h

#pragma once

#include<iostream>
#include<string>

using namespace::std;

class InventoryBins
{
public:
	InventoryBins(int = 0, string = "", double = 0.0); // Contructor
	~InventoryBins(); // Destructor

    // Setters
	void setInventoryNumber(int);
	void setDescription(string);
	void setStock(double);

	// Getters
	int getInventoryNumber() const;
	string getDescription() const;
	double getStock() const;

private:

	int inventoryNumber;
	char description[20];
	double stock;

};