#include "Inventory.h"

CInventory::CInventory(void)
{
	MaxInventorySize = 2;
	MaxTrolleySize = 8;
	CurrentSize = 0;
	EquippedTrolley = false;

	TrolleyPosition.x = 30.f;
	TrolleyPosition.y = 0.f;
	TrolleyPosition.z = 30.f;

	TrolleyDirection.x = 0;
	TrolleyDirection.y = 0;
	TrolleyDirection.z = 0;

	Offset.x = 0.0f;
	Offset.y = 0.0f;
	Offset.z = 0.0f;
	Offset2.x = -4.0f;
	Offset2.y = 0.0f;
	Offset2.z = 0.0f;
}

CInventory::~CInventory(void)
{
}

void CInventory::Init_Trolley(void)
{
	EquippedTrolley = false;

	TrolleyPosition.x = 30.f;
	TrolleyPosition.y = 0.f;
	TrolleyPosition.z = 30.f;

	TrolleyDirection.x = 0;
	TrolleyDirection.y = 0;
	TrolleyDirection.z = 0;

	Offset.x = 0.0f;
	Offset.y = 0.0f;
	Offset.z = 0.0f;
	Offset2.x = -4.0f;
	Offset2.y = 0.0f;
	Offset2.z = 0.0f;

	RotationMinWidth = TrolleyPosition.x;
	RotationMaxWidth = TrolleyPosition.x + 2;
	RotationMinLength = TrolleyPosition.z - 0.5f;
	RotationMaxLength = TrolleyPosition.z + 0.5f;
}

void CInventory::Init_Inventory(void)
{
	for(vector<CItem*>::iterator iter = Inventory.begin(); iter != Inventory.end();)
	{
		if(Inventory.size() > 0)
			Inventory.erase(iter);
		else
			break;
	}
	for(vector<int>::iterator iter = InventoryIndexing.begin(); iter != InventoryIndexing.end();)
	{
		if(InventoryIndexing.size() > 0)
			InventoryIndexing.erase(iter);
		else
			break;
	}
	//for(vector<CItem*>::iterator iter = Inventory.begin(); iter != Inventory.end();)
	//{
	//	if(Inventory.size() > 0)
	//		Inventory.erase(iter);
	//	else
	//		break;
	//}
	//for(vector<int>::iterator iter = InventoryIndexing.begin(); iter != InventoryIndexing.end();)
	//{
	//	if(InventoryIndexing.size() > 0)
	//		InventoryIndexing.erase(iter);
	//	else
	//		break;
	//}
}

bool CInventory::Add_ShelfToTrolley(CItem * Item, int ItemIndex)
{
	if (Inventory.size() < MaxTrolleySize)
	{
		//Only add default items
		//if(Item->ItemState == CItem::DEFAULT)
		{
			Inventory.push_back(Item);
			InventoryIndexing.push_back(ItemIndex);
			Item->ItemState = CItem::IN_TROLLEY;
			return true;
		}
	}
	return false;
}

bool CInventory::Add_ShelfToInvent(CItem *Item, int ItemIndex)
{
	//Adds Items from shelf to inventory
	//Sets Item state from DEFAULT to TAKEN

	//Allows addition only if inventory is not full
	if(Inventory.size() < MaxInventorySize)
	{
		//Only add default items
		if(Item->ItemState == CItem::DEFAULT)
		{
			Inventory.push_back(Item);
			InventoryIndexing.push_back(ItemIndex);
			Item->ItemState = CItem::TAKEN;
			return true;
		}
	}
	return false;
}

bool CInventory::Add_TrolleyToInvent(CItem *Item, int ItemIndex)
{
	//Adds Items from trolley to inventory
	//Sets Item state from IN_TROLLEY to TAKEN

	//Allows addition only if inventory is not full
	if(Inventory.size() < MaxInventorySize)
	{
		//Only add items from trolley
		if(Item->ItemState == CItem::IN_TROLLEY)
		{
			Inventory.push_back(Item);
			InventoryIndexing.push_back(ItemIndex);
			Item->ItemState = CItem::TAKEN;
			return true;
		}
	}
	return false;
}

bool CInventory::Minus_InventToShelf(CItem * Item, int ItemIndex)
{
	//Removes Items from inventory to shelf
	//Sets Item state to DEFAULT

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
					InventoryIndexing.erase(iter);
					Item->ItemState = CItem::DEFAULT;
					return true;
				}
			}
		}
		MatchingIndex++;
	}
	return false;
}

bool CInventory::Minus_InventToTrolley(CItem * Item, int ItemIndex)
{
	//Removes Items from inventory to trolley
	//Sets Item state to IN_TROLLEY

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
					InventoryIndexing.erase(iter);
					Item->ItemState = CItem::IN_TROLLEY;
					return true;
				}
			}
		}
		MatchingIndex++;
	}
	return false;
}

bool CInventory::SwapFromInvent(CItem *Item, int ItemIndex)
{
	int MatchingIndex = 0;
	bool ItemErased = false;
	//Swaps with item on hand(Add then remove)
	if(Inventory.size() == 1)
	{
		Add_ShelfToInvent(Item, ItemIndex);

		//Assign temporary variable to store target details
		CItem *temp = new CItem;
		temp->ItemPosition = Inventory.at(0)->ItemPosition;

		//Swap item positions
		Inventory.at(0)->SetPosition(Vector3(Inventory.at(1)->ItemPosition));
		Inventory.at(1)->SetPosition(Vector3(temp->ItemPosition));

		//Remove item on hand
		Minus_InventToShelf(Inventory.at(0), Inventory.at(0)->ItemIndex);
		return true;
	}
	return false;
}

void CInventory::SetPosition(Vector3 &NewPosition)
{
	TrolleyPosition.x = NewPosition.x;
	TrolleyPosition.y = NewPosition.y;
	TrolleyPosition.z = NewPosition.z;

	RotationMinWidth = TrolleyPosition.x;
	RotationMaxWidth = TrolleyPosition.x + 2;
	RotationMinLength = TrolleyPosition.z - 0.5f;
	RotationMaxLength = TrolleyPosition.z + 0.5f;
}

void CInventory::SetDirection(Vector3 &NewDirection)
{
	TrolleyDirection.x = NewDirection.x;
	TrolleyDirection.y = NewDirection.y;
	TrolleyDirection.z = NewDirection.z;
}

bool CInventory::Add_InventToTrolley(CItem *Item, int ItemIndex)
{
	//Adds Items from inventory to trolley
	//Sets Item state from TAKEN to IN_TROLLEY

	//Only add taken items
	if(Inventory.size() < MaxTrolleySize)
	{
		//Add items
		if(Item->ItemState == CItem::TAKEN)
		{
			Inventory.push_back(Item);
			InventoryIndexing.push_back(ItemIndex);
			Item->ItemState = CItem::IN_TROLLEY;
			return true;
		}
	}
	return false;
}

bool CInventory::Minus_TrolleyToInvent(CItem *Item, int ItemIndex)
{
	//Removes Items from trolley to inventory
	//Sets Item state to TAKEN

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
					InventoryIndexing.erase(iter);
					Item->ItemState = CItem::TAKEN;
					return true;
				}
			}
		}
		MatchingIndex++;
	}
	return false;
}

bool CInventory::UpdateTrolleyBox(Vector3 player_position)
{
	float width = 5;
	float height = 3;
	float angle = TrolleyDirection.y * M_PI / 180.0f;
	float s = sin(angle) / 2;
	float c = cos(angle) / 2;
	if (s < 0) 
	{
			s = -s;
	}
	if (c < 0)
	{
		c = -c;
	}
	//Offset2 = Amount to be offset
	//Offset = The position of the bounding box after offset
	Offset2.x = cos(angle) * -4.0f;
	Offset2.z = -sin(angle) * -4.0f;

	Offset = TrolleyPosition + Offset2;

	ex = (height * s) + (width * c);
	ez = (height * c) + (width * s);
	if (Offset.x + ex > player_position.x && 
		Offset.x - ex  < player_position.x &&
		Offset.z + ez > player_position.z &&
		Offset.z - ez < player_position.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}