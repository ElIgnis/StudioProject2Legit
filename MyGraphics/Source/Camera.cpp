/******************************************************************************/
/*!
\file	Camera.cpp
\author Wei Liang Lee
\par	email: 140511H\@mymail.nyp.edu.sg
\brief
Camera for viewing one side of the scene
*/
/******************************************************************************/
#include "Camera.h"
#include "Application.h"
#include "Mtx44.h"
/******************************************************************************/
/*!
\brief
Default Constructor

\exception None
\return None
*/
/******************************************************************************/
Camera::Camera()
{
	Reset();
}
/******************************************************************************/
/*!
\brief
Default Destructor
*/
/******************************************************************************/
Camera::~Camera()
{
}
/******************************************************************************/
/*!
\brief
Intialise the camera

\param pos - position of vector
\param target - position of target
\param up - position of up
*/
/******************************************************************************/
void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;
}
/******************************************************************************/
/*!
\brief
Reset the camera
*/
/******************************************************************************/
void Camera::Reset()
{
	position.Set(1, 0, 0);
	target.Set(0, 0, 0);
	up.Set(0, 1, 0);
}
/******************************************************************************/
/*!
\brief
Updates the camera

\param dt - updates the camera based on delta time
*/
/******************************************************************************/
void Camera::Update(double dt)
{
	static const float CAMERA_SPEED = 200.f;
	if(Application::IsKeyPressed(VK_LEFT) || Application::IsKeyPressed('A'))
	{
		position.x -= (float)(CAMERA_SPEED * 0.2 * dt);
	}
	if(Application::IsKeyPressed(VK_RIGHT) || Application::IsKeyPressed('D'))
	{
		position.x += (float)(CAMERA_SPEED * 0.2 * dt);
	}
	if(Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed('W'))
	{
		position.y += (float)(CAMERA_SPEED * 0.2 * dt);
	}
	if(Application::IsKeyPressed(VK_DOWN) || Application::IsKeyPressed('S'))
	{
		position.y -= (float)(CAMERA_SPEED * 0.2 * dt);
	}
}