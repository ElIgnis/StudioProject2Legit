/******************************************************************************/
/*!
\file	Item.cpp
\author Wei Liang Lee
\par	email: 140511H\@mymail.nyp.edu.sg
\brief
Item with details and state machine
*/
/******************************************************************************/
#include "Item.h"
/******************************************************************************/
/*!
\brief
Default Constructor

\exception None
\return None
*/
/******************************************************************************/
CItem::CItem(void)
{
	ItemName = "";
	ItemPrice = 0;
	GEO_TYPE = 0;
	ItemShape = Vector3(1.f, 1.f, 1.f);;
	ItemPosition = Vector3(0.f, 0.f, 0.f);
	MinWidth = 0.f;
	MaxWidth = 0.f;
	MinLength = 0.f;
	MaxLength = 0.f;
	MinHeight = 0.f;
	MaxHeight = 0.f;
	ItemIndex = 0;
	ItemState = DEFAULT;
}
/******************************************************************************/
/*!
\brief
Default Destructor
*/
/******************************************************************************/
CItem::~CItem(void)
{
}
/******************************************************************************/
/*!
\brief
Sets details of items

\param SetName - sets name of item
\param SetPrice - sets price of item
\param SetPosition - sets position of item
\param SetType - sets geometry type of item
\param SetIndex - sets index of item
*/
/******************************************************************************/
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
/******************************************************************************/
/*!
\brief
Sets only position of item

\param NewPosition - position to update
*/
/******************************************************************************/
void CItem::SetPosition(Vector3 &NewPosition)
{
	//ItemPosition.x = NewPosition.x;
	//ItemPosition.y = NewPosition.y;
	//ItemPosition.z = NewPosition.z;

	ItemPosition = NewPosition;

	//Invisible box range defined based on item position
	MinWidth = (ItemPosition.x - 1.5f);
	MaxWidth = (ItemPosition.x + 1.5f);

	MinHeight = (ItemPosition.y - 1.f);
	MaxHeight = (ItemPosition.y + 1.f);

	MinLength = (ItemPosition.z - 1.25f);
	MaxLength = (ItemPosition.z + 1.25f);
}
/******************************************************************************/
/*!
\brief
Sets only shape of item

\param NewPosition - shape to update
*/
/******************************************************************************/
void CItem::SetShape(Vector3 &NewShape)
{
	ItemShape.x = NewShape.x;
	ItemShape.y = NewShape.y;
	ItemShape.z = NewShape.z;
}
/******************************************************************************/
/*!
\brief
Gets name of item
*/
/******************************************************************************/
string CItem::GetName(void)
{
	return ItemName;
}
/******************************************************************************/
/*!
\brief
Gets price of item
*/
/******************************************************************************/
double CItem::GetPrice(void)
{
	return ItemPrice;
}