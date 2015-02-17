#include "Inventory.h"

CInventory::CInventory(void)
{
	InventorySize = 15;
}

CInventory::~CInventory(void)
{
}

bool CInventory::AddToInvent(CItem *Item)
{
	//Allows addition only if inventory size is lesser
	if(Inventory.size() < InventorySize)
	{
		Inventory.push_back(Item);
		return true;
	}
	return false;
}

bool CInventory::RemoveFromInvent(unsigned int index)
{
	int count = 0;
	for(vector<CItem*>::iterator iter = Inventory.begin(); iter != Inventory.end(); iter++, count++)
	{
		//Overriding
		if(count == index)
		{
			Inventory.erase(iter);
			return true;
		}
	}
	return false;
}

void CInventory::PrintInvent(void)
{
	for(vector<CItem*>::iterator iter = Inventory.begin(); iter != Inventory.end(); iter++)
	{
		cout << (*iter)->GetName();
		cout << (*iter)->GetPrice();
	}
}