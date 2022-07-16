////////////////////////////////////////////////////////////////////////////////
// Filename: positionclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _POSITIONCLASS_H_
#define _POSITIONCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <math.h>
#include <DirectXMath.h>

////////////////////////////////////////////////////////////////////////////////
// Class name: PositionClass
////////////////////////////////////////////////////////////////////////////////
class PositionClass
{
public:
	PositionClass();
	PositionClass(const PositionClass&);
	~PositionClass();

	void SetFrameTime(float);
	void SetRotation(float, float, float);
	void SetPosition(float, float, float);
	void GetRotation(float&, float&, float&);
	void GetPosition(float&, float&, float&);

	void TurnLeft(bool);
	void TurnRight(bool);
	void TurnUp(bool);
	void TurnDown(bool);
	void MoveRight(bool);
	void MoveLeft(bool);
	void MoveUp(bool);
	void MoveDown(bool);
	void MoveForward(bool);
	void MoveBackward(bool);

private:
	float m_frameTime;
	float m_rotationX, m_rotationY, m_rotationZ;
	float m_leftTurnSpeed, m_rightTurnSpeed, m_upTurnSpeed, m_downTurnSpeed;
	float m_forwardMoveSpeed, m_backwardMoveSpeed, m_leftStrafeSpeed, m_rightStrafeSpeed;
	float m_upwardMoveSpeed, m_downwardMoveSpeed;
	float m_positionX, m_positionY, m_positionZ;
};

#endif