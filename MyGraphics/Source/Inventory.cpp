#include "Inventory.h"

CInventory::CInventory(void)
{
	MaxInventorySize = 5;
	MaxTrolleySize = 9;
}

CInventory::~CInventory(void)
{
}

bool CInventory::AddToInvent(CItem *Item, int ItemIndex)
{
	//Allows addition only if inventory is not full
	if(Inventory.size() < MaxInventorySize)
	{
		////Cannot add destroyed items
		//if(Item->ItemState[CItem::NUM_STATE] == CItem::DESTROYED)
		//{
		//	return false;
		//}
		//Add items
		if(Item->ItemState[CItem::NUM_STATE] == CItem::DEFAULT)
		{
			cout << "Pushing item no.: " << ItemIndex << endl;
			Inventory.push_back(Item);
			ItemIndexing.push_back(ItemIndex);
			return true;
		}
	}
	else
	return false;
}

bool CInventory::RemoveFromInvent(CItem * Item, int ItemIndex)
{
	int MatchingIndex = 0;
	bool ItemErased = false;
	for(vector<CItem*>::iterator iter = Inventory.begin(); iter != Inventory.end(); iter++)
	{
		//Removing items of the name chosen
		if(ItemIndex == ItemIndexing.at(MatchingIndex))
		{
			//Remove only if inventory has items
			if(Inventory.size() > 0)
			{
				Inventory.erase(iter);
				ItemErased = true;
			}
		}
		//Erase from index only if any item has been erased
		if(ItemErased)
		{
			for(vector<int>::iterator iter = ItemIndexing.begin() + MatchingIndex; iter != ItemIndexing.end(); iter++)
			{
				if(ItemIndex == ItemIndexing.at(MatchingIndex) && ItemIndexing.size() > 0)
				{
					cout << "Erasing item no.: " << ItemIndexing.at(MatchingIndex) << endl;
					ItemIndexing.erase(iter);
					return true;
				}
			}
		}
		MatchingIndex++;
	}
	
	return false;
}
//Remove this function when done with UI
void CInventory::PrintInvent(void)
{
	for(vector<CItem*>::iterator iter = Inventory.begin(); iter != Inventory.end(); iter++)
	{
		cout << (*iter)->GetName() << endl;
		cout << (*iter)->GetPrice() << endl;
	}
	return;
}

void CInventory::SetDetails(Vector3 &NewPosition)
{
	TrolleyPosition.x = NewPosition.x;
	TrolleyPosition.y = NewPosition.y;
	TrolleyPosition.z = NewPosition.z;
}

bool CInventory::AddToTrolley(CItem *Item)
{
	//Allows addition only if trolley size is not full
	if(Inventory.size() < MaxTrolleySize)
	{
		////Cannot add destroyed items
		//if(Item->ItemState[CItem::NUM_STATE] == CItem::DESTROYED)
		//{
		//	return false;
		//}
		//Add items
		if(Item->ItemState[CItem::NUM_STATE] == CItem::DEFAULT)
		{
			Inventory.push_back(Item);
			Item->ItemPosition.x = TrolleyPosition.x;
			Item->ItemPosition.y = TrolleyPosition.y;
			Item->ItemPosition.z = TrolleyPosition.z;
			return true;
		}
	}
	else
	return false;
}

bool CInventory::RemoveFromTrolley(CItem *Item)
{
	return false;
}