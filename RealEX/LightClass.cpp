////////////////////////////////////////////////////////////////////////////////
// Filename: lightclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "lightclass.h"


LightClass::LightClass()
{
}


LightClass::LightClass(const LightClass& other)
{
}


LightClass::~LightClass()
{
}

void LightClass::SetAmbientColor(float red, float green, float blue, float alpha)
{
	m_ambientColor = DXFLOAT4(red, green, blue, alpha);
	return;
}

void LightClass::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = DXFLOAT4(red, green, blue, alpha);
	return;
}


void LightClass::SetDirection(float x, float y, float z)
{
	m_direction = DXFLOAT3(x, y, z);
	return;
}

void LightClass::SetPosition(float x, float y, float z)
{
	m_position = DXFLOAT3(x, y, z);
	return;
}

void LightClass::SetLookAt(float x, float y, float z)
{
	m_lookAt.x = x;
	m_lookAt.y = y;
	m_lookAt.z = z;
	return;
}

void LightClass::SetSpecularColor(float red, float green, float blue, float alpha)
{
	m_specularColor = DXFLOAT4(red, green, blue, alpha);
	return;
}

void LightClass::SetSpecularPower(float power)
{
	m_specularPower = power;
	return;
}

DXFLOAT4 LightClass::GetAmbientColor()
{
	return m_ambientColor;
}

DXFLOAT4 LightClass::GetDiffuseColor()
{
	return m_diffuseColor;
}

DXFLOAT3 LightClass::GetDirection()
{
	return m_direction;
}

DXFLOAT3 LightClass::GetPosition()
{
	return m_position;
}

DXFLOAT4 LightClass::GetSpecularColor()
{
	return m_specularColor;
}

float LightClass::GetSpecularPower()
{
	return m_specularPower;
}

void LightClass::GenerateViewMatrix()
{
	DXFLOAT3 up;
	DXVECTOR positionVector, lookAtVector, upVector;

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Load XMFLOATs into XMVECTORs
	positionVector = XMLoadFloat3(&m_position);
	lookAtVector = XMLoadFloat3(&m_lookAt);
	upVector = XMLoadFloat3(&up);

	// Create the view matrix from the three vectors.
	m_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	return;
}

void LightClass::GenerateProjectionMatrix(float screenDepth, float screenNear)
{
	float fieldOfView, screenAspect;


	// Setup field of view and screen aspect for a square light source.
	fieldOfView = (float)XM_PI / 2.0f;
	screenAspect = 1.0f;

	// Create the projection matrix for the light.
	m_projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth);

	return;
}

void LightClass::GetViewMatrix(DXMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}


void LightClass::GetProjectionMatrix(DXMATRIX& projectionMatrix)
{
	projectionMatrix = m_projectionMatrix;
	return;
}

void LightClass::GenerateOrthoMatrix(float height, float width, float depthPlane, float nearPlane)
{
	// Create the orthographic matrix for the light.
	m_orthoMatrix = XMMatrixOrthographicLH(height, width, nearPlane, depthPlane);

	return;
}


void LightClass::GetOrthoMatrix(DXMATRIX& orthoMatrix)
{
	orthoMatrix = m_orthoMatrix;
	return;
}