////////////////////////////////////////////////////////////////////////////////
// Filename: minimapclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MINIMAPCLASS_H_
#define _MINIMAPCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "bitmapclass.h"
#include "shadermanagerclass.h"

//////////////
// TYPEDEFS //
//////////////

typedef DirectX::XMMATRIX DXMATRIX;

////////////////////////////////////////////////////////////////////////////////
// Class name: MiniMapClass
////////////////////////////////////////////////////////////////////////////////
class MiniMapClass
{
public:
	MiniMapClass();
	MiniMapClass(const MiniMapClass&);
	~MiniMapClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, HWND, int, int, DXMATRIX, float, float);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, DXMATRIX, DXMATRIX, ShaderManagerClass*);

	void PositionUpdate(float, float);

private:
	int m_mapLocationX, m_mapLocationY, m_pointLocationX, m_pointLocationY;
	float m_mapSizeX, m_mapSizeY, m_terrainWidth, m_terrainHeight;
	DXMATRIX m_viewMatrix;
	BitmapClass* m_MiniMapBitmap, * m_Border, * m_Point;
};

#endif