////////////////////////////////////////////////////////////////////////////////
// Filename: particlesystemclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "particlesystemclass.h"

ParticleSystemClass::ParticleSystemClass()
{
	m_Texture = 0;
	m_particleList = 0;
	//m_vertices = 0;
	m_instances = 0;
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_instanceBuffer = 0;
}


ParticleSystemClass::ParticleSystemClass(const ParticleSystemClass& other)
{
}


ParticleSystemClass::~ParticleSystemClass()
{
}

bool ParticleSystemClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* textureFilename)
{
	bool result;


	// Load the texture that is used for the particles.
	result = LoadTexture(device, deviceContext, textureFilename);
	if (!result)
	{
		return false;
	}

	// Initialize the particle system.
	result = InitializeParticleSystem();
	if (!result)
	{
		return false;
	}

	// Create the buffers that will be used to render the particles with.
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	return true;
}

void ParticleSystemClass::Shutdown()
{
	// Release the buffers.
	ShutdownBuffers();

	// Release the particle system.
	ShutdownParticleSystem();

	// Release the texture used for the particles.
	ReleaseTexture();

	return;
}

bool ParticleSystemClass::Frame(float frameTime, ID3D11DeviceContext* deviceContext)
{
	bool result;

	// Release old particles.
	KillParticles();

	// Emit new particles.
	EmitParticles(frameTime);

	// Update the position of the particles.
	UpdateParticles(frameTime);

	// Update the dynamic vertex buffer with the new position of each particle.
	result = UpdateBuffers(deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}

void ParticleSystemClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}

ID3D11ShaderResourceView* ParticleSystemClass::GetTexture()
{
	return m_Texture->GetTexture();
}

int ParticleSystemClass::GetIndexCount()
{
	return m_indexCount;
}

int ParticleSystemClass::GetVertexCount()
{
	return m_vertexCount;
}

int ParticleSystemClass::GetCurrentParticleCount()
{
	return m_currentParticleCount;
}

bool ParticleSystemClass::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename)
{
	bool result;


	// Create the texture object.
	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, deviceContext, filename);
	if (!result)
	{
		return false;
	}

	return true;
}

void ParticleSystemClass::ReleaseTexture()
{
	// Release the texture object.
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}

bool ParticleSystemClass::InitializeParticleSystem()
{
	int i;

	// Set the random deviation of where the particles can be located when emitted.
	m_particleDeviationX = 0.5f;
	m_particleDeviationY = 0.1f;
	m_particleDeviationZ = 2.0f;


	// Set the speed and speed variation of particles.
	m_particleVelocity = 1.0f;
	m_particleVelocityVariation = 0.2f;

	// Set the physical size of the particles.
	m_particleSize = 0.2f;

	// Set the number of particles to emit per second.
	m_particlesPerSecond = 250.0f;

	// Set the maximum number of particles allowed in the particle system.
	m_maxParticles = 1000;

	// Create the particle list.
	m_particleList = new ParticleType[m_maxParticles];
	if (!m_particleList)
	{
		return false;
	}

	// Initialize the particle list.
	for (i = 0; i < m_maxParticles; i++)
	{
		m_particleList[i].active = false;
	}

	// Initialize the current particle count to zero since none are emitted yet.
	m_currentParticleCount = 0;

	// Clear the initial accumulated time for the particle per second emission rate.
	m_accumulatedTime = 0.0f;

	return true;
}

void ParticleSystemClass::ShutdownParticleSystem()
{
	// Release the particle list.
	if (m_particleList)
	{
		delete[] m_particleList;
		m_particleList = 0;
	}

	return;
}

bool ParticleSystemClass::InitializeBuffers(ID3D11Device* device)
{
	//unsigned long* indices;
	VertexType* vertices;
	int i;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc, instanceBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData, instanceData;
	HRESULT result;

	// Set the maximum number of vertices in the vertex array.
	m_vertexCount = 6;

	//// Set the maximum number of indices in the index array.
	//m_indexCount = m_vertexCount;

	// Create the vertex array for the particles that will be rendered.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the instance array for the particles that will be rendered.
	m_instances = new InstanceType[m_maxParticles];
	if (!m_instances)
	{
		return false;
	}
	
	//// Create the index array.
	//indices = new unsigned long[m_indexCount];
	//if (!indices)
	//{
	//	return false;
	//}

	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * m_vertexCount));

	// Initialize vertex array to zeros at first.
	memset(m_instances, 0, (sizeof(InstanceType) * m_maxParticles));

	//// Initialize the index array.
	//for (i = 0; i < m_indexCount; i++)
	//{
	//	indices[i] = i;
	//}

	// Load the vertex array with data.
	vertices[0].position = DXFLOAT3(-m_particleSize, -m_particleSize, 0.0f);  // Bottom left.
	vertices[0].texture = DXFLOAT2(0.0f, 1.0f);
	vertices[0].color = DXFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

	vertices[1].position = DXFLOAT3(-m_particleSize, m_particleSize, 0.0f);  // Top left.
	vertices[1].texture = DXFLOAT2(0.0f, 0.0f);
	vertices[1].color = DXFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

	vertices[2].position = DXFLOAT3(m_particleSize, -m_particleSize, 0.0f);  // Top right.
	vertices[2].texture = DXFLOAT2(1.0f, 1.0f);
	vertices[2].color = DXFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

	vertices[3].position = DXFLOAT3(m_particleSize, -m_particleSize, 0.0f);  // Bottom right.
	vertices[3].texture = DXFLOAT2(1.0f, 1.0f);
	vertices[3].color = DXFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

	vertices[4].position = DXFLOAT3(-m_particleSize, m_particleSize, 0.0f);  // Bottom left.
	vertices[4].texture = DXFLOAT2(0.0f, 0.0f);
	vertices[4].color = DXFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

	vertices[5].position = DXFLOAT3(m_particleSize, m_particleSize, 0.0f);  // Top right.
	vertices[5].texture = DXFLOAT2(1.0f, 0.0f);
	vertices[5].color = DXFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

	// Set up the description of the dynamic vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now finally create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the vertex array since it is no longer needed.
	delete[] vertices;
	vertices = 0;

	//// Set up the description of the static index buffer.
	//indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	//indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//indexBufferDesc.CPUAccessFlags = 0;
	//indexBufferDesc.MiscFlags = 0;
	//indexBufferDesc.StructureByteStride = 0;

	//// Give the subresource structure a pointer to the index data.
	//indexData.pSysMem = indices;
	//indexData.SysMemPitch = 0;
	//indexData.SysMemSlicePitch = 0;

	//// Create the index buffer.
	//result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	//if (FAILED(result))
	//{
	//	return false;
	//}

	//// Release the index array since it is no longer needed.
	//delete[] indices;
	//indices = 0;

	// Set up the description of the dynamic vertex buffer.
	instanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	instanceBufferDesc.ByteWidth = sizeof(InstanceType) * m_maxParticles;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	instanceData.pSysMem = m_instances;
	instanceData.SysMemPitch = 0;
	instanceData.SysMemSlicePitch = 0;

	// Now finally create the vertex buffer.
	result = device->CreateBuffer(&instanceBufferDesc, &instanceData, &m_instanceBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void ParticleSystemClass::ShutdownBuffers()
{
	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_instanceBuffer)
	{
		m_instanceBuffer->Release();
		m_instanceBuffer = 0;
	}

	return;
}

void ParticleSystemClass::EmitParticles(float frameTime)
{
	bool emitParticle, found;
	float positionX, positionY, positionZ, velocity, red, green, blue, angle, initialX, initialZ;
	int index, i, j;


	// Increment the frame time.
	m_accumulatedTime += frameTime;

	// Set emit particle to false for now.
	emitParticle = false;

	// Check if it is time to emit a new particle or not.
	if (m_accumulatedTime > (1000.0f / m_particlesPerSecond))
	{
		m_accumulatedTime = 0.0f;
		emitParticle = true;
	}

	// If there are particles to emit then emit one per frame.
	if ((emitParticle == true) && (m_currentParticleCount < (m_maxParticles - 1)))
	{
		m_currentParticleCount++;

		// Now generate the randomized particle properties.
		initialX = (((float)rand() - (float)rand()) / RAND_MAX) * m_particleDeviationX;
		positionY = (((float)rand() - (float)rand()) / RAND_MAX) * m_particleDeviationY;
		initialZ = (((float)rand() - (float)rand()) / RAND_MAX) * m_particleDeviationZ;

		velocity = m_particleVelocity + (((float)rand() - (float)rand()) / RAND_MAX) * m_particleVelocityVariation;

		red = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
		green = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
		blue = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;

		angle = (float)rand() / 360.0f;
		positionX = initialX + (cosf(angle) * 0.5f);
		positionZ = initialZ + (sinf(angle) * 0.5f) + 2.0f;

		// Now since the particles need to be rendered from back to front for blending we have to sort the particle array.
		// We will sort using Z depth so we need to find where in the list the particle should be inserted.
		index = 0;
		found = false;
		while (!found)
		{
			if ((m_particleList[index].active == false) || (m_particleList[index].positionZ < positionZ))
			{
				found = true;
			}
			else
			{
				index++;
			}
		}

		// Now that we know the location to insert into we need to copy the array over by one position from the index to make room for the new particle.
		i = m_currentParticleCount;
		j = i - 1;

		while (i != index)
		{
			m_particleList[i].positionX = m_particleList[j].positionX;
			m_particleList[i].positionY = m_particleList[j].positionY;
			m_particleList[i].positionZ = m_particleList[j].positionZ;
			m_particleList[i].initialX = m_particleList[j].initialX;
			m_particleList[i].initialZ = m_particleList[j].initialZ;
			m_particleList[i].red = m_particleList[j].red;
			m_particleList[i].green = m_particleList[j].green;
			m_particleList[i].blue = m_particleList[j].blue;
			m_particleList[i].velocity = m_particleList[j].velocity;
			m_particleList[i].angle = m_particleList[j].angle;
			m_particleList[i].active = m_particleList[j].active;
			i--;
			j--;
		}

		// Now insert it into the particle array in the correct depth order.
		m_particleList[index].positionX = positionX;
		m_particleList[index].positionY = positionY;
		m_particleList[index].positionZ = positionZ;
		m_particleList[index].initialX = initialX;
		m_particleList[index].initialZ = initialZ;
		m_particleList[index].red = red;
		m_particleList[index].green = green;
		m_particleList[index].blue = blue;
		m_particleList[index].velocity = velocity;
		m_particleList[index].angle = angle;
		m_particleList[index].active = true;
	}

	return;
}

void ParticleSystemClass::UpdateParticles(float frameTime)
{
	int i, j, k = 0;
	float rotation;

	// Each frame we update all the particles by making them move downwards using their position, velocity, and the frame time.
	for (i = 0; i < m_currentParticleCount; i++)
	{
		m_particleList[i].angle += (float)XM_PI * 0.001f;
		if (m_particleList[i].angle > 360.0f)
		{
			m_particleList[i].angle -= 360.0f;
		}
		m_particleList[i].positionX = m_particleList[i].initialX + (cosf(m_particleList[i].angle) * 0.5f);
		m_particleList[i].positionY -= m_particleList[i].velocity * frameTime * 0.001f;
		m_particleList[i].positionZ = m_particleList[i].initialZ + (sinf(m_particleList[i].angle) * 0.5f) + 2.0f;
		m_particleList[i].red = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
		m_particleList[i].green = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
		m_particleList[i].blue = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
	}

	// The Z positions will keep changing and overlapping continously, so we need to sort the array according to updated Z positions
	QuickSort(m_particleList, 0, m_currentParticleCount);

	return;
}

void ParticleSystemClass::KillParticles()
{
	int i, j;


	// Kill all the particles that have gone below a certain height range.
	for (i = 0; i < m_maxParticles; i++)
	{
		if ((m_particleList[i].active == true) && (m_particleList[i].positionY < -3.0f))
		{
			m_particleList[i].active = false;
			m_currentParticleCount--;

			// Now shift all the live particles back up the array to erase the destroyed particle and keep the array sorted correctly.
			for (j = i; j < m_maxParticles - 1; j++)
			{
				m_particleList[j].positionX = m_particleList[j + 1].positionX;
				m_particleList[j].positionY = m_particleList[j + 1].positionY;
				m_particleList[j].positionZ = m_particleList[j + 1].positionZ;
				m_particleList[j].initialX = m_particleList[j + 1].initialX;
				m_particleList[j].initialZ = m_particleList[j + 1].initialZ;
				m_particleList[j].red = m_particleList[j + 1].red;
				m_particleList[j].green = m_particleList[j + 1].green;
				m_particleList[j].blue = m_particleList[j + 1].blue;
				m_particleList[j].velocity = m_particleList[j + 1].velocity;
				m_particleList[j].angle = m_particleList[j + 1].angle;
				m_particleList[j].active = m_particleList[j + 1].active;
			}
		}
	}

	return;
}

bool ParticleSystemClass::UpdateBuffers(ID3D11DeviceContext* deviceContext)
{
	int index, i;
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	//VertexType* verticesPtr;
	InstanceType* instancesPtr;

	//// Initialize vertex array to zeros at first.
	//memset(m_vertices, 0, (sizeof(VertexType) * m_vertexCount));

	//// Now build the vertex array from the particle list array.  Each particle is a quad made out of two triangles.
	//index = 0;

	//for (i = 0; i < m_currentParticleCount; i++)
	//{
	//	m_vertices[index].position = DXFLOAT3(m_particleList[i].positionX - m_particleSize, m_particleList[i].positionY - m_particleSize, m_particleList[i].positionZ);
	//	m_vertices[index].texture = DXFLOAT2(0.0f, 1.0f);
	//	m_vertices[index].color = DXFLOAT4(m_particleList[i].red, m_particleList[i].green, m_particleList[i].blue, 1.0f);
	//	index++;

	//	// Top left.
	//	m_vertices[index].position = DXFLOAT3(m_particleList[i].positionX - m_particleSize, m_particleList[i].positionY + m_particleSize, m_particleList[i].positionZ);
	//	m_vertices[index].texture = DXFLOAT2(0.0f, 0.0f);
	//	m_vertices[index].color = DXFLOAT4(m_particleList[i].red, m_particleList[i].green, m_particleList[i].blue, 1.0f);
	//	index++;

	//	// Bottom right.
	//	m_vertices[index].position = DXFLOAT3(m_particleList[i].positionX + m_particleSize, m_particleList[i].positionY - m_particleSize, m_particleList[i].positionZ);
	//	m_vertices[index].texture = DXFLOAT2(1.0f, 1.0f);
	//	m_vertices[index].color = DXFLOAT4(m_particleList[i].red, m_particleList[i].green, m_particleList[i].blue, 1.0f);
	//	index++;

	//	// Bottom right.
	//	m_vertices[index].position = DXFLOAT3(m_particleList[i].positionX + m_particleSize, m_particleList[i].positionY - m_particleSize, m_particleList[i].positionZ);
	//	m_vertices[index].texture = DXFLOAT2(1.0f, 1.0f);
	//	m_vertices[index].color = DXFLOAT4(m_particleList[i].red, m_particleList[i].green, m_particleList[i].blue, 1.0f);
	//	index++;

	//	// Top left.
	//	m_vertices[index].position = DXFLOAT3(m_particleList[i].positionX - m_particleSize, m_particleList[i].positionY + m_particleSize, m_particleList[i].positionZ);
	//	m_vertices[index].texture = DXFLOAT2(0.0f, 0.0f);
	//	m_vertices[index].color = DXFLOAT4(m_particleList[i].red, m_particleList[i].green, m_particleList[i].blue, 1.0f);
	//	index++;

	//	// Top right.
	//	m_vertices[index].position = DXFLOAT3(m_particleList[i].positionX + m_particleSize, m_particleList[i].positionY + m_particleSize, m_particleList[i].positionZ);
	//	m_vertices[index].texture = DXFLOAT2(1.0f, 0.0f);
	//	m_vertices[index].color = DXFLOAT4(m_particleList[i].red, m_particleList[i].green, m_particleList[i].blue, 1.0f);
	//	index++;
	//}

	//// Lock the vertex buffer.
	//result = deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	//if (FAILED(result))
	//{
	//	return false;
	//}

	//// Get a pointer to the data in the vertex buffer.
	//verticesPtr = (VertexType*)mappedResource.pData;

	//// Copy the data into the vertex buffer.
	//memcpy(verticesPtr, (void*)m_vertices, (sizeof(VertexType) * m_vertexCount));

	//// Unlock the vertex buffer.
	//deviceContext->Unmap(m_vertexBuffer, 0);

	// Initialize vertex array to zeros at first.
	memset(m_instances, 0, (sizeof(InstanceType) * m_maxParticles));

	for (i = 0; i < m_currentParticleCount; i++)
	{
		m_instances[i].position = DXFLOAT3(m_particleList[i].positionX, m_particleList[i].positionY, m_particleList[i].positionZ);
		m_instances[i].color = DXFLOAT4(m_particleList[i].red, m_particleList[i].green, m_particleList[i].blue, 1.0f);
	}

	// Lock the instance buffer.
	result = deviceContext->Map(m_instanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the vertex buffer.
	instancesPtr = (InstanceType*)mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy(instancesPtr, (void*)m_instances, (sizeof(InstanceType) * m_maxParticles));

	// Unlock the vertex buffer.
	deviceContext->Unmap(m_instanceBuffer, 0);

	return true;
}

void ParticleSystemClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int strides[2];
	unsigned int offsets[2];
	ID3D11Buffer* bufferPointers[2];

	// Set the buffer strides.
	strides[0] = sizeof(VertexType);
	strides[1] = sizeof(InstanceType);

	// Set the buffer offsets.
	offsets[0] = 0;
	offsets[1] = 0;

	// Set the array of pointers to the vertex and instance buffers.
	bufferPointers[0] = m_vertexBuffer;
	bufferPointers[1] = m_instanceBuffer;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

void ParticleSystemClass::QuickSort(ParticleType particleList[], int low, int high)
{
	if (low < high) {

		// find the pivot element such that
		// elements smaller than pivot are on left of pivot
		// elements greater than pivot are on righ of pivot
		int pi = QuickSortPartition(particleList, low, high);

		// recursive call on the left of pivot
		QuickSort(particleList, low, pi - 1);

		// recursive call on the right of pivot
		QuickSort(particleList, pi + 1, high);
	}
}

// function to rearrange array (find the partition point)
int ParticleSystemClass::QuickSortPartition(ParticleType particleList[], int low, int high) {

	// select the rightmost element as pivot
	float pivot = particleList[high].positionZ;

	// pointer for greater element
	int i = (low - 1);

	// traverse each element of the array
	// compare them with the pivot
	for (int j = low; j < high; j++) {
		if (particleList[j].positionZ > pivot) {

			// if element smaller than pivot is found
			// swap it with the greater element pointed by i
			i++;

			// swap element at i with element at j
			swap(particleList[i], particleList[j]);
		}
	}

	// swap pivot with the greater element at i
	swap(particleList[i + 1], particleList[high]);

	// return the partition point
	return (i + 1);
}