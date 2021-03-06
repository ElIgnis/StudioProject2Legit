/******************************************************************************/
/*!
\file	Villain.h
\author Wei Liang Lee
\par	email: 140511H\@mymail.nyp.edu.sg
\brief
Villain NPC going around to wreck stuff randomly
*/
/******************************************************************************/
#pragma once

#include "Vector3.h"
#include "Item.h"
#define VillainPathSize 16
/******************************************************************************/
/*!
		Class CVillainAI:
\brief	A Villain NPC class
*/
/******************************************************************************/
class CVillainAI
{
private:
	Vector3 Position;
	Vector3 Direction;
	int CurrentState;

public:
	//! An enum.
	/*! Enum for uniform type */
	enum States
	{
		DEFAULT,	/*!< DEFAULT */
		CAUGHT,		/*!< CAUGHT */
		DETECTED,	/*!< DETECTED */
		NUM_STATES,	/*!< NUM_STATES */
	};
	
	CVillainAI(void);
	~CVillainAI(void);

	float RotationSpeed;
	float MovementSpeed;
	int RotateLeft;
	bool Anim_Wreck;
	bool Anim_Rotate;
	bool Anim_Revert;
	bool ItemAtLeft;
	bool ItemAtRight;

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

	void Init_Villain(void);
	void SetPosition(Vector3 &NewPosition);
	void SetDirection(Vector3 &NewDirection, double dt);
	void UpdateAI(double dt, Vector3 &PlayerPosition);
	bool UpdatePath(double dt);
	bool DestroyItem(CItem *Item, double dt);
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

