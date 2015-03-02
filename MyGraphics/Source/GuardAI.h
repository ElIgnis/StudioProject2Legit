#pragma once

#include "Vector3.h"
#include <iostream>
#include <math.h>
using std::string;

class CGuardAI
{
private:
	Vector3 guard_position, guard_direction;

	//Placeholder for shoplifter
	Vector3 shoplifter;

	Vector3 distance_to_shoplifter;
	Vector3 distance_to_player;
	Vector3 distance_to_point;
	Vector3 rotation_difference; //difference between guard's direction and direction he has to face
	Vector3 PatrolPoint[8];
	int current_patrol_point;
	int patrol_direction;
	float guard_next_direction;

	//Guard Animation
	float RotationSpeed, MovementSpeed;
	bool Rotate_Leg_Left_Back;
	bool Rotate_Leg_Right_Back;
	bool Rotate_Hand_Left_Back;
	bool Rotate_Hand_Right_Back;

	
	bool rotation_complete;

	enum STATE
	{
		IDLE,
		PATROLLING,
		CHASING,
		CAUGHT,
	};

	STATE Guard_State;

public:
	CGuardAI(void);
	~CGuardAI(void);

	//Guard Animation
	float Rotation_Left_Leg;
	float Rotation_Right_Leg;
	float Rotation_Left_Hand;
	float Rotation_Right_Hand;
	
	void InitGuard(float x, float z, float Movement_Speed, float Rotation_Speed);
	void UpdateState(Vector3 player_position, double dt);
	void UpdateGuard(Vector3 player_position, bool modeShopper, bool modeVillain, double dt);
	void PatrolPath(double dt);  // Pathing for patrolling Supermarket
	void ChasingPath(double dt); //Pathing for chasing shoplifters
	void RotateLeft(float rotation);
	void RotateRight(float rotation);
	bool shoplifted, chase_path_completed;

	void setShoplifter(Vector3 shoplifter_position);
	float getX(void);
	float getY(void); //Returns Position.Y
	float getY2(void); //Returns Direction.Y
	float getZ(void);
	string returnState(void);
};

