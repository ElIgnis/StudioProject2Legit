#pragma once
#include <iostream>
//#include "Source\SP2.h"
#include <Vector3.h>


using namespace std;
class CShopperAI
{
private:
	Vector3 position;
	Vector3 Direction;
	int direction;
	int Rotangle;
	float timer;
	bool SetDirection;
	bool Animate_ON;
	bool Directions;


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
	void ShopperInitialize();
	// AI Path 
	void WalkingPath(double dt, int NewState);
	void Payment(double dt, int NewState);

	void UpdatePath(double dt, Vector3 &Playerposition);
	//Move
	void MoveZPlus(double StopPoint, int NewState, double Speed, double dt);
	void MoveZMinus(double StopPoint, int NewState, double Speed, double dt);
	void MoveXPlus(double StopPoint, int NewState, double Speed, double dt);
	void MoveXMinus(double StopPoint, int NewState, double Speed, double dt);
};

