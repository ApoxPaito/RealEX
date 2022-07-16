////////////////////////////////////////////////////////////////////////////////
// Filename: viewpointclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "viewpointclass.h"


ViewPointClass::ViewPointClass()
{
}


ViewPointClass::ViewPointClass(const ViewPointClass& other)
{
}


ViewPointClass::~ViewPointClass()
{
}


void ViewPointClass::SetPosition(float x, float y, float z)
{
	m_position = DXFLOAT3(x, y, z);
	return;
}


void ViewPointClass::SetLookAt(float x, float y, float z)
{
	m_lookAt = DXFLOAT3(x, y, z);
	return;
}


void ViewPointClass::SetProjectionParameters(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	m_fieldOfView = fieldOfView;
	m_aspectRatio = aspectRatio;
	m_nearPlane = nearPlane;
	m_farPlane = farPlane;
	return;
}


void ViewPointClass::GenerateViewMatrix()
{
	DXFLOAT3 up;
	DXVECTOR positionVector, lookAtVector, upVector;

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Load XMFLOAT3s to XMVECTORs
	positionVector = XMLoadFloat3(&m_position);
	lookAtVector = XMLoadFloat3(&m_lookAt);
	upVector = XMLoadFloat3(&up);

	// Create the view matrix from the three vectors.
	m_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	return;
}


void ViewPointClass::GenerateProjectionMatrix()
{
	// Create the projection matrix for the view point.
	m_projectionMatrix = XMMatrixPerspectiveFovLH(m_fieldOfView, m_aspectRatio, m_nearPlane, m_farPlane);

	return;
}


void ViewPointClass::GetViewMatrix(DXMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}


void ViewPointClass::GetProjectionMatrix(DXMATRIX& projectionMatrix)
{
	projectionMatrix = m_projectionMatrix;
	return;
}