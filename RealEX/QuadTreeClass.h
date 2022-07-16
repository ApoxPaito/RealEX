////////////////////////////////////////////////////////////////////////////////
// Filename: quadtreeclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _QUADTREECLASS_H_
#define _QUADTREECLASS_H_

/////////////
// GLOBALS //
/////////////
const int MAX_TRIANGLES = 10000;
const int HIGH_QUALITY_NODES = 6;
const int MEDIUM_QUALITY_NODES = HIGH_QUALITY_NODES + 7;
// Rest will be low quality

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "terrainclass.h"
#include "frustumclass.h"
#include "shadermanagerclass.h"
#include <vector>
#include <algorithm>

//////////////
// TYPEDEFS //
//////////////

typedef DirectX::XMFLOAT2 DXFLOAT2;
typedef DirectX::XMFLOAT3 DXFLOAT3;
typedef DirectX::XMFLOAT4 DXFLOAT4;
typedef DirectX::XMMATRIX DXMATRIX;

////////////////////////////////////////////////////////////////////////////////
// Class name: QuadTreeClass
////////////////////////////////////////////////////////////////////////////////
class QuadTreeClass
{
private:
	struct VectorType
	{
		float x, y, z;
	};

	enum LevelofDetail
	{
		High,
		Med,
		Low
	};

	struct NodeType
	{
		float positionX, positionZ, width;
		int triangleCount;
		ID3D11Buffer* highDetailVertexBuffer, * highDetailIndexBuffer;
		ID3D11Buffer* medDetailVertexBuffer, * medDetailIndexBuffer;
		ID3D11Buffer* lowDetailVertexBuffer, * lowDetailIndexBuffer;
		VectorType* vertexArray;
		NodeType* nodes[4];
		LevelofDetail lastRenderDetail;
	};
	
public:
	struct RenderNodeType
	{
		NodeType* node;
		float distance;
	};
public:
	QuadTreeClass();
	QuadTreeClass(const QuadTreeClass&);
	~QuadTreeClass();

	bool Initialize(TerrainClass*, ID3D11Device*);
	void Shutdown();
	void Render(FrustumClass*, ID3D11DeviceContext*, ShaderManagerClass*, DXFLOAT3);
	void SetShaderParameters(DXMATRIX, DXMATRIX, DXMATRIX, DXFLOAT4, DXFLOAT4, DXFLOAT3);
	bool InitializeTextureArray(ID3D11ShaderResourceView*[], int);

	int GetDrawCount();
	bool GetHeightAtPosition(float, float, float&);

private:
	void CalculateMeshDimensions(int, float&, float&, float&);
	void CreateTreeNode(NodeType*, float, float, float, ID3D11Device*);
	int CountTriangles(float, float, float);
	bool IsTriangleContained(int, float, float, float);
	void ReleaseNode(NodeType*);
	void CalculateNodeDistances(NodeType*, FrustumClass*, DXFLOAT3);
	void RenderNode(NodeType*, FrustumClass*, ID3D11DeviceContext*, ShaderManagerClass*, DXFLOAT3);
	void RenderNodes(ID3D11DeviceContext*, ShaderManagerClass*);

	void FindNode(NodeType*, float, float, float&);
	bool CheckHeightOfTriangle(float, float, float&, float[3], float[3], float[3]);

private:
	int m_triangleCount, m_drawCount;
	TerrainClass::VertexType* m_mediumQualityVertexList, *m_lowQualityVertexList;
	TerrainClass::HighQualityVertexType* m_highQualityVertexList;
	NodeType* m_parentNode;
	DXMATRIX m_worldMatrix, m_viewMatrix, m_projectionMatrix;
	DXFLOAT4 m_ambientColor, m_diffuseColor;
	DXFLOAT3 m_lightDirection, m_cameraPosLast;
	ID3D11ShaderResourceView** m_Textures;
	vector<RenderNodeType> m_renderedNodes;
};

#endif