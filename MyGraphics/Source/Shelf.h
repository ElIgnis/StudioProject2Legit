#pragma once

#include "Item.h"

class CShelf
{
public:
	vector<CItem*>Shelf;
	vector<Vector3>Init_Pos;
	Vector3 Position;
	float MinWidth;
	float MaxWidth;
	float MinLength;
	float MaxLength;

	void SetShelfPosition(Vector3 &NewPosition);
	void SetShelfCollision(float Width, float Length);
	CShelf(void);
	~CShelf(void);
};