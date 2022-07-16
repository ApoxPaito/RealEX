////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


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

//////////////
// TYPEDEFS //
//////////////

typedef DirectX::XMFLOAT2 DXFLOAT2;
typedef DirectX::XMFLOAT3 DXFLOAT3;
typedef DirectX::XMFLOAT4 DXFLOAT4;

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
private:
	struct VertexType
	{
		DXFLOAT3 position;
		DXFLOAT2 texture;
		DXFLOAT3 normal;
		DXFLOAT3 tangent;
		DXFLOAT3 binormal;
	};
	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
		float tx, ty, tz;
		float bx, by, bz;
	};

	struct TempVertexType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct VectorType
	{
		float x, y, z;
	};

	struct InstanceType
	{
		DXFLOAT3 position;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, char*);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, char*, float);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, char*, char*);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, char*, char*, char*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	void RenderWithInstancing(ID3D11DeviceContext*);
	void RenderWithTessellation(ID3D11DeviceContext*);
	void SetPosition(float, float, float);

	int GetVertexCount();
	int GetInstanceCount();
	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();
	ID3D11ShaderResourceView** GetTextures();
	void GetPosition(float&, float&, float&);

private:
	bool InitializeBuffers(ID3D11Device*);
	bool InitializeBuffers(ID3D11Device*, float);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
	void RenderInstanceBuffers(ID3D11DeviceContext*);
	void RenderTessellationBuffers(ID3D11DeviceContext*);
	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	bool LoadTextures(ID3D11Device*, ID3D11DeviceContext*, char*, char*);
	bool LoadTextures(ID3D11Device*, ID3D11DeviceContext*, char*, char*, char*);
	void ReleaseTexture();
	void ReleaseTextures();
	bool LoadModel(char*);
	void ReleaseModel();
	void CalculateModelVectors();
	void CalculateTangentBinormal(TempVertexType, TempVertexType, TempVertexType, VectorType&, VectorType&);
	void CalculateNormal(VectorType, VectorType, VectorType&);
private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	ModelType* m_model;
	TextureArrayClass* m_TextureArray;
	ID3D11Buffer* m_instanceBuffer;
	int m_instanceCount;
	float posX, posY, posZ;
};

#endif