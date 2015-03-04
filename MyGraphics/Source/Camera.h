/******************************************************************************/
/*!
\file	Camera.h
\author Wei Liang Lee
\par	email: 140511H\@mymail.nyp.edu.sg
\brief
Camera for viewing one side of the scene
*/
/******************************************************************************/
#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
/******************************************************************************/
/*!
		Class Camera:
\brief	A camera with center point at (0, 0, 0)
*/
/******************************************************************************/
class Camera
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;

	Camera();
	~Camera();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Reset();
	virtual void Update(double dt);
};

#endif