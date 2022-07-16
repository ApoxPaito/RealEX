////////////////////////////////////////////////////////////////////////////////
// Filename: shadermanagerclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ShaderManagerClass.h"

ShaderManagerClass::ShaderManagerClass()
{
	m_device = 0;
	m_TextureShader = 0;
	m_LightShaderSpecular = 0;
	m_LightShaderDiffuse = 0;
	m_LightShaderAmbient = 0;
	m_LightShaderMultiple = 0;
	m_LightShaderDeferred = 0;
	m_BumpMapShader = 0;
	m_MultiTextureShader = 0;
	m_LightMapShader = 0;
	m_AlphaMapShader = 0;
	m_SpecMapShader = 0;
	m_FogShader = 0;
	m_ClipPlaneShader = 0;
	m_TranslateShader = 0;
	m_TransparentShader = 0;
	m_ReflectionShader = 0;
	m_FadeShader = 0;
	m_WaterShader = 0;
	m_RefractionShader = 0;
	m_GlassShader = 0;
	m_FireShader = 0;
	m_HorizontalBlurShader = 0;
	m_VerticalBlurShader = 0;
	m_ColorShader = 0;
	m_ColorTessellationShader = 0;
	m_ParticleShader = 0;
	m_DepthShader = 0;
	m_ShadowShader = 0;
	m_SoftShadowShader = 0;
	m_ProjectionShader = 0;
	m_GlowMapShader = 0;
	m_GlowShader = 0;
	m_TransparentDepthShader = 0;
	m_DeferredShader = 0;
	m_TerrainShader = 0;
	m_SkyDomeShader = 0;
	m_SkyPlaneShader = 0;
}


ShaderManagerClass::ShaderManagerClass(const ShaderManagerClass& other)
{
}


ShaderManagerClass::~ShaderManagerClass()
{
}

bool ShaderManagerClass::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;

	// Initialize device and window variables
	m_device = device;
	m_hwnd = hwnd;

	return true;
}

void ShaderManagerClass::Shutdown()
{
	// Release the sky plane shader object.
	if (m_SkyPlaneShader)
	{
		m_SkyPlaneShader->Shutdown();
		delete m_SkyPlaneShader;
		m_SkyPlaneShader = 0;
	}

	// Release the sky dome shader object.
	if (m_SkyDomeShader)
	{
		m_SkyDomeShader->Shutdown();
		delete m_SkyDomeShader;
		m_SkyDomeShader = 0;
	}

	// Release the terrain shader object.
	if (m_TerrainShader)
	{
		m_TerrainShader->Shutdown();
		delete m_TerrainShader;
		m_TerrainShader = 0;
	}

	// Release the deferred shader object.
	if (m_DeferredShader)
	{
		m_DeferredShader->Shutdown();
		delete m_DeferredShader;
		m_DeferredShader = 0;
	}

	// Release the transparent depth shader object.
	if (m_TransparentDepthShader)
	{
		m_TransparentDepthShader->Shutdown();
		delete m_TransparentDepthShader;
		m_TransparentDepthShader = 0;
	}

	// Release the glow shader object.
	if (m_GlowShader)
	{
		m_GlowShader->Shutdown();
		delete m_GlowShader;
		m_GlowShader = 0;
	}

	// Release the glow map shader object.
	if (m_GlowMapShader)
	{
		m_GlowMapShader->Shutdown();
		delete m_GlowMapShader;
		m_GlowMapShader = 0;
	}

	// Release the light map shader object.
	if (m_LightMapShader)
	{
		m_LightMapShader->Shutdown();
		delete m_LightMapShader;
		m_LightMapShader = 0;
	}

	// Release the alpha map shader object.
	if (m_AlphaMapShader)
	{
		m_AlphaMapShader->Shutdown();
		delete m_AlphaMapShader;
		m_AlphaMapShader = 0;
	}

	// Release the spec map shader object.
	if (m_SpecMapShader)
	{
		m_SpecMapShader->Shutdown();
		delete m_SpecMapShader;
		m_SpecMapShader = 0;
	}

	// Release the fog shader object.
	if (m_FogShader)
	{
		m_FogShader->Shutdown();
		delete m_FogShader;
		m_FogShader = 0;
	}

	// Release the clip plane shader object.
	if (m_ClipPlaneShader)
	{
		m_ClipPlaneShader->Shutdown();
		delete m_ClipPlaneShader;
		m_ClipPlaneShader = 0;
	}

	// Release the translate shader object.
	if (m_TranslateShader)
	{
		m_TranslateShader->Shutdown();
		delete m_TranslateShader;
		m_TranslateShader = 0;
	}

	// Release the transparent shader object.
	if (m_TransparentShader)
	{
		m_TransparentShader->Shutdown();
		delete m_TransparentShader;
		m_TransparentShader = 0;
	}

	// Release the reflection shader object.
	if (m_ReflectionShader)
	{
		m_ReflectionShader->Shutdown();
		delete m_ReflectionShader;
		m_ReflectionShader = 0;
	}

	// Release the fade shader object.
	if (m_FadeShader)
	{
		m_FadeShader->Shutdown();
		delete m_FadeShader;
		m_FadeShader = 0;
	}

	// Release the water shader object.
	if (m_WaterShader)
	{
		m_WaterShader->Shutdown();
		delete m_WaterShader;
		m_WaterShader = 0;
	}

	// Release the refraction shader object.
	if (m_RefractionShader)
	{
		m_RefractionShader->Shutdown();
		delete m_RefractionShader;
		m_RefractionShader = 0;
	}

	// Release the glass shader object.
	if (m_GlassShader)
	{
		m_GlassShader->Shutdown();
		delete m_GlassShader;
		m_GlassShader = 0;
	}

	// Release the fire shader object.
	if (m_FireShader)
	{
		m_FireShader->Shutdown();
		delete m_FireShader;
		m_FireShader = 0;
	}

	// Release the vertical blur shader object.
	if (m_VerticalBlurShader)
	{
		m_VerticalBlurShader->Shutdown();
		delete m_VerticalBlurShader;
		m_VerticalBlurShader = 0;
	}

	// Release the horizontal blur shader object.
	if (m_HorizontalBlurShader)
	{
		m_HorizontalBlurShader->Shutdown();
		delete m_HorizontalBlurShader;
		m_HorizontalBlurShader = 0;
	}

	// Release the color shader object.
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}
	
	// Release the particle shader object.
	if (m_ParticleShader)
	{
		m_ParticleShader->Shutdown();
		delete m_ParticleShader;
		m_ParticleShader = 0;
	}

	// Release the depth shader object.
	if (m_DepthShader)
	{
		m_DepthShader->Shutdown();
		delete m_DepthShader;
		m_DepthShader = 0;
	}

	// Release the shadow shader object.
	if (m_ShadowShader)
	{
		m_ShadowShader->Shutdown();
		delete m_ShadowShader;
		m_ShadowShader = 0;
	}

	// Release the soft shadow shader object.
	if (m_SoftShadowShader)
	{
		m_SoftShadowShader->Shutdown();
		delete m_SoftShadowShader;
		m_SoftShadowShader = 0;
	}

	// Release the projection shader object.
	if (m_ProjectionShader)
	{
		m_ProjectionShader->Shutdown();
		delete m_ProjectionShader;
		m_ProjectionShader = 0;
	}

	// Release the multi texture shader object.
	if (m_MultiTextureShader)
	{
		m_MultiTextureShader->Shutdown();
		delete m_MultiTextureShader;
		m_MultiTextureShader = 0;
	}

	// Release the bump map shader object.
	if (m_BumpMapShader)
	{
		m_BumpMapShader->Shutdown();
		delete m_BumpMapShader;
		m_BumpMapShader = 0;
	}

	// Release the diffuse light shader object.
	if (m_LightShaderDiffuse)
	{
		m_LightShaderDiffuse->Shutdown();
		delete m_LightShaderDiffuse;
		m_LightShaderDiffuse = 0;
	}

	// Release the specular light shader object.
	if (m_LightShaderSpecular)
	{
		m_LightShaderSpecular->Shutdown();
		delete m_LightShaderSpecular;
		m_LightShaderSpecular = 0;
	}

	// Release the ambient light shader object.
	if (m_LightShaderAmbient)
	{
		m_LightShaderAmbient->Shutdown();
		delete m_LightShaderAmbient;
		m_LightShaderAmbient = 0;
	}

	// Release the multiple light shader object.
	if (m_LightShaderMultiple)
	{
		m_LightShaderMultiple->Shutdown();
		delete m_LightShaderMultiple;
		m_LightShaderMultiple = 0;
	}

	// Release the deferred light shader object.
	if (m_LightShaderDeferred)
	{
		m_LightShaderDeferred->Shutdown();
		delete m_LightShaderDeferred;
		m_LightShaderDeferred = 0;
	}

	// Release the instanced texture shader object.
	if (m_TextureInstancedShader)
	{
		m_TextureInstancedShader->Shutdown();
		delete m_TextureInstancedShader;
		m_TextureInstancedShader = 0;
	}

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	return;
}

bool ShaderManagerClass::RenderTextureShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture)
{
	bool result;

	// Initialize texture shader if it isn't yet
	if (!m_TextureShader)
	{
		m_TextureShader = new TextureShaderClass;
		if (!m_TextureShader)
		{
			return false;
		}

		// Initialize the texture shader object.
		result = m_TextureShader->Initialize(m_device, m_hwnd, false);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the texture shader.
	result = m_TextureShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderTextureShader(ID3D11DeviceContext* deviceContext, int vertexCount, int instanceCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture)
{
	bool result;

	// Initialize instanced texture shader if it isn't yet
	if (!m_TextureInstancedShader)
	{
		m_TextureInstancedShader = new TextureShaderClass;
		if (!m_TextureInstancedShader)
		{
			return false;
		}

		// Initialize the instanced texture shader object.
		result = m_TextureInstancedShader->Initialize(m_device, m_hwnd, true);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the instanced texture shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the instanced texture shader.
	result = m_TextureInstancedShader->Render(deviceContext, vertexCount, instanceCount, worldMatrix, viewMatrix, projectionMatrix, texture);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderLightShaderDiffuse(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, DXFLOAT3 lightDirection, DXFLOAT4 diffuse)
{
	bool result;

	// Initialize light shader if it isn't yet
	if (!m_LightShaderDiffuse)
	{
		m_LightShaderDiffuse = new LightShaderClass;
		if (!m_LightShaderDiffuse)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_LightShaderDiffuse->Initialize(m_device, m_hwnd, LightShaderClass::Diffuse);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the diffuse light shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the light shader.
	result = m_LightShaderDiffuse->RenderDiffuse(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, diffuse);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderLightShaderAmbient(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, DXFLOAT3 lightDirection, DXFLOAT4 ambient, DXFLOAT4 diffuse)
{
	bool result;

	// Initialize light shader if it isn't yet
	if (!m_LightShaderAmbient)
	{
		m_LightShaderAmbient = new LightShaderClass;
		if (!m_LightShaderAmbient)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_LightShaderAmbient->Initialize(m_device, m_hwnd, LightShaderClass::Ambient);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the ambient light shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the light shader.
	result = m_LightShaderAmbient->RenderAmbient(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, ambient, diffuse);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderLightShaderSpecular(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, DXFLOAT3 lightDirection, DXFLOAT4 ambient, DXFLOAT4 diffuse,
	DXFLOAT3 cameraPosition, DXFLOAT4 specular, float specularPower)
{
	bool result;

	// Initialize light shader if it isn't yet
	if (!m_LightShaderSpecular)
	{
		m_LightShaderSpecular = new LightShaderClass;
		if (!m_LightShaderSpecular)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_LightShaderSpecular->Initialize(m_device, m_hwnd, LightShaderClass::Specular);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the specular light shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the light shader.
	result = m_LightShaderSpecular->RenderSpecular(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, ambient, diffuse, cameraPosition,
		specular, specularPower);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderLightShaderMultiple(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, DXFLOAT4 diffuseColor[], DXFLOAT4 lightPosition[])
{
	bool result;

	// Initialize light shader if it isn't yet
	if (!m_LightShaderMultiple)
	{
		m_LightShaderMultiple = new LightShaderClass;
		if (!m_LightShaderMultiple)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_LightShaderMultiple->Initialize(m_device, m_hwnd, LightShaderClass::Multiple);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the multiple light shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the light shader.
	result = m_LightShaderMultiple->RenderMultiple(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, diffuseColor, lightPosition);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderLightShaderDeferred(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture, DXFLOAT3 direction)
{
	bool result;

	// Initialize light shader if it isn't yet
	if (!m_LightShaderDeferred)
	{
		m_LightShaderDeferred = new LightShaderClass;
		if (!m_LightShaderDeferred)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_LightShaderDeferred->Initialize(m_device, m_hwnd, LightShaderClass::Deferred);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the deferred light shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the light shader.
	result = m_LightShaderDeferred->RenderDeferred(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, colorTexture, normalTexture, direction);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderBumpMapShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView** textureArray, DXFLOAT3 lightDirection, DXFLOAT4 diffuse)
{
	bool result;

	// Initialize bump map shader if it isn't yet
	if (!m_BumpMapShader)
	{
		m_BumpMapShader = new BumpMapShaderClass;
		if (!m_BumpMapShader)
		{
			return false;
		}

		// Initialize the bump map shader object.
		result = m_BumpMapShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the bump shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the bump map shader.
	result = m_BumpMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, textureArray, lightDirection, diffuse);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderMultiTextureShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView** textureArray)
{
	bool result;

	// Initialize multi texture shader if it isn't yet
	if (!m_MultiTextureShader)
	{
		m_MultiTextureShader = new MultiTextureShaderClass;
		if (!m_MultiTextureShader)
		{
			return false;
		}

		// Initialize the multi texture shader object.
		result = m_MultiTextureShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the multi texture shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the multi texture shader.
	result = m_MultiTextureShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, textureArray);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderLightMapShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView** textureArray)
{
	bool result;

	// Initialize light map shader if it isn't yet
	if (!m_LightMapShader)
	{
		m_LightMapShader = new LightMapShaderClass;
		if (!m_LightMapShader)
		{
			return false;
		}

		// Initialize the light map shader object.
		result = m_LightMapShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the light map shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the light map shader.
	result = m_LightMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, textureArray);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderAlphaMapShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView** textureArray)
{
	bool result;

	// Initialize alpha map shader if it isn't yet
	if (!m_AlphaMapShader)
	{
		m_AlphaMapShader = new AlphaMapShaderClass;
		if (!m_AlphaMapShader)
		{
			return false;
		}

		// Initialize the alpha map shader object.
		result = m_AlphaMapShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the alpha map shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the alpha map shader.
	result = m_AlphaMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, textureArray);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderSpecMapShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView** textureArray, DXFLOAT3 lightDirection, DXFLOAT4 diffuse,
	DXFLOAT3 cameraPosition, DXFLOAT4 specular, float specularPower)
{
	bool result;

	// Initialize spec map shader if it isn't yet
	if (!m_SpecMapShader)
	{
		m_SpecMapShader = new SpecMapShaderClass;
		if (!m_SpecMapShader)
		{
			return false;
		}

		// Initialize the spec map shader object.
		result = m_SpecMapShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the spec map shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the spec map shader.
	result = m_SpecMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, textureArray, lightDirection, diffuse, cameraPosition,
		specular, specularPower);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderFogShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, float fogStart, float fogEnd)
{
	bool result;

	// Initialize fog shader if it isn't yet
	if (!m_FogShader)
	{
		m_FogShader = new FogShaderClass;
		if (!m_FogShader)
		{
			return false;
		}

		// Initialize the fog shader object.
		result = m_FogShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the fog shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the fog shader.
	result = m_FogShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, fogStart, fogEnd);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderClipPlaneShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, DXFLOAT4 clipPlane)
{
	bool result;

	// Initialize clip plane shader if it isn't yet
	if (!m_ClipPlaneShader)
	{
		m_ClipPlaneShader = new ClipPlaneShaderClass;
		if (!m_ClipPlaneShader)
		{
			return false;
		}

		// Initialize the clip plane shader object.
		result = m_ClipPlaneShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the clip plane shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the clip plane shader.
	result = m_ClipPlaneShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, clipPlane);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderTranslateShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, float translation)
{
	bool result;

	// Initialize translate shader if it isn't yet
	if (!m_TranslateShader)
	{
		m_TranslateShader = new TranslateShaderClass;
		if (!m_TranslateShader)
		{
			return false;
		}

		// Initialize the translate shader object.
		result = m_TranslateShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the translate shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the translate shader.
	result = m_TranslateShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, translation);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderTransparentShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, float blend)
{
	bool result;

	// Initialize transparent shader if it isn't yet
	if (!m_TransparentShader)
	{
		m_TransparentShader = new TransparentShaderClass;
		if (!m_TransparentShader)
		{
			return false;
		}

		// Initialize the transparent shader object.
		result = m_TransparentShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the transparent shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the transparent shader.
	result = m_TransparentShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, blend);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderReflectionShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix,
	DXMATRIX projectionMatrix, ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture,
	DXFLOAT4 lightDiffuseColor, DXFLOAT3 lightDirection, float colorTextureBrightness, DXFLOAT4 clipPlane)
{
	bool result;

	// Initialize reflection shader if it isn't yet
	if (!m_ReflectionShader)
	{
		m_ReflectionShader = new ReflectionShaderClass;
		if (!m_ReflectionShader)
		{
			return false;
		}

		// Initialize the reflection shader object.
		result = m_ReflectionShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the reflection shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the reflection shader.
	result = m_ReflectionShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, colorTexture, normalTexture, lightDiffuseColor, lightDirection,
		colorTextureBrightness, clipPlane);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderFadeShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, float fadeAmount)
{
	bool result;

	// Initialize fade shader if it isn't yet
	if (!m_FadeShader)
	{
		m_FadeShader = new FadeShaderClass;
		if (!m_FadeShader)
		{
			return false;
		}

		// Initialize the fade shader object.
		result = m_FadeShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the fade shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the fade shader.
	result = m_FadeShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, fadeAmount);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderWaterShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix,
	DXMATRIX projectionMatrix, DXMATRIX reflectionMatrix, ID3D11ShaderResourceView* refractionTexture,
	ID3D11ShaderResourceView* reflectionTexture, ID3D11ShaderResourceView* normalTexture, DXFLOAT3 cameraPosition,
	DXFLOAT2 normalMapTiling, float waterTranslation, float reflectRefractScale, DXFLOAT4 refractionTint,
	DXFLOAT3 lightDirection, float specularShininess)
{
	bool result;

	// Initialize water shader if it isn't yet
	if (!m_WaterShader)
	{
		m_WaterShader = new WaterShaderClass;
		if (!m_WaterShader)
		{
			return false;
		}

		// Initialize the water shader object.
		result = m_WaterShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the water shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the water shader.
	result = m_WaterShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, reflectionMatrix, reflectionTexture, refractionTexture,
		normalTexture, cameraPosition, normalMapTiling, waterTranslation, reflectRefractScale, refractionTint, lightDirection, specularShininess);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderRefractionShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, DXFLOAT3 lightDirection, DXFLOAT4 ambient, DXFLOAT4 diffuse, DXFLOAT4 clipPlane)
{
	bool result;

	// Initialize refraction shader if it isn't yet
	if (!m_RefractionShader)
	{
		m_RefractionShader = new RefractionShaderClass;
		if (!m_RefractionShader)
		{
			return false;
		}

		// Initialize the refraction shader object.
		result = m_RefractionShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the refraction shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the refraction shader.
	result = m_RefractionShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, ambient, diffuse, clipPlane);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderGlassShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture, ID3D11ShaderResourceView* refractionTexture, float refractionScale)
{
	bool result;

	// Initialize glass shader if it isn't yet
	if (!m_GlassShader)
	{
		m_GlassShader = new GlassShaderClass;
		if (!m_GlassShader)
		{
			return false;
		}

		// Initialize the glass shader object.
		result = m_GlassShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the glass shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the glass shader.
	result = m_GlassShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, colorTexture, normalTexture, refractionTexture, refractionScale);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderFireShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* fireTexture, ID3D11ShaderResourceView* noiseTexture, ID3D11ShaderResourceView* alphaTexture, float frameTime, DXFLOAT3 scrollSpeeds,
	DXFLOAT3 scales, DXFLOAT2 distortion1, DXFLOAT2 distortion2, DXFLOAT2 distortion3, float distortionScale, float distortionBias)
{
	bool result;

	// Initialize fire shader if it isn't yet
	if (!m_FireShader)
	{
		m_FireShader = new FireShaderClass;
		if (!m_FireShader)
		{
			return false;
		}

		// Initialize the fire shader object.
		result = m_FireShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the fire shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the fire shader.
	result = m_FireShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, fireTexture, noiseTexture, alphaTexture, frameTime, scrollSpeeds,
		scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderHorizontalBlurShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, float screenWidth)
{
	bool result;

	// Initialize horizontal blur shader if it isn't yet
	if (!m_HorizontalBlurShader)
	{
		m_HorizontalBlurShader = new BlurShaderClass;
		if (!m_HorizontalBlurShader)
		{
			return false;
		}

		// Initialize the horizontal blur shader object.
		result = m_HorizontalBlurShader->InitializeHorizontal(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the horizontal blur shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the horizontal blur shader.
	result = m_HorizontalBlurShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, screenWidth);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderVerticalBlurShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, float screenHeight)
{
	bool result;

	// Initialize vertical blur shader if it isn't yet
	if (!m_VerticalBlurShader)
	{
		m_VerticalBlurShader = new BlurShaderClass;
		if (!m_VerticalBlurShader)
		{
			return false;
		}

		// Initialize the vertical blur shader object.
		result = m_VerticalBlurShader->InitializeHorizontal(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the vertical blur shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the vertical blur shader.
	result = m_VerticalBlurShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, screenHeight);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderColorShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix)
{
	bool result;

	// Initialize color shader if it isn't yet
	if (!m_ColorShader)
	{
		m_ColorShader = new ColorShaderClass;
		if (!m_ColorShader)
		{
			return false;
		}

		// Initialize the color shader object.
		result = m_ColorShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the color shader.
	result = m_ColorShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderColorShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	float tessellationAmount)
{
	bool result;

	// Initialize color tessellation shader if it isn't yet
	if (!m_ColorTessellationShader)
	{
		m_ColorTessellationShader = new ColorShaderClass;
		if (!m_ColorTessellationShader)
		{
			return false;
		}

		// Initialize the color tessellation shader object.
		result = m_ColorTessellationShader->InitializeWithTessellation(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the color tessellation shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the color tessellation shader.
	result = m_ColorTessellationShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, tessellationAmount);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderParticleShader(ID3D11DeviceContext* deviceContext, int vertexCount, int instanceCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture)
{
	bool result;

	// Initialize particle shader if it isn't yet
	if (!m_ParticleShader)
	{
		m_ParticleShader = new ParticleShaderClass;
		if (!m_ParticleShader)
		{
			return false;
		}

		// Initialize the particle shader object.
		result = m_ParticleShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the particle shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the particle shader.
	result = m_ParticleShader->Render(deviceContext, vertexCount, instanceCount, worldMatrix, viewMatrix, projectionMatrix, texture);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderDepthShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix)
{
	bool result;

	// Initialize depth shader if it isn't yet
	if (!m_DepthShader)
	{
		m_DepthShader = new DepthShaderClass;
		if (!m_DepthShader)
		{
			return false;
		}

		// Initialize the depth shader object.
		result = m_DepthShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the depth shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the depth shader.
	result = m_DepthShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderShadowShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix, DXMATRIX lightViewMatrix,
	DXMATRIX lightProjectionMatrix, ID3D11ShaderResourceView* depthMapTexture, DXFLOAT3 lightPosition)
{
	bool result;

	// Initialize shadow shader if it isn't yet
	if (!m_ShadowShader)
	{
		m_ShadowShader = new ShadowShaderClass;
		if (!m_ShadowShader)
		{
			return false;
		}

		// Initialize the shadow shader object.
		result = m_ShadowShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the shadow shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the shadow shader.
	result = m_ShadowShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix, lightProjectionMatrix, 
		depthMapTexture, lightPosition);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderShadowShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix,
	DXMATRIX projectionMatrix, DXMATRIX lightViewMatrix, DXMATRIX lightProjectionMatrix,
	ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* depthMapTexture, DXFLOAT3 lightDirection,
	DXFLOAT4 ambientColor, DXFLOAT4 diffuseColor)
{
	bool result;

	// Initialize shadow shader if it isn't yet
	if (!m_ShadowShader)
	{
		m_ShadowShader = new ShadowShaderClass;
		if (!m_ShadowShader)
		{
			return false;
		}

		// Initialize the shadow shader object.
		result = m_ShadowShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the shadow shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the shadow shader.
	result = m_ShadowShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix, lightProjectionMatrix,
		texture, depthMapTexture, lightDirection, ambientColor, diffuseColor);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderSoftShadowShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* shadowTexture, DXFLOAT3 lightPosition, DXFLOAT4 ambient, DXFLOAT4 diffuse)
{
	bool result;

	// Initialize soft shadow shader if it isn't yet
	if (!m_SoftShadowShader)
	{
		m_SoftShadowShader = new SoftShadowShaderClass;
		if (!m_SoftShadowShader)
		{
			return false;
		}

		// Initialize the soft shadow shader object.
		result = m_SoftShadowShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the soft shadow shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the soft shadow shader.
	result = m_SoftShadowShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, shadowTexture, lightPosition, ambient, diffuse);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderProjectionShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, DXFLOAT4 ambient, DXFLOAT4 diffuse, DXFLOAT3 lightDirection, DXMATRIX viewMatrix2, DXMATRIX projectionMatrix2, 
	ID3D11ShaderResourceView* projectionTexture)
{
	bool result;

	// Initialize projection shader if it isn't yet
	if (!m_ProjectionShader)
	{
		m_ProjectionShader = new ProjectionShaderClass;
		if (!m_ProjectionShader)
		{
			return false;
		}

		// Initialize the projection shader object.
		result = m_ProjectionShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the projection shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the projection shader.
	result = m_ProjectionShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, ambient, diffuse, lightDirection, viewMatrix2, projectionMatrix2,
		projectionTexture);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderGlowMapShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* glowMapTexture)
{
	bool result;

	// Initialize glow map shader if it isn't yet
	if (!m_GlowMapShader)
	{
		m_GlowMapShader = new GlowMapShaderClass;
		if (!m_GlowMapShader)
		{
			return false;
		}

		// Initialize the glow map shader object.
		result = m_GlowMapShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the glow map shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the glow map shader.
	result = m_GlowMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, glowMapTexture);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderGlowShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* glowTexture, float strength)
{
	bool result;

	// Initialize glow shader if it isn't yet
	if (!m_GlowShader)
	{
		m_GlowShader = new GlowShaderClass;
		if (!m_GlowShader)
		{
			return false;
		}

		// Initialize the glow shader object.
		result = m_GlowShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the glow shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the glow shader.
	result = m_GlowShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, glowTexture, strength);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderTransparentDepthShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture)
{
	bool result;

	// Initialize transparent depth shader if it isn't yet
	if (!m_TransparentDepthShader)
	{
		m_TransparentDepthShader = new TransparentDepthShaderClass;
		if (!m_TransparentDepthShader)
		{
			return false;
		}

		// Initialize the transparent depth shader object.
		result = m_TransparentDepthShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the transparent depth shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the transparent depth shader.
	result = m_TransparentDepthShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderDeferredShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture)
{
	bool result;

	// Initialize deferred shader if it isn't yet
	if (!m_DeferredShader)
	{
		m_DeferredShader = new DeferredShaderClass;
		if (!m_DeferredShader)
		{
			return false;
		}

		// Initialize the deferred shader object.
		result = m_DeferredShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the deferred shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the deferred shader.
	result = m_DeferredShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderSkyDomeShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	DXFLOAT4 apexColor, DXFLOAT4 centerColor)
{
	bool result;

	// Initialize sky dome shader if it isn't yet
	if (!m_SkyDomeShader)
	{
		m_SkyDomeShader = new SkyDomeShaderClass;
		if (!m_SkyDomeShader)
		{
			return false;
		}

		// Initialize the sky dome shader object.
		result = m_SkyDomeShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the sky dome shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the sky dome shader.
	result = m_SkyDomeShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, apexColor, centerColor);
	if (!result)
	{
		return false;
	}
}

bool ShaderManagerClass::RenderSkyPlaneShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	ID3D11ShaderResourceView* firstTexture, ID3D11ShaderResourceView* secondTexture, ID3D11ShaderResourceView* perturbTexture,
	float firstTranslation, float secondTranslation, float scale, float brightness)
{
	bool result;

	// Initialize sky plane shader if it isn't yet
	if (!m_SkyPlaneShader)
	{
		m_SkyPlaneShader = new SkyPlaneShaderClass;
		if (!m_SkyPlaneShader)
		{
			return false;
		}

		// Initialize the sky plane shader object.
		result = m_SkyPlaneShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the sky plane shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the sky plane shader.
	result = m_SkyPlaneShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, firstTexture, secondTexture,
		perturbTexture, firstTranslation, secondTranslation, scale, brightness);
	if (!result)
	{
		return false;
	}
}

bool ShaderManagerClass::RenderTerrainShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix,
	DXMATRIX projectionMatrix, DXFLOAT4 diffuseColor, DXFLOAT3 lightDirection, ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalMapTexture)
{
	bool result;

	// Initialize terrain shader if it isn't yet
	if (!m_TerrainShader)
	{
		m_TerrainShader = new TerrainShaderClass;
		if (!m_TerrainShader)
		{
			return false;
		}

		// Initialize the terrain shader object.
		result = m_TerrainShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the terrain shader.
	result = m_TerrainShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, diffuseColor, lightDirection, colorTexture,
		normalMapTexture);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderTerrainShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix,
	DXMATRIX projectionMatrix, DXFLOAT4 diffuseColor, DXFLOAT3 lightDirection, ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalMapTexture,
	float textureBrightness)
{
	bool result;

	// Initialize terrain shader if it isn't yet
	if (!m_TerrainShader)
	{
		m_TerrainShader = new TerrainShaderClass;
		if (!m_TerrainShader)
		{
			return false;
		}

		// Initialize the terrain shader object.
		result = m_TerrainShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the terrain shader.
	result = m_TerrainShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, diffuseColor, lightDirection, colorTexture,
		normalMapTexture, textureBrightness);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderTerrainShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix,
	DXMATRIX projectionMatrix, DXFLOAT4 ambientColor, DXFLOAT4 diffuseColor, DXFLOAT3 lightDirection, ID3D11ShaderResourceView* texture,
	ID3D11ShaderResourceView* normalTexture, ID3D11ShaderResourceView* detailTexture)
{
	bool result;

	// Initialize terrain shader if it isn't yet
	if (!m_TerrainShader)
	{
		m_TerrainShader = new TerrainShaderClass;
		if (!m_TerrainShader)
		{
			return false;
		}

		// Initialize the terrain shader object.
		result = m_TerrainShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the terrain shader.
	result = m_TerrainShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, ambientColor, diffuseColor, lightDirection, texture,
		normalTexture, detailTexture);
	if (!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderTerrainShader(ID3D11DeviceContext* deviceContext, int indexCount, DXMATRIX worldMatrix, DXMATRIX viewMatrix, DXMATRIX projectionMatrix,
	DXFLOAT3 lightDirection, ID3D11ShaderResourceView* colorTexture1, ID3D11ShaderResourceView* colorTexture2, ID3D11ShaderResourceView* colorTexture3,
	ID3D11ShaderResourceView* colorTexture4, ID3D11ShaderResourceView* alphaTexture1, ID3D11ShaderResourceView* normalMap1, ID3D11ShaderResourceView* normalMap2)
{
	bool result;

	// Initialize terrain shader if it isn't yet
	if (!m_TerrainShader)
	{
		m_TerrainShader = new TerrainShaderClass;
		if (!m_TerrainShader)
		{
			return false;
		}

		// Initialize the terrain shader object.
		result = m_TerrainShader->Initialize(m_device, m_hwnd);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Render the model using the terrain shader.
	result = m_TerrainShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, lightDirection, colorTexture1, colorTexture2, colorTexture3,
		colorTexture4, alphaTexture1, normalMap1, normalMap2);
	if (!result)
	{
		return false;
	}

	return true;
}