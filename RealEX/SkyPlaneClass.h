////////////////////////////////////////////////////////////////////////////////
// Filename: skyplaneclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SKYPLANECLASS_H_
#define _SKYPLANECLASS_H_

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

////////////////////////////////////////////////////////////////////////////////
// Class name: SkyPlaneClass
////////////////////////////////////////////////////////////////////////////////
class SkyPlaneClass
{
private:
	struct SkyPlaneType
	{
		float x, y, z;
		float tu, tv;
	};
	struct VertexType
	{
		DXFLOAT3 position;
		DXFLOAT2 texture;
	};

public:
	SkyPlaneClass();
	SkyPlaneClass(const SkyPlaneClass&);
	~SkyPlaneClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, char*, char*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	void Frame(float);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetCloudTexture0();
	ID3D11ShaderResourceView* GetCloudTexture1();
	ID3D11ShaderResourceView* GetPerturbTexture();

	float GetScale();
	float GetBrightness();
	float GetFirstTranslation();
	float GetSecondTranslation();

private:
	bool InitializeSkyPlane(int, float, float, float, int);
	void ShutdownSkyPlane();

	bool InitializeBuffers(ID3D11Device*, int);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTextures(ID3D11Device*, ID3D11DeviceContext*, char*, char*, char*);
	void ReleaseTextures();

private:
	SkyPlaneType* m_skyPlane;
	int m_vertexCount, m_indexCount;
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	TextureClass* m_CloudTexture0, *m_CloudTexture1, * m_PerturbTexture;
	float m_brightness, m_scale, m_firstTranslation, m_secondTranslation;
};

#endif