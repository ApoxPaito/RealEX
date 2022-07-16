////////////////////////////////////////////////////////////////////////////////
// Filename: shadermanagerclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SHADERMANAGERCLASS_H_
#define _SHADERMANAGERCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "textureshaderclass.h"
#include "lightshaderclass.h"
#include "bumpmapshaderclass.h"
#include "multitextureshaderclass.h"
#include "lightmapshaderclass.h"
#include "alphamapshaderclass.h"
#include "specmapshaderclass.h"
#include "FogShaderClass.h"
#include "ClipPlaneShaderClass.h"
#include "TranslateShaderClass.h"
#include "TransparentShaderClass.h"
#include "ReflectionShaderClass.h"
#include "FadeShaderClass.h"
#include "WaterShaderClass.h"
#include "RefractionShaderClass.h"
#include "GlassShaderClass.h"
#include "FireShaderClass.h"
#include "blurshaderclass.h"
#include "ColorShaderClass.h"
#include "particleshaderclass.h"
#include "DepthShaderClass.h"
#include "ShadowShaderClass.h"
#include "softshadowshaderclass.h"
#include "ProjectionShaderClass.h"
#include "glowmapshaderclass.h"
#include "glowshaderclass.h"
#include "TransparentDepthShaderClass.h"
#include "DeferredShaderClass.h"
#include "terrainshaderclass.h"
#include "skydomeshaderclass.h"
#include "SkyPlaneShaderClass.h"

//////////////
// TYPEDEFS //
//////////////
typedef DirectX::XMMATRIX DXMATRIX;
typedef DirectX::XMFLOAT3 DXFLOAT3;
typedef DirectX::XMFLOAT4 DXFLOAT4;

////////////////////////////////////////////////////////////////////////////////
// Class name: ShaderManagerClass
////////////////////////////////////////////////////////////////////////////////
class ShaderManagerClass
{
public:
	ShaderManagerClass();
	ShaderManagerClass(const ShaderManagerClass&);
	~ShaderManagerClass();

	bool Initialize(ID3D11Device*, HWND); // We'll initialize shaders on their first render calls, down the line I might add a drop overtime if the shader is unused
	void Shutdown();

	bool RenderTextureShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*);
	bool RenderTextureShader(ID3D11DeviceContext*, int, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*);
	bool RenderLightShaderDiffuse(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*,
		DXFLOAT3, DXFLOAT4);
	bool RenderLightShaderAmbient(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*,
		DXFLOAT3, DXFLOAT4, DXFLOAT4);
	bool RenderLightShaderSpecular(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*,
		DXFLOAT3, DXFLOAT4, DXFLOAT4, DXFLOAT3, DXFLOAT4, float);
	bool RenderLightShaderMultiple(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*,
		DXFLOAT4[], DXFLOAT4[]);
	bool RenderLightShaderDeferred(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, DXFLOAT3);
	bool RenderBumpMapShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView**, DXFLOAT3, DXFLOAT4);
	bool RenderMultiTextureShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView**);
	bool RenderLightMapShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView**);
	bool RenderAlphaMapShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView**);
	bool RenderSpecMapShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView**,
		DXFLOAT3, DXFLOAT4, DXFLOAT3, DXFLOAT4, float);
	bool RenderFogShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, float, float);
	bool RenderClipPlaneShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, DXFLOAT4);
	bool RenderTranslateShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, float);
	bool RenderTransparentShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, float);
	bool RenderReflectionShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, DXFLOAT4, DXFLOAT3,
		float, DXFLOAT4);
	bool RenderFadeShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, float);
	bool RenderWaterShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, DXFLOAT3, DXFLOAT2, float, float, DXFLOAT4, DXFLOAT3, float);
	bool RenderRefractionShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, DXFLOAT3, DXFLOAT4, DXFLOAT4, DXFLOAT4);
	bool RenderGlassShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, float);
	bool RenderFireShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, float, DXFLOAT3, DXFLOAT3, DXFLOAT2, DXFLOAT2, DXFLOAT2, float, float);
	bool RenderHorizontalBlurShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, float);
	bool RenderVerticalBlurShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, float);
	bool RenderColorShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX);
	bool RenderColorShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, float);
	bool RenderParticleShader(ID3D11DeviceContext*, int, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*);
	bool RenderDepthShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX);
	bool RenderShadowShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, DXFLOAT3);
	bool RenderShadowShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		DXFLOAT3, DXFLOAT4, DXFLOAT4);
	bool RenderSoftShadowShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		DXFLOAT3, DXFLOAT4, DXFLOAT4);
	bool RenderProjectionShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, DXFLOAT4, DXFLOAT4, DXFLOAT3, DXMATRIX,
		DXMATRIX, ID3D11ShaderResourceView*);
	bool RenderGlowMapShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*);
	bool RenderGlowShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, float);
	bool RenderTransparentDepthShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*);
	bool RenderDeferredShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*);
	bool RenderSkyDomeShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, DXFLOAT4, DXFLOAT4);
	bool RenderSkyPlaneShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		float, float, float, float);
	bool RenderTerrainShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, DXFLOAT4, DXFLOAT3, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*);
	bool RenderTerrainShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, DXFLOAT4, DXFLOAT3, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, float);
	bool RenderTerrainShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, DXFLOAT4, DXFLOAT4, DXFLOAT3, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*);
	bool RenderTerrainShader(ID3D11DeviceContext*, int, DXMATRIX, DXMATRIX, DXMATRIX, DXFLOAT3, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*);

private:
	ID3D11Device* m_device;
	HWND m_hwnd;
	TextureShaderClass* m_TextureShader, *m_TextureInstancedShader;
	LightShaderClass* m_LightShaderAmbient, *m_LightShaderDiffuse, *m_LightShaderSpecular, *m_LightShaderMultiple, *m_LightShaderDeferred;
	BumpMapShaderClass* m_BumpMapShader;
	MultiTextureShaderClass* m_MultiTextureShader;
	LightMapShaderClass* m_LightMapShader;
	AlphaMapShaderClass* m_AlphaMapShader;
	SpecMapShaderClass* m_SpecMapShader;
	FogShaderClass* m_FogShader;
	ClipPlaneShaderClass* m_ClipPlaneShader;
	TranslateShaderClass* m_TranslateShader;
	TransparentShaderClass* m_TransparentShader;
	ReflectionShaderClass* m_ReflectionShader;
	FadeShaderClass* m_FadeShader;
	WaterShaderClass* m_WaterShader;
	RefractionShaderClass* m_RefractionShader;
	GlassShaderClass* m_GlassShader;
	FireShaderClass* m_FireShader;
	BlurShaderClass* m_VerticalBlurShader, *m_HorizontalBlurShader;
	ColorShaderClass* m_ColorShader, *m_ColorTessellationShader;
	ParticleShaderClass* m_ParticleShader;
	DepthShaderClass* m_DepthShader;
	ShadowShaderClass* m_ShadowShader;
	SoftShadowShaderClass* m_SoftShadowShader;
	ProjectionShaderClass* m_ProjectionShader;
	GlowMapShaderClass* m_GlowMapShader;
	GlowShaderClass* m_GlowShader;
	TransparentDepthShaderClass* m_TransparentDepthShader;
	DeferredShaderClass* m_DeferredShader;
	TerrainShaderClass* m_TerrainShader;
	SkyDomeShaderClass* m_SkyDomeShader;
	SkyPlaneShaderClass* m_SkyPlaneShader;
};

#endif