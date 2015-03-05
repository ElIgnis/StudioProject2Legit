/******************************************************************************/
/*!
\file	GuardAI.cpp
\author Bryn Shannon Ho Zhi Wen
\par	email: 144104B\@mymail.nyp.edu.sg
\brief
Class to define the Guard NPC patrolling the supermarket and interacting with the player
*/
/******************************************************************************/
#include "GuardAI.h"
#include <iostream>
#include <stdlib.h>
#include <time.h> 
#define _USE_MATH_DEFINES
#include <math.h>
using std::string;
/******************************************************************************/
/*!
\brief
Default Constructor

\exception None
\return None
*/
/******************************************************************************/
CGuardAI::CGuardAI(void)
{
}
/******************************************************************************/
/*!
\brief
Default Destructor
*/
/******************************************************************************/
CGuardAI::~CGuardAI(void)
{
}
/******************************************************************************/
/*!
\brief
Intializes the Security Guard

\param x - X axis position of Guard
\param z - Z axis position of Guard
\param Movement_Speed - Movement speed of guard
\param Rotation_Speed - Rotation speed of guard
*/
/******************************************************************************/
void CGuardAI::InitGuard(float x, float z, float Movement_Speed, float Rotation_Speed)
{
	//placeholder for shoplifter
	shoplifted = false;
	chase_path_completed = false;
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
	guard_direction.Set(0,0,0);
	rotation_complete = true;
	Rotate_Leg_Left_Back = false;
	Rotate_Leg_Right_Back = false;
	Rotate_Hand_Left_Back = false;
	Rotate_Hand_Right_Back = false;

	MovementSpeed = Movement_Speed;
	RotationSpeed = Rotation_Speed;
	Rotation_Left_Leg = 0.f;
	Rotation_Right_Leg = 0.f;
	Rotation_Left_Hand = 0.f;
	Rotation_Right_Hand = 0.f;
}
/******************************************************************************/
/*!
\brief
Updates the state of the guard

\param player_position - Position of player
\param dt - Delta time update
*/
/******************************************************************************/
void CGuardAI::UpdateState(Vector3 player_position, double dt)
{
	//Guard moves or responds according to its state
	switch (Guard_State)
	{
	case PATROLLING:
		//Guard patrols according to pathing
		PatrolPath(dt);
		break;
	case CHASING:
		//Guard chases after shoplifter
		ChasingPath(dt);
		break;
	case CAUGHT:
		//Guard has caught the player
		break;
	};
}
/******************************************************************************/
/*!
\brief
Updates guard based on game mode

\param player_position - Position of player
\param modeShopper - Check if in Shopper game mode
\param modeVillain - Checik if in Villain game mode
\param dt - delta time update
*/
/******************************************************************************/
void CGuardAI::UpdateGuard(Vector3 player_position, bool modeShopper, bool modeVillain, double dt)
{
	//Obtain distance based on guard's position and player's/shoplifter's position
	distance_to_player = guard_position - player_position;
	distance_to_shoplifter = guard_position - shoplifter;

	//If they are within reach of the shoplifter, the guard will catch them
	if (distance_to_shoplifter.Length() < 5.0)
	{
		Guard_State = CAUGHT;
		shoplifted = false;
	}

	//Villain Scenario
	//If the player is within reach, the guard will catch them
	if (modeVillain == true && distance_to_player.Length() < 5.0)
	{
		Guard_State = CAUGHT;
	}

	//Update Guard's State
	UpdateState(player_position, dt);

	//Guard walking animation
	//Left Arm
	if (Rotate_Hand_Left_Back == false)
	{
		Rotation_Left_Hand += (float)(RotationSpeed * 5 * dt);
	}
	if (Rotate_Hand_Left_Back == true)
	{
		Rotation_Left_Hand -= (float)(RotationSpeed * 5 * dt);
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
		Rotation_Right_Hand += (float)(RotationSpeed * 5 * dt);
	}
	if (Rotate_Hand_Right_Back == true)
	{
		Rotation_Right_Hand -= (float)(RotationSpeed * 5 * dt);
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
		Rotation_Left_Leg += (float)(RotationSpeed * 5 * dt);
	}
	if (Rotate_Leg_Left_Back == true)
	{
		Rotation_Left_Leg -= (float)(RotationSpeed * 5 * dt);
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
		Rotation_Right_Leg += (float)(RotationSpeed * 5 * dt);
	}
	if (Rotate_Leg_Right_Back == true)
	{
		Rotation_Right_Leg -= (float)(RotationSpeed * 5 * dt);
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
/******************************************************************************/
/*!
\brief
Updates guard and moves him along patrol path

\param dt - delta time update
*/
/******************************************************************************/
void CGuardAI::PatrolPath(double dt)
{
	//If Guard is facing the correct direction, he will move towards closest point at a rate of 1 unit
	if (rotation_complete == true)
	{
		guard_position += distance_to_point.Normalized() * dt * MovementSpeed;
	}
	//Else, he will turn to face the correct direction
	else
	{
		//Update the difference of rotation
		rotation_difference.y = guard_next_direction - guard_direction.y;
		//Rotate guard if not fully rotated
		if (fabs(fabs(guard_direction.y) - fabs(guard_next_direction)) >= 2.0f)
		{
			guard_direction += rotation_difference.Normalized() * dt * (RotationSpeed * 5);
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
	if (distance_to_point.Length() <= 2.0F)
	{
		//However, if someone has shoplifted, he will begin to chase down the person
		if (shoplifted == true)
		{
			Guard_State = CHASING;
			MovementSpeed *= 2;
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
/******************************************************************************/
/*!
\brief
Updates guard and moves him along path to chase shoplifter

\param dt - delta time update
*/
/******************************************************************************/
void CGuardAI::ChasingPath(double dt)
{
	//If the guard is done turning on the spot, he will begin the pathing
	if (rotation_complete == true)
	{
		//Guard will first follow a set path out of the Supermarket before chasing the shoplifter
		Vector3 Z_Required, X_Required;
		if (chase_path_completed == false)
		{
			Z_Required.Set(guard_position.x, guard_position.y, (12.0F - guard_position.z));
			X_Required.Set((guard_position.x - shoplifter.x),guard_position.y,guard_position.z);
		}
		//Once done, guard will chase down shoplifter
		if (X_Required.x <= 2.0F && Z_Required.z <= 2.0F)
		{	
			Z_Required.z = X_Required.x = 0.0F;
			chase_path_completed = true;
			//Guard will close in on shoplifter
			distance_to_shoplifter = guard_position - shoplifter;
			guard_position -= distance_to_shoplifter.Normalized() * dt * MovementSpeed;

			
			//Guard will always face shoplifter
			//Obtain angle via trigonometry
			Vector3 far(guard_position.x, 0, shoplifter.z);
			Vector3 adjecant = far - guard_position;
			Vector3 hypotenuse = guard_position - shoplifter;
			float angle = acos(adjecant.Length() / hypotenuse.Length()) * 180.0f / M_PI;

			//Angle obtained will only result in 0 ~ 90 degrees
			//full 360 degree rotation is based on Guard and Player positions
			if (guard_position.x >= shoplifter.x)
			{
				if (guard_position.z >= shoplifter.z) 
				{
					angle += 180.0f;
				}
				else 
				{
					angle *= -1.0f;
				}
			}
			else
			{
				if (guard_position.z >= shoplifter.z) 
				{
					angle += 180.0f;
					angle *= -1.0f;
				}
				else 
				{
				}
			}

			//Set the guard to immediately face the direction of the shoplifter
			//Instead of rotating to it
			guard_direction.y = guard_next_direction = angle;
		}

		//Guard will first move to Z-coordinates which is just before the Cashier area
		if (Z_Required.z >= 2.0F)
		{				
			Z_Required.x = 0.0F;
			guard_position += Z_Required.Normalized() * dt * MovementSpeed;

			guard_next_direction = 0.0F;
		}
		//Guard will then move in a straight line, out of the shop
		if (X_Required.x >= 2.0F && Z_Required.z <= 2.0F)
		{	
			X_Required.z = 0.0F;
			
			guard_position -= X_Required.Normalized() * dt * MovementSpeed;
			if (guard_next_direction != 90.0F && guard_next_direction != -90.0F)
			{
				if (guard_position.x - shoplifter.x > 0.0F)
				{
					guard_next_direction = -90.0F;
				}
				else
				{
					guard_next_direction = 90.0F;
				}
			}
		}

		//Rotate the guard to face the direction he's walking
		rotation_difference.y = guard_next_direction - guard_direction.y;
		if (guard_direction.y != guard_next_direction)
		{
			rotation_complete = false;
		}
	} //End of check of whether guard is rotating on spot

	//If guard is not done rotating, rotate the guard
	else
	{
		//Update the difference of rotation
		rotation_difference.y = guard_next_direction - guard_direction.y;
		//Continue rotating guard if not fully rotated
		if (fabs(fabs(guard_direction.y) - fabs(guard_next_direction)) >= 2.0F)
		{
			guard_direction += rotation_difference.Normalized() * dt * (RotationSpeed * 5);
		}
		//Else, rotation is complete
		else
		{
			rotation_complete = true;
		}
	}

}
/******************************************************************************/
/*!
\brief
Rotates the guard to his left

\param rotation - amount to rotate in degrees
*/
/******************************************************************************/
void CGuardAI::RotateLeft(float rotation)
{
	//Add the difference of the rotation
	if (rotation_complete == true)
	{
		guard_next_direction = guard_direction.y + rotation;
		rotation_complete = false;
	}
}
/******************************************************************************/
/*!
\brief
Rotates the guard to his right

\param rotation - amount to rotate in degrees
*/
/******************************************************************************/
void CGuardAI::RotateRight(float rotation)
{
	//Add the difference of the rotation
	if (rotation_complete == true)
	{
		guard_next_direction = guard_direction.y - rotation;
		rotation_complete = false;
	}
}
/******************************************************************************/
/*!
\brief
Sets the shoplifter's position

\param shoplifter_position - The shoplifter's current position
*/
/******************************************************************************/
void CGuardAI::setShoplifter(Vector3 shoplifter_position)
{
	shoplifter = shoplifter_position;
}
/******************************************************************************/
/*!
\brief
Returns X axis coordinate of guard's position
\return 
	Value of X coordinate of guard's position
*/
/******************************************************************************/
float CGuardAI::getX(void)
{
	return guard_position.x;
}
/******************************************************************************/
/*!
\brief
Returns Y axis coordinate of guard's position
\return 
	Value of Y coordinate of guard's position
*/
/******************************************************************************/
float CGuardAI::getY(void)
{
	return guard_position.y;
}
/******************************************************************************/
/*!
\brief
Returns Y axis coordinate of guard's direction (Amount of degrees to rotate counter-clockwise)
\return 
	Value of Y coordinate of guard's direction
*/
/******************************************************************************/
float CGuardAI::getY2(void)
{
	return guard_direction.y;
}
/******************************************************************************/
/*!
\brief
Returns Z axis coordinate of guard's position
\return 
	Value of Z coordinate of guard's position
*/
/******************************************************************************/
float CGuardAI::getZ(void)
{
	return guard_position.z;
}
/******************************************************************************/
/*!
\brief
Returns state of guard
\return
	State of guard as a string
*/
/******************************************************************************/
string CGuardAI::returnState(void)
{
	//Return Guard's current State
	switch (Guard_State)
	{
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