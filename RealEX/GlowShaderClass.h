////////////////////////////////////////////////////////////////////////////////
// Filename: glowmapclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GLOWMAPCLASS_H_
#define _GLOWMAPCLASS_H_

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h> //This replaces that d3d11async.h
#include <fstream>

using namespace std;
using namespace DirectX;

//////////////
// TYPEDEFS //
//////////////
typedef DirectX::XMMATRIX DXMATRIX;
typedef DirectX::XMFLOAT3 DXFLOAT3;

////////////////////////////////////////////////////////////////////////////////
// Class name: GlowMapClass
////////////////////////////////////////////////////////////////////////////////
class GlowShaderClass
{
private:
	struct MatrixBufferType
	{
		DXMATRIX world;
		DXMATRIX view;
		DXMATRIX projection;
	};

	struct GlowBufferType
	{
		float glowStrength;
		DXFLOAT3 padding;
	};

public:
	GlowShaderClass();
	GlowShaderClass(const GlowShaderClass&);
	~GlowShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, float);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, float);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_glowBuffer;
	ID3D11SamplerState* m_sampleState;
};

#endif