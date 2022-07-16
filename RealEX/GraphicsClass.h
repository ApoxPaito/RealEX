////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_
//https://stackoverflow.com/questions/17475929/access-floats-of-xmmatrix-operator-not-working
//#define _XM_NO_INTRINSICS_
// Note: if turned on, remember to also define on subclasses working with any DirectX structs, otherwise it will cause undetectable overflows
// For good measure, I've already turned everything needing a no intrinsic into an intrinsic one, so I don't go mad over why there are overflows again

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightclass.h"
#include "bitmapclass.h"
#include "textclass.h"
#include "modellistclass.h"
#include "frustumclass.h"
#include "rendertextureclass.h"
#include "debugwindowclass.h"
#include "orthowindowclass.h"
#include "particlesystemclass.h"
#include "ViewPointClass.h"
#include "ShaderManagerClass.h"
#include "TreeClass.h"
#include "DeferredBuffersClass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 100.0f;
const float SCREEN_NEAR = 1.0f;
const int SHADOWMAP_WIDTH = 1024;
const int SHADOWMAP_HEIGHT = 1024;
const float SHADOWMAP_DEPTH = 50.0f;
const float SHADOWMAP_NEAR = 1.0f;

//////////////
// TYPEDEFS //
//////////////
typedef DirectX::XMFLOAT3 DXFLOAT3;
typedef DirectX::XMMATRIX DXMATRIX;
typedef DirectX::XMVECTOR DXVECTOR;

////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(int, int, int, int, float, float, float, float, float, float, float, bool);
	bool Render(int, int);
	void UpdateText(WPARAM);

private:
	bool RenderGlowMapToTexture();
	bool RenderFadingScene();
	bool RenderNormalScene(float);
	bool RenderToTexture(float);
	bool RenderRefractionToTexture();
	bool RenderReflectionToTexture();
	bool RenderScene();
	bool RenderSceneToTexture(RenderTextureClass*, LightClass*);
	bool RenderSceneToTexture();
	bool DownSampleTexture();
	bool RenderHorizontalBlurToTexture();
	bool RenderVerticalBlurToTexture();
	bool UpSampleTexture();
	bool Render2DTextureScene(int, int);
	bool RenderBlackAndWhiteShadows();
	bool RenderUIElementsToTexture();
	bool RenderGlowScene();

	void TestIntersection(int, int);
	bool RaySphereIntersect(DXVECTOR, DXVECTOR, float, float&);
	bool RayCubeIntersect(DXVECTOR, DXVECTOR, float);
	void UpdateLighting(LightClass*, float);

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass *m_Model0, *m_Model1, *m_GroundModel, *m_WallModel, *m_BathModel, *m_WaterModel, *m_CubeModel, *m_SphereModel;
	LightClass *m_Light, *m_Light0, *m_Light1, *m_Light2, *m_Light3, *m_Light4;
	BitmapClass* m_Bitmap;
	BitmapClass* m_Cursor;
	TextClass* m_Text;
	ModelListClass* m_ModelList;
	FrustumClass* m_Frustum;
	RenderTextureClass *m_RenderTexture, *m_RenderTexture0, *m_RefractionTexture, *m_ReflectionTexture, * m_DownSampleTexture, 
		*m_HorizontalBlurTexture, *m_VerticalBlurTexture, *m_UpSampleTexture, *m_BlackWhiteRenderTexture;
	DebugWindowClass* m_DebugWindow;
	float m_fadeInTime, m_accumulatedTime, m_fadePercentage, m_waterHeight, m_waterTranslation;
	bool m_FadeDone;
	ModelClass* m_Model;
	ModelClass* m_WindowModel;
	ModelClass *m_FloorModel, *m_BillboardModel;
	TextureClass* m_ProjectionTexture;
	OrthoWindowClass *m_SmallWindow, *m_FullScreenWindow;
	ParticleSystemClass* m_ParticleSystem;
	ViewPointClass* m_ViewPoint;
	ShaderManagerClass* m_ShaderManager;
	bool m_beginCheck;
	int m_screenWidth, m_screenHeight;
	ModelClass* m_selectedModel;
	TreeClass* m_Tree;
	DeferredBuffersClass* m_DeferredBuffers;
};

#endif