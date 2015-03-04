/******************************************************************************/
/*!
\file	Cashier.cpp
\author Marcus Lim Tow Siang
\par	email: 141732S\@mymail.nyp.edu.sg
\brief
Cashier with position and price calculator and area to check out
*/
/******************************************************************************/
#include "Cashier.h"
/******************************************************************************/
/*!
\brief
Default Constructor

\exception None
\return None
*/
/******************************************************************************/
CCashier::CCashier(void)
{
}
/******************************************************************************/
/*!
\brief
Default Destructor
*/
/******************************************************************************/
CCashier::~CCashier(void)
{
}
/******************************************************************************/
/*!
\brief
Set details of cashier

\param NewPosition - new position of vector
*/
/******************************************************************************/
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
/******************************************************************************/
/*!
\brief
Perform checkout

\param Inventory - inventory of items
\return	Total price of items
*/
/******************************************************************************/
float CCashier::CheckOutItems(vector<CItem*> Inventory)
{
	//Calculate all items bought;
	for(vector<CItem*>::iterator iter = Inventory.begin(); iter != Inventory.end(); iter++)
	{
		TotalPrice += (*iter)->GetPrice();
	}
	return TotalPrice;
}