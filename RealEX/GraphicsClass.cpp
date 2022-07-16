////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model0 = 0;
	m_Model1 = 0;
	m_Light0 = 0;
	m_Light1 = 0;
	m_Light2 = 0;
	m_Light3 = 0;
	m_Light4 = 0;
	m_Bitmap = 0;
	m_Cursor = 0;
	m_Text = 0;
	m_ModelList = 0;
	m_Frustum = 0;
	m_RenderTexture = 0;
	m_DebugWindow = 0;
	m_RefractionTexture = 0;
	m_ReflectionTexture = 0;
	m_GroundModel = 0;
	m_WallModel = 0;
	m_BathModel = 0;
	m_WaterModel = 0;
	m_Model = 0;
	m_WindowModel = 0;
	m_FloorModel = 0;
	m_BillboardModel = 0;
	m_DownSampleTexture = 0;
	m_HorizontalBlurTexture = 0;
	m_VerticalBlurTexture = 0;
	m_UpSampleTexture = 0;
	m_SmallWindow = 0;
	m_FullScreenWindow = 0;
	m_ParticleSystem = 0;
	m_Light = 0;
	m_CubeModel = 0;
	m_SphereModel = 0;
	m_RenderTexture0 = 0;
	m_BlackWhiteRenderTexture = 0;
	m_ViewPoint = 0;
	m_ProjectionTexture = 0;
	m_ShaderManager = 0;
	m_selectedModel = 0;
	m_Tree = 0;
	m_DeferredBuffers = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	/*int downSampleWidth, downSampleHeight;*/
	DXMATRIX baseViewMatrix;

	//// Set the size to sample down to.
	//downSampleWidth = SHADOWMAP_WIDTH / 2;
	//downSampleHeight = SHADOWMAP_HEIGHT / 2;

	// Assign the screen width and height values
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	/*m_Camera->SetRotation(20.0f, 0.0f, 0.0f);*/
	m_Camera->Render();
	m_Camera->RenderBaseViewMatrix();
	m_Camera->GetBaseViewMatrix(baseViewMatrix);

	//// Create the cube model object.
	//m_CubeModel = new ModelClass;
	//if (!m_CubeModel)
	//{
	//	return false;
	//}

	//// Initialize the cube model object.
	//result = m_CubeModel->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), (char*) "../RealEX/data/cube.txt", (char*) "../RealEX/textures/moom.tga");
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the cube model object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Set the position for the cube model.
	//m_CubeModel->SetPosition(-2.0f, 2.0f, 0.0f);

	//// Create the sphere model object.
	//m_SphereModel = new ModelClass;
	//if (!m_SphereModel)
	//{
	//	return false;
	//}

	//// Initialize the sphere model object.
	//result = m_SphereModel->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), (char*) "../RealEX/data/sphere.txt", (char*) "../RealEX/textures/ogey.tga");
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the sphere model object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Set the position for the sphere model.
	//m_SphereModel->SetPosition(2.0f, 2.0f, 0.0f);

	//// Create the ground model object.
	//m_GroundModel = new ModelClass;
	//if (!m_GroundModel)
	//{
	//	return false;
	//}

	//// Initialize the ground model object.
	//result = m_GroundModel->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), (char*)"../RealEX/data/floor.txt", (char*) "../RealEX/textures/ground_earth.tga");
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the ground model object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Set the position for the ground model.
	//m_GroundModel->SetPosition(0.0f, 1.0f, 0.0f);

	//// Create the tree object.
	//m_Tree = new TreeClass;
	//if (!m_Tree)
	//{
	//	return false;
	//}

	//// Initialize the ground model object.
	//result = m_Tree->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), (char*)"../RealEX/data/flora/trunk001.txt", (char*)"../RealEX/textures/flora/trunk001.tga",
	//	(char*) "../RealEX/data/flora/leaf001.txt", (char*) "../RealEX/textures/flora/leaf001.tga", 0.1f);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the tree object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Set the position for the ground model.
	//m_Tree->SetPosition(0.0f, 1.0f, 0.0f);

	//// Create the text object.
	//m_Text = new TextClass;
	//if (!m_Text)
	//{
	//	return false;
	//}

	//// Initialize the text object.
	//result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the particle system object.
	//m_ParticleSystem = new ParticleSystemClass;
	//if (!m_ParticleSystem)
	//{
	//	return false;
	//}

	//// Initialize the particle system object.
	//result = m_ParticleSystem->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), (char*) "../RealEX/textures/star.tga");
	//if (!result)
	//{
	//	return false;
	//}

	//// Create the wall model object.
	//m_WallModel = new ModelClass;
	//if (!m_WallModel)
	//{
	//	return false;
	//}

	//// Initialize the wall model object.
	//result = m_WallModel->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), (char*)"../RealEX/data/wall.txt", (char*) "../RealEX/textures/ina.tga");
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the wall model object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the bath model object.
	//m_BathModel = new ModelClass;
	//if (!m_BathModel)
	//{
	//	return false;
	//}

	//// Initialize the bath model object.
	//result = m_BathModel->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), (char*)"../RealEX/data/bath.txt", (char*) "../RealEX/textures/marble01.tga");
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the bath model object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the water model object.
	//m_WaterModel = new ModelClass;
	//if (!m_WaterModel)
	//{
	//	return false;
	//}

	//// Initialize the water model object.
	//result = m_WaterModel->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), (char*) "../RealEX/data/water.txt", (char*)"../RealEX/textures/water01.tga");
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the water model object.", L"Error", MB_OK);
	//	return false;
	//}

	// Create the model object.
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), (char*) "../RealEX/data/cube.txt", (char*) "../RealEX/textures/ina.tga");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Set the position for the cube model.
	m_Model->SetPosition(0.0f, 0.0f, 0.0f);

	//// Create the model object.
	//m_Model = new ModelClass;
	//if (!m_Model)
	//{
	//	return false;
	//}

	//// Initialize the model object.
	//result = m_Model->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), (char*) "../RealEX/data/square.txt", (char*) "../RealEX/textures/fire01.tga",
	//	(char*) "../RealEX/textures/noise01.tga", (char*) "../RealEX/textures/firealpha01.tga");
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the model object.
	//m_FloorModel = new ModelClass;
	//if (!m_FloorModel)
	//{
	//	return false;
	//}

	//// Initialize the model object.
	//result = m_FloorModel->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), (char*)"../RealEX/data/floor.txt", (char*)"../RealEX/textures/grid01.tga");
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the model object.
	//m_BillboardModel = new ModelClass;
	//if (!m_BillboardModel)
	//{
	//	return false;
	//}

	//// Initialize the model object.
	//result = m_BillboardModel->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), (char*)"../RealEX/data/square.txt", (char*)"../RealEX/textures/ground_earth.tga");
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the window model object.
	//m_WindowModel = new ModelClass;
	//if (!m_WindowModel)
	//{
	//	return false;
	//}

	//// Initialize the window model object.
	//result = m_WindowModel->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), (char*) "../RealEX/data/square.txt",
	//	(char*) "../RealEX/textures/ice01.tga", (char*) "../RealEX/textures/icebump01.tga");
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the window model object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the first model object.
	//m_Model0 = new ModelClass;
	//if (!m_Model0)
	//{
	//	return false;
	//}

	//// Initialize the first model object.
	//result = m_Model0->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), (char*)"../RealEX/data/pyramid.txt", (char*) "../RealEX/textures/ogey.tga");
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the first model object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the second model object.
	//m_Model1 = new ModelClass;
	//if (!m_Model1)
	//{
	//	return false;
	//}

	//// Initialize the second model object.
	//result = m_Model1->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), (char*)"../RealEX/data/floor.txt", (char*) "../RealEX/textures/blue01.tga");
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the second model object.", L"Error", MB_OK);
	//	return false;
	//}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	/*m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);*/
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	/*m_Light->SetPosition(2.0f, 5.0f, -2.0f);*/
	//m_Light->GenerateProjectionMatrix(SCREEN_DEPTH, SCREEN_NEAR);
	/*m_Light->GenerateOrthoMatrix(15.0f, 15.0f, SHADOWMAP_DEPTH, SHADOWMAP_NEAR);*/

	//// Create the first light object.
	//m_Light0 = new LightClass;
	//if (!m_Light0)
	//{
	//	return false;
	//}

	//// Initialize the light object.
	//m_Light0->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	//m_Light0->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	//m_Light0->SetLookAt(0.0f, 0.0f, 0.0f);
	//m_Light0->GenerateProjectionMatrix(SCREEN_DEPTH, SCREEN_NEAR);

	//// Create the second light object.
	//m_Light1 = new LightClass;
	//if (!m_Light1)
	//{
	//	return false;
	//}

	//// Initialize the second light object.
	//m_Light1->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	//m_Light1->SetLookAt(0.0f, 0.0f, 0.0f);
	//m_Light1->GenerateProjectionMatrix(SCREEN_DEPTH, SCREEN_NEAR);

	//// Create the third light object.
	//m_Light2 = new LightClass;
	//if (!m_Light2)
	//{
	//	return false;
	//}

	//// Initialize the third light object.
	//m_Light2->SetDiffuseColor(0.0f, 0.0f, 1.0f, 1.0f);
	//m_Light2->SetPosition(-3.0f, 1.0f, -3.0f);

	//// Create the fourth light object.
	//m_Light3 = new LightClass;
	//if (!m_Light3)
	//{
	//	return false;
	//}

	//// Initialize the fourth light object.
	//m_Light3->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	//m_Light3->SetPosition(3.0f, 1.0f, -3.0f);

	//// Create the fifth light object.
	//m_Light4 = new LightClass;
	//if (!m_Light4)
	//{
	//	return false;
	//}

	//// Initialize the fifth light object.
	//m_Light4->SetDiffuseColor(0.0f, 0.5f, 0.5f, 1.0f);
	//m_Light4->SetPosition(0.0f, 1.0f, 0.0f);

	//// Create the model list object.
	//m_ModelList = new ModelListClass;
	//if (!m_ModelList)
	//{
	//	return false;
	//}

	//// Initialize the model list object.
	//result = m_ModelList->Initialize(500);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the model list object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the frustum object.
	//m_Frustum = new FrustumClass;
	//if (!m_Frustum)
	//{
	//	return false;
	//}

	//// Create the bitmap object.
	//m_Bitmap = new BitmapClass;
	//if (!m_Bitmap)
	//{
	//	return false;
	//}

	//// Initialize the bitmap object.
	//result = m_Bitmap->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), screenWidth, screenHeight, (char*) "../RealEX/textures/test.tga",
	//	(char*) "../RealEX/textures/glowmap.tga", 256, 32);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
	//	return false;
	//}

	// Create the cursor object.
	m_Cursor = new BitmapClass;
	if (!m_Cursor)
	{
		return false;
	}

	// Initialize the cursor object.
	result = m_Cursor->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), screenWidth, screenHeight, (char*)"../RealEX/textures/cursor.tga", 32, 32);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	//// Create the refraction render to texture object.
	//m_RefractionTexture = new RenderTextureClass;
	//if (!m_RefractionTexture)
	//{
	//	return false;
	//}

	//// Initialize the refraction render to texture object.
	//result = m_RefractionTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the refraction render to texture object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the reflection render to texture object.
	//m_ReflectionTexture = new RenderTextureClass;
	//if (!m_ReflectionTexture)
	//{
	//	return false;
	//}

	//// Initialize the reflection render to texture object.
	//result = m_ReflectionTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the reflection render to texture object.", L"Error", MB_OK);
	//	return false;
	//}

	// Create the render to texture object.
	m_RenderTexture = new RenderTextureClass;
	if (!m_RenderTexture)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = m_RenderTexture->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SHADOWMAP_DEPTH, SHADOWMAP_NEAR);
	if (!result)
	{
		return false;
	}

	//// Create the second render to texture object.
	//m_RenderTexture0 = new RenderTextureClass;
	//if (!m_RenderTexture0)
	//{
	//	return false;
	//}

	//// Initialize the second render to texture object.
	//result = m_RenderTexture0->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the second render to texture object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the down sample render to texture object.
	//m_DownSampleTexture = new RenderTextureClass;
	//if (!m_DownSampleTexture)
	//{
	//	return false;
	//}

	//// Initialize the down sample render to texture object.
	//result = m_DownSampleTexture->Initialize(m_D3D->GetDevice(), (screenWidth / 2), (screenHeight / 2), SCREEN_DEPTH, SCREEN_NEAR);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the down sample render to texture object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the up sample render to texture object.
	//m_UpSampleTexture = new RenderTextureClass;
	//if (!m_UpSampleTexture)
	//{
	//	return false;
	//}

	//// Initialize the up sample render to texture object.
	//result = m_UpSampleTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the up sample render to texture object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the horizontal blur render to texture object.
	//m_HorizontalBlurTexture = new RenderTextureClass;
	//if (!m_HorizontalBlurTexture)
	//{
	//	return false;
	//}

	//// Initialize the horizontal blur render to texture object.
	//result = m_HorizontalBlurTexture->Initialize(m_D3D->GetDevice(), (screenWidth / 2), (screenHeight / 2), SCREEN_DEPTH, SCREEN_NEAR);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the horizontal blur render to texture object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the vertical blur render to texture object.
	//m_VerticalBlurTexture = new RenderTextureClass;
	//if (!m_VerticalBlurTexture)
	//{
	//	return false;
	//}

	//// Initialize the vertical blur render to texture object.
	//result = m_VerticalBlurTexture->Initialize(m_D3D->GetDevice(), (screenWidth / 2), (screenHeight / 2), SCREEN_DEPTH, SCREEN_NEAR);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the vertical blur render to texture object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the render to texture object.
	//m_BlackWhiteRenderTexture = new RenderTextureClass;
	//if (!m_BlackWhiteRenderTexture)
	//{
	//	return false;
	//}

	//// Initialize the black and white render to texture object.
	//result = m_BlackWhiteRenderTexture->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the black and white render to texture object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the small ortho window object.
	//m_SmallWindow = new OrthoWindowClass;
	//if (!m_SmallWindow)
	//{
	//	return false;
	//}

	//// Initialize the small ortho window object.
	//result = m_SmallWindow->Initialize(m_D3D->GetDevice(), (screenWidth / 2), (screenHeight / 2));
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the small ortho window object.", L"Error", MB_OK);
	//	return false;
	//}

	// Create the full screen ortho window object.
	m_FullScreenWindow = new OrthoWindowClass;
	if (!m_FullScreenWindow)
	{
		return false;
	}

	// Initialize the full screen ortho window object.
	result = m_FullScreenWindow->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the full screen ortho window object.", L"Error", MB_OK);
		return false;
	}

	//// Set the fade in time to 3000 milliseconds.
	//m_fadeInTime = 3000.0f;

	//// Initialize the accumulated time to zero milliseconds.
	//m_accumulatedTime = 0;

	//// Initialize the fade percentage to zero at first so the scene is black.
	//m_fadePercentage = 0;

	//// Set the fading in effect to not done.
	//m_FadeDone = false;

	//// Create the debug window object.
	//m_DebugWindow = new DebugWindowClass;
	//if (!m_DebugWindow)
	//{
	//	return false;
	//}

	//// Initialize the debug window object.
	//result = m_DebugWindow->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, 100, 100);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the debug window object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the horizontal blur shader object.
	//m_HorizontalBlurShader = new BlurShaderClass;
	//if (!m_HorizontalBlurShader)
	//{
	//	return false;
	//}

	//// Initialize the horizontal blur shader object.
	//result = m_HorizontalBlurShader->InitializeHorizontal(m_D3D->GetDevice(), hwnd);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the horizontal blur shader object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the vertical blur shader object.
	//m_VerticalBlurShader = new BlurShaderClass;
	//if (!m_VerticalBlurShader)
	//{
	//	return false;
	//}

	//// Initialize the vertical blur shader object.
	//result = m_VerticalBlurShader->InitializeVertical(m_D3D->GetDevice(), hwnd);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the vertical blur shader object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Set the height of the water.
	//m_waterHeight = 2.75f;

	//// Initialize the position of the water.
	//m_waterTranslation = 0.0f;

	//// Create the projection texture object.
	//m_ProjectionTexture = new TextureClass;
	//if (!m_ProjectionTexture)
	//{
	//	return false;
	//}

	//// Initialize the projection texture object.
	//result = m_ProjectionTexture->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), (char*) "../RealEX/textures/glow.tga");
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the projection texture object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the view point object.
	//m_ViewPoint = new ViewPointClass;
	//if (!m_ViewPoint)
	//{
	//	return false;
	//}

	//// Initialize the view point object.
	//m_ViewPoint->SetPosition(2.0f, 5.0f, -2.0f);
	//m_ViewPoint->SetLookAt(0.0f, 0.0f, 0.0f);
	//m_ViewPoint->SetProjectionParameters((float)(XM_PI / 2.0f), 1.0f, 0.1f, 100.0f);
	//m_ViewPoint->GenerateViewMatrix();
	//m_ViewPoint->GenerateProjectionMatrix();

	// Create the deferred buffers object.
	m_DeferredBuffers = new DeferredBuffersClass;
	if (!m_DeferredBuffers)
	{
		return false;
	}

	// Initialize the deferred buffers object.
	result = m_DeferredBuffers->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the deferred buffers object.", L"Error", MB_OK);
		return false;
	}

	// Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if (!m_ShaderManager)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Set the selected model pointer to null since it might point to a model that will be deleted later.
	m_selectedModel = 0;

	// Release the view point object.
	if (m_DeferredBuffers)
	{
		m_DeferredBuffers->Shutdown();
		delete m_DeferredBuffers;
		m_DeferredBuffers = 0;
	}

	// Release the view point object.
	if (m_ViewPoint)
	{
		delete m_ViewPoint;
		m_ViewPoint = 0;
	}

	// Release the projection texture object.
	if (m_ProjectionTexture)
	{
		m_ProjectionTexture->Shutdown();
		delete m_ProjectionTexture;
		m_ProjectionTexture = 0;
	}

	// Release the soft shadow shader object.
	if (m_BlackWhiteRenderTexture)
	{
		m_BlackWhiteRenderTexture->Shutdown();
		delete m_BlackWhiteRenderTexture;
		m_BlackWhiteRenderTexture = 0;
	}

	// Release the second render to texture object.
	if (m_RenderTexture0)
	{
		m_RenderTexture0->Shutdown();
		delete m_RenderTexture0;
		m_RenderTexture0 = 0;
	}

	// Release the particle system object.
	if (m_ParticleSystem)
	{
		m_ParticleSystem->Shutdown();
		delete m_ParticleSystem;
		m_ParticleSystem = 0;
	}

	// Release the full screen ortho window object.
	if (m_FullScreenWindow)
	{
		m_FullScreenWindow->Shutdown();
		delete m_FullScreenWindow;
		m_FullScreenWindow = 0;
	}

	// Release the small ortho window object.
	if (m_SmallWindow)
	{
		m_SmallWindow->Shutdown();
		delete m_SmallWindow;
		m_SmallWindow = 0;
	}

	// Release the up sample render to texture object.
	if (m_UpSampleTexture)
	{
		m_UpSampleTexture->Shutdown();
		delete m_UpSampleTexture;
		m_UpSampleTexture = 0;
	}

	// Release the vertical blur render to texture object.
	if (m_VerticalBlurTexture)
	{
		m_VerticalBlurTexture->Shutdown();
		delete m_VerticalBlurTexture;
		m_VerticalBlurTexture = 0;
	}

	// Release the horizontal blur render to texture object.
	if (m_HorizontalBlurTexture)
	{
		m_HorizontalBlurTexture->Shutdown();
		delete m_HorizontalBlurTexture;
		m_HorizontalBlurTexture = 0;
	}

	// Release the down sample render to texture object.
	if (m_DownSampleTexture)
	{
		m_DownSampleTexture->Shutdown();
		delete m_DownSampleTexture;
		m_DownSampleTexture = 0;
	}

	// Release the render to texture object.
	if (m_RenderTexture)
	{
		m_RenderTexture->Shutdown();
		delete m_RenderTexture;
		m_RenderTexture = 0;
	}

	// Release the floor model object.
	if (m_FloorModel)
	{
		m_FloorModel->Shutdown();
		delete m_FloorModel;
		m_FloorModel = 0;
	}

	// Release the window model object.
	if (m_BillboardModel)
	{
		m_BillboardModel->Shutdown();
		delete m_BillboardModel;
		m_BillboardModel = 0;
	}

	// Release the window model object.
	if (m_WindowModel)
	{
		m_WindowModel->Shutdown();
		delete m_WindowModel;
		m_WindowModel = 0;
	}

	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the light objects.
	if (m_Light0)
	{
		delete m_Light0;
		m_Light0 = 0;
	}

	if (m_Light1)
	{
		delete m_Light1;
		m_Light1 = 0;
	}

	if (m_Light2)
	{
		delete m_Light2;
		m_Light2 = 0;
	}

	if (m_Light3)
	{
		delete m_Light3;
		m_Light3 = 0;
	}

	if (m_Light4)
	{
		delete m_Light4;
		m_Light4 = 0;
	}

	// Release the reflection render to texture object.
	if (m_ReflectionTexture)
	{
		m_ReflectionTexture->Shutdown();
		delete m_ReflectionTexture;
		m_ReflectionTexture = 0;
	}

	// Release the refraction render to texture object.
	if (m_RefractionTexture)
	{
		m_RefractionTexture->Shutdown();
		delete m_RefractionTexture;
		m_RefractionTexture = 0;
	}

	// Release the water model object.
	if (m_WaterModel)
	{
		m_WaterModel->Shutdown();
		delete m_WaterModel;
		m_WaterModel = 0;
	}

	// Release the bath model object.
	if (m_BathModel)
	{
		m_BathModel->Shutdown();
		delete m_BathModel;
		m_BathModel = 0;
	}

	// Release the wall model object.
	if (m_WallModel)
	{
		m_WallModel->Shutdown();
		delete m_WallModel;
		m_WallModel = 0;
	}

	// Release the ground model object.
	if (m_GroundModel)
	{
		m_GroundModel->Shutdown();
		delete m_GroundModel;
		m_GroundModel = 0;
	}

	// Release the debug window object.
	if (m_DebugWindow)
	{
		m_DebugWindow->Shutdown();
		delete m_DebugWindow;
		m_DebugWindow = 0;
	}

	// Release the render to texture object.
	if (m_RenderTexture)
	{
		m_RenderTexture->Shutdown();
		delete m_RenderTexture;
		m_RenderTexture = 0;
	}

	// Release the frustum object.
	if (m_Frustum)
	{
		delete m_Frustum;
		m_Frustum = 0;
	}

	// Release the model list object.
	if (m_ModelList)
	{
		m_ModelList->Shutdown();
		delete m_ModelList;
		m_ModelList = 0;
	}

	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the bitmap object.
	if (m_Cursor)
	{
		m_Cursor->Shutdown();
		delete m_Cursor;
		m_Cursor = 0;
	}

	// Release the model object.
	if (m_Model0)
	{
		m_Model0->Shutdown();
		delete m_Model0;
		m_Model0 = 0;
	}

	// Release the model object.
	if (m_Model1)
	{
		m_Model1->Shutdown();
		delete m_Model1;
		m_Model1 = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame(int mouseX, int mouseY, int fps, int cpu, float positionX, float positionY, float positionZ, float rotationX, float rotationY, float rotationZ,
	float frameTime, bool leftClickState)
{
	bool result;
	DXMATRIX worldMatrix;
	static float rotation = 0.0f;
	static float lightAngle = 270.0f;
	float radians;
	static float lightPosX = 9.0f;

	//// Update the rotation variable each frame.
	//rotation += (float)XM_PI * 0.001f;
	//if (rotation > 360.0f)
	//{
	//	rotation -= 360.0f;
	//}

	// Update the position of the camera.
	m_Camera->SetPosition(positionX, positionY, positionZ);
	m_Camera->SetRotation(rotationX, rotationY, rotationZ);

	//// If clicked on the screen with the mouse then perform an intersection test.
	//if (!m_beginCheck && leftClickState)
	//{
	//	m_beginCheck = true;
	//	TestIntersection(mouseX, mouseY);
	//}

	//// Check if the left mouse button has been released.
	//if (!leftClickState)
	//{
	//	m_beginCheck = false;
	//}

	//// Update the position of the light each frame.
	//lightPosX -= 0.003f * frameTime;

	//// Update the angle of the light each frame.
	//lightAngle -= 0.03f * frameTime;
	//if (lightAngle < 90.0f)
	//{
	//	lightAngle = 270.0f;

	//	// Reset the light position also.
	//	lightPosX = 9.0f;
	//}
	//radians = lightAngle * 0.0174532925f;

	//// Update the direction of the light.
	//m_Light->SetDirection(sinf(radians), cosf(radians), 0.0f);

	//// Set the position and lookat for the light.
	//m_Light->SetPosition(lightPosX, 8.0f, -0.1f);
	//m_Light->SetLookAt(-lightPosX, 0.0f, 0.0f);

	//// Render the scene to texture first.
	//result = RenderToTexture(rotation);
	//if (!result)
	//{
	//	return false;
	//}

	//// Get the world matrix
	//m_D3D->GetWorldMatrix(worldMatrix);

	//// Run the frame processing for the particle system.
	//m_ParticleSystem->Frame(frameTime, m_D3D->GetDeviceContext());

	//// Update the position of the light each frame.
	//lightPositionX += 0.05f;
	//if (lightPositionX > 5.0f)
	//{
	//	lightPositionX = -5.0f;
	//}

	//// Update the position of the light.
	//m_Light0->SetPosition(sinf(rotation) * 5.0f, 8.0f, cosf(rotation) * 5.0f);

	//// Set the position of the first light.
	//m_Light0->SetPosition(5.0, 8.0f, -5.0f);

	//// Set the position of the second light.
	//m_Light1->SetPosition(-5.0f, 8.0f, -5.0f);

	//// Update the scene lighting.
	//UpdateLighting(m_Light, frameTime);

	// Render the graphics scene.
	result = Render(mouseX, mouseY);
	if (!result)
	{
		return false;
	}

	//// Set the frames per second.
	//result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	//if (!result)
	//{
	//	return false;
	//}

	//// Set the cpu usage.
	//result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
	//if (!result)
	//{
	//	return false;
	//}

	//if (!m_FadeDone)
	//{
	//	// Update the accumulated time with the extra frame time addition.
	//	m_accumulatedTime += frameTime;

	//	// While the time goes on increase the fade in amount by the time that is passing each frame.
	//	if (m_accumulatedTime < m_fadeInTime)
	//	{
	//		// Calculate the percentage that the screen should be faded in based on the accumulated time.
	//		m_fadePercentage = m_accumulatedTime / m_fadeInTime;
	//	}
	//	else
	//	{
	//		// If the fade in time is complete then turn off the fade effect and render the scene normally.
	//		m_FadeDone = true;

	//		// Set the percentage to 100%.
	//		m_fadePercentage = 1.0f;

	//		// Reset the accumulated time
	//		m_accumulatedTime = 0.0f;
	//	}
	//}
	//else
	//{
	//	// Update the accumulated time with the extra frame time addition.
	//	m_accumulatedTime += frameTime;

	//	// While the time goes on increase the fade in amount by the time that is passing each frame.
	//	if (m_accumulatedTime < m_fadeInTime)
	//	{
	//		// Calculate the percentage that the screen should be faded in based on the accumulated time.
	//		m_fadePercentage = 1.0f - (m_accumulatedTime / m_fadeInTime);
	//	}
	//	else
	//	{
	//		// If the fade in time is complete then turn off the fade effect and render the scene normally.
	//		m_FadeDone = false;

	//		// Set the percentage to 0%.
	//		m_fadePercentage = 0.0f;

	//		// Reset the accumulated time
	//		m_accumulatedTime = 0.0f;
	//	}
	//}

	//// Update the position of the water to simulate motion.
	//m_waterTranslation += 0.001f;
	//if (m_waterTranslation > 1.0f)
	//{
	//	m_waterTranslation -= 1.0f;
	//}

	//// Set the position of the camera.
	//m_Camera->SetPosition(2.0f, 1.0f, -10.0f);

	//// Set the rotation of the camera.
	//m_Camera->SetRotation(0.0f, -10.0f, 0.0f);

	//// Set the position and rotation of the camera.
	//m_Camera->SetPosition(-10.0f, 6.0f, -15.0f);
	//m_Camera->SetRotation(10.0f, 30.0f, 0.0f);

	return true;
}


bool GraphicsClass::Render(int mouseX, int mouseY)
{
	float fogColor, fogStart, fogEnd;
	DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, translateMatrix, lightViewMatrix, lightProjectionMatrix, 
		lightViewMatrix2, lightProjectionMatrix2, viewMatrix2, projectionMatrix2, baseViewMatrix, lightOrthoMatrix;
	int modelCount, renderCount, index;
	float positionX, positionY, positionZ, radius, blendAmount, refractionScale;
	DXFLOAT2 distortion1, distortion2, distortion3;
	DXFLOAT3 scrollSpeeds, scales;
	DXFLOAT4 color, clipPlane, diffuseColors[5], lightPosition[5], ambientColor, diffuseColor;
	float distortionScale, distortionBias, posX, posY, posZ;
	bool renderModel, result;
	static float rotation = 0.0f;
	static float textureTranslation = 0.0f;
	static float frameTime = 0.0f;
	DXFLOAT3 cameraPosition, modelPosition;
	double angle;

	//// First render the glow maps to a render texture.
	//result = RenderGlowMapToTexture();
	//if (!result)
	//{
	//	return false;
	//}

	// Render the scene to the render buffers.
	result = RenderSceneToTexture();
	if (!result)
	{
		return false;
	}

	//// First render the scene to a render texture.
	//result = RenderSceneToTexture(m_RenderTexture, m_Light);
	//if (!result)
	//{
	//	return false;
	//}

	//// First render the scene to a render texture.
	//result = RenderSceneToTexture(m_RenderTexture0, m_Light1);
	//if (!result)
	//{
	//	return false;
	//}

	//// Next render the shadowed scene in black and white.
	//result = RenderBlackAndWhiteShadows();
	//if (!result)
	//{
	//	return false;
	//}

	//// Then down sample the black and white scene texture.
	//result = DownSampleTexture();
	//if (!result)
	//{
	//	return false;
	//}

	//// Perform a horizontal blur on the down sampled texture.
	//result = RenderHorizontalBlurToTexture();
	//if (!result)
	//{
	//	return false;
	//}

	//// Now perform a vertical blur on the texture.
	//result = RenderVerticalBlurToTexture();
	//if (!result)
	//{
	//	return false;
	//}

	//// Finally up sample the final blurred render to texture that can now be used in the soft shadow shader.
	//result = UpSampleTexture();
	//if (!result)
	//{
	//	return false;
	//}

	//// Render the blurred up sampled render texture to the screen.
	//result = Render2DTextureScene(mouseX, mouseY);
	//if (!result)
	//{
	//	return false;
	//}

	//// Render the regular UI elements to a full screen texture.
	//result = RenderUIElementsToTexture();
	//if (!result)
	//{
	//	return false;
	//}

	//// Render the final scene combining the UI elements with the glowing UI elements.
	//RenderGlowScene();

	//// Increment the frame time counter.
	//frameTime += 0.01f;
	//if (frameTime > 1000.0f)
	//{
	//	frameTime = 0.0f;
	//}

	//// Set the three scrolling speeds for the three different noise textures.
	//scrollSpeeds = DXFLOAT3(1.3f, 2.1f, 2.3f);

	//// Set the three scales which will be used to create the three different noise octave textures.
	//scales = DXFLOAT3(3.0f, 2.0f, 1.0f);

	//// Set the three different x and y distortion factors for the three different noise textures.
	//distortion1 = DXFLOAT2(0.1f, 0.2f);
	//distortion2 = DXFLOAT2(0.1f, 0.3f);
	//distortion3 = DXFLOAT2(0.1f, 0.1f);

	//// The the scale and bias of the texture coordinate sampling perturbation.
	//distortionScale = 0.8f;
	//distortionBias = 0.1f;

	//// Create the diffuse color array from the four light colors.
	//diffuseColor[0] = m_Light0->GetDiffuseColor();
	//diffuseColor[1] = m_Light1->GetDiffuseColor();
	//diffuseColor[2] = m_Light2->GetDiffuseColor();
	//diffuseColor[3] = m_Light3->GetDiffuseColor();
	//diffuseColor[4] = m_Light4->GetDiffuseColor();

	//// Create the light position array from the four light positions.
	//lightPosition[0] = m_Light0->GetPosition();
	//lightPosition[1] = m_Light1->GetPosition();
	//lightPosition[2] = m_Light2->GetPosition();
	//lightPosition[3] = m_Light3->GetPosition();
	//lightPosition[4] = m_Light4->GetPosition();

	//// Set the refraction scale for the glass shader.
	//refractionScale = 0.05f;

	//// Set the blending amount to 50%.
	//blendAmount = 0.1f;

	//// Increment the texture translation position.
	//textureTranslation += 0.001f;
	//if (textureTranslation > 1.0f)
	//{
	//	textureTranslation -= 1.0f;
	//}

	//// Setup a clipping plane.
	//clipPlane = DXFLOAT4(1.0f, 0.0f, 0.0f, 0.0f);

	//// Set the color of the fog to grey.
	//fogColor = 0.5f;

	//// Set the start and end of the fog.
	//fogStart = 0.0f;
	//fogEnd = 10.0f;

	//// Render the entire scene to the texture first.
	//result = RenderToTexture();
	//if (!result)
	//{
	//	return false;
	//}

	//// Update the rotation variable each frame.
	//rotation += (float)XM_PI * 0.001f;
	//if (rotation > 360.0f)
	//{
	//	rotation -= 360.0f;
	//}

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	//// Render the scene as normal to the back buffer.
	//result = RenderScene();
	//if (!result)
	//{
	//	return false;
	//}

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, base view, view, projection, and ortho matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);

	//// Generate the light view matrix based on the light's position.
	//m_Light->GenerateViewMatrix();

	//// Generate the light view matrix based on the light's position.
	//m_Light0->GenerateViewMatrix();

	//// Generate the light view matrix based on the light's position.
	//m_Light1->GenerateViewMatrix();

	//// Get the view and projection matrices from the view point object.
	//m_ViewPoint->GetViewMatrix(viewMatrix2);
	//m_ViewPoint->GetProjectionMatrix(projectionMatrix2);

	//// Update the position of light according to the cam
	//cameraPosition = m_Camera->GetPosition();
	//DXFLOAT3 cameraRotation = m_Camera->GetRotation();
	//m_Light->SetPosition(cameraPosition.x, cameraPosition.y, cameraPosition.z);
	//m_Light->SetLookAt(cameraRotation.x, cameraRotation.y, cameraRotation.z);

	//// Get the position of the camera.
	//cameraPosition = m_Camera->GetPosition();

	//// Get the light's view and projection matrices from the light object.
	//m_Light->GetViewMatrix(lightViewMatrix);
	//m_Light->GetOrthoMatrix(lightOrthoMatrix);

	//// Set the light color attributes.
	//diffuseColor = DXFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//ambientColor = DXFLOAT4(0.15f, 0.15f, 0.15f, 1.0f);

	//// Get the light's view and projection matrices from the light object.
	//m_Light0->GetViewMatrix(lightViewMatrix);
	//m_Light0->GetProjectionMatrix(lightProjectionMatrix);

	//// Get the light's view and projection matrices from the second light object.
	//m_Light1->GetViewMatrix(lightViewMatrix2);
	//m_Light1->GetProjectionMatrix(lightProjectionMatrix2);

	//// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_Model->Render(m_D3D->GetDeviceContext());

	//// Render the model using the depth shader.
	//result = m_DepthShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	//if (!result)
	//{
	//	return false;
	//}

	//if (m_selectedModel)
	//{
	//	// Setup the translation matrix for the selected model.
	//	m_selectedModel->GetPosition(posX, posY, posZ);
	//	worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	//	// Render the selected model with a yellow tint
	//	m_selectedModel->Render(m_D3D->GetDeviceContext());
	//	result = m_ShaderManager->RenderLightShaderAmbient(m_D3D->GetDeviceContext(), m_selectedModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//		m_selectedModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), DXFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));
	//	if (!result)
	//	{
	//		return false;
	//	}
	//}

	//// Setup the translation for the cube model.
	//m_CubeModel->GetPosition(posX, posY, posZ);
	//worldMatrix = XMMatrixTranslation(posX, posY, posZ);
	///*worldMatrix *= XMMatrixRotationY(rotation);*/

	//// Put the cube model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_CubeModel->Render(m_D3D->GetDeviceContext());
	//result = m_ShaderManager->RenderShadowShader(m_D3D->GetDeviceContext(), m_CubeModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
	//	lightOrthoMatrix, m_CubeModel->GetTexture(), m_RenderTexture->GetShaderResourceView(), m_Light->GetDirection(),
	//	m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	//if (!result)
	//{
	//	return false;
	//}

	//// Setup the translation matrix for the sphere model.
	//m_SphereModel->GetPosition(posX, posY, posZ);
	//worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	//// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_SphereModel->Render(m_D3D->GetDeviceContext());
	//result = m_ShaderManager->RenderShadowShader(m_D3D->GetDeviceContext(), m_SphereModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
	//	lightOrthoMatrix, m_SphereModel->GetTexture(), m_RenderTexture->GetShaderResourceView(), m_Light->GetDirection(),
	//	m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	//if (!result)
	//{
	//	return false;
	//}

	//// Setup the translation matrix for the sphere model.
	//m_Model->GetPosition(posX, posY, posZ);
	//worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	//// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_Model->Render(m_D3D->GetDeviceContext());
	//result = m_ShaderManager->RenderLightShaderAmbient(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	//if (!result)
	//{
	//	return false;
	//}

	//// Reset the world matrix and setup the translation for the ground model.
	//m_GroundModel->GetPosition(posX, posY, posZ);
	///*m_D3D->GetWorldMatrix(worldMatrix);*/
	//worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	//// Render the ground model using the shadow shader.
	//m_GroundModel->Render(m_D3D->GetDeviceContext());
	//result = m_ShaderManager->RenderShadowShader(m_D3D->GetDeviceContext(), m_GroundModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
	//lightOrthoMatrix, m_GroundModel->GetTexture(), m_RenderTexture->GetShaderResourceView(), m_Light->GetDirection(),
	//	ambientColor, diffuseColor);
	//if (!result)
	//{
	//	return false;
	//}
	//m_D3D->GetWorldMatrix(worldMatrix);

	//// Translate to the position of the tree model.
	//m_Tree->GetPosition(posX, posY, posZ);
	//worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	//// Render the tree trunk.
	//m_Tree->RenderTrunk(m_D3D->GetDeviceContext());
	//m_ShaderManager->RenderShadowShader(m_D3D->GetDeviceContext(), m_Tree->GetTrunkIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
	//	lightOrthoMatrix, m_Tree->GetTrunkTexture(), m_RenderTexture->GetShaderResourceView(), m_Light->GetDirection(),
	//	ambientColor, diffuseColor);

	// Turn on alpha blending and turn off Z buffer to render 2D textures.
	m_D3D->TurnZBufferOff();

	// Put the full screen ortho window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_FullScreenWindow->Render(m_D3D->GetDeviceContext());

	// Render the full screen ortho window using the deferred light shader and the render buffers.
	m_ShaderManager->RenderLightShaderDeferred(m_D3D->GetDeviceContext(), m_FullScreenWindow->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix,
		m_DeferredBuffers->GetShaderResourceView(0), m_DeferredBuffers->GetShaderResourceView(1),
		m_Light->GetDirection());
	m_D3D->TurnOnAlphaBlending();
	/*m_Tree->RenderLeaves(m_D3D->GetDeviceContext());
	m_ShaderManager->RenderShadowShader(m_D3D->GetDeviceContext(), m_Tree->GetLeafIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
		lightOrthoMatrix, m_Tree->GetLeafTexture(), m_RenderTexture->GetShaderResourceView(), m_Light->GetDirection(),
		ambientColor, diffuseColor);*/

	//// Put the full screen ortho window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_FullScreenWindow->Render(m_D3D->GetDeviceContext());

	//// Render the full screen ortho window using the texture shader and the full screen sized blurred render to texture resource.
	//m_ShaderManager->RenderGlowShader(m_D3D->GetDeviceContext(), m_FullScreenWindow->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix,
	//	m_RenderTexture->GetShaderResourceView(), m_UpSampleTexture->GetShaderResourceView(), 3.0f);

	// Put the cursor vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_Cursor->RenderWithInstancing(m_D3D->GetDeviceContext(), mouseX, mouseY);
	if (!result)
	{
		return false;
	}

	// Render the cursor with the texture shader.
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_Cursor->GetVertexCount(), m_Cursor->GetInstanceCount(), worldMatrix, baseViewMatrix, orthoMatrix, m_Cursor->GetTexture());
	if (!result)
	{
		return false;
	}

	//// Render the text strings.
	//result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	//if (!result)
	//{
	//	return false;
	//}

	// Turn on Z buffer and turn off alpha blending now that we are all done with 2D rendering
	m_D3D->TurnOffAlphaBlending();
	m_D3D->TurnZBufferOn();

	//// Set the position of the billboard model.
	//modelPosition.x = 0.0f;
	//modelPosition.y = 0.0f;
	//modelPosition.z = 0.0f;

	//// Calculate the rotation that needs to be applied to the billboard model to face the current camera position using the arc tangent function.
	//angle = atan2(modelPosition.x - cameraPosition.x, modelPosition.z - cameraPosition.z) * (180.0 / XM_PI);

	//// Convert rotation into radians.
	//rotation = (float)angle * 0.0174532925f;

	//// Translate to back where the window model will be rendered.
	//worldMatrix = XMMatrixTranslation(0.0f, 0.0f, -1.5f);

	//// Setup the translation matrix from the billboard model.
	//translateMatrix = XMMatrixTranslation(modelPosition.x, modelPosition.y, modelPosition.z);

	//// Finally combine the rotation and translation matrices to create the final world matrix for the billboard model.
	//worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//// Put the particle system vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_ParticleSystem->Render(m_D3D->GetDeviceContext());

	//// Render the model using the texture shader.
	//result = m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetVertexCount(), m_ParticleSystem->GetCurrentParticleCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_ParticleSystem->GetTexture());
	//if (!result)
	//{
	//	return false;
	//}

	//// Put the debug window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//result = m_DebugWindow->Render(m_D3D -> GetDeviceContext(), 50, 50);
	//if (!result)
	//{
	//	return false;
	//}

	//// Render the refraction of the scene to a texture.
	//result = RenderRefractionToTexture();
	//if (!result)
	//{
	//	return false;
	//}

	//// Render the reflection of the scene to a texture.
	//result = RenderReflectionToTexture();
	//if (!result)
	//{
	//	return false;
	//}

	//// Render the scene as normal to the back buffer.
	//result = RenderScene();
	//if (!result)
	//{
	//	return false;
	//}

	//// Rotate the world matrix by the rotation value.
	//worldMatrix = XMMatrixRotationY(rotation);

	//if (m_FadeDone)
	//{
	//	// If fading in is complete then render the scene normally using the back buffer.
	//	RenderNormalScene(rotation);
	//}
	//else
	//{
	//	// If fading in is not complete then render the scene to a texture and fade that texture in.
	//	result = RenderToTexture(rotation);
	//	if (!result)
	//	{
	//		return false;
	//	}

	//	result = RenderFadingScene();
	//	if (!result)
	//	{
	//		return false;
	//	}
	//}

	//// Construct the frustum.
	//m_Frustum->ConstructFrustum(SCREEN_DEPTH, projectionMatrix, viewMatrix);

	//// Get the number of models that will be rendered.
	//modelCount = m_ModelList->GetModelCount();

	//// Initialize the count of models that have been rendered.
	//renderCount = 0;

	//// Go through all the models and render them only if they can be seen by the camera view.
	//for (index = 0; index < modelCount; index++)
	//{
	//	// Get the position and color of the sphere model at this index.
	//	m_ModelList->GetData(index, positionX, positionY, positionZ, color);

	//	// Set the radius of the sphere to 1.0 since this is already known.
	//	radius = 1.0f;

	//	// Check if the sphere model is in the view frustum.
	//	renderModel = m_Frustum->CheckSphere(positionX, positionY, positionZ, radius);

	//	// If it can be seen then render it, if not skip this model and check the next sphere.
	//	if (renderModel)
	//	{
	//		// Move the model to the location it should be rendered at.
	//		worldMatrix = XMMatrixTranslation(positionX, positionY, positionZ);

	//		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//		m_Model->Render(m_D3D->GetDeviceContext());

	//		// Render the model using the light shader.
	//		m_LightShader->RenderDiffuse(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//			m_Model->GetTexture(), m_Light->GetDirection(), color);

	//		// Reset to the original world matrix.
	//		m_D3D->GetWorldMatrix(worldMatrix);

	//		// Since this model was rendered then increase the count for this frame.
	//		renderCount++;
	//	}
	//}

	//// Set the number of models that was actually rendered this frame.
	//result = m_Text->SetRenderCount(renderCount, m_D3D->GetDeviceContext());
	//if (!result)
	//{
	//	return false;
	//}

	//// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 256, 256);
	//if (!result)
	//{
	//	return false;
	//}

	//// Render the bitmap with the texture shader.
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_DebugWindow->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_RenderTexture->GetShaderResourceView());
	//if (!result)
	//{
	//	return false;
	//}

	//// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_Model->RenderWithTessellation(m_D3D->GetDeviceContext());

	//// Render the model using the texture shader.
	//result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 12.0f);
	//if (!result)
	//{
	//	return false;
	//}

	//// Render the square model using the fire shader.
	//result = m_FireShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model->GetTextures()[0], m_Model->GetTextures()[1], m_Model->GetTextures()[2], frameTime, scrollSpeeds,
	//	scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
	//if (!result)
	//{
	//	return false;
	//}

	//// Put the floor model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_FloorModel->Render(m_D3D->GetDeviceContext());

	//// Render the model with the texture shader.
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_FloorModel->GetIndexCount(), worldMatrix, viewMatrix,
	//	projectionMatrix, m_FloorModel->GetTexture());
	//if (!result)
	//{
	//	return false;
	//}

	//// Setup the translation matrix from the billboard model.
	//translateMatrix = XMMatrixTranslation(modelPosition.x, modelPosition.y, modelPosition.z);

	//// Finally combine the rotation and translation matrices to create the final world matrix for the billboard model.
	//worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_BillboardModel->Render(m_D3D->GetDeviceContext());

	//// Put the window model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_WindowModel->Render(m_D3D->GetDeviceContext());

	//// Render the window model using the glass shader.
	//result = m_GlassShader->Render(m_D3D->GetDeviceContext(), m_WindowModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_WindowModel->GetTextures()[0], m_WindowModel->GetTextures()[1], m_RenderTexture->GetShaderResourceView(),
	//	refractionScale);
	//if (!result)
	//{
	//	return false;
	//}

	//// Translate to the right by one unit and towards the camera by one unit.
	//worldMatrix = XMMatrixTranslation(1.0f, 0.0f, -1.0f);

	//// Turn on the alpha blending before rendering the text.
	//m_D3D->TurnOnAlphaBlending();

	//// Put the second square model on the graphics pipeline.
	//m_Model1->Render(m_D3D->GetDeviceContext());

	//// Render the second square model with the stone texture and use the 50% blending amount for transparency.
	//result = m_TransparentShader->Render(m_D3D->GetDeviceContext(), m_Model1->GetIndexCount(), worldMatrix, viewMatrix,
	//	projectionMatrix, m_Model1->GetTexture(), blendAmount);
	//if (!result)
	//{
	//	return false;
	//}

	//// Render the text strings.
	//result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	//if (!result)
	//{
	//	return false;
	//}

	//// Turn off alpha blending after rendering the text.
	//m_D3D->TurnOffAlphaBlending();

	//// Turn the Z buffer back on now that all 2D rendering has completed.
	//m_D3D->TurnZBufferOn();

	//// Rotate the world matrix by the rotation value so that the triangle will spin.
	//worldMatrix = XMMatrixRotationY(rotation);

	//// Render the model using the texture shader.
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_BillboardModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_BillboardModel->GetTexture());
	//if (!result)
	//{
	//	return false;
	//}

	//// Render the model using the specular map shader.
	//m_SpecMapShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model->GetTextures(), m_Light->GetDirection(), m_Light->GetDiffuseColor(),
	//	m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	//// Render the model using the bump map shader.
	//m_BumpMapShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model->GetTextures(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

	//// Render the model using the alpha map shader.
	//m_AlphaMapShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model->GetTextures());

	//// Render the model using the light map shader.
	//m_LightMapShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model->GetTextures());

	//// Render the model using the multitexture shader.
	//m_MultiTextureShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model->GetTextures());

	//// Render the model using the light shader.
	//result = m_LightShader->RenderMultiple(m_D3D->GetDeviceContext(), m_Model0->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model0->GetTexture(), diffuseColor, lightPosition);
	//if (!result)
	//{
	//	return false;
	//}

	//// Render the model using the texture shader.
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model->GetTexture());
	//if (!result)
	//{
	//	return false;
	//}

	//// Render the model with the fog shader.
	//result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model->GetTexture(), fogStart, fogEnd);
	//if (!result)
	//{
	//	return false;
	//}

	//// Render the model with the clip plane shader.
	//result = m_ClipPlaneShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix,
	//	projectionMatrix, m_Model->GetTexture(), clipPlane);
	//if (!result)
	//{
	//	return false;
	//}

	//// Render the model with the texture translation shader.
	//result = m_TranslateShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix,
	//	projectionMatrix, m_Model->GetTexture(), textureTranslation);
	//if (!result)
	//{
	//	return false;
	//}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

void GraphicsClass::UpdateText(WPARAM wparam)
{
	if (m_Text) m_Text->UpdateString(wparam, m_D3D->GetDeviceContext());
	return;
}

bool GraphicsClass::RenderGlowMapToTexture()
{
	DXMATRIX worldMatrix, baseViewMatrix, orthoMatrix;
	bool result;


	// Set the render target to be the render to texture.
	m_RenderTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_RenderTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 100, 100);
	if (!result)
	{
		return false;
	}

	// Render the bitmap using the glow map shader.
	m_ShaderManager->RenderGlowMapShader(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix,
		m_Bitmap->GetTexture(), m_Bitmap->GetGlowMap());

	//// Turn the Z buffer back on now that all 2D rendering has completed.
	//m_D3D->TurnZBufferOn();

	//// Reset the render target back to the original back buffer and not the render to texture anymore.
	//m_D3D->SetBackBufferRenderTarget();

	//// Reset the viewport back to the original.
	//m_D3D->ResetViewport();

	return true;
}

bool GraphicsClass::RenderToTexture(float rotation)
{
	DXMATRIX worldMatrix, reflectionViewMatrix, projectionMatrix, viewMatrix;
	/*static float rotation = 0.0f;*/
	bool result;

	// Set the render target to be the render to texture.
	m_RenderTexture->SetRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView());

	// Clear the render to texture.
	m_RenderTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	//// Use the camera to calculate the reflection matrix.
	//m_Camera->RenderReflection(-1.0f);

	//// Render the scene now and it will draw to the render to texture instead of the back buffer.
	//result = RenderScene();
	//if (!result)
	//{
	//	return false;
	//}

	//// Get the camera reflection view matrix instead of the normal view matrix.
	//reflectionViewMatrix = m_Camera->GetReflectionViewMatrix();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Multiply the world matrix by the rotation.
	worldMatrix = XMMatrixRotationY(rotation);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the texture shader and the reflection view matrix.
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_Model->GetTexture());
	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	return true;
}

bool GraphicsClass::RenderFadingScene()
{
	DXMATRIX worldMatrix, viewMatrix, orthoMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and ortho matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 0, 0);
	if (!result)
	{
		return false;
	}

	// Render the bitmap using the fade shader.
	result = m_ShaderManager->RenderFadeShader(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix,
		m_RenderTexture->GetShaderResourceView(), m_fadePercentage);
	if (!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

bool GraphicsClass::RenderNormalScene(float rotation)
{
	DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Multiply the world matrix by the rotation.
	worldMatrix = XMMatrixRotationY(rotation);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model0->Render(m_D3D->GetDeviceContext());

	// Render the model with the texture shader.
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_Model0->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_Model0->GetTexture());
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

bool GraphicsClass::RenderScene()
{
	DXMATRIX worldMatrix, viewMatrix, projectionMatrix, reflectionMatrix;
	bool result;
	static float rotation = 0.0f;
	float posX, posY, posZ;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Translate to where the ground model will be rendered.
	worldMatrix = XMMatrixTranslation(0.0f, 1.0f, 0.0f);

	// Put the ground model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_GroundModel->Render(m_D3D->GetDeviceContext());

	// Render the ground model using the light shader.
	result = m_ShaderManager->RenderLightShaderAmbient(m_D3D->GetDeviceContext(), m_GroundModel->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_GroundModel->GetTexture(), m_Light0->GetDirection(),
		m_Light0->GetAmbientColor(), m_Light0->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Translate to where the wall model will be rendered.
	worldMatrix = XMMatrixTranslation(0.0f, 6.0f, 8.0f);

	// Put the wall model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_WallModel->Render(m_D3D->GetDeviceContext());

	// Render the wall model using the light shader.
	result = m_ShaderManager->RenderLightShaderAmbient(m_D3D->GetDeviceContext(), m_WallModel->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_WallModel->GetTexture(), m_Light0->GetDirection(),
		m_Light0->GetAmbientColor(), m_Light0->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Translate to where the bath model will be rendered.
	worldMatrix = XMMatrixTranslation(0.0f, 2.0f, 0.0f);

	// Put the bath model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_BathModel->Render(m_D3D->GetDeviceContext());

	// Render the bath model using the light shader.
	result = m_ShaderManager->RenderLightShaderAmbient(m_D3D->GetDeviceContext(), m_BathModel->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_BathModel->GetTexture(), m_Light0->GetDirection(),
		m_Light0->GetAmbientColor(), m_Light0->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Get the camera reflection view matrix.
	//reflectionMatrix = m_Camera->GetReflectionViewMatrix();

	// Translate to where the water model will be rendered.
	worldMatrix = XMMatrixTranslation(0.0f, m_waterHeight, 0.0f);

	// Put the water model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_WaterModel->Render(m_D3D->GetDeviceContext());

	// Render the water model using the water shader.
	/*result = m_ShaderManager->RenderWaterShader(m_D3D->GetDeviceContext(), m_WaterModel->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, reflectionMatrix, m_ReflectionTexture->GetShaderResourceView(),
		m_RefractionTexture->GetShaderResourceView(), m_WaterModel->GetTexture(),
		m_waterTranslation, 0.01f);*/
	if (!result)
	{
		return false;
	}

	//// Update the rotation variable each frame.
	//rotation += (float)XM_PI * 0.0005f;
	//if (rotation > 360.0f)
	//{
	//	rotation -= 360.0f;
	//}

	//worldMatrix = XMMatrixRotationY(rotation);

	//// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_Model0->Render(m_D3D -> GetDeviceContext());

	//// Render the model with the texture shader.
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model0->GetIndexCount(), worldMatrix, viewMatrix,
	//	projectionMatrix, m_Model0->GetTexture());
	//if (!result)
	//{
	//	return false;
	//}

	//// Get the world matrix again and translate down for the floor model to render underneath the cube.
	//m_D3D->GetWorldMatrix(worldMatrix);
	//worldMatrix = XMMatrixRotationZ(180.645f);
	//worldMatrix = worldMatrix * XMMatrixTranslation(-1.5f, 0.0f, 0.0f);

	//// Get the camera reflection view matrix.
	//reflectionMatrix = m_Camera->GetReflectionViewMatrix();

	//// Put the floor model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_Model1->Render(m_D3D->GetDeviceContext());


	//// Render the floor model using the reflection shader, reflection texture, and reflection view matrix.
	//result = m_ReflectionShader->Render(m_D3D->GetDeviceContext(), m_Model1->GetIndexCount(), worldMatrix, viewMatrix,
	//	projectionMatrix, m_Model1->GetTexture(), m_RenderTexture->GetShaderResourceView(),
	//	reflectionMatrix);

	// Render the model using the spec map shader.
	/*result = m_SpecMapShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model->GetTextures(), m_Light->GetDirection(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}*/

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

bool GraphicsClass::RenderRefractionToTexture()
{
	DXFLOAT4 clipPlane;
	DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	// Setup a clipping plane based on the height of the water to clip everything above it.
	clipPlane = DXFLOAT4(0.0f, -1.0f, 0.0f, m_waterHeight + 0.1f);

	// Set the render target to be the refraction render to texture.
	m_RefractionTexture->SetRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView());

	// Clear the refraction render to texture.
	m_RefractionTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Translate to where the bath model will be rendered.
	worldMatrix = XMMatrixTranslation(0.0f, 2.0f, 0.0f);

	// Put the bath model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_BathModel->Render(m_D3D->GetDeviceContext());

	// Render the bath model using the light shader.
	result = m_ShaderManager->RenderRefractionShader(m_D3D->GetDeviceContext(), m_BathModel->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_BathModel->GetTexture(), m_Light0->GetDirection(),
		m_Light0->GetAmbientColor(), m_Light0->GetDiffuseColor(), clipPlane);
	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	return true;
}

bool GraphicsClass::RenderReflectionToTexture()
{
	DXMATRIX reflectionViewMatrix, worldMatrix, projectionMatrix;
	bool result;

	// Set the render target to be the reflection render to texture.
	m_ReflectionTexture->SetRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView());

	// Clear the reflection render to texture.
	m_ReflectionTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Use the camera to render the reflection and create a reflection view matrix.
	m_Camera->RenderReflection(m_waterHeight);

	// Get the camera reflection view matrix instead of the normal view matrix.
	//reflectionViewMatrix = m_Camera->GetReflectionViewMatrix();

	// Get the world and projection matrices from the d3d object.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Translate to where the wall model will be rendered.
	worldMatrix = XMMatrixTranslation(0.0f, 6.0f, 8.0f);

	// Put the wall model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_WallModel->Render(m_D3D->GetDeviceContext());

	// Render the wall model using the light shader and the reflection view matrix.
	/*/result = m_ShaderManager->RenderLightShaderAmbient(m_D3D->GetDeviceContext(), m_WallModel->GetIndexCount(), worldMatrix, reflectionViewMatrix,
		projectionMatrix, m_WallModel->GetTexture(), m_Light0->GetDirection(),
		m_Light0->GetAmbientColor(), m_Light0->GetDiffuseColor());*/
	result = false;
	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	return true;
}

bool GraphicsClass::RenderSceneToTexture(RenderTextureClass* renderTexture, LightClass* light)
{
	DXMATRIX worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix, lightProjectionMatrix, lightOrthoMatrix, translateMatrix;
	float posX, posY, posZ;
	bool result;

	// Set the render target to be the render to texture.
	renderTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	renderTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Get the world matrix from the d3d object.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Generate the light view matrix based on the light's position.
	light->GenerateViewMatrix();

	// Get the view and orthographic matrices from the light object.
	light->GetViewMatrix(lightViewMatrix);
	light->GetOrthoMatrix(lightOrthoMatrix);

	// Translate to the position of the tree.
	m_Tree->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	// Render the tree trunk with the depth shader.
	m_Tree->RenderTrunk(m_D3D->GetDeviceContext());
	m_ShaderManager->RenderDepthShader(m_D3D->GetDeviceContext(), m_Tree->GetTrunkIndexCount(), worldMatrix, lightViewMatrix, lightOrthoMatrix);

	// Render the tree leaves using the depth transparency shader.
	m_Tree->RenderLeaves(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTransparentDepthShader(m_D3D->GetDeviceContext(), m_Tree->GetLeafIndexCount(), worldMatrix, lightViewMatrix,
		lightOrthoMatrix, m_Tree->GetLeafTexture());
	if (!result)
	{
		return false;
	}

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Translate to the position of the ground model.
	m_GroundModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	// Render the ground model with the depth shader.
	m_GroundModel->Render(m_D3D->GetDeviceContext());
	m_ShaderManager->RenderDepthShader(m_D3D->GetDeviceContext(), m_GroundModel->GetIndexCount(), worldMatrix, lightViewMatrix, lightOrthoMatrix);

	//// Setup the translation matrix for the cube model.
	//m_CubeModel->GetPosition(posX, posY, posZ);
	//worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	//// Render the cube model with the depth shader.
	//m_CubeModel->Render(m_D3D->GetDeviceContext());
	//result = m_ShaderManager->RenderDepthShader(m_D3D->GetDeviceContext(), m_CubeModel->GetIndexCount(), worldMatrix, lightViewMatrix, lightOrthoMatrix);
	//if (!result)
	//{
	//	return false;
	//}

	//// Reset the world matrix.
	//m_D3D->GetWorldMatrix(worldMatrix);

	//// Setup the translation matrix for the sphere model.
	//m_SphereModel->GetPosition(posX, posY, posZ);
	//translateMatrix = XMMatrixTranslation(posX, posY, posZ);
	//worldMatrix *= translateMatrix;

	//// Render the sphere model with the depth shader.
	//m_SphereModel->Render(m_D3D->GetDeviceContext());
	//result = m_ShaderManager->RenderDepthShader(m_D3D->GetDeviceContext(), m_SphereModel->GetIndexCount(), worldMatrix, lightViewMatrix, lightOrthoMatrix);
	//if (!result)
	//{
	//	return false;
	//}

	//// Reset the world matrix.
	//m_D3D->GetWorldMatrix(worldMatrix);

	//// Setup the translation matrix for the ground model.
	//m_GroundModel->GetPosition(posX, posY, posZ);
	//worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	//// Render the ground model with the depth shader.
	//m_GroundModel->Render(m_D3D->GetDeviceContext());
	//result = m_ShaderManager->RenderDepthShader(m_D3D->GetDeviceContext(), m_GroundModel->GetIndexCount(), worldMatrix, lightViewMatrix, lightOrthoMatrix);
	//if (!result)
	//{
	//	return false;
	//}

	//// Generate the view matrix based on the camera's position.
	//m_Camera->Render();

	//// Get the world, view, and projection matrices from the camera and d3d objects.
	//m_Camera->GetViewMatrix(viewMatrix);
	//m_D3D->GetWorldMatrix(worldMatrix);
	//m_D3D->GetProjectionMatrix(projectionMatrix);

	//// Rotate the world matrix by the rotation value so that the cube will spin.
	//worldMatrix = XMMatrixRotationY(rotation);

	//// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_Model->Render(m_D3D->GetDeviceContext());

	//// Render the model using the texture shader.
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model->GetTexture());
	//if (!result)
	//{
	//	return false;
	//}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return true;
}

bool GraphicsClass::RenderSceneToTexture()
{
	DXMATRIX worldMatrix, viewMatrix, projectionMatrix;

	// Set the render buffers to be the render target.
	m_DeferredBuffers->SetRenderTargets(m_D3D->GetDeviceContext());

	// Clear the render buffers.
	m_DeferredBuffers->ClearRenderTargets(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Get the matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Update the rotation variable each frame.
	static float rotation = 0.0f;
	rotation += (float)XM_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Rotate the world matrix by the rotation value so that the cube will spin.
	worldMatrix = XMMatrixRotationY(rotation);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the deferred shader.
	m_ShaderManager->RenderDeferredShader(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture());

	// Reset the render target back to the original back buffer and not the render buffers anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return true;
}

bool GraphicsClass::RenderBlackAndWhiteShadows()
{
	DXMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix;
	DXMATRIX lightViewMatrix, lightProjectionMatrix;
	float posX, posY, posZ;
	bool result;


	// Set the render target to be the render to texture.
	m_BlackWhiteRenderTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_BlackWhiteRenderTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Generate the light view matrix based on the light's position.
	m_Light0->GenerateViewMatrix();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Get the light's view and projection matrices from the light object.
	m_Light0->GetViewMatrix(lightViewMatrix);
	m_Light0->GetProjectionMatrix(lightProjectionMatrix);

	// Setup the translation matrix for the cube model.
	m_CubeModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	// Render the cube model using the shadow shader.
	m_CubeModel->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderShadowShader(m_D3D->GetDeviceContext(), m_CubeModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
		lightProjectionMatrix, m_RenderTexture->GetShaderResourceView(), m_Light0->GetPosition());
	if (!result)
	{
		return false;
	}

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Setup the translation matrix for the sphere model.
	m_SphereModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	// Render the sphere model using the shadow shader.
	m_SphereModel->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderShadowShader(m_D3D->GetDeviceContext(), m_SphereModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
		lightProjectionMatrix, m_RenderTexture->GetShaderResourceView(), m_Light0->GetPosition());
	if (!result)
	{
		return false;
	}

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Setup the translation matrix for the ground model.
	m_GroundModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	// Render the ground model using the shadow shader.
	m_GroundModel->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderShadowShader(m_D3D->GetDeviceContext(), m_GroundModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
		lightProjectionMatrix, m_RenderTexture->GetShaderResourceView(), m_Light0->GetPosition());
	if (!result)
	{
		return false;
	}

	//// Reset the render target back to the original back buffer and not the render to texture anymore.
	//m_D3D->SetBackBufferRenderTarget();

	//// Reset the viewport back to the original.
	//m_D3D->ResetViewport();

	return true;
}

bool GraphicsClass::DownSampleTexture()
{
	DXMATRIX worldMatrix, baseViewMatrix, orthoMatrix;
	bool result;


	// Set the render target to be the render to texture.
	m_DownSampleTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_DownSampleTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 1.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world and view matrices from the camera and d3d objects.
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);

	// Get the ortho matrix from the render to texture since texture has different dimensions being that it is smaller.
	m_DownSampleTexture->GetOrthoMatrix(orthoMatrix);

	//// Turn off the Z buffer to begin all 2D rendering.
	//m_D3D->TurnZBufferOff();

	// Put the small ortho window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_SmallWindow->Render(m_D3D->GetDeviceContext());

	// Render the small ortho window using the texture shader and the render to texture of the scene as the texture resource.
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_SmallWindow->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix,
		m_RenderTexture->GetShaderResourceView());
	if (!result)
	{
		return false;
	}

	//// Turn the Z buffer back on now that all 2D rendering has completed.
	//m_D3D->TurnZBufferOn();

	//// Reset the render target back to the original back buffer and not the render to texture anymore.
	//m_D3D->SetBackBufferRenderTarget();

	//// Reset the viewport back to the original.
	//m_D3D->ResetViewport();

	return true;
}

bool GraphicsClass::RenderHorizontalBlurToTexture()
{
	DXMATRIX worldMatrix, baseViewMatrix, orthoMatrix;
	float screenSizeX;
	bool result;

	// Set the render target to be the render to texture.
	m_HorizontalBlurTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_HorizontalBlurTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world and view matrices from the camera and d3d objects.
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);

	// Get the ortho matrix from the render to texture since texture has different dimensions.
	m_HorizontalBlurTexture->GetOrthoMatrix(orthoMatrix);

	//// Turn off the Z buffer to begin all 2D rendering.
	//m_D3D->TurnZBufferOff();

	// Store the screen width in a float that will be used in the horizontal blur shader.
	screenSizeX = (float)m_HorizontalBlurTexture->GetTextureWidth();

	// Put the small ortho window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_SmallWindow->Render(m_D3D->GetDeviceContext());

	// Render the small ortho window using the horizontal blur shader and the down sampled render to texture resource.
	result = m_ShaderManager->RenderHorizontalBlurShader(m_D3D->GetDeviceContext(), m_SmallWindow->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix,
		m_DownSampleTexture->GetShaderResourceView(), screenSizeX);
	if (!result)
	{
		return false;
	}

	//// Turn the Z buffer back on now that all 2D rendering has completed.
	//m_D3D->TurnZBufferOn();

	//// Reset the render target back to the original back buffer and not the render to texture anymore.
	//m_D3D->SetBackBufferRenderTarget();

	//// Reset the viewport back to the original.
	//m_D3D->ResetViewport();

	return true;
}

bool GraphicsClass::RenderVerticalBlurToTexture()
{
	DXMATRIX worldMatrix, baseViewMatrix, orthoMatrix;
	float screenSizeY;
	bool result;

	// Set the render target to be the render to texture.
	m_VerticalBlurTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_VerticalBlurTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world and view matrices from the camera and d3d objects.
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);

	// Get the ortho matrix from the render to texture since texture has different dimensions.
	m_VerticalBlurTexture->GetOrthoMatrix(orthoMatrix);

	//// Turn off the Z buffer to begin all 2D rendering.
	//m_D3D->TurnZBufferOff();

		// Store the screen height in a float that will be used in the vertical blur shader.
	screenSizeY = (float)m_VerticalBlurTexture->GetTextureHeight();

	// Put the small ortho window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_SmallWindow->Render(m_D3D->GetDeviceContext());

	// Render the small ortho window using the vertical blur shader and the horizontal blurred render to texture resource.
	result = m_ShaderManager->RenderVerticalBlurShader(m_D3D->GetDeviceContext(), m_SmallWindow->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix,
		m_HorizontalBlurTexture->GetShaderResourceView(), screenSizeY);
	if (!result)
	{
		return false;
	}

	//// Turn the Z buffer back on now that all 2D rendering has completed.
	//m_D3D->TurnZBufferOn();

	//// Reset the render target back to the original back buffer and not the render to texture anymore.
	//m_D3D->SetBackBufferRenderTarget();

	//// Reset the viewport back to the original.
	//m_D3D->ResetViewport();

	return true;
}

bool GraphicsClass::UpSampleTexture()
{
	DXMATRIX worldMatrix, baseViewMatrix, orthoMatrix;
	bool result;


	// Set the render target to be the render to texture.
	m_UpSampleTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_UpSampleTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world and view matrices from the camera and d3d objects.
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);

	// Get the ortho matrix from the render to texture since texture has different dimensions.
	m_UpSampleTexture->GetOrthoMatrix(orthoMatrix);

	//// Turn off the Z buffer to begin all 2D rendering.
	//m_D3D->TurnZBufferOff();

	// Put the full screen ortho window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_FullScreenWindow->Render(m_D3D->GetDeviceContext());

	// Render the full screen ortho window using the texture shader and the small sized final blurred render to texture resource.
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_FullScreenWindow->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix,
		m_VerticalBlurTexture->GetShaderResourceView());
	if (!result)
	{
		return false;
	}

	//// Turn the Z buffer back on now that all 2D rendering has completed.
	//m_D3D->TurnZBufferOn();

	//// Reset the render target back to the original back buffer and not the render to texture anymore.
	//m_D3D->SetBackBufferRenderTarget();

	//// Reset the viewport back to the original.
	//m_D3D->ResetViewport();

	return true;
}

bool GraphicsClass::Render2DTextureScene(int mouseX, int mouseY)
{
	DXMATRIX worldMatrix, viewMatrix, orthoMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(1.0f, 0.0f, 0.0f, 0.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and ortho matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	//// Turn off the Z buffer to begin all 2D rendering.
	//m_D3D->TurnZBufferOff();

	// Put the full screen ortho window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_FullScreenWindow->Render(m_D3D->GetDeviceContext());

	// Render the full screen ortho window using the texture shader and the full screen sized blurred render to texture resource.
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_FullScreenWindow->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix,
		m_UpSampleTexture->GetShaderResourceView());
	if (!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

bool GraphicsClass::RenderUIElementsToTexture()
{
	DXMATRIX worldMatrix, baseViewMatrix, orthoMatrix;
	bool result;


	// Set the render target to be the render to texture.
	m_RenderTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_RenderTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and ortho matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	//// Turn off the Z buffer to begin all 2D rendering.
	//m_D3D->TurnZBufferOff();

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 100, 100);
	if (!result)
	{
		return false;
	}

	// Render the bitmap using the texture shader.
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	if (!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return true;
}

bool GraphicsClass::RenderGlowScene()
{
	DXMATRIX worldMatrix, baseViewMatrix, orthoMatrix;


	//// Clear the buffers to begin the scene.
	//m_D3D->BeginScene(1.0f, 0.0f, 0.0f, 0.0f);

	//// Generate the view matrix based on the camera's position.
	//m_Camera->Render();

	// Get the world, view, and ortho matrices from the camera and d3d objects.
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	//// Turn off the Z buffer to begin all 2D rendering.
	//m_D3D->TurnZBufferOff();

	// Put the full screen ortho window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_FullScreenWindow->Render(m_D3D->GetDeviceContext());

	// Render the full screen ortho window using the texture shader and the full screen sized blurred render to texture resource.
	m_ShaderManager->RenderGlowShader(m_D3D->GetDeviceContext(), m_FullScreenWindow->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix,
		m_RenderTexture->GetShaderResourceView(), m_UpSampleTexture->GetShaderResourceView(), 3.0f);

	//// Turn the Z buffer back on now that all 2D rendering has completed.
	//m_D3D->TurnZBufferOn();

	//// Present the rendered scene to the screen.
	//m_D3D->EndScene();

	return true;
}

void GraphicsClass::TestIntersection(int mouseX, int mouseY)
{
	float pointX, pointY, posX, posY, posZ, distance, distanceTemp;
	DXMATRIX projectionMatrix, viewMatrix, inverseViewMatrix, worldMatrix, translateMatrix, inverseWorldMatrix;
	DXFLOAT3 direction, origin;
	DXVECTOR rayOrigin, rayDirection, directionVector, originVector;
	bool intersect, result;

	// Set selected model to null for now
	m_selectedModel = 0;

	// Initialize distances
	distance = -D3D11_FLOAT32_MAX;
	distanceTemp = -D3D11_FLOAT32_MAX;

	// Move the mouse cursor coordinates into the -1 to +1 range.
	pointX = ((2.0f * (float)mouseX) / (float)m_screenWidth) - 1.0f;
	pointY = (((2.0f * (float)mouseY) / (float)m_screenHeight) - 1.0f) * -1.0f;

	// Adjust the points using the projection matrix to account for the aspect ratio of the viewport.
	m_D3D->GetProjectionMatrix(projectionMatrix);
	pointX = pointX / projectionMatrix.r[0].m128_f32[0];
	pointY = pointY / projectionMatrix.r[1].m128_f32[1];

	// Get the inverse of the view matrix.
	m_Camera->GetViewMatrix(viewMatrix);
	//inverseViewMatrix = XMMatrixInverse(NULL, viewMatrix);
	// Well what do you know, this isn't really the way to do it, kinda funny Raster's code isn't 100% perfect, it's a given though I guess

	// Calculate the direction of the picking ray in view space.
	direction.x = (pointX * viewMatrix.r[0].m128_f32[0]) + (pointY * viewMatrix.r[0].m128_f32[1]) + viewMatrix.r[0].m128_f32[2];
	direction.y = (pointX * viewMatrix.r[1].m128_f32[0]) + (pointY * viewMatrix.r[1].m128_f32[1]) + viewMatrix.r[1].m128_f32[2];
	direction.z = (pointX * viewMatrix.r[2].m128_f32[0]) + (pointY * viewMatrix.r[2].m128_f32[1]) + viewMatrix.r[2].m128_f32[2];

	// Get the origin of the picking ray which is the position of the camera.
	origin = m_Camera->GetPosition();

	// Get the world matrix and translate to the location of the sphere.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_SphereModel->GetPosition(posX, posY, posZ);
	translateMatrix = XMMatrixTranslation(posX, posY, posZ);
	worldMatrix *= translateMatrix;

	// Now get the inverse of the translated world matrix.
	inverseWorldMatrix = XMMatrixInverse(NULL, worldMatrix);

	// Load the origin and direction XMFLOAT3s into XMVECTORs
	originVector = XMLoadFloat3(&origin);
	directionVector = XMLoadFloat3(&direction);

	// Now transform the ray origin and the ray direction from view space to world space.
	rayOrigin = XMVector3TransformCoord(originVector, inverseWorldMatrix);
	rayDirection = XMVector3TransformNormal(directionVector, inverseWorldMatrix);

	// Normalize the ray direction.
	/*rayDirection = XMVector3Normalize(rayDirection);*/

	// Now perform the ray-sphere intersection test.
	intersect = RaySphereIntersect(rayOrigin, rayDirection, 1.0f, distanceTemp);

	if (intersect && distanceTemp > distance)
	{
		// If it does intersect then set the intersection to "yes" in the text string that is displayed to the screen.
		distance = distanceTemp;
		result = m_Text->SetIntersection(true, m_D3D->GetDeviceContext());
		m_selectedModel = m_SphereModel;
	}
	else if (!intersect && !m_selectedModel)
	{
		// If not then set the intersection to "No".
		result = m_Text->SetIntersection(false, m_D3D->GetDeviceContext());
		m_selectedModel = 0;
	}

	// Get the world matrix and translate to the location of the sphere.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Model->GetPosition(posX, posY, posZ);
	translateMatrix = XMMatrixTranslation(posX, posY, posZ);
	worldMatrix *= translateMatrix;

	// Now get the inverse of the translated world matrix.
	inverseWorldMatrix = XMMatrixInverse(NULL, worldMatrix);

	// Now transform the ray origin and the ray direction from view space to world space.
	rayOrigin = XMVector3TransformCoord(originVector, inverseWorldMatrix);
	rayDirection = XMVector3TransformNormal(directionVector, inverseWorldMatrix);

	// Normalize the ray direction.
	/*rayDirection = XMVector3Normalize(rayDirection);*/

	// Now perform the ray-sphere intersection test.
	intersect = RaySphereIntersect(rayOrigin, rayDirection, 1.0f, distanceTemp);

	if (intersect && distanceTemp > distance)
	{
		// If it does intersect then set the intersection to "yes" in the text string that is displayed to the screen.
		distance = distanceTemp;
		result = m_Text->SetIntersection(true, m_D3D->GetDeviceContext());
		m_selectedModel = m_Model;
	}
	else if (!intersect && !m_selectedModel)
	{
		// If not then set the intersection to "No".
		result = m_Text->SetIntersection(false, m_D3D->GetDeviceContext());
		m_selectedModel = 0;
	}

	// Get the world matrix and translate to the location of the cube.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_CubeModel->GetPosition(posX, posY, posZ);
	translateMatrix = XMMatrixTranslation(posX, posY, posZ);
	worldMatrix *= translateMatrix;

	// Now get the inverse of the translated world matrix.
	inverseWorldMatrix = XMMatrixInverse(NULL, worldMatrix);

	// Now transform the ray origin and the ray direction from view space to world space.
	rayOrigin = XMVector3TransformCoord(originVector, inverseWorldMatrix);
	rayDirection = XMVector3TransformNormal(directionVector, inverseWorldMatrix);

	//// Normalize the ray direction.
	//rayDirection = XMVector3Normalize(rayDirection);

	// Now perform the ray-cube intersection test.
	intersect = RayCubeIntersect(rayOrigin, rayDirection, 1.0f);

	if (intersect && distanceTemp)
	{
		// If it does intersect then set the intersection to "yes" in the text string that is displayed to the screen.
		result = m_Text->SetIntersection(true, m_D3D->GetDeviceContext());
		m_selectedModel = m_CubeModel;
	}
	else if (!intersect && !m_selectedModel)
	{
		// If not then set the intersection to "No".
		result = m_Text->SetIntersection(false, m_D3D->GetDeviceContext());
		m_selectedModel = 0;
	}

	return;
}

bool GraphicsClass::RaySphereIntersect(DXVECTOR rayOrigin, DXVECTOR rayDirection, float radius, float& distance)
{
	float a, b, c, discriminant;


	// Calculate the a, b, and c coefficients.
	a = (rayDirection.m128_f32[0] * rayDirection.m128_f32[0]) + (rayDirection.m128_f32[1] * rayDirection.m128_f32[1]) + (rayDirection.m128_f32[2] * rayDirection.m128_f32[2]);
	b = ((rayDirection.m128_f32[0] * rayOrigin.m128_f32[0]) + (rayDirection.m128_f32[1] * rayOrigin.m128_f32[1]) + (rayDirection.m128_f32[2] * rayOrigin.m128_f32[2])) * 2.0f;
	c = ((rayOrigin.m128_f32[0] * rayOrigin.m128_f32[0]) + (rayOrigin.m128_f32[1] * rayOrigin.m128_f32[1]) + (rayOrigin.m128_f32[2] * rayOrigin.m128_f32[2])) - (radius * radius);

	// Find the discriminant.
	discriminant = (b * b) - (4 * a * c);

	// If discriminant is negative and the picking ray missed the sphere, otherwise it intersected the sphere.
	// Also, if the b cofactor is positive that means the ray is shooting towards the viewer, hence the sphere is behind FOV. 
	if (discriminant < 0.0f || b > 0.0f)
	{
		return false;
	}

	distance = b;
	return true;
}

bool GraphicsClass::RayCubeIntersect(DXVECTOR rayOrigin, DXVECTOR rayDirection, float edge)
{
	// Final code
	// Camera relative min-max cube selection, probably has shit performance but has to do for now
	float xmin, xmax, ymin, ymax, zmin, zmax;
	float distance, direction, angle;

	// Determine distance
	// Maybe we could use the camera rotation later on to determine the axis we're looking along faster down the line?
	// Calculate x-z axis angle first
	distance = atan2f(rayOrigin.m128_f32[2] * rayDirection.m128_f32[2], rayOrigin.m128_f32[0] * rayDirection.m128_f32[0]) * 180.0f / XM_PI;
	if (distance <= 135.0f && distance >= 45.0f)
	{
		distance = rayOrigin.m128_f32[2];
		direction = -rayDirection.m128_f32[2];
	}
	else if (distance <= 45.0f && distance >= -45.0f)
	{
		distance = rayOrigin.m128_f32[0];
		direction = -rayDirection.m128_f32[0];
	}
	else if (distance <= -45.0f && distance >= -135.0f)
	{
		distance = -rayOrigin.m128_f32[2];
		direction = rayDirection.m128_f32[2];
	}
	else
	{
		distance = -rayOrigin.m128_f32[0];
		direction = rayDirection.m128_f32[0];
	}
	
	// Calculate the relative distance and y-axis now
	angle = atan2f(rayOrigin.m128_f32[1] * rayDirection.m128_f32[1], distance * direction) * 180.0f / XM_PI;
	if (angle <= 135.0f && angle >= 45.0f)
	{
		distance = rayOrigin.m128_f32[1];
		direction = -rayDirection.m128_f32[1];
	}
	else if (angle <= -45.0f && angle >= -135.0f)
	{
		distance = -rayOrigin.m128_f32[1];
		direction = rayDirection.m128_f32[1];
	}

	// Calculate the minimum and maximum possible coordinates where the ray could exist at distance tmin and tmax
	xmin = rayOrigin.m128_f32[0] + (distance - edge) * (rayDirection.m128_f32[0] / direction);
	xmax = rayOrigin.m128_f32[0] + (distance + edge) * (rayDirection.m128_f32[0] / direction);
	if (((xmin < -edge) || (xmin > edge)) && ((xmax < -edge) || (xmax > edge))) return false;
	zmin = rayOrigin.m128_f32[2] + (distance - edge) * (rayDirection.m128_f32[2] / direction);
	zmax = rayOrigin.m128_f32[2] + (distance + edge) * (rayDirection.m128_f32[2] / direction);
	if (((zmin < -edge) || (zmin > edge)) && ((zmax < -edge) || (zmax > edge))) return false;
	ymin = rayOrigin.m128_f32[1] + (distance - edge) * (rayDirection.m128_f32[1] / direction);
	ymax = rayOrigin.m128_f32[1] + (distance + edge) * (rayDirection.m128_f32[1] / direction);
	if (((ymin < -edge) || (ymin > edge)) && ((ymax < -edge) || (ymax > edge))) return false;

	//// Check if minimum or maximum possible collision coordinates of the ray are within the boundaries of the cube
	//if (((xmin >= -edge) && (xmin <= edge)) && ((ymin >= -edge) && (ymin <= edge)) && ((zmin >= -edge) && (zmin <= edge)))
	//	return true;
	//if (((xmax >= -edge) && (xmax <= edge)) && ((ymax >= -edge) && (ymax <= edge)) && ((zmax >= -edge) && (zmax <= edge)))
	//	return true;

	// Failed code
	/*FAILED CODE BEGIN*/
	/*float signX, signY, signZ;*/
	//// Set up sign factors
	//signX = rayDirection.m128_f32[0] > 0.0f ? 1.0f : -1.0f;
	//signY = rayDirection.m128_f32[1] > 0.0f ? 1.0f : -1.0f;
	//signZ = rayDirection.m128_f32[2] > 0.0f ? 1.0f : -1.0f;
	// 
	// I need to crank down maths for this it seems huh...
	//float temp, temp2, temp3;
	//temp = (-rayOrigin.m128_f32[0] - edge) / -rayOrigin.m128_f32[2];
	//temp2 = (-rayOrigin.m128_f32[0] - edge) / (-rayOrigin.m128_f32[2] * XM_PI);
	//temp3 = (-rayOrigin.m128_f32[0] - edge) / (-rayOrigin.m128_f32[2] * XM_PI);
	//if (rayDirection.m128_f32[0] > (-rayOrigin.m128_f32[0] - edge) / (-rayOrigin.m128_f32[2] * XM_PI) &&
	//	rayDirection.m128_f32[0] < (-rayOrigin.m128_f32[0] + edge) / (-rayOrigin.m128_f32[2] * XM_PI) &&
	//	rayDirection.m128_f32[1] > (-rayOrigin.m128_f32[1] - edge) / (-rayOrigin.m128_f32[2] * XM_PI) &&
	//	rayDirection.m128_f32[1] < (-rayOrigin.m128_f32[1] + edge) / (-rayOrigin.m128_f32[2] * XM_PI))
	//	return true;
	//// Paitone, Gen 3 2D intersection
	//if (rayDirection.m128_f32[0] > (-rayOrigin.m128_f32[0] - edge) / -rayOrigin.m128_f32[2] && rayDirection.m128_f32[0] < (-rayOrigin.m128_f32[0] + edge) / -rayOrigin.m128_f32[2] &&
	//	rayDirection.m128_f32[1] > (-rayOrigin.m128_f32[1] - edge) / -rayOrigin.m128_f32[2] && rayDirection.m128_f32[1] < (-rayOrigin.m128_f32[1] + edge) / -rayOrigin.m128_f32[2])
	//	return true;
	// P = orig + t * dir
	// 
	// I will approach this by calculating the positions at the minimum boundaries of the cube, indiviually

	// From P = orig + t * dir, we'll indiviually calculate positions with (orig +- edge) * dir
	// Note that our origins are reversed, so they will always be multiplied by negative
	// Also, we'll swap the coordinates around if they are reverse
	// The values need to preserve their sign as well and need to be the same and the sign of direction
	/*xmin = (edge - rayOrigin.m128_f32[0]) * rayDirection.m128_f32[0];
	xmax = (-rayOrigin.m128_f32[0] - edge) * rayDirection.m128_f32[0];
	if (xmin > xmax) swap(xmin, xmax);
	ymin = (edge - rayOrigin.m128_f32[1]) * rayDirection.m128_f32[1];
	ymax = (-rayOrigin.m128_f32[1] - edge) * rayDirection.m128_f32[1];
	if (ymin > ymax) swap(ymin, ymax);
	zmin = (edge - rayOrigin.m128_f32[2]) * rayDirection.m128_f32[2];
	zmax = (-rayOrigin.m128_f32[2] - edge) * rayDirection.m128_f32[2];
	if (zmin > zmax) swap(zmin, zmax);*/

	//// No no... the distance dammit?
	//xmin = (sqrtf((edge - rayOrigin.m128_f32[1]) * (edge - rayOrigin.m128_f32[1]) + (edge - rayOrigin.m128_f32[2]) * (edge - rayOrigin.m128_f32[2]))) * rayDirection.m128_f32[0] * -signX;
	//xmax = (sqrtf((edge - rayOrigin.m128_f32[1]) * (edge - rayOrigin.m128_f32[1]) + (edge - rayOrigin.m128_f32[2]) * (edge - rayOrigin.m128_f32[2]))) * rayDirection.m128_f32[0] * signX;
	//ymin = (sqrtf((edge - rayOrigin.m128_f32[0]) * (edge - rayOrigin.m128_f32[0]) + (edge - rayOrigin.m128_f32[2]) * (edge - rayOrigin.m128_f32[2]))) * rayDirection.m128_f32[1] * -signY;
	//ymax = (sqrtf((edge - rayOrigin.m128_f32[0]) * (edge - rayOrigin.m128_f32[0]) + (edge - rayOrigin.m128_f32[2]) * (edge - rayOrigin.m128_f32[2])))* rayDirection.m128_f32[1] * signY;
	//zmin = (sqrtf((edge - rayOrigin.m128_f32[0]) * (edge - rayOrigin.m128_f32[0]) + (edge - rayOrigin.m128_f32[1]) * (edge - rayOrigin.m128_f32[1]))) * rayDirection.m128_f32[2] * -signZ;
	//zmax = (sqrtf((edge - rayOrigin.m128_f32[0]) * (edge - rayOrigin.m128_f32[0]) + (edge - rayOrigin.m128_f32[1]) * (edge - rayOrigin.m128_f32[1]))) * rayDirection.m128_f32[2] * signZ;

	//// Let's go step-by-step and don't overcomplicate things, we'll start by implementing x, y and z-axises respectively
	//	xmin = rayOrigin.m128_f32[0] + (distance - edge) * (rayDirection.m128_f32[0] / direction);
	//xmax = rayOrigin.m128_f32[0] + (distance + edge) * (rayDirection.m128_f32[0] / direction);
	////if (xmin > xmax) swap(xmin, xmax);
	//ymin = rayOrigin.m128_f32[1] + (distance - edge) * (rayDirection.m128_f32[1] / direction);
	//ymax = rayOrigin.m128_f32[1] + (distance + edge) * (rayDirection.m128_f32[1] / direction);
	////if (ymin > ymax) swap(ymin, ymax);
	// y is a weirdo and uses the pythagorean distance between x and z distances
	// Note to thyself Paitone, the y-axis angle needs to be calculated individually
	// Nope, it will influence the x-z axis distances so need to think on this further
	/*ymin = rayOrigin.m128_f32[1] + (distance == abs(rayOrigin.m128_f32[1]) ?
		distance - edge : (sqrtf(powf(rayOrigin.m128_f32[0] - edge, 2) + powf(rayOrigin.m128_f32[2] - edge, 2)))) * (rayDirection.m128_f32[1] / direction);
	ymax = rayOrigin.m128_f32[1] + (distance == abs(rayOrigin.m128_f32[1]) ?
		distance + edge : (sqrtf(powf(rayOrigin.m128_f32[0] + edge, 2) + powf(rayOrigin.m128_f32[2] + edge, 2)))) * (rayDirection.m128_f32[1] / direction);*/
		/*ymin = rayOrigin.m128_f32[1] + (distance == abs(rayOrigin.m128_f32[1]) ?
			distance - edge : (sqrtf(powf(rayOrigin.m128_f32[0] - xmin, 2) + powf(rayOrigin.m128_f32[2] - zmin, 2)))) * (rayDirection.m128_f32[1] / (rayDirection.m128_f32[0] * rayDirection.m128_f32[2]));
		ymax = rayOrigin.m128_f32[1] + (distance == abs(rayOrigin.m128_f32[1]) ?
			distance + edge : (sqrtf(powf(rayOrigin.m128_f32[0] - xmax, 2) + powf(rayOrigin.m128_f32[2] - zmax, 2)))) * (rayDirection.m128_f32[1] / (rayDirection.m128_f32[0] * rayDirection.m128_f32[2]));*/
			/*ymin = rayOrigin.m128_f32[1] + (distance == abs(rayOrigin.m128_f32[1]) ?
				distance - edge : distance - zmin) * (rayDirection.m128_f32[1]);
			ymax = rayOrigin.m128_f32[1] + (distance == abs(rayOrigin.m128_f32[1]) ?
				distance + edge : distance - zmax) * (rayDirection.m128_f32[1]);*/
	//// This will need some trigonometry, I need to figure the angle of projecting ray here
	//// Or maybe, just the X distance of the origin will do, we'll see
	//// Z distance?
	//// Isn't the factor always one (direction factor)?
	//// The answer lies here, the way I implement this when the origin is almost perfectly aligned to Z is the key to solving all the problems
	//zmin = rayOrigin.m128_f32[2] + (distance - edge) * (rayDirection.m128_f32[2] / direction);
	//zmax = rayOrigin.m128_f32[2] + (distance + edge) * (rayDirection.m128_f32[2] / direction);
	////if (zmin > zmax) swap(zmin, zmax);

	// The ray might not intersect with near face but it might shoot through the back face of the cube,
	// so we are bailing out if the front face is never hit
	// Nvm, a 3D cube will show its side face from front
	// Do we actually need to calculate the max values ever then..?
	// I can't stress how important greater or less than EQUALs are important because they mean that we have inch perfect intersections
	// Especially true if we are at a position where we are looking perfectly across X, Y or Z-axis
	/*if (((xmin >= -edge) && (xmin <= edge)) && ((ymin >= -edge) && (ymin <= edge)) && ((zmin >= -edge) && (zmin <= edge)))
		return true;
	if (((xmax >= -edge) && (xmax <= edge)) && ((ymax >= -edge) && (ymax <= edge)) && ((zmax >= -edge) && (zmax <= edge)))
		return true;*/
	/*FAILED CODE END*/

	return true;
}

void GraphicsClass::UpdateLighting(LightClass* light, float frameTime)
{
	static float angle = 270.0f;
	float radians;
	static float offsetX = 9.0f;


	// Update direction of the light.
	angle -= 0.03f * frameTime;
	if (angle < 90.0f)
	{
		angle = 270.0f;
		offsetX = 9.0f;
	}
	radians = angle * 0.0174532925f;
	light->SetDirection(sinf(radians), cosf(radians), 0.0f);

	// Update the lookat and position.
	offsetX -= 0.003f * frameTime;
	light->SetPosition(0.0f + offsetX, 10.0f, 1.0f);
	light->SetLookAt(0.0f - offsetX, 0.0f, 2.0f);

	return;
}