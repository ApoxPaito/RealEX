////////////////////////////////////////////////////////////////////////////////
// Filename: lightclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _LIGHTCLASS_H_
#define _LIGHTCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <DirectXMath.h>
using namespace DirectX;

//////////////
// TYPEDEFS //
//////////////
typedef DirectX::XMMATRIX DXMATRIX;
typedef DirectX::XMFLOAT3 DXFLOAT3;
typedef DirectX::XMFLOAT4 DXFLOAT4;
typedef DirectX::XMVECTOR DXVECTOR;

////////////////////////////////////////////////////////////////////////////////
// Class name: LightClass
////////////////////////////////////////////////////////////////////////////////
class LightClass
{
public:
	LightClass();
	LightClass(const LightClass&);
	~LightClass();

	void SetAmbientColor(float, float, float, float);
	void SetDiffuseColor(float, float, float, float);
	void SetDirection(float, float, float);
	void SetPosition(float, float, float);
	void SetLookAt(float, float, float);
	void SetSpecularColor(float, float, float, float);
	void SetSpecularPower(float);

	DXFLOAT4 GetAmbientColor();
	DXFLOAT4 GetDiffuseColor();
	DXFLOAT3 GetDirection();
	DXFLOAT3 GetPosition();
	DXFLOAT4 GetSpecularColor();
	float GetSpecularPower();

	void GenerateViewMatrix();
	void GenerateProjectionMatrix(float, float);

	void GetViewMatrix(DXMATRIX&);
	void GetProjectionMatrix(DXMATRIX&);

	void GenerateOrthoMatrix(float, float, float, float);
	void GetOrthoMatrix(DXMATRIX&);

private:
	DXFLOAT4 m_ambientColor;
	DXFLOAT4 m_diffuseColor;
	DXFLOAT3 m_direction;
	DXFLOAT3 m_lookAt;
	DXFLOAT3 m_position;
	DXFLOAT4 m_specularColor;
	float m_specularPower;
	DXMATRIX m_viewMatrix;
	DXMATRIX m_projectionMatrix;
	DXMATRIX m_orthoMatrix;
};

#endif

