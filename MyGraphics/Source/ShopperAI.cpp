#include "ShopperAI.h"

bool ShopperPath2[12] = { true, false, false, false, false, false, false, false, false, false, false, false };
bool ShopperPath3[15] = { true, false, false, false, false, false, false, false, false, false, false, false, false, false, false };

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
	Animate_ON = true;
	Directions = false;
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


CShopperAI::~CShopperAI()
{
}
//Kel's
void CShopperAI::setPositionX(float x)
{
	position.x = x;
}
void CShopperAI::setPositionZ(float z)
{
	position.z = z;
}

float CShopperAI::getPositionX(void)
{
	return position.x;
}
float CShopperAI::getPositionZ(void)
{
	return position.z;
}

void CShopperAI::setShopperDirection(int r)
{
	Rotangle = r;
}
int CShopperAI::getShopperDirection(void)
{
	return Rotangle;
}

//Kel's
void CShopperAI::ShopperInitialize(void)
{
	//initialize Shopper state
	ShopperSTATE = WALK;
}

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

	////Walking ( Last week Coding)
	//if (walkFront = true)
	//{
	//	if (position.z > -56)
	//	{
	//		position.z -= (30 * dt);
	//	}
	//	else if ((position.z <= -56) && (position.x > 8))
	//	{ 
	//		position.x -= (30 * dt);
	//		direction = 1;
	//	}
	//	else if ((position.z <= -55) && (position.x >= 7))
	//	{
	//		direction = 2;
	//		walkFront = false;
	//		walkBack = true;
	//	}
	//}
	//if ((walkBack == true))// && (walkFront ==false))
	//{
	//	position.z += (30 * dt);
	//}

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
		}
		if (timer == 40)
		{
			NewState = CShopperAI::EXIT;
			Animate_ON = true;
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
					//NewState = CShopperAI::WALK;
				}
			}
		}
		if (NewState == CShopperAI::WALK)
		{
			ShopperPath2[10] = true;
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
			ShopperPath2[10] = false;
			ShopperPath3[0] = true;
			RENDERINGAI = false;
			Rotangle = 0;
			timer = 0;
			position.Set(36, 1, 37);
		}
	}
}
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
			RenderTrolley = false;
			item_choco = false;
			item_iceCream = false;
			item_maggie = false;
			item_milo = false;
			item_MnC = false;
			item_sardine = false;
		}
		if (NewState == CShopperAI::Pay)
		{
			timer++;
		}
		if (timer == 100)
		{
			NewState = CShopperAI::EXIT;
		}
		if (NewState == CShopperAI::EXIT)
		{
			direction = 10;
			SetDirection = true;

			NewState = CShopperAI::WALK;
			if (SetDirection == true)
			{
				if (Animate_ON == false)
				{
					item_choco = true;
					item_iceCream = true;
					item_maggie = true;
					item_milo = true;
					item_MnC = true;
					item_sardine = true;
					RenderTrolley = false;
					ShopperPath3[12] = false;
					//NewState = CShopperAI::WALK;
				}
			}
		}
		if (NewState == CShopperAI::WALK)
		{
			ShopperPath3[12] = true;
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
			ShopperPath3[12] = false;
			RENDERINGAI = true;
			ShopperPath2[0] = true;
			position.Set(36, 1, 37);
			Rotangle = 0;
			timer = 0;
		}
	}
}


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
