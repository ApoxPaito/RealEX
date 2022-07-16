////////////////////////////////////////////////////////////////////////////////
// Filename: texturearrayclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TEXTUREARRAYCLASS_H_
#define _TEXTUREARRAYCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <fstream>

////////////////////////////////////////////////////////////////////////////////
// Class name: TextureArrayClass
////////////////////////////////////////////////////////////////////////////////
class TextureArrayClass
{
private:
	struct TargaHeader
	{
		unsigned char data1[12];
		unsigned short width;
		unsigned short height;
		unsigned char bpp;
		unsigned char data2;
	};

public:
	TextureArrayClass();
	TextureArrayClass(const TextureArrayClass&);
	~TextureArrayClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, char*);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, char*, char*);
	void SetupTextureDesc(D3D11_TEXTURE2D_DESC*, int, int);
	void Shutdown();

	ID3D11ShaderResourceView** GetTextureArray();

private:
	bool LoadTarga(char*, int&, int&, int);

private:
	ID3D11ShaderResourceView* m_textureShaders[3];
	unsigned char* m_targaData[3];
	ID3D11Texture2D* m_textures[3];
};

#endif
