////////////////////////////////////////////////////////////////////////////////
// Filename: skyplaneshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SKYPLANESHADERCLASS_H_
#define _SKYPLANESHADERCLASS_H_

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

typedef DirectX::XMFLOAT3 DXFLOAT3;
typedef DirectX::XMMATRIX DXMATRIX;

////////////////////////////////////////////////////////////////////////////////
// Class name: SkyPlaneShaderClass
////////////////////////////////////////////////////////////////////////////////
class SkyPlaneShaderClass
{
private:
	struct MatrixBufferType
	{
		DXMATRIX world;
		DXMATRIX view;
		DXMATRIX projection;
	};

	struct SkyBufferType
	{
		float firstTranslation;
		float secondTranslation;
		float brightness;
		float scale;
	};

public:
	SkyPlaneShaderClass();
	SkyPlaneShaderClass(const SkyPlaneShaderClass&);
	~SkyPlaneShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		float, float, float, float);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		float, float, float, float);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_skyBuffer;
};

#endif