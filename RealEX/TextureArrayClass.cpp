////////////////////////////////////////////////////////////////////////////////
// Filename: texturearrayclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "texturearrayclass.h"

TextureArrayClass::TextureArrayClass()
{
	m_textures[0] = 0;
	m_textures[1] = 0;
	m_textures[2] = 0;
	m_textureShaders[0] = 0;
	m_textureShaders[1] = 0;
	m_textureShaders[2] = 0;
	m_targaData[0] = 0;
	m_targaData[1] = 0;
	m_targaData[2] = 0;
}

TextureArrayClass::TextureArrayClass(const TextureArrayClass& other)
{
}


TextureArrayClass::~TextureArrayClass()
{
}


bool TextureArrayClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename1, char* filename2)
{
	bool result;
	int height, width;
	D3D11_TEXTURE2D_DESC textureDesc;
	HRESULT hResult;
	unsigned int rowPitch;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;

	// Load the first targa image data into memory.
	result = LoadTarga(filename1, height, width, 0);
	if (!result)
	{
		return false;
	}

	// Setup the description of the texture.
	SetupTextureDesc(&textureDesc, height, width);

	// Create the first empty texture.
	hResult = device->CreateTexture2D(&textureDesc, NULL, &m_textures[0]);
	if (FAILED(hResult))
	{
		return false;
	}

	// Set the row pitch of the targa image data.
	rowPitch = (width * 4) * sizeof(unsigned char);

	// Copy the first targa image data into the first texture.
	deviceContext->UpdateSubresource(m_textures[0], 0, NULL, m_targaData[0], rowPitch, 0);

	// Setup the shader resource view description.
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;

	// Create the shader resource view for the first texture.
	hResult = device->CreateShaderResourceView(m_textures[0], &srvDesc, &m_textureShaders[0]);
	if (FAILED(hResult))
	{
		return false;
	}

	// Load the second targa image data into memory.
	result = LoadTarga(filename2, height, width, 1);
	if (!result)
	{
		return false;
	}

	// Setup the description of the texture.
	SetupTextureDesc(&textureDesc, height, width);

	// Create the second empty texture.
	hResult = device->CreateTexture2D(&textureDesc, NULL, &m_textures[1]);
	if (FAILED(hResult))
	{
		return false;
	}

	// Set the row pitch of the targa image data.
	rowPitch = (width * 4) * sizeof(unsigned char);

	// Copy the second targa image data into the second texture.
	deviceContext->UpdateSubresource(m_textures[1], 0, NULL, m_targaData[1], rowPitch, 0);

	// Setup the shader resource view description.
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;

	// Create the shader resource view for the second texture.
	hResult = device->CreateShaderResourceView(m_textures[1], &srvDesc, &m_textureShaders[1]);
	if (FAILED(hResult))
	{
		return false;
	}

	// Generate mipmaps for first texture.
	deviceContext->GenerateMips(m_textureShaders[0]);

	// Generate mipmaps for second texture.
	deviceContext->GenerateMips(m_textureShaders[1]);

	// Release the targa image data now that the image data have been (mind the plural) loaded into the texture.
	delete[] m_targaData[0];
	m_targaData[0] = 0;
	delete[] m_targaData[1];
	m_targaData[1] = 0;

	return true;
}

bool TextureArrayClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename1, char* filename2, char* filename3)
{
	bool result;
	int height, width;
	D3D11_TEXTURE2D_DESC textureDesc;
	HRESULT hResult;
	unsigned int rowPitch;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;

	// Load the first targa image data into memory.
	result = LoadTarga(filename1, height, width, 0);
	if (!result)
	{
		return false;
	}

	// Setup the description of the texture.
	SetupTextureDesc(&textureDesc, height, width);

	// Create the first empty texture.
	hResult = device->CreateTexture2D(&textureDesc, NULL, &m_textures[0]);
	if (FAILED(hResult))
	{
		return false;
	}

	// Set the row pitch of the targa image data.
	rowPitch = (width * 4) * sizeof(unsigned char);

	// Copy the first targa image data into the first texture.
	deviceContext->UpdateSubresource(m_textures[0], 0, NULL, m_targaData[0], rowPitch, 0);

	// Setup the shader resource view description.
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;

	// Create the shader resource view for the first texture.
	hResult = device->CreateShaderResourceView(m_textures[0], &srvDesc, &m_textureShaders[0]);
	if (FAILED(hResult))
	{
		return false;
	}

	// Load the second targa image data into memory.
	result = LoadTarga(filename2, height, width, 1);
	if (!result)
	{
		return false;
	}

	// Setup the description of the texture.
	SetupTextureDesc(&textureDesc, height, width);

	// Create the second empty texture.
	hResult = device->CreateTexture2D(&textureDesc, NULL, &m_textures[1]);
	if (FAILED(hResult))
	{
		return false;
	}

	// Set the row pitch of the targa image data.
	rowPitch = (width * 4) * sizeof(unsigned char);

	// Copy the second targa image data into the second texture.
	deviceContext->UpdateSubresource(m_textures[1], 0, NULL, m_targaData[1], rowPitch, 0);

	// Setup the shader resource view description.
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;

	// Create the shader resource view for the second texture.
	hResult = device->CreateShaderResourceView(m_textures[1], &srvDesc, &m_textureShaders[1]);
	if (FAILED(hResult))
	{
		return false;
	}

	// Load the second targa image data into memory.
	result = LoadTarga(filename3, height, width, 2);
	if (!result)
	{
		return false;
	}

	// Setup the description of the texture.
	SetupTextureDesc(&textureDesc, height, width);

	// Create the second empty texture.
	hResult = device->CreateTexture2D(&textureDesc, NULL, &m_textures[2]);
	if (FAILED(hResult))
	{
		return false;
	}

	// Set the row pitch of the targa image data.
	rowPitch = (width * 4) * sizeof(unsigned char);

	// Copy the second targa image data into the second texture.
	deviceContext->UpdateSubresource(m_textures[2], 0, NULL, m_targaData[2], rowPitch, 0);

	// Setup the shader resource view description.
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;

	// Create the shader resource view for the second texture.
	hResult = device->CreateShaderResourceView(m_textures[2], &srvDesc, &m_textureShaders[2]);
	if (FAILED(hResult))
	{
		return false;
	}

	// Generate mipmaps for first texture.
	deviceContext->GenerateMips(m_textureShaders[0]);

	// Generate mipmaps for second texture.
	deviceContext->GenerateMips(m_textureShaders[1]);

	// Generate mipmaps for second texture.
	deviceContext->GenerateMips(m_textureShaders[2]);

	// Release the targa image data now that the image data have been (mind the plural) loaded into the texture.
	delete[] m_targaData[0];
	m_targaData[0] = 0;
	delete[] m_targaData[1];
	m_targaData[1] = 0;
	delete[] m_targaData[2];
	m_targaData[2] = 0;

	return true;
}

void TextureArrayClass::SetupTextureDesc(D3D11_TEXTURE2D_DESC* textureDesc, int height, int width)
{
	textureDesc->Height = height;
	textureDesc->Width = width;
	textureDesc->MipLevels = 0;
	textureDesc->ArraySize = 1;
	textureDesc->Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc->SampleDesc.Count = 1;
	textureDesc->SampleDesc.Quality = 0;
	textureDesc->Usage = D3D11_USAGE_DEFAULT;
	textureDesc->BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	textureDesc->CPUAccessFlags = 0;
	textureDesc->MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
}

void TextureArrayClass::Shutdown()
{
	/*ID3D11ShaderResourceView* m_textureShaders[2];
	unsigned char* m_targaData[2];
	ID3D11Texture2D* m_textures[2];*/

	// Release the texture resources.
	if (m_textures[0])
	{
		m_textures[0]->Release();
		m_textures[0] = 0;
	}

	if (m_textures[1])
	{
		m_textures[1]->Release();
		m_textures[1] = 0;
	}

	if (m_textureShaders[0])
	{
		m_textureShaders[0]->Release();
		m_textureShaders[0] = 0;
	}

	if (m_textureShaders[1])
	{
		m_textureShaders[1]->Release();
		m_textureShaders[1] = 0;
	}

	return;
}

bool TextureArrayClass::LoadTarga(char* filename, int& height, int& width, int targaIndex)
{
	int error, bpp, imageSize, index, i, j, k;
	FILE* filePtr;
	unsigned int count;
	TargaHeader targaFileHeader;
	unsigned char* targaImage;


	// Open the targa file for reading in binary.
	error = fopen_s(&filePtr, filename, "rb");
	if (error != 0)
	{
		return false;
	}

	// Read in the file header.
	count = (unsigned int)fread(&targaFileHeader, sizeof(TargaHeader), 1, filePtr);
	if (count != 1)
	{
		return false;
	}

	// Get the important information from the header.
	height = (int)targaFileHeader.height;
	width = (int)targaFileHeader.width;
	bpp = (int)targaFileHeader.bpp;

	// Check that it is 32 bit and not 24 bit.
	if (bpp != 32)
	{
		return false;
	}

	// Calculate the size of the 32 bit image data.
	imageSize = width * height * 4;

	// Allocate memory for the targa image data.
	targaImage = new unsigned char[imageSize];
	if (!targaImage)
	{
		return false;
	}

	// Read in the targa image data.
	count = (unsigned int)fread(targaImage, 1, imageSize, filePtr);
	if (count != imageSize)
	{
		return false;
	}

	// Close the file.
	error = fclose(filePtr);
	if (error != 0)
	{
		return false;
	}

	// Allocate memory for the targa destination data.
	m_targaData[targaIndex] = new unsigned char[imageSize];
	if (!m_targaData[targaIndex])
	{
		return false;
	}

	// Initialize the index into the targa destination data array.
	index = 0;

	// Initialize the index into the targa image data.
	k = (width * height * 4) - (width * 4);

	// Now copy the targa image data into the targa destination array in the correct order since the targa format is stored upside down.
	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			m_targaData[targaIndex][index + 0] = targaImage[k + 2];  // Red.
			m_targaData[targaIndex][index + 1] = targaImage[k + 1];  // Green.
			m_targaData[targaIndex][index + 2] = targaImage[k + 0];  // Blue
			m_targaData[targaIndex][index + 3] = targaImage[k + 3];  // Alpha

			// Increment the indexes into the targa data.
			k += 4;
			index += 4;
		}

		// Set the targa image data index back to the preceding row at the beginning of the column since its reading it in upside down.
		k -= (width * 8);
	}

	// Release the targa image data now that it was copied into the destination array.
	delete[] targaImage;
	targaImage = 0;

	return true;
}

ID3D11ShaderResourceView** TextureArrayClass::GetTextureArray()
{
	return m_textureShaders;
}