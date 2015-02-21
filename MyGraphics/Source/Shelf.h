#pragma once

#include "Item.h"

class CShelf
{
public:
	vector<CItem*>Shelf;
	Vector3 ShelfPosition;
	int MaxShelfSize;

	void SetShelfPosition(Vector3 &Position);
	CShelf(void);
	~CShelf(void);
};