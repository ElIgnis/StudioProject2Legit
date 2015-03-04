/******************************************************************************/
/*!
\file	Cashier.h
\author Marcus Lim Tow Siang
\par	email: 141732S\@mymail.nyp.edu.sg
\brief
Cashier with position and price calculator and area to check out
*/
/******************************************************************************/
#pragma once
#include "Inventory.h"
/******************************************************************************/
/*!
		Class CCashier:
\brief	A Cashier class
*/
/******************************************************************************/
class CCashier
{
public:

	float TotalPrice;
	float MinWidth;
	float MaxWidth;
	float MinLength;
	float MaxLength;

	Vector3 CashierPosition;

	float CheckOutItems(vector<CItem*> Inventory);
	void SetDetails(Vector3 &NewPosition);

	CCashier(void);
	~CCashier(void);
};

