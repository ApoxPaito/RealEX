////////////////////////////////////////////////////////////////////////////////
// Filename: debugwindowclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _DEBUGWINDOWCLASS_H_
#define _DEBUGWINDOWCLASS_H_


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
class DebugWindowClass
{
private:
	struct VertexType
	{
		DXFLOAT3 position;
		DXFLOAT2 texture;
	};

public:
	DebugWindowClass();
	DebugWindowClass(const DebugWindowClass&);
	~DebugWindowClass();

	bool Initialize(ID3D11Device*, int, int, int, int);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, int);

	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(ID3D11DeviceContext*, int, int);
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;
	int m_screenWidth, m_screenHeight;
	int m_bitmapWidth, m_bitmapHeight;
	int m_previousPosX, m_previousPosY;
};

#endif