#pragma once

#include "SP2.h"

#include<iostream>

using std::cout;
using std::endl;

class CItem
{
public:
	//Vars
	string ItemName;
	double ItemPrice;
	Vector3 ItemShape;

	//States
	bool IsDestroyed;
	bool IsCheckedOut;

	void SetDetails(string SetName, double SetPrice);
	void SetShape(Vector3 &NewShape);
	string GetName(void);
	double GetPrice(void);

	CItem(void);
	~CItem(void);
};