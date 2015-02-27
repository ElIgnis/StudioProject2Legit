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

	void SetPosition(Vector3 &NewPosition);
	void SetDirection(Vector3 &NewDirection, double dt);
	void UpdateAI(double dt, Vector3 &PlayerPosition);
	//void UpdateAI(double dt, Vector3 &PlayerPosition, CItem *Item);
	bool UpdatePath(double dt, int NewState);
	bool DestroyItem(CItem *Item);
	bool NearItem(CItem *Item);
	void UpdateGoal(CItem *Item);
	void MoveZPlus(double StopPoint, int NewState, double Speed, double dt);
	void MoveZMinus(double StopPoint, int NewState, double Speed, double dt);
	void MoveXPlus(double StopPoint, int NewState, double Speed, double dt);
	void MoveXMinus(double StopPoint, int NewState, double Speed, double dt);
	Vector3 GetPosition(void);
	Vector3 GetDirection(void);
};

