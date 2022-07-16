////////////////////////////////////////////////////////////////////////////////
// Filename: terrainclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TERRAINCLASS_H_
#define _TERRAINCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <DirectXMath.h>
#include <stdio.h>
#include <fstream>
using namespace std;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "TextureClass.h"

/////////////
// GLOBALS //
/////////////
const int TEXTURE_REPEAT = 32;

//////////////
// TYPEDEFS //
//////////////

typedef DirectX::XMFLOAT2 DXFLOAT2;
typedef DirectX::XMFLOAT3 DXFLOAT3;
typedef DirectX::XMFLOAT4 DXFLOAT4;

////////////////////////////////////////////////////////////////////////////////
// Class name: TerrainClass
////////////////////////////////////////////////////////////////////////////////
class TerrainClass
{
public:
	struct HighQualityVertexType
	{
		DXFLOAT3 position;
		DXFLOAT4 texture;
		DXFLOAT3 normal;
		DXFLOAT3 tangent;
		DXFLOAT3 binormal;
	};

	struct VertexType
	{
		DXFLOAT3 position;
		DXFLOAT4 color;
		DXFLOAT3 normal;
	};
private:
	struct HeightMapType
	{
		float x, y, z;
		float nx, ny, nz;
		float r, g, b;
	};

	struct VectorType
	{
		float x, y, z;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
		float tx, ty, tz;
		float bx, by, bz;
		float r, g, b;
		float tu2, tv2;
	};

	struct TempVertexType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct MaterialGroupType
	{
		int textureIndex1, textureIndex2, alphaIndex;
		int red, green, blue;
		ID3D11Buffer* vertexBuffer, * indexBuffer;
		int vertexCount, indexCount;
		VertexType* vertices;
		unsigned long* indices;
	};

	struct DetailLevelBufferType
	{
		ID3D11Buffer* vertexBuffer, * indexBuffer;
		int vertexCount, indexCount;
	};
public:
	TerrainClass();
	TerrainClass(const TerrainClass&);
	~TerrainClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, char*, float, char*, char*);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, float, char*, char*, char*);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, char*, float, char*, char*, char*);
	bool Initialize(ID3D11Device*, char*, float);
	void Shutdown();
	bool Render(ID3D11DeviceContext*);

	ID3D11ShaderResourceView* GetTexture();
	ID3D11ShaderResourceView* GetDetailMapTexture();
	ID3D11ShaderResourceView* GetNormalMapTexture();
	void GetTerrainSize(int&, int&);

	int GetHighQualityVertexCount();
	int GetHighQualityIndexCount();
	int GetMedQualityVertexCount();
	int GetMedQualityIndexCount();
	int GetLowQualityVertexCount();
	int GetLowQualityIndexCount();

	void CopyHighQualityVertexArray(void*);
	void CopyMedQualityVertexArray(void*);
	void CopyLowQualityVertexArray(void*);

private:
	bool LoadHeightMap(char*);
	void ReduceHeightMap(float);
	bool CalculateNormals();
	void ShutdownHeightMap();

	bool LoadColorMap(char*);

	bool BuildModel();
	void ReleaseModel();
	void CalculateModelVectors();

	bool BuildTerrainModel();
	void ReleaseTerrainModel();
	void CalculateTerrainVectors();
	void CalculateTangentBinormal(TempVertexType, TempVertexType, TempVertexType, VectorType&, VectorType&);

	bool LoadTextures(ID3D11Device*, ID3D11DeviceContext*, char*, char*);
	bool LoadTextures(ID3D11Device*, ID3D11DeviceContext*, char*, char*, char*);
	void ReleaseTextures();

	bool InitializeBuffers(ID3D11Device*);
	void RenderBuffers(ID3D11DeviceContext*);
	void ShutdownBuffers();

private:
	int m_terrainWidth, m_terrainHeight;
	HeightMapType* m_heightMap;
	ModelType* m_TerrainModel;
	TextureClass* m_Texture, *m_DetailMapTexture, *m_NormalMapTexture;
	HighQualityVertexType* m_highQualityVertices;
	VertexType* m_medQualityVertices, * m_lowQualityVertices;
	MaterialGroupType* m_Materials;
	ModelType* m_model;
	DetailLevelBufferType* m_highLevel, * m_medLevel, * m_lowLevel;
};

#endif