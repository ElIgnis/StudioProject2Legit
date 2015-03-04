/******************************************************************************/
/*!
\file	ShopperAI.cpp
\author Kelvin Tan Young Yew
\par	email: 144117P\@mymail.nyp.edu.sg
\brief
Shopper NPC without trolley walking around and takes some items before checking out
*/
/******************************************************************************/
#include "ShopperAI.h"

bool ShopperPath2[ShopperPathSize2] = { true, false, false, false, false, false, false, false, false, false };
bool ShopperPath3[ShopperPathSize3] = { true, false, false, false, false, false, false, false, false, false, false, false };
/******************************************************************************/
/*!
\brief
Default Constructor

\exception None
\return None
*/
/******************************************************************************/
CShopperAI::CShopperAI()
{
	//starting point
	position.x = 36;
	position.y = 1;
	position.z = 37;
	//position.Set(36, 1, 37);
	direction = 0;
	Rotangle = 0;
	timer = 0;
	SetDirection = false;
	Directions = false;
	Animate_ON = true;
	RENDERINGAI = true;
	//timer_item1 = 0;
	item1 = false;
	item2 = false;
	RenderTrolley = false;
	item_milo = false;
	item_sardine =false;
	item_MnC = false;
	item_maggie = false;
	item_iceCream = false;
	item_choco = false;
}
/******************************************************************************/
/*!
\brief
Default Destructor
*/
/******************************************************************************/
CShopperAI::~CShopperAI()
{
}
/******************************************************************************/
/*!
\brief
Sets X axis position

\param x - X axis position
*/
/******************************************************************************/
void CShopperAI::setPositionX(float x)
{
	position.x = x;
}
/******************************************************************************/
/*!
\brief
Sets Z axis position

\param x - Z axis position
*/
/******************************************************************************/
void CShopperAI::setPositionZ(float z)
{
	position.z = z;
}
/******************************************************************************/
/*!
\brief
Sets X axis position

\return X axis position
*/
/******************************************************************************/
float CShopperAI::getPositionX(void)
{
	return position.x;
}
/******************************************************************************/
/*!
\brief
Sets Z axis position

\return Z axis position
*/
/******************************************************************************/
float CShopperAI::getPositionZ(void)
{
	return position.z;
}
/******************************************************************************/
/*!
\brief
Sets shopper direction

\param r - direction of shopper
*/
/******************************************************************************/
void CShopperAI::setShopperDirection(int r)
{
	Rotangle = r;
}
/******************************************************************************/
/*!
\brief
Returns rotation angle

\return rotation angle of shopper
*/
/******************************************************************************/
int CShopperAI::getShopperDirection(void)
{
	return Rotangle;
}
/******************************************************************************/
/*!
\brief
Initialise shopper properties

*/
/******************************************************************************/
void CShopperAI::ShopperInitialize(void)
{
	ShopperPath2[0] = true;
	for(int i = 1; i < ShopperPathSize2; i++)
	{
		ShopperPath2[i] = false;
	}

	ShopperPath3[0] = true;
	for(int i = 1; i < ShopperPathSize3; i++)
	{
		ShopperPath3[i] = false;
	}

	//starting point
	position.x = 36;
	position.y = 1;
	position.z = 37;
	direction = 0;
	Rotangle = 0;
	timer = 0;
	SetDirection = false;
	Directions = false;
	Animate_ON = true;
	RENDERINGAI = true;
	item1 = false;
	item2 = false;
	RenderTrolley = false;
	item_milo = false;
	item_sardine =false;
	item_MnC = false;
	item_maggie = false;
	item_iceCream = false;
	item_choco = false;

	//initialize Shopper state
	ShopperSTATE = WALK;
}
/******************************************************************************/
/*!
\brief
Updates path of shopper NPC

\param dt - delta time update
\param Playerposition - position of player
*/
/******************************************************************************/
void CShopperAI::UpdatePath(double dt, Vector3 &Playerposition)
{
	//TODO: Update path till if reach item
	//TODO: if reach item, take item
	//TODO: generate item from list
	
	if (RENDERINGAI == true)
	{
		WalkingPath(dt, CShopperAI::WALK);
	}
	else if (RENDERINGAI == false)
	{
		WalkingPath3(dt, CShopperAI::WALK);
	}
}
/******************************************************************************/
/*!
\brief
Updates path of shopper NPC

\param dt - delta time update
\param NewState - moves based on state
*/
/******************************************************************************/
void CShopperAI::WalkingPath(double dt, int NewState)
{
	//#######Rotation of Shoppers#############

	if (SetDirection == true)
	{
		//turn Left's
		if (direction == 0)
		{
			if (Rotangle != 0)
			{
				//Rotangle += (float)(90 * dt);
				Rotangle++;
			
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 1)
		{
			if (Rotangle != 90)
			{
				//Rotangle += (float)(90 * dt);
				Rotangle++;
			
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 2)
		{
			if (Rotangle != 180)
			{
				//Rotangle += (float)(90 * dt);
				Rotangle++;
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 3)
		{
			if (Rotangle != 270)
			{
				//Rotangle += (float)(90 * dt);
				Rotangle++;
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		//Turn Right's
		else if (direction == 4)
		{
			if (Rotangle != 0)
			{
				//Rotangle -= (float)(90 * dt);
				Rotangle --;
			}
			else
			{

				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 5)
		{
			if (Rotangle != -90)
			{
				//Rotangle -= (float)(90 * dt);
				Rotangle--;
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 6)
		{
			if (Rotangle != -180)
			{
				//Rotangle -= (float)(90 * dt);
				Rotangle--;
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 7)
		{
			if (Rotangle != -270)
			{
				//Rotangle -= (float)(90 * dt);
				Rotangle--;
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}

		else if (direction == 8)
		{
			if (Rotangle != -90)
			{
				//Rotangle += (float)(90 * dt);
				Rotangle++;
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
	}
	// speed
	float Speed = 10.f;
	//Shopper2 Path-ing
	float Shopper2 = 15.f;
	float Shopper2_1= 38.f;
	//float Item_1 = -20.f;
	float Shopper2_2 = 55.f;
	float Shopper2_3 = 30.f;
//	float Item_2 = -21.f;
	float Shopper2_4 = 5.f;
	float Shopper2_5 = 17.f;
	float Shopper2_6 = 9.f;
	float Shopper2_7 = 20.f;
	float Shopper2_EXIT = 36.f;

	//Path 2
	if (ShopperPath2[0] == true)
	{
		
		if (position.z > Shopper2)
		{
			MoveZMinus(Shopper2, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 1; 
			SetDirection = true;

			if (SetDirection == true)
			{
				
				if (Animate_ON == false)
				{
					ShopperPath2[0] = false;
					ShopperPath2[1] = true;
				}
			}

		}
	}
	if (ShopperPath2[1] == true)
	{
		
		if (position.x > -Shopper2_1)
		{
			MoveXMinus(-Shopper2_1, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 4;
			SetDirection = true;
			item1 = true;

			if (SetDirection == true)
			{
				
				if (Animate_ON == false)
				{
					ShopperPath2[1] = false;
					ShopperPath2[2] = true;
				}
			}
		}
	}
	if (ShopperPath2[2] == true)
	{
		if (position.z > -Shopper2_2)
		{
			MoveZMinus(-Shopper2_2, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 5;
			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath2[2] = false;
					ShopperPath2[3] = true;
				}
			}
		}
	}
	if (ShopperPath2[3] == true)
	{
		if (position.x < -Shopper2_3)
		{
			MoveXPlus(-Shopper2_3, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 6;
			item2 = true;
			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath2[3] = false;
					ShopperPath2[4] = true;
				}
			}
		}
	}
	if (ShopperPath2[4] == true)
	{
		if (position.z < Shopper2_4)
		{
			MoveZPlus(Shopper2_4, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 8;

			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath2[4] = false;
					ShopperPath2[5] = true;
				}
			}
		}
	}
	if (ShopperPath2[5] == true)
	{
		if (position.x < -Shopper2_5)
		{
			MoveXPlus(-Shopper2_5, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 0;

			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath2[5] = false;
					ShopperPath2[6] = true;
				}
			}
		}
	}

	if (ShopperPath2[6] == true)
	{
		if (position.z > -Shopper2_2)
		{
			MoveZMinus(-Shopper2_2, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 5;
			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath2[6] = false;
					ShopperPath2[7] = true;
				}
			}
		}
	}
	if (ShopperPath2[7] == true)
	{
		if (position.x < -Shopper2_6)
		{
			MoveXPlus(Shopper2_6, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 6;
			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath2[7] = false;
					ShopperPath2[8] = true;
				}
			}
		}
	}
	if (ShopperPath2[8] == true)
	{
		if (position.z < Shopper2_7)
		{
			MoveZPlus(Shopper2_7, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 8;
			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath2[8] = false;
					ShopperPath2[9] = true;
				}
			}
		}
	}
	if (ShopperPath2[9] == true)
	{
		if (position.z >= Shopper2_7)
		{
			NewState = CShopperAI::Pay;
		}
		if (NewState == CShopperAI::Pay)
		{
			timer++;
			item1 = false;
			item2 = false;
			Animate_ON = true;
		}
		if (timer == 40)
		{
			NewState = CShopperAI::EXIT;
			Animate_ON = false;
		}
		if (NewState == CShopperAI::EXIT)
		{
			item1 = true;
			item2 = true;
			direction = 6;
			SetDirection = true;
			NewState = CShopperAI::WALK;
			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath2[9] = false;
					ShopperPath2[10] = true;
				}
			}
		}
	}		
	if (ShopperPath2[10] == true)
	{
		if (position.z < Shopper2_EXIT)
		{
			MoveZPlus(Shopper2_EXIT, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			position.x = 36;
			position.y = 1;
			position.z = 37;
			direction = 0;
			Rotangle = 0;
			timer = 0;
			SetDirection = false;
			Directions = false;
			item1 = false;
			item2 = false;
			ShopperPath2[10] = false;
			ShopperPath2[0] = true;
			RENDERINGAI = false;
		}
	}
}
/******************************************************************************/
/*!
\brief
Updates alternate path of shopper NPC

\param dt - delta time update
\param NewState - moves based on state
*/
/******************************************************************************/
void CShopperAI::WalkingPath3(double dt, int NewState)
{
	//#######Rotation of Shoppers#############
	if (SetDirection == true)
	{
		//turn Left's
		if (direction == 0)
		{
			if (Rotangle != 0)
			{
				//Rotangle += (float)(90 * dt);
				Rotangle++;
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 1)
		{
			if (Rotangle != 90)
			{
				//Rotangle += (float)(90 * dt);
				Rotangle++;
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 2)
		{
			if (Rotangle != 180)
			{
				//Rotangle += (float)(90 * dt);
				Rotangle++;
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 3)
		{
			if (Rotangle != 270)
			{
				//Rotangle += (float)(90 * dt);
				Rotangle++;
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		//Turn Right's
		else if (direction == 4)
		{
			if (Rotangle != 0)
			{
				//Rotangle -= (float)(90 * dt);
				Rotangle --;
			}
			else
			{

				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 5)
		{
			if (Rotangle != -90)
			{
				//Rotangle -= (float)(90 * dt);
				Rotangle--;
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 6)
		{
			if (Rotangle != -180)
			{
				//Rotangle -= (float)(90 * dt);
				Rotangle--;
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 7)
		{
			if (Rotangle != -270)
			{
				//Rotangle -= (float)(90 * dt);
				Rotangle--;
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}

		else if (direction == 8)
		{
			if (Rotangle != -90)
			{
				//Rotangle += (float)(90 * dt);
				Rotangle++;
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 9)
		{
			if (Rotangle != 90)
			{
				//Rotangle -= (float)(90 * dt);
				Rotangle--;
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
		else if (direction == 10)
		{
			if (Rotangle != 180)
			{
				//Rotangle -= (float)(90 * dt);
				Rotangle--;
			}
			else
			{
				Animate_ON = false;
				SetDirection = false;
			}
		}
	}
	float Speed = 10.f;
	//Shopper3 Path-ing
	//Trolley
	float trolley = 30.f;
	float take_trolley = 29.f;
	//Red shelf coords
	float RedShelfBack = 56.f;
	float RedShelfFront = 5.f;
	float Right_RedShelfRight = 19.5f;
	float Right_RedShelfLeft = 9.5f;
	float Left_RedShelfRight = 18.5f;
	float Left_RedShelfLeft = 28.5f;

	//Middle Fridge
	float FridgeFront = 2.f;
	float FridgeRight = 1.5f;
	float FridgeLeft = 7.5f;

	//Cold fridge
	float ColdFridgeBack = 56.f;
	float Left_ColdFridge = 39.f;
	float Right_ColdFridge = 37.f;
	float ColdFridgeFront = 16.f;

	//Path 3
	if (ShopperPath3[0] == true)
	{

		if (position.z > trolley)
		{
			MoveZMinus(trolley, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 1;
			SetDirection = true;

			if (SetDirection == true)
			{

				if (Animate_ON == false)
				{
					ShopperPath3[0] = false;
					ShopperPath3[1] = true;
				}
			}

		}
	}
	if (ShopperPath3[1] == true)
	{

		if (position.x > take_trolley)
		{
			MoveXMinus(take_trolley, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 4;
			SetDirection = true;
			RenderTrolley = true;

			if (SetDirection == true)
			{

				if (Animate_ON == false)
				{
					ShopperPath3[1] = false;
					ShopperPath3[2] = true;
				}
			}
		}
	}
	if (ShopperPath3[2] == true)
	{
		if (position.z > -RedShelfBack)
		{
			MoveZMinus(-RedShelfBack, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 1;
			SetDirection = true;
			item_milo = true;
			item_sardine = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath3[2] = false;
					ShopperPath3[3] = true;
				}
			}
		}
	}
	if (ShopperPath3[3] == true)
	{
		if (position.x > 7.f)
		{
			MoveXMinus(7.f, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 2;
			SetDirection = true;
			item_maggie = true;
			item_MnC = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath3[3] = false;
					ShopperPath3[4] = true;
				}
			}
		}
	}
	if (ShopperPath3[4] == true)
	{
		if (position.z < 2.5f)
		{
			MoveZPlus(2.5f, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 9;

			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath3[4] = false;
					ShopperPath3[5] = true;
				}
			}
		}
	}
	if (ShopperPath3[5] == true)
	{
		if (position.x > 6.f)
		{
			MoveXMinus(6.f, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 4;

			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath3[5] = false;
					ShopperPath3[6] = true;
				}
			}
		}
	}
	if (ShopperPath3[6] == true)
	{
		if (position.z > -ColdFridgeBack)
		{
			MoveZMinus(-ColdFridgeBack, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 1;
			SetDirection = true;
			item_choco = true;
			item_iceCream = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath3[6] = false;
					ShopperPath3[7] = true;
				}
			}
		}
	}
	if (ShopperPath3[7] == true)
	{
		if (position.x > -16.f)
		{
			MoveXMinus(-16.f, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 2;
			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath3[7] = false;
					ShopperPath3[8] = true;
				}
			}
		}
	}
	if (ShopperPath3[8] == true)
	{
		if (position.z < 6.f)
		{
			MoveZPlus(6.f, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 3;
			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath3[8] = false;
					ShopperPath3[9] = true;
				}
			}
		}
	}
	if (ShopperPath3[9] == true)
	{
		if (position.x < -6.5f)
		{
			MoveXPlus(-6.5f, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 10;
			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath3[9] = false;
					ShopperPath3[10] = true;
				}
			}
		}
	}
	if (ShopperPath3[10] == true)
	{
		if (position.z < 19.f)
		{
			MoveZPlus(19.f, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			direction = 3;
			SetDirection = true;

			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath3[10] = false;
					ShopperPath3[11] = true;
				}
			}
		}
	}
	if (ShopperPath3[11] == true)
	{
		if (position.z >= 19.f)
		{
			NewState = CShopperAI::Pay;
		}
		if (NewState == CShopperAI::Pay)
		{
			timer++;
			RenderTrolley = false;
			item_choco = false;
			item_iceCream = false;
			item_maggie = false;
			item_milo = false;
			item_MnC = false;
			item_sardine = false;
			Animate_ON = true;
		}
		if (timer == 100)
		{
			NewState = CShopperAI::EXIT;
			Animate_ON = false;
		}
		if (NewState == CShopperAI::EXIT)
		{
			direction = 10;
			item_choco = true;
			item_iceCream = true;
			item_maggie = true;
			item_milo = true;
			item_MnC = true;
			item_sardine = true;
			RenderTrolley = false;
			SetDirection = true;

			NewState = CShopperAI::WALK;
			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					ShopperPath3[11] = false;
					ShopperPath3[12] = true;
				}
			}
		}
	}
	if (ShopperPath3[12] == true)
	{
		if (position.z < 36.f)
		{
			MoveZPlus(36.f, NewState, Speed, dt);
			Animate_ON = true;
		}
		else
		{
			position.x = 36;
			position.y = 1;
			position.z = 37;
			direction = 0;
			Rotangle = 0;
			timer = 0;
			SetDirection = false;
			Directions = false;
			RenderTrolley = false;
			item_choco = false;
			item_iceCream = false;
			item_maggie = false;
			item_milo = false;
			item_MnC = false;
			item_sardine = false;
			ShopperPath3[12] = false;
			ShopperPath3[0] = true;
			RENDERINGAI = true;
		}
	}
}
/******************************************************************************/
/*!
\brief
Moves Z axis positive

\param StopPoint - point to stop
\param NewState - moves based on state
\param Speed - speed of movement
\param dt - delta time update
*/
/******************************************************************************/
void CShopperAI::MoveZPlus(double StopPoint, int NewState, double Speed, double dt)
{
	//Speed based on state
	if (NewState == CShopperAI::WALK)
	{
		Speed = 10.f;
	}
	else if (NewState == CShopperAI::ShopperSTATE)
	{
		Speed = 0.f;
	}
	//Move till stop point
	if (position.z < StopPoint)
	{
		position.z += (float)(dt * Speed);
	}
}
/******************************************************************************/
/*!
\brief
Moves Z axis negative

\param StopPoint - point to stop
\param NewState - moves based on state
\param Speed - speed of movement
\param dt - delta time update
*/
/******************************************************************************/
void CShopperAI::MoveZMinus(double StopPoint, int NewState, double Speed, double dt)
{
	//Speed based on state
	if (NewState == CShopperAI::WALK)
	{
		Speed = 10.f;
	}
	//Move till stop point
	if (position.z > StopPoint)
	{
		position.z -= (float)(dt * Speed);
	}
}
/******************************************************************************/
/*!
\brief
Moves X axis positive

\param StopPoint - point to stop
\param NewState - moves based on state
\param Speed - speed of movement
\param dt - delta time update
*/
/******************************************************************************/
void CShopperAI::MoveXPlus(double StopPoint, int NewState, double Speed, double dt)
{
	//Speed based on state
	if (NewState == CShopperAI::WALK)
	{
		Speed = 10.f;
	}
	//Move till stop point
	if (position.x < StopPoint)
	{
		position.x += (float)(dt * Speed);
	}
}
/******************************************************************************/
/*!
\brief
Moves x axis negative

\param StopPoint - point to stop
\param NewState - moves based on state
\param Speed - speed of movement
\param dt - delta time update
*/
/******************************************************************************/
void CShopperAI::MoveXMinus(double StopPoint, int NewState, double Speed, double dt)
{
	//Speed based on state
	if (NewState == CShopperAI::WALK)
	{
		Speed = 10.f;
	}
	//Move till stop point
	if (position.x > StopPoint)
	{
		position.x -= (float)(dt * Speed);
	}
}
