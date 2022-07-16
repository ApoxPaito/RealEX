////////////////////////////////////////////////////////////////////////////////
// Filename: treeclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "treeclass.h"

TreeClass::TreeClass()
{
	m_Trunk = 0;
	m_Leaves = 0;
}


TreeClass::TreeClass(const TreeClass& other)
{
}


TreeClass::~TreeClass()
{
}

bool TreeClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* trunkModel, char* trunkTexture, char* leafModel, char* leafTexture, float scale)
{
	bool result;

	// Create the trunk model object
	m_Trunk = new ModelClass;
	if (!m_Trunk)
	{
		return false;
	}

	// Initialize the trunk model
	result = m_Trunk->Initialize(device, deviceContext, trunkModel, trunkTexture, scale);
	if (!result)
	{
		return false;
	}

	// Create the leaves model object
	m_Leaves = new ModelClass;
	if (!m_Leaves)
	{
		return false;
	}

	// Initialize the leaves model
	result = m_Leaves->Initialize(device, deviceContext, leafModel, leafTexture, scale);
	if (!result)
	{
		return false;
	}

	return true;
}

void TreeClass::Shutdown()
{
	// Shutdown the model instances.
	if (m_Trunk)
	{
		m_Trunk->Shutdown();
		delete m_Trunk;
		m_Trunk = 0;
	}

	if (m_Leaves)
	{
		m_Leaves->Shutdown();
		delete m_Leaves;
		m_Leaves = 0;
	}

	return;
}

void TreeClass::RenderTrunk(ID3D11DeviceContext* deviceContext)
{
	// Pass the device context along to the trunk model to render it.
	m_Trunk->Render(deviceContext);

	return;
}

void TreeClass::RenderLeaves(ID3D11DeviceContext* deviceContext)
{
	// Pass the device context along to the trunk model to render it.
	m_Leaves->Render(deviceContext);

	return;
}

void TreeClass::SetPosition(float posX, float posY, float posZ)
{
	this->posX = posX;
	this->posY = posY;
	this->posZ = posZ;
	return;
}

int TreeClass::GetTrunkVertexCount()
{
	return m_Trunk->GetVertexCount();
}

int TreeClass::GetTrunkIndexCount()
{
	return m_Trunk->GetIndexCount();
}

int TreeClass::GetLeafVertexCount()
{
	return m_Leaves->GetVertexCount();
}

int TreeClass::GetLeafIndexCount()
{
	return m_Leaves->GetIndexCount();
}

ID3D11ShaderResourceView* TreeClass::GetTrunkTexture()
{
	return m_Trunk->GetTexture();
}

ID3D11ShaderResourceView* TreeClass::GetLeafTexture()
{
	return m_Leaves->GetTexture();
}

void TreeClass::GetPosition(float& posX, float& posY, float& posZ)
{
	posX = this->posX;
	posY = this->posY;
	posZ = this->posZ;
	return;
}