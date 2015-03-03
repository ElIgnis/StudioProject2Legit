#pragma once
#include <iostream>
#include "Vector3.h"
#include "Item.h"

using namespace std;

class CShopperAI2
{
private:
	Vector3 Position;
	Vector3 Direction;
	int CurrentState;

public:
	CShopperAI2();
	~CShopperAI2();

	enum States
	{
		DEFAULT,
		CAUGHT,
		DETECTED,
		NUM_STATES,
	};

	float RotationSpeed;
	float MovementSpeed;
	int RotateLeft;
	bool Anime_Take;
	bool Anim_Rotate;
	bool Anim_Revert;
	bool ItemAtLeft;
	bool ItemAtRight;

	bool DoNotTurn;
	bool fowardtrolley;
	bool backwardtrolley;

	float DetectionTimer;
	float ResetTimer;
	bool RecentlyDestroyed;

	//Shopper AI Movement
	bool Rotate_Leg_Left_Back;
	bool Rotate_Leg_Right_Back;
	bool Rotate_Hand_Left_Back;
	bool Rotate_Hand_Right_Back;

	float Rotation_Left_Leg;
	float Rotation_Right_Leg;
	float Rotation_Left_Hand;
	float Rotation_Right_Hand;

	void SetPosition(Vector3 &NewPosition);
	void SetDirection(Vector3 &NewDirection, double dt);
	void UpdateAI(double dt, Vector3 &PlayerPosition);
	//void UpdateAI(double dt, Vector3 &PlayerPosition, CItem *Item);
	bool UpdatePath(double dt);
	bool TakingItem(CItem *Item, double dt);
	void UpdateGoal(CItem *Item);
	void MoveZPlus(double StopPoint, double dt);
	void MoveZMinus(double StopPoint, double dt);
	void MoveXPlus(double StopPoint, double dt);
	void MoveXMinus(double StopPoint, double dt);
	Vector3 GetPosition(void);
	Vector3 GetDirection(void);
	int GetState(void);
	void SetState(int NewState);


};

