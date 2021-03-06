////////////////////////////////////////////////////////////////////////////////
// Filename: waterclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _WATERCLASS_H_
#define _WATERCLASS_H_

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <DirectXMath.h>

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"

//////////////
// TYPEDEFS //
//////////////

typedef DirectX::XMFLOAT2 DXFLOAT2;
typedef DirectX::XMFLOAT3 DXFLOAT3;
typedef DirectX::XMFLOAT4 DXFLOAT4;

////////////////////////////////////////////////////////////////////////////////
// Class name: WaterClass
////////////////////////////////////////////////////////////////////////////////
class WaterClass
{
private:
	struct VertexType
	{
		DXFLOAT3 position;
		DXFLOAT2 texture;
	};

public:
	WaterClass();
	WaterClass(const WaterClass&);
	~WaterClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext* , char*, float, float);
	void Shutdown();
	void Frame();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

	float GetWaterHeight();
	DXFLOAT2 GetNormalMapTiling();
	float GetWaterTranslation();
	float GetReflectRefractScale();
	DXFLOAT4 GetRefractionTint();
	float GetSpecularShininess();

private:
	bool InitializeBuffers(ID3D11Device*, float);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	void ReleaseTexture();

private:
	float m_waterHeight;
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	DXFLOAT2 m_normalMapTiling;
	float m_waterTranslation;
	float m_reflectRefractScale;
	DXFLOAT4 m_refractionTint;
	float m_specularShininess;
};

#endif