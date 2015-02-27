#include "ShopperAI.h"

bool ShopperPath[15] = { true, false, false, false, false, false, false, false, false, false, false, false , false , false , false};
bool ShopperPath2[12] = { true, false, false, false, false, false, false, false, false, false, false, false };

CShopperAI::CShopperAI()
{
	//starting point
	position.x = 36;
	position.y = 0;
	position.z = 37;
	direction = 0;
	Rotangle = 0;
	timer = 0;
	//walkFront = true;
	//walkBack = false;

}


CShopperAI::~CShopperAI()
{
}

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

void CShopperAI::ShopperInitialize(void)
{
	//initialize Shopper state
	ShopperSTATE = WALK;

	//initialize Shopper Points
	//ShopperPoint[0].Set(35,0,15);
	//ShopperPoint[1].Set(35,0,-34);
}

void CShopperAI::UpdatePath(double dt, Vector3 &Playerposition)
{
	//TODO: Update path till if reach item
	//TODO: if reach item, take item
	//TODO: generate item from list
	WalkingPath(dt, CShopperAI::WALK);
	//Payment(dt, CShopperAI::Pay);
	//WalkingPath(dt, CShopperAI::EXIT);
}

void CShopperAI::WalkingPath(double dt, int NewState)
{
	//Rotation of Shoppers
	if (direction == 1)
	{
		Rotangle = 90;
	}
	else if (direction == 2)
	{
		Rotangle = 180;
	}
	else if (direction == 4)
	{
		Rotangle = 270;
	}
	else
	{
		Rotangle = 0;
	}
	////Walking
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

	float Speed = 10.f;
	float RedShelfBack = 55.f;
	float RedShelfFront = 5.f;
	float FridgeFront = 0.f;

	//Shopper2 Path-ing
	float Shopper2 = 15.f;
	float Shopper2_1= 38.f;
	float Shopper2_2 = 55.f;
	float Shopper2_3 = 30.f;
	float Shopper2_4 = 5.f;
	float Shopper2_5 = 17.f;
	float Shopper2_6 = 9.f;
	float Shopper2_7 = 20.f;
	float Shopper2_EXIT = 34.f;


	if (ShopperPath2[0] == true)
	{
		if (position.z > Shopper2)
		{
			MoveZMinus(Shopper2, NewState, Speed, dt);
		}
		else
		{
			ShopperPath2[0] = false;
			ShopperPath2[1] = true;
			direction = 1;
		}
	}
	if (ShopperPath2[1] == true)
	{
		if (position.x > -Shopper2_1)
		{
			MoveXMinus(-Shopper2_1, NewState, Speed, dt);
		}
		else
		{
			ShopperPath2[1] = false;
			ShopperPath2[2] = true;
			direction = 3;
		}
	}
	if (ShopperPath2[2] == true)
	{
		if (position.z > -Shopper2_2)
		{
			MoveZMinus(-Shopper2_2, NewState, Speed, dt);
		}
		else
		{
			ShopperPath2[2] = false;
			ShopperPath2[3] = true;
			direction = 4;
		}
	}
	if (ShopperPath2[3] == true)
	{
		if (position.x < -Shopper2_3)
		{
			MoveXPlus(-Shopper2_3, NewState, Speed, dt);
		}
		else
		{
			ShopperPath2[3] = false;
			ShopperPath2[4] = true;
			direction = 2;
		}
	}
	if (ShopperPath2[4] == true)
	{
		if (position.z < Shopper2_4)
		{
			MoveZPlus(Shopper2_4, NewState, Speed, dt);
		}
		else
		{
			ShopperPath2[4] = false;
			ShopperPath2[5] = true;
			direction = 4;
		}
	}
	if (ShopperPath2[5] == true)
	{
		if (position.x < -Shopper2_5)
		{
			MoveXPlus(-Shopper2_5, NewState, Speed, dt);
		}
		else
		{
			ShopperPath2[5] = false;
			ShopperPath2[6] = true;
			direction = 3;
		}
	}

	if (ShopperPath2[6] == true)
	{
		if (position.z > -Shopper2_2)
		{
			MoveZMinus(-Shopper2_2, NewState, Speed, dt);
		}
		else
		{
			ShopperPath2[6] = false;
			ShopperPath2[7] = true;
			direction = 4;
		}
	}
	if (ShopperPath2[7] == true)
	{
		if (position.x < -Shopper2_6)
		{
			MoveXPlus(Shopper2_6, NewState, Speed, dt);
		}
		else
		{
			ShopperPath2[7] = false;
			ShopperPath2[8] = true;
			direction = 2;
		}
	}
	if (ShopperPath2[8] == true)
	{
		if (position.z < Shopper2_7)
		{
			MoveZPlus(Shopper2_7, NewState, Speed, dt);
		}
		else
		{
			ShopperPath2[8] = false;
			ShopperPath2[9] = true;
			direction = 4;
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
		}
		if (timer == 40)
		{
			NewState = CShopperAI::EXIT;
		}
		if (NewState == CShopperAI::EXIT)
		{
			direction = 2;
			timer = 0;
			ShopperPath2[9] = false;
			NewState = CShopperAI::WALK;
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
		}
		else
		{
			ShopperPath2[10] = false;
		}
	}
	//if (ShopperPath[0] == true)
	//{
	//	if (position.z > -RedShelfBack)
	//	{
	//		MoveZMinus(-RedShelfBack, NewState, Speed, dt);
	//	}
	//	else
	//	{
	//		ShopperPath[0] = false;
	//		ShopperPath[1] = true;
	//		direction = 1;
	//	}
	//}
	//if (ShopperPath[1] == true)
	//{
	//	if (position.x > 9.f)
	//	{
	//		MoveXMinus(9.f, NewState, Speed, dt);
	//	}
	//	else
	//	{
	//		ShopperPath[1] = false;
	//		ShopperPath[2] = true;
	//		direction = 2;
	//	}
	//}
	//if (ShopperPath[2] == true)
	//{
	//	if (position.z < RedShelfFront)
	//	{
	//		MoveZPlus(RedShelfFront, NewState, Speed, dt);
	//	}
	//	else
	//	{
	//		ShopperPath[2] = false;
	//		ShopperPath[3] = true;
	//		direction = 1;
	//	}
	//}
	//if (ShopperPath[3] == true)
	//{
	//	if (position.x > 2.f)
	//	{
	//		MoveXMinus(2.f, NewState, Speed, dt);
	//	}
	//	else
	//	{
	//		ShopperPath[3] = false;
	//		ShopperPath[4] = true;
	//		direction = 3;
	//	}
	//}
	//if (ShopperPath[4] == true)
	//{
	//	if (position.z > -RedShelfBack)
	//	{
	//		MoveZMinus(-RedShelfBack, NewState, Speed, dt);
	//	}
	//	else
	//	{
	//		ShopperPath[4] = false;
	//		ShopperPath[5] = true;
	//		direction = 1;
	//	}
	//}
	//if (ShopperPath[5] == true)
	//{
	//	if (position.x > -8.f)
	//	{
	//		MoveXMinus(-8.f, NewState, Speed, dt);
	//	}
	//	else
	//	{
	//		ShopperPath[5] = false;
	//		ShopperPath[6] = true;
	//		direction = 2;
	//	}
	//}
	//if (ShopperPath[6] == true)
	//{
	//	if (position.z < RedShelfFront)

	//	{
	//		MoveZPlus(RedShelfFront, NewState, Speed, dt);
	//	}
	//	else
	//	{
	//		ShopperPath[6] = false;
	//		ShopperPath[7] = true;
	//		direction = 1;
	//	}
	//}
	//if (ShopperPath[7] == true)
	//{
	//	if (position.x > -18.f)
	//	{
	//		MoveXMinus(-18.f, NewState, Speed, dt);
	//	}
	//	else
	//	{
	//		ShopperPath[7] = false;
	//		ShopperPath[8] = true;
	//		direction = 3;
	//	}
	//}
	//if (ShopperPath[8] == true)
	//{
	//	if (position.z > -RedShelfBack)

	//	{
	//		MoveZMinus(-RedShelfBack, NewState, Speed, dt);
	//	}
	//	else
	//	{
	//		ShopperPath[8] = false;
	//		ShopperPath[9] = true;
	//		direction = 1;
	//	}
	//}
	//if (ShopperPath[9] == true)
	//{
	//	if (position.x > -29.f)
	//	{
	//		MoveXMinus(-29.f, NewState, Speed, dt);
	//	}
	//	else
	//	{
	//		ShopperPath[9] = false;
	//		ShopperPath[10] = true;
	//		direction = 2;
	//	}
	//}
	//if (ShopperPath[10] == true)
	//{
	//	if (position.z < RedShelfFront)

	//	{
	//		MoveZPlus(RedShelfFront, NewState, Speed, dt);
	//	}
	//	else
	//	{
	//		ShopperPath[10] = false;
	//		ShopperPath[11] = true;
	//		direction = 4;
	//	}
	//}
	//if (ShopperPath[11] == true)
	//{
	//	if (position.x < 29.f)
	//	{
	//		MoveXPlus(29.f, NewState, Speed, dt);
	//	}
	//	else
	//	{
	//		ShopperPath[11] = false;
	//		ShopperPath[0] = true;
	//		direction = 3;
	//	}
	//}
}
//void CShopperAI::Payment(double dt, int NewState)
//{
		//if (NewState == CShopperAI::Pay)
		//{
		//	timer++;
		//}
		//if (timer == 100)
		//{
		//	NewState = CShopperAI::EXIT;
		//}
		//if (NewState == CShopperAI::EXIT)
		//{
		//	direction = 1;
		//	timer = 0;
		//}
//}
void CShopperAI::MoveZPlus(double StopPoint, int NewState, double Speed, double dt)
{
	//Speed based on state
	if (NewState == CShopperAI::WALK)
	{
		Speed = 30.f;
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
		Speed = 30.f;
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
		Speed = 30.f;
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
		Speed = 30.f;
	}
	//Move till stop point
	if (position.x > StopPoint)
	{
		position.x -= (float)(dt * Speed);
	}
}
