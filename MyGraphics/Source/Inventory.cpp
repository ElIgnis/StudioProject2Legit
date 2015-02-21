#include "Inventory.h"

CInventory::CInventory(void)
{
	MaxInventorySize = 9;
}

CInventory::~CInventory(void)
{
}

bool CInventory::AddToInvent(CItem *Item)
{
	//Allows addition only if inventory size is lesser
	if(Inventory.size() < MaxInventorySize)
	{
		//Cannot add destroyed items
		if(Item->ItemState[CItem::NUM_STATE] == CItem::DESTROYED)
		{
			return false;
		}
		else if(Item->ItemState[CItem::NUM_STATE] == CItem::DEFAULT)
		{
			Inventory.push_back(Item);
			return true;
		}
	}
	else
	return false;
}

bool CInventory::RemoveFromInvent(CItem * Item)
{
	int count = 0;
	for(vector<CItem*>::iterator iter = Inventory.begin(); iter != Inventory.end(); iter++, count++)
	{
		//Overriding
		if(Item->ItemName == (*iter)->GetName())
		{
			if(Inventory.size() > 0)
			{
				Inventory.erase(iter);
				return true;
			}
		}	
	}
	return false;
}

void CInventory::PrintInvent(void)
{
	for(vector<CItem*>::iterator iter = Inventory.begin(); iter != Inventory.end(); iter++)
	{
		cout << (*iter)->GetName() << endl;
		cout << (*iter)->GetPrice() << endl;
	}
	return;
}