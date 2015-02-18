#pragma once
#include "Item.h"

#include<vector>

using std::vector;

class CInventory
{
public:

	vector<CItem*>Inventory;

	unsigned int MaxInventorySize;

	bool AddToInvent(CItem *Item);
	bool RemoveFromInvent(unsigned int index);
	void PrintInvent(void);

	CInventory(void);
	~CInventory(void);
};

