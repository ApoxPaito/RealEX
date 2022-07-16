////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_

//////////////
// INCLUDES //
//////////////
#include <DirectXMath.h>
using namespace DirectX;

//////////////
// TYPEDEFS //
//////////////

typedef XMFLOAT3 DXFLOAT3;
typedef XMMATRIX DXMATRIX;
typedef XMVECTOR DXVECTOR;

////////////////////////////////////////////////////////////////////////////////
// Class name: CameraClass
////////////////////////////////////////////////////////////////////////////////
class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	DXFLOAT3 GetPosition();
	DXFLOAT3 GetRotation();

	void Render();
	void RenderBaseViewMatrix();

	void GetViewMatrix(DXMATRIX&);
	void GetBaseViewMatrix(DXMATRIX&);

	void RenderReflection(float);
	void GetReflectionViewMatrix(DXMATRIX&);
private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	DXMATRIX m_viewMatrix, m_reflectionViewMatrix, m_baseViewMatrix;
};

#endif