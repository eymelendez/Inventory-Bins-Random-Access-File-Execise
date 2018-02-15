// InventoryBins.cpp

#include<iostream>
#include<string>
using namespace::std;

#include"InventoryBins.h"

InventoryBins::InventoryBins(int inventoryNumberValue,
		string descriptionValue, double stockValue)
{
	setInventoryNumber(inventoryNumberValue);
	setDescription(descriptionValue);
	setStock(stockValue);

}

InventoryBins::~InventoryBins()
{
}

void InventoryBins::setInventoryNumber(int inventoryNumberValue)
{
	inventoryNumber = inventoryNumberValue;
}


void InventoryBins::setDescription(string descriptionString)
{
	// copy at most 15 characters from string to description

	int length = descriptionString.size();
	length = (length < 20 ? length : 19);
	descriptionString._Copy_s(description, 20, length);
	description[length] = '\0'; // append null character to lastName
}

void InventoryBins::setStock(double stockValue)
{
	stock = stockValue;
}

int InventoryBins::getInventoryNumber() const
{
	return inventoryNumber;
}

string InventoryBins::getDescription() const
{
	return description;
}

double InventoryBins::getStock() const
{
	return stock;
}