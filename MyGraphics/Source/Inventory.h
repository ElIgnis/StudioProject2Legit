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
	unsigned int CurrentSize;
	bool EquippedTrolley;

	float RotationMinWidth;
	float RotationMaxWidth;
	float RotationMinLength;
	float RotationMaxLength;

	//For collision
	float MinWidth;
	float MaxWidth;
	float MinLength;
	float MaxLength;

	bool Add_ShelfToTrolley(CItem * Item, int ItemIndex);
	bool Add_ShelfToInvent(CItem *Item, int ItemIndex);
	bool Add_TrolleyToInvent(CItem *Item, int ItemIndex);
	bool Minus_InventToShelf(CItem *Item, int ItemIndex);
	bool Minus_InventToTrolley(CItem *Item, int ItemIndex);
	bool SwapFromInvent(CItem *Item, int ItemIndex);
	bool Add_InventToTrolley(CItem *Item, int ItemIndex);
	bool Minus_TrolleyToInvent(CItem *Item, int ItemIndex);
	void SetPosition(Vector3 &NewPosition);
	void SetDirection(Vector3 &NewDirection);

	CInventory(void);
	~CInventory(void);
};