#include "Cashier.h"


CCashier::CCashier(void)
{
}


CCashier::~CCashier(void)
{
}

void CCashier::SetDetails(Vector3 &NewPosition)
{
	CashierPosition.x = NewPosition.x;
	CashierPosition.y = NewPosition.y;
	CashierPosition.z = NewPosition.z;

	MinWidth = CashierPosition.x - 2.f;
	MaxWidth = CashierPosition.x;

	MinLength = CashierPosition.z - 2.f;
	MinLength = CashierPosition.z;
}

float CCashier::CheckOutItems(vector<CItem*> Inventory)
{
	//Calculate all items bought;
	for(vector<CItem*>::iterator iter = Inventory.begin(); iter != Inventory.end(); iter++)
	{
		TotalPrice += (*iter)->GetPrice();
	}
	return TotalPrice;
}

Vector3 CCashier::RollItems(vector<CItem*> Inventory)
{
	return Inventory.at(0)->ItemPosition;
}