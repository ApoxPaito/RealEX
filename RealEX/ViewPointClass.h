////////////////////////////////////////////////////////////////////////////////
// Filename: viewpointclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _VIEWPOINTCLASS_H_
#define _VIEWPOINTCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <DirectXMath.h>
using namespace DirectX;

//////////////
// TYPEDEFS //
//////////////
typedef DirectX::XMFLOAT3 DXFLOAT3;
typedef DirectX::XMMATRIX DXMATRIX;
typedef DirectX::XMVECTOR DXVECTOR;

////////////////////////////////////////////////////////////////////////////////
// Class name: ViewPointClass
////////////////////////////////////////////////////////////////////////////////
class ViewPointClass
{
public:
	ViewPointClass();
	ViewPointClass(const ViewPointClass&);
	~ViewPointClass();

	void SetPosition(float, float, float);
	void SetLookAt(float, float, float);
	void SetProjectionParameters(float, float, float, float);

	void GenerateViewMatrix();
	void GenerateProjectionMatrix();

	void GetViewMatrix(DXMATRIX&);
	void GetProjectionMatrix(DXMATRIX&);

private:
	DXFLOAT3 m_position, m_lookAt;
	DXMATRIX m_viewMatrix, m_projectionMatrix;
	float m_fieldOfView, m_aspectRatio, m_nearPlane, m_farPlane;
};

#endif