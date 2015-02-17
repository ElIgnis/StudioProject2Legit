#include "Item.h"

CItem::CItem(void)
{

}

CItem::~CItem(void)
{

}

void CItem::SetDetails(string SetName, double SetPrice)
{
	ItemName = SetName;
	ItemPrice = SetPrice;
}

void CItem::SetShape(Vector3 &NewShape)
{
	ItemShape.x = NewShape.x;
	ItemShape.y = NewShape.y;
	ItemShape.z = NewShape.z;
}

string CItem::GetName(void)
{
	return ItemName;
}
double CItem::GetPrice(void)
{
	return ItemPrice;
}