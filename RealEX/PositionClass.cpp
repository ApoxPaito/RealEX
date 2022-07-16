////////////////////////////////////////////////////////////////////////////////
// Filename: positionclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "positionclass.h"

PositionClass::PositionClass()
{
	m_frameTime = 0.0f;
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;
	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
	m_leftTurnSpeed = 0.0f;
	m_rightTurnSpeed = 0.0f;
	m_upTurnSpeed = 0.0f;
	m_downTurnSpeed = 0.0f;
	m_forwardMoveSpeed = 0.0f;
	m_backwardMoveSpeed = 0.0f;
	m_leftStrafeSpeed = 0.0f;
	m_rightStrafeSpeed = 0.0f;
	m_upwardMoveSpeed = 0.0f;
	m_downwardMoveSpeed = 0.0f;
}


PositionClass::PositionClass(const PositionClass& other)
{
}


PositionClass::~PositionClass()
{
}

void PositionClass::SetFrameTime(float time)
{
	m_frameTime = time;
	return;
}

void PositionClass::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}

void PositionClass::GetRotation(float& x, float& y, float& z)
{
	x = m_rotationX;
	y = m_rotationY;
	z = m_rotationZ;
	return;
}

void PositionClass::TurnLeft(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns left.  If not slow down the turn speed.
	if (keydown)
	{
		m_leftTurnSpeed += m_frameTime * 0.01f;

		if (m_leftTurnSpeed > (m_frameTime * 0.15f))
		{
			m_leftTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_leftTurnSpeed -= m_frameTime * 0.005f;

		if (m_leftTurnSpeed < 0.0f)
		{
			m_leftTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationY -= m_leftTurnSpeed;
	if (m_rotationY < 0.0f)
	{
		m_rotationY += 360.0f;
	}

	return;
}

void PositionClass::TurnRight(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns right.  If not slow down the turn speed.
	if (keydown)
	{
		m_rightTurnSpeed += m_frameTime * 0.01f;

		if (m_rightTurnSpeed > (m_frameTime * 0.15f))
		{
			m_rightTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_rightTurnSpeed -= m_frameTime * 0.005f;

		if (m_rightTurnSpeed < 0.0f)
		{
			m_rightTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationY += m_rightTurnSpeed;
	if (m_rotationY > 360.0f)
	{
		m_rotationY -= 360.0f;
	}

	return;
}

void PositionClass::TurnUp(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns right.  If not slow down the turn speed.
	if (keydown)
	{
		m_upTurnSpeed += m_frameTime * 0.01f;

		if (m_upTurnSpeed > (m_frameTime * 0.15f))
		{
			m_upTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_upTurnSpeed -= m_frameTime * 0.005f;

		if (m_upTurnSpeed < 0.0f)
		{
			m_upTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationX -= m_upTurnSpeed;
	if (m_rotationX > 360.0f)
	{
		m_rotationX -= 360.0f;
	}

	return;
}

void PositionClass::TurnDown(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns right.  If not slow down the turn speed.
	if (keydown)
	{
		m_downTurnSpeed += m_frameTime * 0.01f;

		if (m_downTurnSpeed > (m_frameTime * 0.15f))
		{
			m_downTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_downTurnSpeed -= m_frameTime * 0.005f;

		if (m_downTurnSpeed < 0.0f)
		{
			m_downTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationX += m_downTurnSpeed;
	if (m_rotationX > 360.0f)
	{
		m_rotationX -= 360.0f;
	}

	return;
}

void PositionClass::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}

void PositionClass::GetPosition(float& x, float& y, float& z)
{
	x = m_positionX;
	y = m_positionY;
	z = m_positionZ;
	return;
}

void PositionClass::MoveLeft(bool keydown)
{
	// If the key is pressed increase the speed at which the camera moves forward.  If not slow down the moving speed.
	if (keydown)
	{
		m_leftStrafeSpeed += m_frameTime * 0.001f;

		if (m_leftStrafeSpeed > (m_frameTime * 0.05f))
		{
			m_leftStrafeSpeed = m_frameTime * 0.05f;
		}
	}
	else
	{
		m_leftStrafeSpeed -= m_frameTime * 0.001f;

		if (m_leftStrafeSpeed < 0.0f)
		{
			m_leftStrafeSpeed = 0.0f;
		}
	}

	// Update the position using the strafe speed.
	m_positionX -= m_leftStrafeSpeed * cosf(m_rotationY * DirectX::XM_PI / 180.0f);
	m_positionZ -= m_leftStrafeSpeed * sinf(-m_rotationY * DirectX::XM_PI / 180.0f);

	return;
}

void PositionClass::MoveRight(bool keydown)
{
	// If the key is pressed increase the speed at which the camera moves forward.  If not slow down the moving speed.
	if (keydown)
	{
		m_rightStrafeSpeed += m_frameTime * 0.001f;

		if (m_rightStrafeSpeed > (m_frameTime * 0.05f))
		{
			m_rightStrafeSpeed = m_frameTime * 0.05f;
		}
	}
	else
	{
		m_rightStrafeSpeed -= m_frameTime * 0.001f;

		if (m_rightStrafeSpeed < 0.0f)
		{
			m_rightStrafeSpeed = 0.0f;
		}
	}

	// Update the position using the strafe speed.
	m_positionX += m_rightStrafeSpeed * cosf(m_rotationY * DirectX::XM_PI / 180.0f);
	m_positionZ += m_rightStrafeSpeed * sinf(-m_rotationY * DirectX::XM_PI / 180.0f);
	
	return;
}

void PositionClass::MoveUp(bool keydown)
{
	if (keydown) m_positionY += 0.05f;
	return;
}

void PositionClass::MoveDown(bool keydown)
{
	if (keydown) m_positionY -= 0.05f;
	return;
}

void PositionClass::MoveForward(bool keydown)
{
	// If the key is pressed increase the speed at which the camera moves forward.  If not slow down the moving speed.
	if (keydown)
	{
		m_forwardMoveSpeed += m_frameTime * 0.001f;

		if (m_forwardMoveSpeed > (m_frameTime * 0.05f))
		{
			m_forwardMoveSpeed = m_frameTime * 0.05f;
		}
	}
	else
	{
		m_forwardMoveSpeed -= m_frameTime * 0.001f;

		if (m_forwardMoveSpeed < 0.0f)
		{
			m_forwardMoveSpeed = 0.0f;
		}
	}

	// Update the position using the move speed.
	m_positionX += m_forwardMoveSpeed * sinf(m_rotationY * DirectX::XM_PI / 180.0f);
	m_positionY += m_forwardMoveSpeed * sinf(-m_rotationX * DirectX::XM_PI / 180.0f);
	m_positionZ += m_forwardMoveSpeed * cosf(m_rotationY * DirectX::XM_PI / 180.0f);

	return;
}

void PositionClass::MoveBackward(bool keydown)
{
	// If the key is pressed increase the speed at which the camera moves forward.  If not slow down the moving speed.
	if (keydown)
	{
		m_backwardMoveSpeed += m_frameTime * 0.001f;

		if (m_backwardMoveSpeed > (m_frameTime * 0.05f))
		{
			m_backwardMoveSpeed = m_frameTime * 0.05f;
		}
	}
	else
	{
		m_backwardMoveSpeed -= m_frameTime * 0.001f;

		if (m_backwardMoveSpeed < 0.0f)
		{
			m_backwardMoveSpeed = 0.0f;
		}
	}

	// Update the position using the move speed.
	m_positionX -= m_backwardMoveSpeed * sinf(m_rotationY * DirectX::XM_PI / 180.0f);
	m_positionY -= m_backwardMoveSpeed * sinf(-m_rotationX * DirectX::XM_PI / 180.0f);
	m_positionZ -= m_backwardMoveSpeed * cosf(m_rotationY * DirectX::XM_PI / 180.0f);

	return;
}