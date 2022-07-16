///////////////////////////////////////////////////////////////////////////////
// Filename: textclass.cpp
///////////////////////////////////////////////////////////////////////////////
#include "textclass.h"

TextClass::TextClass()
{
	m_Font = 0;
	m_FontShader = 0;

	m_videoAdapterName = 0;
	m_videoMemory = 0;
	m_Fps = 0;
	m_Cpu = 0;
	m_posX = 0;
	m_posY = 0;
	m_posZ = 0;
	m_rotX = 0;
	m_rotY = 0;
	m_rotZ = 0;

	strcpy_s(m_string, "this is nice string");
}

TextClass::TextClass(const TextClass& other)
{
}


TextClass::~TextClass()
{
}

bool TextClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, HWND hwnd, int screenWidth, int screenHeight,
	DXMATRIX baseViewMatrix)
{
	bool result;

	// Store the screen width and height.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Store the base view matrix.
	m_baseViewMatrix = baseViewMatrix;

	// Create the font object.
	m_Font = new FontClass;
	if (!m_Font)
	{
		return false;
	}

	// Initialize the font object.
	result = m_Font->Initialize(device, deviceContext, (char*) "../RealEX/data/font.txt", (char*) "../RealEX/textures/font.tga");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the font object.", L"Error", MB_OK);
		return false;
	}

	// Create the font shader object.
	m_FontShader = new FontShaderClass;
	if (!m_FontShader)
	{
		return false;
	}

	// Initialize the font shader object.
	result = m_FontShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the video adapter name sentence.
	result = InitializeSentence(&m_videoAdapterName, 64, device);
	if (!result)
	{
		return false;
	}

	// Initialize the video memory sentence.
	result = InitializeSentence(&m_videoMemory, 32, device);
	if (!result)
	{
		return false;
	}

	// Initialize the FPS sentence.
	result = InitializeSentence(&m_Fps, 32, device);
	if (!result)
	{
		return false;
	}

	// Initialize the CPU sentence.
	result = InitializeSentence(&m_Cpu, 32, device);
	if (!result)
	{
		return false;
	}

	// Initialize the X position sentence.
	result = InitializeSentence(&m_posX, 32, device);
	if (!result)
	{
		return false;
	}

	// Initialize the Y position sentence.
	result = InitializeSentence(&m_posY, 32, device);
	if (!result)
	{
		return false;
	}

	// Initialize the Z position sentence.
	result = InitializeSentence(&m_posZ, 32, device);
	if (!result)
	{
		return false;
	}

	// Initialize the X rotation sentence.
	result = InitializeSentence(&m_rotX, 32, device);
	if (!result)
	{
		return false;
	}

	// Initialize the Y rotation sentence.
	result = InitializeSentence(&m_rotY, 32, device);
	if (!result)
	{
		return false;
	}

	// Initialize the Z rotation sentence.
	result = InitializeSentence(&m_rotZ, 32, device);
	if (!result)
	{
		return false;
	}

	// Initialize the render count sentence.
	result = InitializeSentence(&m_renderCount, 32, device);
	if (!result)
	{
		return false;
	}

	return true;
}

void TextClass::Shutdown()
{
	// Release the video adapter name sentence.
	ReleaseSentence(&m_videoAdapterName);

	// Release the video memory sentence.
	ReleaseSentence(&m_videoMemory);

	// Release the FPS sentence.
	ReleaseSentence(&m_Fps);

	// Release the CPU sentence.
	ReleaseSentence(&m_Cpu);

	// Release the X position sentence.
	ReleaseSentence(&m_posX);

	// Release the Y position sentence.
	ReleaseSentence(&m_posY);

	// Release the Z position sentence.
	ReleaseSentence(&m_posZ);

	// Release the X rotation sentence.
	ReleaseSentence(&m_rotX);

	// Release the Y rotation sentence.
	ReleaseSentence(&m_rotY);

	// Release the Z rotation sentence.
	ReleaseSentence(&m_rotZ);

	// Release the render count sentence.
	ReleaseSentence(&m_renderCount);

	// Release the font shader object.
	if (m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}

	// Release the font object.
	if (m_Font)
	{
		m_Font->Shutdown();
		delete m_Font;
		m_Font = 0;
	}

	return;
}

bool TextClass::Render(ID3D11DeviceContext* deviceContext, DXMATRIX worldMatrix, DXMATRIX orthoMatrix)
{
	bool result;


	// Draw the video adapter name sentence.
	result = RenderSentence(deviceContext, m_videoAdapterName, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Draw the video memory sentence.
	result = RenderSentence(deviceContext, m_videoMemory, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Draw the FPS sentence.
	result = RenderSentence(deviceContext, m_Fps, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Draw the CPU sentence.
	result = RenderSentence(deviceContext, m_Cpu, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Draw the X position sentence.
	result = RenderSentence(deviceContext, m_posX, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Draw the Y position sentence.
	result = RenderSentence(deviceContext, m_posY, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Draw the Z position sentence.
	result = RenderSentence(deviceContext, m_posZ, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Draw the X rotation sentence.
	result = RenderSentence(deviceContext, m_rotX, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Draw the Y rotation sentence.
	result = RenderSentence(deviceContext, m_rotY, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Draw the Z rotation sentence.
	result = RenderSentence(deviceContext, m_rotZ, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Draw the render count sentence.
	result = RenderSentence(deviceContext, m_renderCount, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	return true;
}

bool TextClass::InitializeSentence(SentenceType** sentence, int maxLength, ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;


	// Create a new sentence object.
	*sentence = new SentenceType;
	if (!*sentence)
	{
		return false;
	}

	// Initialize the sentence buffers to null.
	(*sentence)->vertexBuffer = 0;
	(*sentence)->indexBuffer = 0;

	// Set the maximum length of the sentence.
	(*sentence)->maxLength = maxLength;

	// Set the number of vertices in the vertex array.
	(*sentence)->vertexCount = 6 * maxLength;

	// Set the number of indexes in the index array.
	(*sentence)->indexCount = (*sentence)->vertexCount;

	// Create the vertex array.
	vertices = new VertexType[(*sentence)->vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[(*sentence)->indexCount];
	if (!indices)
	{
		return false;
	}

	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * (*sentence)->vertexCount));

	// Initialize the index array.
	for (i = 0; i < (*sentence)->indexCount; i++)
	{
		indices[i] = i;
	}

	// Set up the description of the dynamic vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * (*sentence)->vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &(*sentence)->vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * (*sentence)->indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &(*sentence)->indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the vertex array as it is no longer needed.
	delete[] vertices;
	vertices = 0;

	// Release the index array as it is no longer needed.
	delete[] indices;
	indices = 0;

	return true;
}

bool TextClass::UpdateSentence(SentenceType* sentence, char* text, int positionX, int positionY, float red, float green, float blue,
	ID3D11DeviceContext* deviceContext)
{
	int numLetters;
	VertexType* vertices;
	float drawX, drawY;
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;

	// Store the color of the sentence.
	sentence->red = red;
	sentence->green = green;
	sentence->blue = blue;

	// Get the number of letters in the sentence.
	numLetters = (int)strlen(text);

	// Check for possible buffer overflow.
	if (numLetters > sentence->maxLength)
	{
		return false;
	}

	// Create the vertex array.
	vertices = new VertexType[sentence->vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * sentence->vertexCount));

	// Calculate the X and Y pixel position on the screen to start drawing to.
	drawX = (float)(((m_screenWidth / 2) * -1) + positionX);
	drawY = (float)((m_screenHeight / 2) - positionY);

	// Use the font class to build the vertex array from the sentence text and sentence draw location.
	m_Font->BuildVertexArray((void*)vertices, text, drawX, drawY);

	// Lock the vertex buffer so it can be written to.
	result = deviceContext->Map(sentence->vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the vertex buffer.
	verticesPtr = (VertexType*)mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * sentence->vertexCount));

	// Unlock the vertex buffer.
	deviceContext->Unmap(sentence->vertexBuffer, 0);

	// Release the vertex array as it is no longer needed.
	delete[] vertices;
	vertices = 0;

	return true;
}

void TextClass::ReleaseSentence(SentenceType** sentence)
{
	if (*sentence)
	{
		// Release the sentence vertex buffer.
		if ((*sentence)->vertexBuffer)
		{
			(*sentence)->vertexBuffer->Release();
			(*sentence)->vertexBuffer = 0;
		}

		// Release the sentence index buffer.
		if ((*sentence)->indexBuffer)
		{
			(*sentence)->indexBuffer->Release();
			(*sentence)->indexBuffer = 0;
		}

		// Release the sentence.
		delete* sentence;
		*sentence = 0;
	}

	return;
}

bool TextClass::RenderSentence(ID3D11DeviceContext* deviceContext, SentenceType* sentence, DXMATRIX worldMatrix,
	DXMATRIX orthoMatrix)
{
	unsigned int stride, offset;
	DXFLOAT4 pixelColor;
	bool result;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &sentence->vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(sentence->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Create a pixel color vector with the input sentence color.
	pixelColor = DXFLOAT4(sentence->red, sentence->green, sentence->blue, 1.0f);

	// Render the text using the font shader.
	result = m_FontShader->Render(deviceContext, sentence->indexCount, worldMatrix, m_baseViewMatrix, orthoMatrix, m_Font->GetTexture(),
		pixelColor);
	if (!result)
	{
		false;
	}

	return true;
}

void TextClass::UpdateString(WPARAM wparam, ID3D11DeviceContext* deviceContext)
{
	switch (wparam)
	{
		case VK_BACK:
		{
			if (strlen(m_string) == 0)
				return;
			m_string[strlen(m_string) - 1] = '\0';
			m_string[strlen(m_string) + 1] = -1;
			UpdateSentence(m_Fps, (char*)m_string, 100, 300, 1.0f, 1.0f, 0.0f, deviceContext);
			return;
		}
		default:
		{
			char carriage[2] = { (char)wparam, '\0' };
			strcat_s(m_string, carriage);
			UpdateSentence(m_Fps, (char*)m_string, 100, 300, 1.0f, 1.0f, 0.0f, deviceContext);
			return;
		}
	}
}

bool TextClass::SetVideoCardInfo(char videoAdapterName[], int videoMemory, ID3D11DeviceContext* deviceContext)
{
	char videoAdapterNameString[64];
	char tempString[32];
	char videoMemoryString[32];
	bool result;

	// Setup the video adapter name string.
	strcpy_s(videoAdapterNameString, "Video Card: ");
	strcat_s(videoAdapterNameString, videoAdapterName);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_videoAdapterName, videoAdapterNameString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	// Truncate the memory value to prevent buffer over flow.
	if (videoMemory > 9999999)
	{
		videoMemory = 9999999;
	}

	// Convert the memory integer to string format.
	_itoa_s(videoMemory, tempString, 10);

	// Setup the video memory string.
	strcpy_s(videoMemoryString, "Video Memory: ");
	strcat_s(videoMemoryString, tempString);
	strcat_s(videoMemoryString, " MB");

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_videoMemory, videoMemoryString, 10, 30, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}

bool TextClass::SetFps(int fps, ID3D11DeviceContext* deviceContext)
{
	char tempString[32];
	char fpsString[32];
	float red, green, blue;
	bool result;


	// Truncate the fps to below 10,000.
	if (fps > 9999)
	{
		fps = 9999;
	}

	// Convert the fps integer to string format.
	_itoa_s(fps, tempString, 10);

	// Setup the fps string.
	strcpy_s(fpsString, "Fps: ");
	strcat_s(fpsString, tempString);

	// If fps is 60 or above set the fps color to green.
	if (fps >= 60)
	{
		red = 0.0f;
		green = 1.0f;
		blue = 0.0f;
	}

	// If fps is below 60 set the fps color to yellow.
	if (fps < 60)
	{
		red = 1.0f;
		green = 1.0f;
		blue = 0.0f;
	}

	// If fps is below 30 set the fps color to red.
	if (fps < 30)
	{
		red = 1.0f;
		green = 0.0f;
		blue = 0.0f;
	}

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_Fps, fpsString, 10, 70, red, green, blue, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}

bool TextClass::SetCpu(int cpu, ID3D11DeviceContext* deviceContext)
{
	char tempString[32];
	char cpuString[32];
	bool result;


	// Convert the cpu integer to string format.
	_itoa_s(cpu, tempString, 10);

	// Setup the cpu string.
	strcpy_s(cpuString, "Cpu: ");
	strcat_s(cpuString, tempString);
	strcat_s(cpuString, "%");

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_Cpu, cpuString, 10, 90, 0.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}

bool TextClass::SetCameraPosition(float posX, float posY, float posZ, ID3D11DeviceContext* deviceContext)
{
	int positionX, positionY, positionZ;
	char tempString[32];
	char posString[32];
	bool result;

	// Convert the position from floating point to integer.
	positionX = (int)posX;
	positionY = (int)posY;
	positionZ = (int)posZ;

	// Truncate the position if it exceeds either 9999 or -9999.
	if (positionX > 9999) { positionX = 9999; }
	if (positionY > 9999) { positionY = 9999; }
	if (positionZ > 9999) { positionZ = 9999; }

	if (positionX < -9999) { positionX = -9999; }
	if (positionY < -9999) { positionY = -9999; }
	if (positionZ < -9999) { positionZ = -9999; }

	// Convert the position integer to string format.
	_itoa_s(positionX, tempString, 10);

	// Setup the position string.
	strcpy_s(posString, "X: ");
	strcat_s(posString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_posX, posString, 10, 130, 0.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	// Convert the position integer to string format.
	_itoa_s(positionY, tempString, 10);

	// Setup the position string.
	strcpy_s(posString, "Y: ");
	strcat_s(posString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_posY, posString, 10, 150, 0.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	// Convert the position integer to string format.
	_itoa_s(positionZ, tempString, 10);

	// Setup the position string.
	strcpy_s(posString, "Z: ");
	strcat_s(posString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_posZ, posString, 10, 170, 0.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}

bool TextClass::SetCameraRotation(float rotX, float rotY, float rotZ, ID3D11DeviceContext* deviceContext)
{
	int rotationX, rotationY, rotationZ;
	char tempString[32];
	char rotString[32];
	bool result;

	// Convert the rotation from floating point to integer.
	rotationX = (int)rotX;
	rotationY = (int)rotY;
	rotationZ = (int)rotZ;

	// Convert the rotation integer to string format.
	_itoa_s(rotationX, tempString, 10);

	// Setup the rotation string.
	strcpy_s(rotString, "rX: ");
	strcat_s(rotString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_rotX, rotString, 10, 210, 0.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	// Convert the rotation integer to string format.
	_itoa_s(rotationY, tempString, 10);

	// Setup the rotation string.
	strcpy_s(rotString, "rY: ");
	strcat_s(rotString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_rotY, rotString, 10, 230, 0.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	// Convert the rotation integer to string format.
	_itoa_s(rotationZ, tempString, 10);

	// Setup the rotation string.
	strcpy_s(rotString, "rZ: ");
	strcat_s(rotString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_rotZ, rotString, 10, 250, 0.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}

bool TextClass::SetRenderCount(int renderCount, ID3D11DeviceContext* deviceContext)
{
	char temp[32];
	char renderStr[32];
	bool result;

	// Truncate the render count if it gets to large to prevent a buffer overflow.
	if (renderCount > 999999999)
	{
		renderCount = 999999999;
	}

	// Convert the render count to string
	_itoa_s(renderCount, temp, 10);

	// Set the string up
	strcpy_s(renderStr, "Render Count: ");
	strcat_s(renderStr, temp);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_renderCount, renderStr, 10, 290, 0.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}

bool TextClass::SetIntersection(bool intersection, ID3D11DeviceContext* deviceContext)
{
	bool result;

	if (intersection)
	{
		// Update the sentence vertex buffer with the new string information.
		result = UpdateSentence(m_Fps, (char*)"Intersection: Yes", 20, 40, 0.0f, 1.0f, 0.0f, deviceContext);
		if (!result)
		{
			return false;
		}
	}
	else
	{
		// Update the sentence vertex buffer with the new string information.
		result = UpdateSentence(m_Fps, (char*)"Intersection: No", 20, 40, 1.0f, 0.0f, 0.0f, deviceContext);
		if (!result)
		{
			return false;
		}
	}

	return true;
}