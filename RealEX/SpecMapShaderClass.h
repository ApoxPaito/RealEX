////////////////////////////////////////////////////////////////////////////////
// Filename: specmapshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SPECMAPSHADERCLASS_H_
#define _SPECMAPSHADERCLASS_H_


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

typedef XMMATRIX DXMATRIX;
typedef XMFLOAT4 DXFLOAT4;
typedef XMFLOAT3 DXFLOAT3;

////////////////////////////////////////////////////////////////////////////////
// Class name: SpecMapShaderClass
////////////////////////////////////////////////////////////////////////////////
class SpecMapShaderClass
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
		DXFLOAT4 diffuseColor;
		DXFLOAT4 specularColor;
		float specularPower;
		DXFLOAT3 lightDirection;
	};

	struct CameraBufferType
	{
		DXFLOAT3 cameraPosition;
		float padding;
	};

public:
	SpecMapShaderClass();
	SpecMapShaderClass(const SpecMapShaderClass&);
	~SpecMapShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView**, DXFLOAT3,
		DXFLOAT4, DXFLOAT3, DXFLOAT4, float);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView**, DXFLOAT3,
		DXFLOAT4, DXFLOAT3, DXFLOAT4, float);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_lightBuffer;
	ID3D11Buffer* m_cameraBuffer;
};

#endif