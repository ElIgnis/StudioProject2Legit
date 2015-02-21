#pragma once
#include "Item.h"

class CInventory
{
public:

	vector<CItem*>Inventory;
	unsigned int MaxInventorySize;

	bool AddToInvent(CItem *Item);
	bool RemoveFromInvent(CItem *Item);
	void PrintInvent(void);

	CInventory(void);
	~CInventory(void);
};

//&& Container.Shelf.at(i)->ItemState[CItem::NUM_STATE] == CItem::DEFAULT