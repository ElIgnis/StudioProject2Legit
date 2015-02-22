#pragma once
#include "Item.h"

class CInventory
{
public:
	Vector3 TrolleyPosition;
	vector<CItem*>Inventory;
	vector<int>ItemIndexing;
	unsigned int MaxInventorySize;
	unsigned int MaxTrolleySize;

	bool AddToInvent(CItem *Item, int ItemIndex);
	bool RemoveFromInvent(CItem *Item, int ItemIndex);
	void PrintInvent(void);
	bool AddToTrolley(CItem *Item);
	bool RemoveFromTrolley(CItem *Item);
	void SetDetails(Vector3 &NewPosition);

	CInventory(void);
	~CInventory(void);
};