#include "Inventory.h"

CInventory::CInventory(void)
{
	MaxInventorySize = 2;
	MaxTrolleySize = 8;
	CurrentSize = 0;
	EquippedTrolley = false;

	TrolleyDirection.x = 0;
	TrolleyDirection.y = 0;
	TrolleyDirection.z = 0;
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
		if(Item->ItemState[CItem::NUM_STATE] == CItem::DEFAULT || Item->ItemState[CItem::NUM_STATE] == CItem::IN_TROLLEY)
		{
			cout << "Pushing item no.: " << ItemIndex << endl;
			Inventory.push_back(Item);
			InventoryIndexing.push_back(ItemIndex);
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
		if(ItemIndex == InventoryIndexing.at(MatchingIndex))
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
			for(vector<int>::iterator iter = InventoryIndexing.begin() + MatchingIndex; iter != InventoryIndexing.end(); iter++)
			{
				if(ItemIndex == InventoryIndexing.at(MatchingIndex) && InventoryIndexing.size() > 0)
				{
					cout << "Erasing item no.: " << InventoryIndexing.at(MatchingIndex) << endl;
					InventoryIndexing.erase(iter);
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

void CInventory::SetPosition(Vector3 &NewPosition)
{
	TrolleyPosition.x = NewPosition.x;
	TrolleyPosition.y = NewPosition.y;
	TrolleyPosition.z = NewPosition.z;

	RotationMinWidth = TrolleyPosition.x + 3;
	RotationMaxWidth = TrolleyPosition.x + 5;
	RotationMinLength = TrolleyPosition.z - 0.5f;
	RotationMaxLength = TrolleyPosition.z + 0.5f;
}

void CInventory::SetDirection(Vector3 &NewDirection)
{
	TrolleyDirection.x = NewDirection.x;
	TrolleyDirection.y = NewDirection.y;
	TrolleyDirection.z = NewDirection.z;
}

bool CInventory::AddToTrolley(CItem *Item, int ItemIndex)
{
	//Allows addition only if inventory is not full
	if(Inventory.size() < MaxTrolleySize)
	{
		//Add items
		if(Item->ItemState[CItem::NUM_STATE] == CItem::TAKEN)
		{
			cout << "Pushing item no.: " << ItemIndex << endl;
			Inventory.push_back(Item);
			InventoryIndexing.push_back(ItemIndex);
			return true;
		}
	}
	else
	return false;
}

bool CInventory::RemoveFromTrolley(CItem *Item, int ItemIndex)
{
	int MatchingIndex = 0;
	bool ItemErased = false;
	for(vector<CItem*>::iterator iter = Inventory.begin(); iter != Inventory.end(); iter++)
	{
		//Removing items of the name chosen
		if(ItemIndex == InventoryIndexing.at(MatchingIndex))
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
			for(vector<int>::iterator iter = InventoryIndexing.begin() + MatchingIndex; iter != InventoryIndexing.end(); iter++)
			{
				if(ItemIndex == InventoryIndexing.at(MatchingIndex) && InventoryIndexing.size() > 0)
				{
					cout << "Erasing item no.: " << InventoryIndexing.at(MatchingIndex) << endl;
					InventoryIndexing.erase(iter);
					return true;
				}
			}
		}
		MatchingIndex++;
	}
	return false;
}