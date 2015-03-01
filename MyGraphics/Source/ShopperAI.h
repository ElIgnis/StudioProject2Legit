#pragma once
#include <iostream>
//#include "Source\SP2.h"
#include <Vector3.h>
#include "Item.h"


using namespace std;
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

	//###Following Wlcode###
	//ShopperAI Movement
	bool Rotate_Leg_Left_Back;
	bool Rotate_Leg_Right_Back;
	bool Rotate_Hand_Left_Back;
	bool Rotate_Hand_Right_Back;

	float Rotation_Left_Leg;
	float Rotation_Right_Leg;
	float Rotation_Left_Hand;
	float Rotation_Right_Hand;

	float RotationSpeed;
	float MovementSpeed;
	int RotateLeft;
	bool Anim_Wreck;
	bool Anim_Rotate;
	bool Anim_Revert;
	bool ItemAtLeft;
	bool ItemAtRight;

	bool RecentlyDestroyed;


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
	void WalkingPath3(double dt, int NewState);


	void UpdatePath(double dt, Vector3 &Playerposition);
	//Move
	void MoveZPlus(double StopPoint, int NewState, double Speed, double dt);
	void MoveZMinus(double StopPoint, int NewState, double Speed, double dt);
	void MoveXPlus(double StopPoint, int NewState, double Speed, double dt);
	void MoveXMinus(double StopPoint, int NewState, double Speed, double dt);

//WL's
	bool WalkingPath2(double dt);

	void MoveZPlus2(double StopPoint, double dt);
	void MoveZMinus2(double StopPoint, double dt);
	void MoveXPlus2(double StopPoint, double dt);
	void MoveXMinus2(double StopPoint, double dt);

	void SetDirections(Vector3 &NewDirection, double dt);
	void SetPosition(Vector3 &NewPosition);
	Vector3 GetPosition(void);
	Vector3 GetDirections(void);
	int GetState(void);
	void SetState(int NewState);
	//taking item
	bool TakingItem(CItem *Item, double dt);
};


