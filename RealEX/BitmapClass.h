////////////////////////////////////////////////////////////////////////////////
// Filename: bitmapclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _BITMAPCLASS_H_
#define _BITMAPCLASS_H_


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

typedef DirectX::XMFLOAT3 DXFLOAT3;
typedef DirectX::XMFLOAT2 DXFLOAT2;

////////////////////////////////////////////////////////////////////////////////
// Class name: BitmapClass
////////////////////////////////////////////////////////////////////////////////
class BitmapClass
{
private:
	struct VertexType
	{
		DXFLOAT3 position;
		DXFLOAT2 texture;
	};

	struct InstanceType
	{
		DXFLOAT3 position;
	};

public:
	BitmapClass();
	BitmapClass(const BitmapClass&);
	~BitmapClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, int, int, int, int);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, int, int, char*, int, int);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, int, int, char*, char*, int, int);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, int);
	bool RenderWithInstancing(ID3D11DeviceContext*, int, int);

	int GetIndexCount();
	int GetVertexCount();
	int GetInstanceCount();
	ID3D11ShaderResourceView* GetTexture();
	ID3D11ShaderResourceView* GetGlowMap();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(ID3D11DeviceContext*, int, int);
	bool UpdateInstanceBuffers(ID3D11DeviceContext*, int, int);
	void RenderBuffers(ID3D11DeviceContext*);
	void RenderInstanceBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	bool LoadTextures(ID3D11Device*, ID3D11DeviceContext*, char*, char*);
	void ReleaseTextures();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer, *m_instanceBuffer;
	int m_vertexCount, m_indexCount, m_instanceCount;
	TextureClass* m_Texture, *m_GlowMap;
	int m_screenWidth, m_screenHeight;
	int m_bitmapWidth, m_bitmapHeight;
	int m_previousPosX, m_previousPosY;
};

#endif