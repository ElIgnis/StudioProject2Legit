#pragma once
#include "Inventory.h"

class CCashier
{
public:

	float TotalPrice;
	float MinWidth;
	float MaxWidth;
	float MinLength;
	float MaxLength;

	Vector3 CashierPosition;

	Vector3 RollItems(vector<CItem*> Inventory);
	float CheckOutItems(vector<CItem*> Inventory);
	void SetDetails(Vector3 &NewPosition);

	CCashier(void);
	~CCashier(void);
};

