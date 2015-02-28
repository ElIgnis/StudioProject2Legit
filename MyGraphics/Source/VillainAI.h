#pragma once

#include "Vector3.h"
#include "Item.h"

class CVillainAI
{
private:
	Vector3 Position;
	Vector3 Direction;

	enum States
	{
		DEFAULT,
		MOVING,
		CAUGHT,
		DETECTED,
		DESTROYING,
		NUM_STATES,
	};
public:
	CVillainAI(void);
	~CVillainAI(void);

	float RotationSpeed;
	int RotateLeft;
	bool Anim_Wreck;
	bool Anim_Rotate;
	bool Anim_Revert;
	bool ItemAtLeft;
	bool ItemAtRight;

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
	bool UpdatePath(double dt, int NewState);
	bool DestroyItem(CItem *Item, double dt);
	void UpdateGoal(CItem *Item);
	void MoveZPlus(double StopPoint, int NewState, double Speed, double dt);
	void MoveZMinus(double StopPoint, int NewState, double Speed, double dt);
	void MoveXPlus(double StopPoint, int NewState, double Speed, double dt);
	void MoveXMinus(double StopPoint, int NewState, double Speed, double dt);
	Vector3 GetPosition(void);
	Vector3 GetDirection(void);
};

