////////////////////////////////////////////////////////////////////////////////
// Filename: colorshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _COLORSHADERCLASS_H_
#define _COLORSHADERCLASS_H_


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
// Class name: ColorShaderClass
////////////////////////////////////////////////////////////////////////////////
class ColorShaderClass
{
private:
	struct MatrixBufferType
	{
		DXMATRIX world;
		DXMATRIX view;
		DXMATRIX projection;
	};

	struct TessellationBufferType
	{
		float tessellationAmount;
		DXFLOAT3 padding;
	};

public:
	ColorShaderClass();
	ColorShaderClass(const ColorShaderClass&);
	~ColorShaderClass();
	bool Initialize(ID3D11Device*, HWND);
	bool InitializeWithTessellation(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX);
	bool Render(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, float);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, DXMATRIX, DXMATRIX, DXMATRIX);
	bool SetShaderParameters(ID3D11DeviceContext*, DXMATRIX, DXMATRIX, DXMATRIX, float);
	void RenderShader(ID3D11DeviceContext*, int);
	void RenderTessellationShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11HullShader* m_hullShader;
	ID3D11DomainShader* m_domainShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer *m_matrixBuffer, *m_tessellationBuffer;
};

#endif