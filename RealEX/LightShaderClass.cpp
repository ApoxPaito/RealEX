////////////////////////////////////////////////////////////////////////////////
// Filename: lightshaderclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "lightshaderclass.h"


LightShaderClass::LightShaderClass()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_sampleState = 0;
	m_matrixBuffer = 0;
	m_cameraBuffer = 0;
	m_lightBuffer = 0;
	m_lightColorBuffer = 0;
	m_lightPositionBuffer = 0;
}


LightShaderClass::LightShaderClass(const LightShaderClass& other)
{
}


LightShaderClass::~LightShaderClass()
{
}


bool LightShaderClass::Initialize(ID3D11Device* device, HWND hwnd, LightningType type)
{
	bool result;

	switch (type)
	{
		case Diffuse:
			// Initialize the vertex and pixel shaders.
			result = InitializeShader(device, hwnd, (WCHAR*)L"../RealEX/LightDiffuse.vs", (WCHAR*)L"../RealEX/LightDiffuse.ps", type);
			if (!result)
			{
				return false;
			}
			break;
		case Specular:
			// Initialize the vertex and pixel shaders.
			result = InitializeShader(device, hwnd, (WCHAR*)L"../RealEX/LightSpecular.vs", (WCHAR*)L"../RealEX/LightSpecular.ps", type);
			if (!result)
			{
				return false;
			}
			break;
		case Ambient:
			// Initialize the vertex and pixel shaders.
			result = InitializeShader(device, hwnd, (WCHAR*)L"../RealEX/LightAmbient.vs", (WCHAR*)L"../RealEX/LightAmbient.ps", type);
			if (!result)
			{
				return false;
			}
			break;
		case Multiple:
			// Initialize the vertex and pixel shaders.
			result = InitializeShader(device, hwnd, (WCHAR*) L"../RealEX/LightMultiple.vs", (WCHAR*) L"../RealEX/LightMultiple.ps", type);
			if (!result)
			{
				return false;
			}
			break;
		case Deferred:
			// Initialize the vertex and pixel shaders.
			result = InitializeShader(device, hwnd, (WCHAR*)L"../RealEX/DeferredLight.vs", (WCHAR*)L"../RealEX/DeferredLight.ps", type);
			if (!result)
			{
				return false;
			}
			break;
		default:
			return false;
	}

	return true;
}

void LightShaderClass::Shutdown()
{
	// Shutdown the vertex and pixel shaders as well as the related objects.
	ShutdownShader();

	return;
}

bool LightShaderClass::RenderSpecular(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX& worldMatrix, DXMATRIX& viewMatrix,
	DXMATRIX& projectionMatrix, ID3D11ShaderResourceView* texture, DXFLOAT3 lightDirection, DXFLOAT4 ambientColor,
	DXFLOAT4 diffuseColor, DXFLOAT3 cameraPosition, DXFLOAT4 specularColor, float specularPower)
{
	bool result;


	// Set the shader parameters that it will use for rendering.
	result = SetShaderParametersSpecular(deviceContext, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, ambientColor, diffuseColor, cameraPosition, specularColor, specularPower);
	if (!result)
	{
		return false;
	}

	// Now render the prepared buffers with the shader.
	RenderShader(deviceContext, indexCount);

	return true;
}

bool LightShaderClass::RenderDiffuse(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX& worldMatrix, DXMATRIX& viewMatrix,
	DXMATRIX& projectionMatrix, ID3D11ShaderResourceView* texture, DXFLOAT3 lightDirection,	DXFLOAT4 diffuseColor)
{
	bool result;


	// Set the shader parameters that it will use for rendering.
	result = SetShaderParametersDiffuse(deviceContext, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, diffuseColor);
	if (!result)
	{
		return false;
	}

	// Now render the prepared buffers with the shader.
	RenderShader(deviceContext, indexCount);

	return true;
}

bool LightShaderClass::RenderAmbient(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX& worldMatrix, DXMATRIX& viewMatrix,
	DXMATRIX& projectionMatrix, ID3D11ShaderResourceView* texture, DXFLOAT3 lightDirection, DXFLOAT4 ambientColor, DXFLOAT4 diffuseColor)
{
	bool result;


	// Set the shader parameters that it will use for rendering.
	result = SetShaderParametersAmbient(deviceContext, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, ambientColor, diffuseColor);
	if (!result)
	{
		return false;
	}

	// Now render the prepared buffers with the shader.
	RenderShader(deviceContext, indexCount);

	return true;
}

bool LightShaderClass::RenderMultiple(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix,
	DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, DXFLOAT4 diffuseColor[], DXFLOAT4 lightPosition[])
{
	bool result;


	// Set the shader parameters that it will use for rendering.
	result = SetShaderParametersMultiple(deviceContext, worldMatrix, viewMatrix, projectionMatrix, texture, diffuseColor, lightPosition);
	if (!result)
	{
		return false;
	}

	// Now render the prepared buffers with the shader.
	RenderShader(deviceContext, indexCount);

	return true;
}

bool LightShaderClass::RenderDeferred(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix,
	DXMATRIX projectionMatrix, ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture,
	DXFLOAT3 lightDirection)
{
	bool result;


	// Set the shader parameters that it will use for rendering.
	result = SetShaderParametersDeferred(deviceContext, worldMatrix, viewMatrix, projectionMatrix, colorTexture, normalTexture, lightDirection);
	if (!result)
	{
		return false;
	}

	// Now render the prepared buffers with the shader.
	RenderShader(deviceContext, indexCount);

	return true;
}

bool LightShaderClass::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename, LightningType type)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;

	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
	unsigned int numElements;
	D3D11_SAMPLER_DESC samplerDesc;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC cameraBufferDesc;
	D3D11_BUFFER_DESC lightBufferDesc;
	D3D11_BUFFER_DESC lightColorBufferDesc;
	D3D11_BUFFER_DESC lightPositionBufferDesc;

	// Initialize the pointers this function will use to null.
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	// Compile the vertex shader code.
	result = D3DCompileFromFile((LPCWSTR)vsFilename, NULL, NULL, "LightVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &vertexShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		}
		// If there was nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(hwnd, vsFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	// Compile the pixel shader code.
	result = D3DCompileFromFile((LPCWSTR)psFilename, NULL, NULL, "LightPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &pixelShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
		}
		// If there was nothing in the error message then it simply could not find the file itself.
		else
		{
			MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	// Create the vertex shader from the buffer.
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if (FAILED(result))
	{
		return false;
	}

	// Create the pixel shader from the buffer.
	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if (FAILED(result))
	{
		return false;
	}

	// Create the vertex input layout description.
	// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	if (type != Deferred)
	{
		polygonLayout[2].SemanticName = "NORMAL";
		polygonLayout[2].SemanticIndex = 0;
		polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		polygonLayout[2].InputSlot = 0;
		polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		polygonLayout[2].InstanceDataStepRate = 0;
	}

	// Get a count of the elements in the layout.
	numElements = type != Deferred ? sizeof(polygonLayout) / sizeof(polygonLayout[0]) : 2;

	// Create the vertex input layout.
	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(),
		&m_layout);
	if (FAILED(result))
	{
		return false;
	}

	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

	// Create a texture sampler state description.
	if (type == Deferred)
	{
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	}
	else
	{
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	}
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	result = device->CreateSamplerState(&samplerDesc, &m_sampleState);
	if (FAILED(result))
	{
		return false;
	}

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(result))
	{
		return false;
	}

	if (type == LightningType::Multiple)
	{
		// Setup the description of the dynamic constant buffer that is in the pixel shader.
		lightColorBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		lightColorBufferDesc.ByteWidth = sizeof(LightColorBufferType);
		lightColorBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		lightColorBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		lightColorBufferDesc.MiscFlags = 0;
		lightColorBufferDesc.StructureByteStride = 0;

		// Create the constant buffer pointer so we can access the pixel shader constant buffer from within this class.
		result = device->CreateBuffer(&lightColorBufferDesc, NULL, &m_lightColorBuffer);
		if (FAILED(result))
		{
			return false;
		}

		// Setup the description of the dynamic constant buffer that is in the vertex shader.
		lightPositionBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		lightPositionBufferDesc.ByteWidth = sizeof(LightPositionBufferType);
		lightPositionBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		lightPositionBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		lightPositionBufferDesc.MiscFlags = 0;
		lightPositionBufferDesc.StructureByteStride = 0;

		// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
		result = device->CreateBuffer(&lightPositionBufferDesc, NULL, &m_lightPositionBuffer);
		if (FAILED(result))
		{
			return false;
		}

		return true;
	}

	if (type != Deferred)
	{
		// Setup the description of the camera dynamic constant buffer that is in the vertex shader.
		cameraBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		cameraBufferDesc.ByteWidth = sizeof(CameraBufferType);
		cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cameraBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cameraBufferDesc.MiscFlags = 0;
		cameraBufferDesc.StructureByteStride = 0;

		// Create the camera constant buffer pointer so we can access the vertex shader constant buffer from within this class.
		result = device->CreateBuffer(&cameraBufferDesc, NULL, &m_cameraBuffer);
		if (FAILED(result))
		{
			return false;
		}
	}

	// Setup the description of the light dynamic constant buffer that is in the pixel shader.
	// Note that ByteWidth always needs to be a multiple of 16 if using D3D11_BIND_CONSTANT_BUFFER or CreateBuffer will fail.
	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	switch (type)
	{
		case Diffuse:
			lightBufferDesc.ByteWidth = sizeof(LightBufferTypeDiffuse);
			break;
		case Specular:
			lightBufferDesc.ByteWidth = sizeof(LightBufferTypeSpecular);
			break;
		case Ambient:
			lightBufferDesc.ByteWidth = sizeof(LightBufferTypeAmbient);
			break;
		case Deferred:
			lightBufferDesc.ByteWidth = sizeof(LightBufferTypeDeferred);
			break;
		default:
			return false;
	}
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	result = device->CreateBuffer(&lightBufferDesc, NULL, &m_lightBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void LightShaderClass::ShutdownShader()
{
	// Release the light constant buffers.
	if (m_lightColorBuffer)
	{
		m_lightColorBuffer->Release();
		m_lightColorBuffer = 0;
	}
	if (m_lightPositionBuffer)
	{
		m_lightPositionBuffer->Release();
		m_lightPositionBuffer = 0;
	}

	// Release the light constant buffer.
	if (m_lightBuffer)
	{
		m_lightBuffer->Release();
		m_lightBuffer = 0;
	}

	// Release the camera constant buffer.
	if (m_cameraBuffer)
	{
		m_cameraBuffer->Release();
		m_cameraBuffer = 0;
	}

	// Release the matrix constant buffer.
	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}

	// Release the sampler state.
	if (m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = 0;
	}

	// Release the layout.
	if (m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}

	// Release the pixel shader.
	if (m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = 0;
	}

	// Release the vertex shader.
	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}

	return;
}

void LightShaderClass::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	ofstream fout;


	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for (i = 0; i < bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();

	// Release the error message.
	errorMessage->Release();
	errorMessage = 0;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}

bool LightShaderClass::SetShaderParametersSpecular(ID3D11DeviceContext* deviceContext, DXMATRIX worldMatrix, DXMATRIX viewMatrix,
	DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, DXFLOAT3 lightDirection, DXFLOAT4 ambientColor,
	DXFLOAT4 diffuseColor, DXFLOAT3 cameraPosition, DXFLOAT4 specularColor, float specularPower)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	unsigned int bufferNumber;
	MatrixBufferType* dataPtr;
	LightBufferTypeSpecular* dataPtr2;
	CameraBufferType* dataPtr3;


	// Transpose the matrices to prepare them for the shader.
	worldMatrix = XMMatrixTranspose(worldMatrix);
	viewMatrix = XMMatrixTranspose(viewMatrix);
	projectionMatrix = XMMatrixTranspose(projectionMatrix);

	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	// Unlock the constant buffer.
	deviceContext->Unmap(m_matrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Now set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

	// Lock the camera constant buffer so it can be written to.
	result = deviceContext->Map(m_cameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr3 = (CameraBufferType*)mappedResource.pData;

	// Copy the camera position into the constant buffer.
	dataPtr3->cameraPosition = cameraPosition;
	dataPtr3->padding = 0.0f;

	// Unlock the camera constant buffer.
	deviceContext->Unmap(m_cameraBuffer, 0);

	// Set the position of the camera constant buffer in the vertex shader.
	bufferNumber = 1;

	// Now set the camera constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_cameraBuffer);

	// Set shader texture resource in the pixel shader.
	deviceContext->PSSetShaderResources(0, 1, &texture);

	// Lock the light constant buffer so it can be written to.
	result = deviceContext->Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr2 = (LightBufferTypeSpecular*)mappedResource.pData;

	// Copy the lighting variables into the constant buffer.
	dataPtr2->ambientColor = ambientColor;
	dataPtr2->diffuseColor = diffuseColor;
	dataPtr2->lightDirection = lightDirection;
	dataPtr2->specularColor = specularColor;
	dataPtr2->specularPower = specularPower;

	// Unlock the constant buffer.
	deviceContext->Unmap(m_lightBuffer, 0);

	// Set the position of the light constant buffer in the pixel shader.
	bufferNumber = 0;

	// Finally set the light constant buffer in the pixel shader with the updated values.
	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_lightBuffer);

	return true;
}

bool LightShaderClass::SetShaderParametersDiffuse(ID3D11DeviceContext* deviceContext, DXMATRIX worldMatrix, DXMATRIX viewMatrix,
	DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, DXFLOAT3 lightDirection,
	DXFLOAT4 diffuseColor)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	unsigned int bufferNumber;
	MatrixBufferType* dataPtr;
	LightBufferTypeDiffuse* dataPtr2;


	// Transpose the matrices to prepare them for the shader.
	worldMatrix = XMMatrixTranspose(worldMatrix);
	viewMatrix = XMMatrixTranspose(viewMatrix);
	projectionMatrix = XMMatrixTranspose(projectionMatrix);

	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	// Unlock the constant buffer.
	deviceContext->Unmap(m_matrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Now set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

	// Set shader texture resource in the pixel shader.
	deviceContext->PSSetShaderResources(0, 1, &texture);

	// Lock the light constant buffer so it can be written to.
	result = deviceContext->Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr2 = (LightBufferTypeDiffuse*)mappedResource.pData;

	// Copy the lighting variables into the constant buffer.
	dataPtr2->diffuseColor = diffuseColor;
	dataPtr2->lightDirection = lightDirection;
	dataPtr2->padding = 0.0f;

	// Unlock the constant buffer.
	deviceContext->Unmap(m_lightBuffer, 0);

	// Set the position of the light constant buffer in the pixel shader.
	bufferNumber = 0;

	// Finally set the light constant buffer in the pixel shader with the updated values.
	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_lightBuffer);

	return true;
}

bool LightShaderClass::SetShaderParametersAmbient(ID3D11DeviceContext* deviceContext, DXMATRIX worldMatrix, DXMATRIX viewMatrix,
	DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, DXFLOAT3 lightDirection, DXFLOAT4 ambientColor,
	DXFLOAT4 diffuseColor)
{

	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	unsigned int bufferNumber;
	MatrixBufferType* dataPtr;
	LightBufferTypeAmbient* dataPtr2;


	// Transpose the matrices to prepare them for the shader.
	worldMatrix = XMMatrixTranspose(worldMatrix);
	viewMatrix = XMMatrixTranspose(viewMatrix);
	projectionMatrix = XMMatrixTranspose(projectionMatrix);

	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	// Unlock the constant buffer.
	deviceContext->Unmap(m_matrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Now set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

	// Set shader texture resource in the pixel shader.
	deviceContext->PSSetShaderResources(0, 1, &texture);

	// Lock the light constant buffer so it can be written to.
	result = deviceContext->Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr2 = (LightBufferTypeAmbient*)mappedResource.pData;

	// Copy the lighting variables into the constant buffer.
	dataPtr2->ambientColor = ambientColor;
	dataPtr2->diffuseColor = diffuseColor;
	dataPtr2->lightDirection = lightDirection;
	dataPtr2->padding = 0.0f;

	// Unlock the constant buffer.
	deviceContext->Unmap(m_lightBuffer, 0);

	// Set the position of the light constant buffer in the pixel shader.
	bufferNumber = 0;

	// Finally set the light constant buffer in the pixel shader with the updated values.
	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_lightBuffer);

	return true;
}

bool LightShaderClass::SetShaderParametersMultiple(ID3D11DeviceContext* deviceContext, DXMATRIX worldMatrix, DXMATRIX viewMatrix,
	DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture,
	DXFLOAT4 diffuseColor[], DXFLOAT4 lightPosition[])
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	LightPositionBufferType* dataPtr2;
	LightColorBufferType* dataPtr3;
	unsigned int bufferNumber;


	// Transpose the matrices to prepare them for the shader.
	worldMatrix = XMMatrixTranspose(worldMatrix);
	viewMatrix = XMMatrixTranspose(viewMatrix);
	projectionMatrix = XMMatrixTranspose(projectionMatrix);

	// Lock the matrix constant buffer so it can be written to.
	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	// Unlock the matrix constant buffer.
	deviceContext->Unmap(m_matrixBuffer, 0);

	// Set the position of the matrix constant buffer in the vertex shader.
	bufferNumber = 0;

	// Now set the matrix constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

	// Lock the light position constant buffer so it can be written to.
	result = deviceContext->Map(m_lightPositionBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr2 = (LightPositionBufferType*)mappedResource.pData;

	// Copy the light position variables into the constant buffer.
	dataPtr2->lightPosition[0] = lightPosition[0];
	dataPtr2->lightPosition[1] = lightPosition[1];
	dataPtr2->lightPosition[2] = lightPosition[2];
	dataPtr2->lightPosition[3] = lightPosition[3];
	dataPtr2->lightPosition[4] = lightPosition[4];

	// Unlock the constant buffer.
	deviceContext->Unmap(m_lightPositionBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 1;

	// Finally set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_lightPositionBuffer);

	// Set shader texture resource in the pixel shader.
	deviceContext->PSSetShaderResources(0, 1, &texture);

	// Lock the light color constant buffer so it can be written to.
	result = deviceContext->Map(m_lightColorBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr3 = (LightColorBufferType*)mappedResource.pData;

	// Copy the light color variables into the constant buffer.
	dataPtr3->diffuseColor[0] = diffuseColor[0];
	dataPtr3->diffuseColor[1] = diffuseColor[1];
	dataPtr3->diffuseColor[2] = diffuseColor[2];
	dataPtr3->diffuseColor[3] = diffuseColor[3];
	dataPtr3->diffuseColor[4] = diffuseColor[4];

	// Unlock the constant buffer.
	deviceContext->Unmap(m_lightColorBuffer, 0);

	// Set the position of the constant buffer in the pixel shader.
	bufferNumber = 0;

	// Finally set the constant buffer in the pixel shader with the updated values.
	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_lightColorBuffer);

	return true;
}

bool LightShaderClass::SetShaderParametersDeferred(ID3D11DeviceContext* deviceContext, DXMATRIX worldMatrix, DXMATRIX viewMatrix,
	DXMATRIX projectionMatrix, ID3D11ShaderResourceView* colorTexture,
	ID3D11ShaderResourceView* normalTexture, DXFLOAT3 lightDirection)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	unsigned int bufferNumber;
	MatrixBufferType* dataPtr;
	LightBufferTypeDeferred* dataPtr2;


	// Transpose the matrices to prepare them for the shader.
	worldMatrix = XMMatrixTranspose(worldMatrix);
	viewMatrix = XMMatrixTranspose(viewMatrix);
	projectionMatrix = XMMatrixTranspose(projectionMatrix);

	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	// Unlock the constant buffer.
	deviceContext->Unmap(m_matrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Now set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

	// Set shader texture resources in the pixel shader.
	deviceContext->PSSetShaderResources(0, 1, &colorTexture);
	deviceContext->PSSetShaderResources(1, 1, &normalTexture);

	// Lock the light constant buffer so it can be written to.
	result = deviceContext->Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr2 = (LightBufferTypeDeferred*)mappedResource.pData;

	// Copy the lighting variables into the constant buffer.
	dataPtr2->lightDirection = lightDirection;
	dataPtr2->padding = 0.0f;

	// Unlock the constant buffer.
	deviceContext->Unmap(m_lightBuffer, 0);

	// Set the position of the light constant buffer in the pixel shader.
	bufferNumber = 0;

	// Finally set the light constant buffer in the pixel shader with the updated values.
	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_lightBuffer);

	return true;
}

void LightShaderClass::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	// Set the vertex input layout.
	deviceContext->IASetInputLayout(m_layout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	// Set the sampler state in the pixel shader.
	deviceContext->PSSetSamplers(0, 1, &m_sampleState);

	// Render the triangle.
	deviceContext->DrawIndexed(indexCount, 0, 0);

	return;
}