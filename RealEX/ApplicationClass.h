////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "ShaderManagerClass.h"
#include "inputclass.h"
#include "d3dclass.h"
#include "cameraclass.h"
#include "terrainclass.h"
#include "timerclass.h"
#include "positionclass.h"
#include "fpsclass.h"
#include "cpuclass.h"
#include "fontshaderclass.h"
#include "textclass.h"
#include "SoundClass.h"
#include "BitmapClass.h"
#include "LightClass.h"
#include "FrustumClass.h"
#include "QuadTreeClass.h"
#include "minimapclass.h"
#include "skydomeclass.h"
#include "SkyPlaneClass.h"
#include "DebugWindowClass.h"
#include "RenderTextureClass.h"
#include "WaterClass.h"
using namespace std;
using namespace DirectX;

//////////////
// TYPEDEFS //
//////////////

typedef DirectX::XMMATRIX DXMATRIX;
typedef DirectX::XMFLOAT3 DXFLOAT3;
typedef DirectX::XMFLOAT4 DXFLOAT4;

////////////////////////////////////////////////////////////////////////////////
// Class name: ApplicationClass
////////////////////////////////////////////////////////////////////////////////
class ApplicationClass
{
public:
	ApplicationClass();
	ApplicationClass(const ApplicationClass&);
	~ApplicationClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();
	InputClass* GetInputInstance();

private:
	bool HandleInput(float);
	bool RenderRefractionToTexture();
	bool RenderReflectionToTexture();
	bool RenderSceneToTexture();
	bool RenderGraphics();

private:
	InputClass* m_Input;
	D3DClass* m_Direct3D;
	CameraClass* m_Camera;
	TerrainClass* m_Terrain;
	ShaderManagerClass* m_ShaderManager;
	TimerClass* m_Timer;
	PositionClass* m_Position;
	FpsClass* m_Fps;
	CpuClass* m_Cpu;
	FontShaderClass* m_FontShader;
	TextClass* m_Text;
	SoundClass* m_Sound;
	BitmapClass* m_Cursor;
	LightClass* m_Light;
	FrustumClass* m_Frustum;
	QuadTreeClass* m_QuadTree;
	MiniMapClass* m_MiniMap;
	SkyDomeClass* m_SkyDome;
	SkyPlaneClass* m_SkyPlane;
	DebugWindowClass* m_DebugWindow;
	RenderTextureClass* m_RenderTexture, *m_RefractionTexture, *m_ReflectionTexture;
	WaterClass* m_Water;
};

#endif