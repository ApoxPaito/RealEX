////////////////////////////////////////////////////////////////////////////////
// Filename: particlesystemclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _PARTICLESYSTEMCLASS_H_
#define _PARTICLESYSTEMCLASS_H_

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <DirectXMath.h>
#include <algorithm>
#include <functional>
#include <array>
#include <iostream>
#include <string_view>
using namespace DirectX;
using namespace std;

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
// Class name: ParticleSystemClass
////////////////////////////////////////////////////////////////////////////////
class ParticleSystemClass
{
private:
	struct ParticleType
	{
		float positionX, positionY, positionZ;
		float initialX, initialZ;
		float red, green, blue;
		float velocity;
		float angle;
		bool active;
	};

	struct VertexType
	{
		DXFLOAT3 position;
		DXFLOAT2 texture;
		DXFLOAT4 color;
	};

	struct InstanceType
	{
		DXFLOAT3 position;
		DXFLOAT4 color;
	};

public:
	ParticleSystemClass();
	ParticleSystemClass(const ParticleSystemClass&);
	~ParticleSystemClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*);
	void Shutdown();
	bool Frame(float, ID3D11DeviceContext*);
	void Render(ID3D11DeviceContext*);

	ID3D11ShaderResourceView* GetTexture();
	int GetIndexCount();
	int GetVertexCount();
	int GetCurrentParticleCount();

private:
	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	void ReleaseTexture();

	bool InitializeParticleSystem();
	void ShutdownParticleSystem();

	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();

	void EmitParticles(float);
	void UpdateParticles(float);
	void KillParticles();

	bool UpdateBuffers(ID3D11DeviceContext*);

	void RenderBuffers(ID3D11DeviceContext*);

	void QuickSort(ParticleType[], int, int);
	int QuickSortPartition(ParticleType[], int, int);

private:
	float m_particleDeviationX, m_particleDeviationY, m_particleDeviationZ;
	float m_particleVelocity, m_particleVelocityVariation;
	float m_particleSize, m_particlesPerSecond;
	int m_maxParticles;
	int m_currentParticleCount;
	float m_accumulatedTime;
	TextureClass* m_Texture;
	ParticleType* m_particleList;
	int m_vertexCount, m_indexCount;
	//VertexType* m_vertices;
	InstanceType* m_instances;
	ID3D11Buffer* m_vertexBuffer, *m_indexBuffer, *m_instanceBuffer;
};

#endif