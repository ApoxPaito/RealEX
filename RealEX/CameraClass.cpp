////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cameraclass.h"

CameraClass::CameraClass()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
}

CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}

void CameraClass::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}


void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}

DXFLOAT3 CameraClass::GetPosition()
{
	return DXFLOAT3(m_positionX, m_positionY, m_positionZ);
}


DXFLOAT3 CameraClass::GetRotation()
{
	return DXFLOAT3(m_rotationX, m_rotationY, m_rotationZ);
}

void CameraClass::Render()
{
	DXFLOAT3 up, position, lookAt;
	DXVECTOR upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	DXMATRIX rotationMatrix;


	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Load it into a XMVECTOR structure.
	upVector = XMLoadFloat3(&up);

	// Setup the position of the camera in the world.
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;

	// Load it into a XMVECTOR structure.
	positionVector = XMLoadFloat3(&position);

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Load it into a XMVECTOR structure.
	lookAtVector = XMLoadFloat3(&lookAt);

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw = m_rotationY * 0.0174532925f;
	roll = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// ngl i hate calling functions everytime i need to work with a sodding Float3 >and it needs XMVector >smh
	// Apparently my initial handling of this wasn't wrong but gonna replace it with Raster's better code anw
	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAtVector = positionVector + lookAtVector;

	// Finally create the view matrix from the three updated vectors.
	m_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	return;
}

void CameraClass::RenderBaseViewMatrix()
{
	DXFLOAT3 up, position, lookAt;
	DXVECTOR upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	DXMATRIX rotationMatrix;


	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw = m_rotationY * 0.0174532925f;
	roll = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVector = XMLoadFloat3(&lookAt);
	positionVector = XMLoadFloat3(&position);
	upVector = XMLoadFloat3(&up);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAtVector = positionVector + lookAtVector;

	// Create the base view matrix from the three vectors.
	m_baseViewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	return;
}

void CameraClass::GetViewMatrix(DXMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}

void CameraClass::GetBaseViewMatrix(DXMATRIX& baseViewMatrix)
{
	baseViewMatrix = m_baseViewMatrix;
	return;
}

void CameraClass::RenderReflection(float height)
{
	DXFLOAT3 up, position, lookAt;
	DXVECTOR upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	DXMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	// For planar reflection invert the X position of the camera.
	position.x = m_positionX;
	position.y = -m_positionY + (height * 2.0f);
	position.z = m_positionZ;

	// Setup where the camera is looking.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.  Invert the X rotation for reflection.
	pitch = -m_rotationX * 0.0174532925f;
	yaw = m_rotationY * 0.0174532925f;
	roll = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the pitch, yaw, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Load XMFLOAT3s into XMVECTORs
	upVector = XMLoadFloat3(&up);
	lookAtVector = XMLoadFloat3(&lookAt);
	positionVector = XMLoadFloat3(&position);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAtVector = positionVector + lookAtVector;

	// Create the view matrix from the three vectors.
	m_reflectionViewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	return;
}

void CameraClass::GetReflectionViewMatrix(DXMATRIX& reflectionViewMatrix)
{
	reflectionViewMatrix = m_reflectionViewMatrix;

	return;
}