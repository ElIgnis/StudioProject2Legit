#include "Item.h"

CItem::CItem(void)
{
	ItemState[NUM_STATE] = DEFAULT;
}

CItem::~CItem(void)
{
}

void CItem::SetDetails(string SetName, double SetPrice, Vector3 &SetPosition, string SetType, int SetIndex)
{
	ItemName = SetName;
	ItemPrice = SetPrice;
	ItemPosition.x = SetPosition.x;
	ItemPosition.y = SetPosition.y;
	ItemPosition.z = SetPosition.z;
	ItemIndex = SetIndex;
	
	if(SetType == "GEO_CAN_COKE")
	{
		GEO_TYPE = 20;
	}
	else if(SetType == "GEO_CAN_MTNDEW")
	{
		GEO_TYPE = 21;
	}
	else if(SetType == "GEO_PACK_KINDER")
	{
		GEO_TYPE = 22;
	}
	else if(SetType == "GEO_PACK_SNICKERS")
	{
		GEO_TYPE = 23;
	}
	else if(SetType == "GEO_BOX_ICECREAM")
	{
		GEO_TYPE = 24;
	}
	else if(SetType == "GEO_BOX_PIZZA")
	{
		GEO_TYPE = 25;
	}
	else if(SetType == "GEO_BOX_CHOC_CEREAL")
	{
		GEO_TYPE = 26;
	}
	else if(SetType == "GEO_BOX_CEREAL")
	{
		GEO_TYPE = 27;
	}
	else if(SetType == "GEO_CAN_BEANS")
	{
		GEO_TYPE = 28;
	}
	else if(SetType == "GEO_CAN_SARDINES")
	{
		GEO_TYPE = 29;
	}
	else if(SetType == "GEO_CAN_ROOTBEER")
	{
		GEO_TYPE = 30;
	}
	else if(SetType == "GEO_CAN_MILO")
	{
		GEO_TYPE = 31;
	}
	else if(SetType == "GEO_PACK_NOODLE")
	{
		GEO_TYPE = 32;
	}
	else if(SetType == "GEO_PACK_TOBLERONE")
	{
		GEO_TYPE = 33;
	}
	else if(SetType == "GEO_BOX_CHOCO")
	{
		GEO_TYPE = 34;
	}

	//Invisible box range defined based on item position
	MinWidth = (ItemPosition.x - 1.5f);
	MaxWidth = (ItemPosition.x + 1.5f);

	MinHeight = (ItemPosition.y - 1.f);
	MaxHeight = (ItemPosition.y + 1.f);

	MinLength = (ItemPosition.z - 1.25f);
	MaxLength = (ItemPosition.z + 1.25f);
}

void CItem::SetPosition(Vector3 &NewPosition)
{
	ItemPosition.x = NewPosition.x;
	ItemPosition.y = NewPosition.y;
	ItemPosition.z = NewPosition.z;

	//Invisible box range defined based on item position
	MinWidth = (ItemPosition.x - 1.5f);
	MaxWidth = (ItemPosition.x + 1.5f);

	MinHeight = (ItemPosition.y - 1.f);
	MaxHeight = (ItemPosition.y + 1.f);

	MinLength = (ItemPosition.z - 1.25f);
	MaxLength = (ItemPosition.z + 1.25f);
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