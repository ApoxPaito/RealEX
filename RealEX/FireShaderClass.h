////////////////////////////////////////////////////////////////////////////////
// Filename: fireshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FIRESHADERCLASS_H_
#define _FIRESHADERCLASS_H_

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

////////////////////////////////////////////////////////////////////////////////
// Class name: FireShaderClass
////////////////////////////////////////////////////////////////////////////////
class FireShaderClass
{
private:
	struct MatrixBufferType
	{
		DXMATRIX world;
		DXMATRIX view;
		DXMATRIX projection;
	};

	struct NoiseBufferType
	{
		float frameTime;
		DXFLOAT3 scrollSpeeds;
		DXFLOAT3 scales;
		float padding;
	};

	struct DistortionBufferType
	{
		DXFLOAT2 distortion1;
		DXFLOAT2 distortion2;
		DXFLOAT2 distortion3;
		float distortionScale;
		float distortionBias;
	};

public:
	FireShaderClass();
	FireShaderClass(const FireShaderClass&);
	~FireShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, float, DXFLOAT3, DXFLOAT3, DXFLOAT2, DXFLOAT2, DXFLOAT2, float, float);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, float, DXFLOAT3, DXFLOAT3, DXFLOAT2,
		DXFLOAT2, DXFLOAT2, float, float);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_noiseBuffer;
	ID3D11SamplerState* m_sampleState;
	ID3D11SamplerState* m_sampleState2;
	ID3D11Buffer* m_distortionBuffer;
};

#endif