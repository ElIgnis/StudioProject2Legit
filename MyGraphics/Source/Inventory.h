#pragma once
#include "Item.h"

class CInventory
{
public:
	Vector3 TrolleyPosition;
	Vector3 TrolleyDirection;
	vector<CItem*>Inventory;
	vector<int>InventoryIndexing;
	unsigned int MaxInventorySize;
	unsigned int MaxTrolleySize;
	bool EquippedTrolley;

	bool AddToInvent(CItem *Item, int ItemIndex);
	bool RemoveFromInvent(CItem *Item, int ItemIndex);
	void PrintInvent(void);
	bool AddToTrolley(CItem *Item, int ItemIndex);
	bool RemoveFromTrolley(CItem *Item, int ItemIndex);
	void SetPosition(Vector3 &NewPosition);
	void SetDirection(Vector3 &NewDirection);

	CInventory(void);
	~CInventory(void);
};