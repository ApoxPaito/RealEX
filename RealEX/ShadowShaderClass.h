////////////////////////////////////////////////////////////////////////////////
// Filename: shadowshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SHADOWSHADERCLASS_H_
#define _SHADOWSHADERCLASS_H_


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
// Class name: ShadowShaderClass
////////////////////////////////////////////////////////////////////////////////
class ShadowShaderClass
{
private:
	struct MatrixBufferType
	{
		DXMATRIX world;
		DXMATRIX view;
		DXMATRIX projection;
		DXMATRIX lightView;
		DXMATRIX lightProjection;
		//DXMATRIX lightView2;
		//DXMATRIX lightProjection2;
	};

	struct LightBufferType
	{
		DXFLOAT4 ambientColor;
		DXFLOAT4 diffuseColor;
		DXFLOAT3 lightDirection;
		//DXFLOAT4 diffuseColor2;
		float padding;
	};

	struct LightBufferType2
	{
		DXFLOAT3 lightPosition;
		float padding;
		//DXFLOAT3 lightPosition2;
		//float padding2;
	};

public:
	ShadowShaderClass();
	ShadowShaderClass(const ShadowShaderClass&);
	~ShadowShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, DXFLOAT3);
	bool Render(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, DXFLOAT3, DXFLOAT4, DXFLOAT4);
	bool Render(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, DXFLOAT3, DXFLOAT4, DXFLOAT4, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, DXFLOAT3,
		DXFLOAT4);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, DXMATRIX, DXMATRIX, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, DXFLOAT3);
	bool SetShaderParameters(ID3D11DeviceContext*, DXMATRIX, DXMATRIX, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, DXFLOAT3, DXFLOAT4, DXFLOAT4);
	bool SetShaderParameters(ID3D11DeviceContext*, DXMATRIX, DXMATRIX, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, DXFLOAT3, DXFLOAT4, DXFLOAT4, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*,
		DXFLOAT3, DXFLOAT4);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleStateWrap;
	ID3D11SamplerState* m_sampleStateClamp;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_lightBuffer;
	ID3D11Buffer* m_lightBuffer2;
};

#endif