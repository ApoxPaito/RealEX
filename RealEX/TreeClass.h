////////////////////////////////////////////////////////////////////////////////
// Filename: treeclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TREECLASS_H_
#define _TREECLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>
using namespace std;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"
#include "TextureArrayClass.h"
#include "ModelClass.h"

//////////////
// TYPEDEFS //
//////////////

typedef DirectX::XMFLOAT2 DXFLOAT2;
typedef DirectX::XMFLOAT3 DXFLOAT3;
typedef DirectX::XMFLOAT4 DXFLOAT4;

////////////////////////////////////////////////////////////////////////////////
// Class name: TreeClass
////////////////////////////////////////////////////////////////////////////////
class TreeClass
{
public:
	TreeClass();
	TreeClass(const TreeClass&);
	~TreeClass();
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, char*, char*, char*, float);
	void Shutdown();
	void RenderTrunk(ID3D11DeviceContext*);
	void RenderLeaves(ID3D11DeviceContext*);
	void SetPosition(float, float, float);

	int GetTrunkVertexCount();
	int GetTrunkIndexCount();
	int GetLeafVertexCount();
	int GetLeafIndexCount();
	ID3D11ShaderResourceView* GetTrunkTexture();
	ID3D11ShaderResourceView* GetLeafTexture();
	void GetPosition(float&, float&, float&);

private:
	ModelClass* m_Trunk, *m_Leaves;
	float posX, posY, posZ;
};

#endif