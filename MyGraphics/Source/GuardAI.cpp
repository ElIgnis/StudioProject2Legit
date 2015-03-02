#include "GuardAI.h"
#include <iostream>
#include <stdlib.h>
#include <time.h> 
using std::string;

CGuardAI::CGuardAI(void)
{
}

CGuardAI::~CGuardAI(void)
{
}

void CGuardAI::InitGuard(float x, float z)
{
	//placeholder for shoplifter
	shoplifted = false;
	shoplifter.Set(1000.0F,1000.0F,1000.0F);


	//Initialize Guard's Patrolpoints

	PatrolPoint[0].Set(35.0F,0.0F,-56.0F);
	PatrolPoint[1].Set(35.0F,0.0F,12.0F);
	PatrolPoint[2].Set(8.0F,0.0F,12.0F);
	PatrolPoint[3].Set(8.0F,0.0F,-56.0F);
	PatrolPoint[4].Set(-10.0F,0.0F,-56.0F);
	PatrolPoint[5].Set(-10.0F,0.0F,12.0F);
	PatrolPoint[6].Set(-30.0F,0.0F,12.0F);
	PatrolPoint[7].Set(-30.0F,0.0F,-56.0F);


	//Initialize patrol pathing
	Guard_State = PATROLLING;
	current_patrol_point = 0;
	patrol_direction = 1;
	distance_to_point = guard_position - PatrolPoint[current_patrol_point];


	//Initialize random patrol direction
	srand(time(NULL));



	//Initialize Guard's Spawn Point & Animation values
	guard_position.Set(x,0,z);
	rotation_complete = true;
	Rotate_Leg_Left_Back = false;
	Rotate_Leg_Right_Back = false;
	Rotate_Hand_Left_Back = false;
	Rotate_Hand_Right_Back = false;

	RotationSpeed = 100.f;
	Rotation_Left_Leg = 0.f;
	Rotation_Right_Leg = 0.f;
	Rotation_Left_Hand = 0.f;
	Rotation_Right_Hand = 0.f;
}



void CGuardAI::UpdateState(Vector3 player_position)
{
	//Guard moves or responds according to its state
	switch (Guard_State)
	{
	case IDLE:
		//TODO : Idle animation(?)
		break;
	case PATROLLING:
		//Guard patrols according to pathing
		PatrolPath();
		break;
	case CHASING:
		//Guard chases after shoplifter
		ChasingPath();
		break;
	case CAUGHT:
		//TODO : What happens when Guard has caught shoplifter/player
		break;
	};
}

void CGuardAI::UpdateGuard(Vector3 player_position, bool modeShopper, bool modeVillain, double dt)
{
	//Obtain distance based on guard's position and player's position
	distance_to_player = guard_position - player_position;
	distance_to_shoplifter = guard_position - shoplifter;

	//Shopper Scenario
	//If the player or a shopper shoplifts, the guard will chase after them
	//TODO: Shoplifter Detection
	/*if (someone has shoplifted)
	{
	shoplifted = true;
	}*/

	//If they are within reach, the guard will catch them
	if (distance_to_shoplifter.Length() < 5.0)
	{
		Guard_State = CAUGHT;
	}

	//Villain Scenario
	//If the player is within reach, the guard will catch them
	if (modeVillain == true && distance_to_player.Length() < 5.0)
	{
		Guard_State = CAUGHT;
	}


	//To be used if creating chasing for AI

	//TODO : Collision Detection
	/*
	//If player is close to the guard, the guard will start chasing the player
	//To Do : Guard has to be facing the player
	if (distance_to_player.Length() < 50.0 && Guard_State == PATROLLING)
	{
	Guard_State = CHASING;
	}
	//If the player manages to outrun the guard, the guard will go back to patrolling
	if (distance_to_player.Length() > 50.0 && Guard_State != PATROLLING)
	{
	Guard_State = PATROLLING;

	//Guard patrols from closest patrol point
	distance_to_point = guard_position - PatrolPoint[0];
	for (int i = 0; i < 8; ++i)
	{
	//Compare guard's position with all patrol points to find closest point
	Vector3 distance_to_point_comparison = guard_position - PatrolPoint[i];
	if (distance_to_point.Length() >= distance_to_point_comparison.Length())
	{
	distance_to_point = distance_to_point_comparison;
	current_patrol_point = i;

	//patrol direction is randomly assigned
	int r = rand() % 2;

	if (r == 1) //forward patrol
	{
	patrol_direction = 1;
	}
	else //backward patrol
	{
	patrol_direction = -1;
	}
	}
	}
	}
	*/

	//Update Guard's State
	UpdateState(player_position);

	//Guard walking animation
	//Left Arm
		if (Rotate_Hand_Left_Back == false)
		{
			Rotation_Left_Hand += (float)(RotationSpeed * dt);
		}
		if (Rotate_Hand_Left_Back == true)
		{
			Rotation_Left_Hand -= (float)(RotationSpeed * dt);
		}
		if (Rotation_Left_Hand >= 30)
		{
			Rotate_Hand_Left_Back = true;
		}
		if (Rotation_Left_Hand <= -30)
		{
			Rotate_Hand_Left_Back = false;
		}
		//Right Arm
		if (Rotate_Hand_Right_Back == false)
		{
			Rotation_Right_Hand += (float)(RotationSpeed * dt);
		}
		if (Rotate_Hand_Right_Back == true)
		{
			Rotation_Right_Hand -= (float)(RotationSpeed * dt);
		}
		if (Rotation_Right_Hand >= 30)
		{
			Rotate_Hand_Right_Back = true;
		}
		if (Rotation_Right_Hand <= -30)
		{
			Rotate_Hand_Right_Back = false;
		}
		//Left Leg
		if (Rotate_Leg_Left_Back == false)
		{
			Rotation_Left_Leg += (float)(RotationSpeed * dt);
		}
		if (Rotate_Leg_Left_Back == true)
		{
			Rotation_Left_Leg -= (float)(RotationSpeed * dt);
		}
		if (Rotation_Left_Leg >= 30)
		{
			Rotate_Leg_Left_Back = true;
		}
		if (Rotation_Left_Leg <= -30)
		{
			Rotate_Leg_Left_Back = false;
		}
		//Right Leg
		if (Rotate_Leg_Right_Back == false)
		{
			Rotation_Right_Leg += (float)(RotationSpeed * dt);
		}
		if (Rotate_Leg_Right_Back == true)
		{
			Rotation_Right_Leg -= (float)(RotationSpeed * dt);
		}
		if (Rotation_Right_Leg >= 30)
		{
			Rotate_Leg_Right_Back = true;
		}
		if (Rotation_Right_Leg <= -30)
		{
			Rotate_Leg_Right_Back = false;
		}
}

void CGuardAI::PatrolPath(void)
{
	//If Guard is facing the correct direction, he will move towards closest point at a rate of 1 unit
	if (rotation_complete == true)
	{
		guard_position += distance_to_point.Normalized();
	}
	//Else, he will turn to face the correct direction
	else
	{
		//Update the difference of rotation
		rotation_difference.y = guard_next_direction - guard_direction.y;
		//Rotate guard if not fully rotated
		if (guard_direction.y != guard_next_direction)
		{
			guard_direction += rotation_difference.Normalized();
		}
		//Else, rotation is complete
		else
		{
			rotation_complete = true;
		}
	}

	//Recalculate distance between Guard and patrol point
	distance_to_point = PatrolPoint[current_patrol_point] - guard_position;

	//Once the guard has reached the checkpoint, he will move to the next checkpoint
	if (distance_to_point.Length() <= 3.0F)
	{
		//However, if someone has shoplifted, he will begin to chase down the person
		if (shoplifted == true)
		{
			Guard_State = CHASING;
		}

		//Guard will rotate before moving to the next point
		//Rotation depends on patrol direction and current patrol point
		if (patrol_direction == 1)
		{			
			if (current_patrol_point == 3 || current_patrol_point == 4)
			{
				RotateLeft(90.0f);
			}
			else if (current_patrol_point == 7)
			{
				RotateRight(180.0f);
			}
			else if (current_patrol_point != 0)
			{
				RotateRight(90.0f);
			}
		}
		else if (patrol_direction == -1)
		{
			if (current_patrol_point == 3 || current_patrol_point == 4)
			{
				RotateRight(90.0f);
			}
			else if (current_patrol_point == 0)
			{
				RotateLeft(180.0f);
			}
			else if (current_patrol_point != 7)
			{
				RotateLeft(90.0f);
			}
		}

		//If the guard has reached the end of the patrol, he will reverse
		if (current_patrol_point == 7)
		{
			patrol_direction = -1;
		}
		//If the guard has then reached the start of the patrol, he will reverse again
		else if (current_patrol_point == 0)
		{
			patrol_direction = 1;
		}
		
		//Next patrol points are assigned based on patrol direction
		current_patrol_point += (1 * patrol_direction);
		distance_to_point = guard_position - PatrolPoint[current_patrol_point];
	}
}

void CGuardAI::ChasingPath(void)
{
	//Guard will first move to Z-coordinates before the Cashier
	if (guard_position.z != 12.0F)
	{
		Vector3 Z_Required(guard_position.x, guard_position.y, (guard_position.z - 12.0F));
		guard_position -= Z_Required.Normalized();
	}
	//Guard will then move towards shoplifter's X-coordinates to be in line with the shoplifter
	if (guard_position.x != shoplifter.x && guard_position.z == 12.0F)
	{
		Vector3 X_Required((guard_position.x - shoplifter.x),guard_position.y,guard_position.z);
		guard_position -= X_Required.Normalized();
	}
	//Once in line, guard will chase down shoplifter
	distance_to_shoplifter = guard_position - shoplifter;
	guard_position -= distance_to_shoplifter.Normalized();
}

void CGuardAI::RotateLeft(float rotation)
{
	//Add the difference of the rotation
	if (rotation_complete == true)
	{
		guard_next_direction = guard_direction.y + rotation;
		rotation_complete = false;
	}
}

void CGuardAI::RotateRight(float rotation)
{
	//Add the difference of the rotation
	if (rotation_complete == true)
	{
		guard_next_direction = guard_direction.y - rotation;
		rotation_complete = false;
	}
}

float CGuardAI::getX(void)
{
	return guard_position.x;
}
float CGuardAI::getY(void)
{
	return guard_position.y;
}

float CGuardAI::getY2(void)
{
	return guard_direction.y;
}

float CGuardAI::getZ(void)
{
	return guard_position.z;
}

string CGuardAI::returnState(void)
{
	//Return Guard's current State
	switch (Guard_State)
	{
	case IDLE:
		return "IDLE";
		break;
	case PATROLLING:
		return "PATROLLING";
		break;
	case CHASING:
		return "CHASING";
		break;
	case CAUGHT:
		return "CAUGHT";
		break;
	};
}