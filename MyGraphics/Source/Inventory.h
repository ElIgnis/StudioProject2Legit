#pragma once
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include "Item.h"

class CInventory
{
public:
	Vector3 TrolleyPosition;
	Vector3 TrolleyDirection;
	Vector3 Offset;
	Vector3 Offset2;
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

	void Init_Trolley(void);
	void Init_Inventory(void);
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

	bool UpdateTrolleyBox(Vector3 player_position);
	long double ex, ez;

	CInventory(void);
	~CInventory(void);
};