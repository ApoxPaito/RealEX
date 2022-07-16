////////////////////////////////////////////////////////////////////////////////
// Filename: terrainshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TERRAINSHADERCLASS_H_
#define _TERRAINSHADERCLASS_H_

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
typedef DirectX::XMFLOAT4 DXFLOAT4;

////////////////////////////////////////////////////////////////////////////////
// Class name: TerrainShaderClass
////////////////////////////////////////////////////////////////////////////////
class TerrainShaderClass
{
private:
	struct MatrixBufferType
	{
		DXMATRIX world;
		DXMATRIX view;
		DXMATRIX projection;
	};

	struct LightBufferType
	{
		DXFLOAT4 ambientColor;
		DXFLOAT4 diffuseColor;
		DXFLOAT3 lightDirection;
		float padding;
	};

public:
	TerrainShaderClass();
	TerrainShaderClass(const TerrainShaderClass&);
	~TerrainShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, DXFLOAT4, DXFLOAT3, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*);
	bool Render(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, DXFLOAT4, DXFLOAT3, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, float);
	bool Render(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, DXFLOAT4, DXFLOAT4, DXFLOAT3, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*);
	bool Render(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, DXFLOAT4, DXFLOAT4, DXFLOAT3, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, ID3D11ShaderResourceView*);
	bool Render(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, DXFLOAT3, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);
	
	bool SetShaderParameters(ID3D11DeviceContext*, DXMATRIX, DXMATRIX, DXMATRIX, DXFLOAT4, DXFLOAT3, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*);
	bool SetShaderParameters(ID3D11DeviceContext*, DXMATRIX, DXMATRIX, DXMATRIX, DXFLOAT4, DXFLOAT3, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, float);
	bool SetShaderParameters(ID3D11DeviceContext*, DXMATRIX, DXMATRIX, DXMATRIX, DXFLOAT4, DXFLOAT4, DXFLOAT3, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*);
	bool SetShaderParameters(ID3D11DeviceContext*, DXMATRIX, DXMATRIX, DXMATRIX, DXFLOAT4, DXFLOAT4, DXFLOAT3, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, ID3D11ShaderResourceView*);
	bool SetShaderParameters(ID3D11DeviceContext*, DXMATRIX, DXMATRIX, DXMATRIX, DXFLOAT3, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*);
	void RenderShader(ID3D11DeviceContext*, int);
private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_lightBuffer;
	ID3D11Buffer* m_textureInfoBuffer;
};

#endif