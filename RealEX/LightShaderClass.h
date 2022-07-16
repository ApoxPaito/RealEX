////////////////////////////////////////////////////////////////////////////////
// Filename: lightshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _LIGHTSHADERCLASS_H_
#define _LIGHTSHADERCLASS_H_

/////////////
// GLOBALS //
/////////////
const int NUM_LIGHTS = 5;

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
// Class name: LightShaderClass
////////////////////////////////////////////////////////////////////////////////
class LightShaderClass
{
private:
	struct MatrixBufferType
	{
		DXMATRIX world;
		DXMATRIX view;
		DXMATRIX projection;
	};

	struct CameraBufferType
	{
		DXFLOAT3 cameraPosition;
		float padding;
	};

	struct LightColorBufferType
	{
		DXFLOAT4 diffuseColor[NUM_LIGHTS];
	};

	struct LightPositionBufferType
	{
		DXFLOAT4 lightPosition[NUM_LIGHTS];
	};

	struct LightBufferTypeDiffuse
	{
		DXFLOAT4 diffuseColor;
		DXFLOAT3 lightDirection;
		float padding;  // Added extra padding so structure is a multiple of 16 for CreateBuffer function requirements.
	};

	struct LightBufferTypeAmbient
	{
		DXFLOAT4 ambientColor;
		DXFLOAT4 diffuseColor;
		DXFLOAT3 lightDirection;
		float padding;
	};

	struct LightBufferTypeSpecular
	{
		DXFLOAT4 ambientColor;
		DXFLOAT4 diffuseColor;
		DXFLOAT3 lightDirection;
		float specularPower;
		DXFLOAT4 specularColor;
	};

	struct LightBufferTypeDeferred
	{
		DXFLOAT3 lightDirection;
		float padding;
	};

public:
	enum LightningType
	{
		Diffuse,
		Specular,
		Ambient,
		Multiple,
		Deferred
	};

public:
	LightShaderClass();
	LightShaderClass(const LightShaderClass&);
	~LightShaderClass();

	bool Initialize(ID3D11Device*, HWND, LightningType);
	void Shutdown();
	bool RenderSpecular(ID3D11DeviceContext*, int, DXMATRIX&, DXMATRIX&, DXMATRIX&, ID3D11ShaderResourceView*, DXFLOAT3, DXFLOAT4, DXFLOAT4, DXFLOAT3, DXFLOAT4, float);
	bool RenderDiffuse(ID3D11DeviceContext*, int, DXMATRIX&, DXMATRIX&, DXMATRIX&, ID3D11ShaderResourceView*, DXFLOAT3, DXFLOAT4);
	bool RenderAmbient(ID3D11DeviceContext*, int, DXMATRIX&, DXMATRIX&, DXMATRIX&, ID3D11ShaderResourceView*, DXFLOAT3, DXFLOAT4, DXFLOAT4);
	bool RenderMultiple(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, DXFLOAT4[], DXFLOAT4[]);
	bool RenderDeferred(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, DXFLOAT3);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*, LightningType);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParametersSpecular(ID3D11DeviceContext*, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, DXFLOAT3, DXFLOAT4, DXFLOAT4, DXFLOAT3, DXFLOAT4, float);
	bool SetShaderParametersDiffuse(ID3D11DeviceContext*, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, DXFLOAT3, DXFLOAT4);
	bool SetShaderParametersAmbient(ID3D11DeviceContext*, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, DXFLOAT3, DXFLOAT4, DXFLOAT4);
	bool SetShaderParametersMultiple(ID3D11DeviceContext*, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, DXFLOAT4[],	DXFLOAT4[]);
	bool SetShaderParametersDeferred(ID3D11DeviceContext*, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, DXFLOAT3);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_cameraBuffer;
	ID3D11Buffer* m_lightBuffer;
	ID3D11Buffer* m_lightColorBuffer;
	ID3D11Buffer* m_lightPositionBuffer;
};

#endif