#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Camera.h"
#include <vector>
#include <Windows.h>

using std::vector;

class Camera3 : public Camera
{
public:
	//Vector3 position;
	//Vector3 target;
	//Vector3 up;
	bool CanRotate;
	bool IsCrouched;
	float worldScale;
	float angle;
	float RotationYAxis;
	float playerArmRotation;
	float CAMERA_SPEED;
	float CAMERA_SPEED2;

	vector<float>MinWidth;
	vector<float>MaxWidth;
	vector<float>MinLength;
	vector<float>MaxLength;
	vector<Vector3>TrolleyMin;
	vector<Vector3>TrolleyMax;

	Vector3 oldpos;
	Vector3 oldtgt;
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	Camera3();
	~Camera3();

	//Boundary checking
	void TrolleyBounds(Vector3 &Minimum, Vector3 &Maximum);
	void SetBounds(float NewMinWidth, float NewMaxWidth, float NewMinLength, float NewMaxLength);
	void BoundsCheck(void);
	void Limiter(void);
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	virtual void Reset();
};

#endif