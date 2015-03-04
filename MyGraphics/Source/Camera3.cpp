#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

Camera3::Camera3()
{
	worldScale = 4004.f;
	angle = 0;
	RotationYAxis = -90.f;
	CAMERA_SPEED = 100.f;
	CAMERA_SPEED2 = 10.f;
	HasEntered = false;
	IsCrouched = false;
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	
	playerMovement = true;
	RotationYAxis = -90.f;
	HasEntered = false;
	IsCrouched = false;
	playerArmRotation = 0.f;
	angle = 0.f;
}

void Camera3::Update(double dt)
{
	CAMERA_SPEED = 100.f;
	CAMERA_SPEED2 = 10.f;
	if(CanRotate)
	{
		if(Application::IsKeyPressed(VK_LEFT))
		{
			Vector3 view = (target - position).Normalized();
			float yaw = (float)(CAMERA_SPEED * dt);
			Mtx44 rotation;
			rotation.SetToRotation(yaw, 0, 1, 0);
			view = rotation * view;
			up = rotation * up;
			target = view + position;

			RotationYAxis += (float)(CAMERA_SPEED * dt);
			//Reset angle for calculation
			if(RotationYAxis >= 180.f)
			{
				RotationYAxis = -180.f;
			}
			playerArmRotation += (float)(CAMERA_SPEED * dt);
			//Vector3 view = (target - position).Normalized();
			//Vector3 right = view.Cross(up);
			//right.Normalize();
			//right.y = 0;
			//up = right.Cross(view).Normalized();

			//float yaw = (float)(CAMERA_SPEED * dt);
			//Mtx44 rotation;
			//rotation.SetToRotation(yaw, up.x, up.y, up.z);
			//view = rotation * view;
			//target = view + position;
		}
		if(Application::IsKeyPressed(VK_RIGHT))
		{
			Vector3 view = (target - position).Normalized();
			float yaw = (float)(-CAMERA_SPEED * dt);
			Mtx44 rotation;
			rotation.SetToRotation(yaw, 0, 1, 0);
			view = rotation * view;
			up = rotation * up;
			target = view + position;

			RotationYAxis -= (float)(CAMERA_SPEED * dt);
			//Reset angle for calculation
			if(RotationYAxis <= -180.f)
			{
				RotationYAxis = 180.f;
			}
			playerArmRotation -= (float)(CAMERA_SPEED * dt);

			//Vector3 view = (target - position).Normalized();
			//Vector3 right = view.Cross(up);
			//right.Normalize();
			//right.y = 0;
			//up = right.Cross(view).Normalized();
			//float yaw = (float)(-CAMERA_SPEED * dt);
			//Mtx44 rotation;
			//rotation.SetToRotation(yaw, up.x, up.y, up.z);
			//view = rotation * view;
			//target = view + position;
		}
	}
	if(Application::IsKeyPressed(VK_UP))
	{
		float pitch = 0.f;
		if(angle < 75.f)
		{
			angle += (float)(CAMERA_SPEED * dt);
			pitch = (float)(CAMERA_SPEED * dt);
		}
		else
		{
			pitch = 0;
		}
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = view + position;
	}
	if(Application::IsKeyPressed(VK_DOWN))
	{
		float pitch = 0.f;
		if(angle > -75.f)
		{
			angle += (float)(-CAMERA_SPEED * dt);
			pitch = (float)(-CAMERA_SPEED * dt);
		}
		else
		{
			pitch = 0;
		}
		
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = view + position;
	}
	
	//Crouching
	if(Application::IsKeyPressed(VK_CONTROL))
	{
		IsCrouched = true;
		if(position.y > -3.5 && target.y > -3.5)
		{
			position.y -= CAMERA_SPEED2 * dt;
			target.y -= CAMERA_SPEED2 * dt;
		}
	}
	//Standing up
	if(Application::IsKeyPressed(VK_SPACE))
	{
		if(position.y < 0 && target.y < 0)
		{
		position.y += CAMERA_SPEED2 * dt;
		target.y += CAMERA_SPEED2 * dt;
		}
		else
		{
			IsCrouched = false;
		}
	}
	//if(Application::IsKeyPressed('R'))
	//{
	//	Reset();
	//}
}

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}

void Camera3::SetBounds(float NewMinWidth, float NewMaxWidth, float NewMinLength, float NewMaxLength)
{
	MinWidth.push_back(NewMinWidth);
	MaxWidth.push_back(NewMaxWidth);
	MinLength.push_back(NewMinLength);
	MaxLength.push_back(NewMaxLength);

}

void Camera3::BoundsCheck()
{
	//Fill in position here and check
	for(int i = 0; i < MinWidth.size(); i++)
	{
		if(position.x > MinWidth.at(i) && position.x < MaxWidth.at(i)
			&& position.z > MinLength.at(i) && position.z < MaxLength.at(i))
		{
			Limiter();
		}
	}
	if(HasEntered)
	{
		if(position.x > 31.f && position.x < 43.f
			&& position.z > 35.f && position.z < 39.f)
		{
			Limiter();
		}
	}
}

//Collision
void Camera3::Limiter(void)
{
	position = oldpos;
	target = oldtgt;
	oldpos = position;
	oldtgt = target;
}

void Camera3::Movement(double dt)
{
	if (playerMovement == true)
	{
	if(Application::IsKeyPressed('A'))
	{
		oldpos = position;
		oldtgt = target;

		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		position -= right * CAMERA_SPEED2 * dt;
		target -= right * CAMERA_SPEED2 * dt;
		BoundsCheck();
	}
	if(Application::IsKeyPressed('D'))
	{
		oldpos = position;
		oldtgt = target;

		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		position += right * CAMERA_SPEED2 * dt;
		target += right * CAMERA_SPEED2 * dt;
		BoundsCheck();
	}
	if(Application::IsKeyPressed('W'))
	{
		oldpos = position;
		oldtgt = target;
		Vector3 view = (target - position).Normalized();
		view.y = 0;
		view.Normalize();
		position += view * CAMERA_SPEED2 * dt;
		target += view * CAMERA_SPEED2 * dt;
		BoundsCheck();
	}
	if(Application::IsKeyPressed('S'))
	{
		oldpos = position;
		oldtgt = target;
		Vector3 view = (target - position).Normalized();
		view.y = 0;
		view.Normalize();
		position -= view * CAMERA_SPEED2 * dt;
		target -= view * CAMERA_SPEED2 * dt;
		BoundsCheck();
	}
	}
}

void Camera3::reverseMovement(double dt)
{
	if (playerMovement == true)
	{
		if(Application::IsKeyPressed('A'))
		{
			oldpos = position;
			oldtgt = target;

			Vector3 view = (target - position).Normalized();
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			position += right * CAMERA_SPEED2 * dt;
			target += right * CAMERA_SPEED2 * dt;
			BoundsCheck();
		}
		if(Application::IsKeyPressed('D'))
		{
			oldpos = position;
			oldtgt = target;

			Vector3 view = (target - position).Normalized();
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			position -= right * CAMERA_SPEED2 * dt;
			target -= right * CAMERA_SPEED2 * dt;
			BoundsCheck();
		}
		if(Application::IsKeyPressed('W'))
		{
			oldpos = position;
			oldtgt = target;
			Vector3 view = (target - position).Normalized();
			view.y = 0;
			view.Normalize();
			position -= view * CAMERA_SPEED2 * dt;
			target -= view * CAMERA_SPEED2 * dt;
			BoundsCheck();
		}
		if(Application::IsKeyPressed('S'))
		{
			oldpos = position;
			oldtgt = target;
			Vector3 view = (target - position).Normalized();
			view.y = 0;
			view.Normalize();
			position += view * CAMERA_SPEED2 * dt;
			target += view * CAMERA_SPEED2 * dt;
			BoundsCheck();
		}
	}
}