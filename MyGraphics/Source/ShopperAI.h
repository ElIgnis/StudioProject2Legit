/******************************************************************************/
/*!
\file	ShopperAI.h
\author Kelvin Tan Young Yew
\par	email: 144117P\@mymail.nyp.edu.sg
\brief
Shopper NPC without trolley walking around and takes some items before checking out
*/
/******************************************************************************/
#pragma once
#include <iostream>
#include <Vector3.h>
#include "Item.h"

#define ShopperPathSize2 10
#define ShopperPathSize3 12

using namespace std;
/******************************************************************************/
/*!
		Class CShopperAI:
\brief	A Shopper NPC class
*/
/******************************************************************************/
class CShopperAI
{
private:
	//Mine own one
	Vector3 position;
	Vector3 Direction;
	int direction;
	int Rotangle;
	float timer;
	bool SetDirection;
	bool Animate_ON;
	bool Directions;
	//float timer_item1;
	int CurrentState;


	enum ShopperState
	{
		WALK,
		STOPnTAKE,
		Pay,
		EXIT,
	};
	ShopperState ShopperSTATE;

public:
	CShopperAI();
	~CShopperAI();

	//bool path1 = false;
	bool item1;
	bool item2;
	bool RenderTrolley;
	bool item_milo;
	bool item_sardine;
	bool item_MnC;
	bool item_maggie;
	bool item_iceCream;
	bool item_choco;




	//AI Position
	void setPositionX(float x);
	void setPositionZ(float z);
	float getPositionX(void);
	float getPositionZ(void);
	//Direction of turning
	void setShopperDirection(int r);
	int getShopperDirection(void);
	
	//Render Shopper AI
	bool RENDERINGAI;


	//Init
	void ShopperInitialize(void);
	// AI Path 
	void WalkingPath(double dt, int NewState);
	void WalkingPath3(double dt, int NewState);


	void UpdatePath(double dt, Vector3 &Playerposition);
	//Move
	void MoveZPlus(double StopPoint, int NewState, double Speed, double dt);
	void MoveZMinus(double StopPoint, int NewState, double Speed, double dt);
	void MoveXPlus(double StopPoint, int NewState, double Speed, double dt);
	void MoveXMinus(double StopPoint, int NewState, double Speed, double dt);

};


