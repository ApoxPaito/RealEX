////////////////////////////////////////////////////////////////////////////////
// Filename: watershaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _WATERSHADERCLASS_H_
#define _WATERSHADERCLASS_H_


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
typedef DirectX::XMFLOAT2 DXFLOAT2;
typedef DirectX::XMFLOAT3 DXFLOAT3;
typedef DirectX::XMFLOAT4 DXFLOAT4;

////////////////////////////////////////////////////////////////////////////////
// Class name: WaterShaderClass
////////////////////////////////////////////////////////////////////////////////
class WaterShaderClass
{
private:
	struct MatrixBufferType
	{
		DXMATRIX world;
		DXMATRIX view;
		DXMATRIX projection;
		DXMATRIX reflection;
	};

	struct CamNormBufferType
	{
		DXFLOAT3 cameraPosition;
		float padding1;
		DXFLOAT2 normalMapTiling;
		DXFLOAT2 padding2;
	};

	struct WaterBufferType
	{
		DXFLOAT4 refractionTint;
		DXFLOAT3 lightDirection;
		float waterTranslation;
		float reflectRefractScale;
		float specularShininess;
		DXFLOAT2 padding;
	};

public:
	WaterShaderClass();
	WaterShaderClass(const WaterShaderClass&);
	~WaterShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, DXFLOAT3, DXFLOAT2, float, float, DXFLOAT4, DXFLOAT3, float);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, DXMATRIX, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, DXFLOAT3, DXFLOAT2, float, float, DXFLOAT4, DXFLOAT3, float);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_camNormBuffer;
	ID3D11Buffer* m_waterBuffer;
};

#endif