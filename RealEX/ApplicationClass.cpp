////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "applicationclass.h"

ApplicationClass::ApplicationClass()
{
	m_Input = 0;
	m_Direct3D = 0;
	m_Camera = 0;
	m_Terrain = 0;
	m_ShaderManager = 0;
	m_Timer = 0;
	m_Position = 0;
	m_Fps = 0;
	m_Cpu = 0;
	m_FontShader = 0;
	m_Text = 0;
	m_Cursor = 0;
	m_Light = 0;
	m_Frustum = 0;
	m_QuadTree = 0;
	m_MiniMap = 0;
	m_SkyDome = 0;
	m_SkyPlane = 0;
	m_Sound = 0;
	m_DebugWindow = 0;
	m_RenderTexture = 0;
	m_RefractionTexture = 0;
	m_ReflectionTexture = 0;
	m_Water = 0;
}

ApplicationClass::ApplicationClass(const ApplicationClass& other)
{
}


ApplicationClass::~ApplicationClass()
{
}


bool ApplicationClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;
	float cameraX, cameraY, cameraZ;
	DXMATRIX baseViewMatrix;
	char videoCard[128];
	int videoMemory;
	int terrainWidth, terrainHeight;

	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_Direct3D = new D3DClass;
	if (!m_Direct3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize DirectX 11.", L"Error", MB_OK);
		return false;
	}

	// Create the color shader object.
	m_ShaderManager = new ShaderManagerClass;
	if (!m_ShaderManager)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ShaderManager->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	// Set the initial position.
	m_Position->SetPosition(14.0f, 13.0f, 10.0f);
	m_Position->SetRotation(25.0f, 0.0f, 0.0f);

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->Render();
	m_Camera->RenderBaseViewMatrix();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the terrain object.
	m_Terrain = new TerrainClass;
	if (!m_Terrain)
	{
		return false;
	}

	// Initialize the terrain object.
	result = m_Terrain->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), (char*)"../RealEX/terrain/heightmap02.bmp", (char*) "../RealEX/terrain/colorm01.bmp",
		10.0f, (char*) "../RealEX/textures/ground_earth.tga", (char*) "../RealEX/terrain/detail001.tga", (char*)"../RealEX/terrain/ground_earth_bump.tga");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	// Create the fps object.
	m_Fps = new FpsClass;
	if (!m_Fps)
	{
		return false;
	}

	// Initialize the fps object.
	m_Fps->Initialize();

	// Create the cpu object.
	m_Cpu = new CpuClass;
	if (!m_Cpu)
	{
		return false;
	}

	// Initialize the cpu object.
	m_Cpu->Initialize();

	// Create the font shader object.
	m_FontShader = new FontShaderClass;
	if (!m_FontShader)
	{
		return false;
	}

	// Initialize the font shader object.
	result = m_FontShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	// Retrieve the video card information.
	m_Direct3D->GetVideoCardInfo(videoCard, videoMemory);

	// Set the video card information in the text object.
	result = m_Text->SetVideoCardInfo(videoCard, videoMemory, m_Direct3D->GetDeviceContext());
	if (!result)
	{
		MessageBox(hwnd, L"Could not set video card info in the text object.", L"Error", MB_OK);
		return false;
	}

	// Create the cursor object.
	m_Cursor = new BitmapClass;
	if (!m_Cursor)
	{
		return false;
	}

	// Initialize the cursor object.
	result = m_Cursor->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, (char*)"../RealEX/textures/cursor.tga", 32, 32);
	if (!result)
	{
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.05f, 0.05f, 0.05f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.5f, -0.75f, 0.0f);

	// Create the frustum object.
	m_Frustum = new FrustumClass;
	if (!m_Frustum)
	{
		return false;
	}

	// Create the quad tree object.
	m_QuadTree = new QuadTreeClass;
	if (!m_QuadTree)
	{
		return false;
	}

	// Initialize the quad tree object.
	result = m_QuadTree->Initialize(m_Terrain, m_Direct3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the quad tree object.", L"Error", MB_OK);
		return false;
	}

	// Create the debug window bitmap object.
	m_DebugWindow = new DebugWindowClass;
	if (!m_DebugWindow)
	{
		return false;
	}

	// Initialize the debug window bitmap object.
	result = m_DebugWindow->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, 256, 256);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the debug window bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Create the render to texture object.
	m_RenderTexture = new RenderTextureClass;
	if (!m_RenderTexture)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = m_RenderTexture->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the refraction render to texture object.
	m_RefractionTexture = new RenderTextureClass;
	if (!m_RefractionTexture)
	{
		return false;
	}

	// Initialize the refraction render to texture object.
	result = m_RefractionTexture->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the refraction render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the reflection render to texture object.
	m_ReflectionTexture = new RenderTextureClass;
	if (!m_ReflectionTexture)
	{
		return false;
	}

	// Initialize the reflection render to texture object.
	result = m_ReflectionTexture->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the reflection render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Get the size of the terrain as the minimap will require this information.
	m_Terrain->GetTerrainSize(terrainWidth, terrainHeight);

	// Create the mini map object.
	m_MiniMap = new MiniMapClass;
	if (!m_MiniMap)
	{
		return false;
	}

	// Initialize the mini map object.
	result = m_MiniMap->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix, (float)(terrainWidth - 1),
		(float)(terrainHeight - 1));
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the mini map object.", L"Error", MB_OK);
		return false;
	}

	// Create the sky dome object.
	m_SkyDome = new SkyDomeClass;
	if (!m_SkyDome)
	{
		return false;
	}

	// Initialize the sky dome object.
	result = m_SkyDome->Initialize(m_Direct3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome object.", L"Error", MB_OK);
		return false;
	}

	// Create the sky plane object.
	m_SkyPlane = new SkyPlaneClass;
	if (!m_SkyPlane)
	{
		return false;
	}

	// Initialize the sky plane object.
	result = m_SkyPlane->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), (char*)"../RealEX/textures/cloud001.tga", (char*) "../RealEX/textures/cloud002.tga",
		(char*)"../RealEX/textures/perturb001.tga");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky plane object.", L"Error", MB_OK);
		return false;
	}

	//// Create the water object.
	//m_Water = new WaterClass;
	//if (!m_Water)
	//{
	//	return false;
	//}

	//// Initialize the water object.
	//result = m_Water->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), (char*) "../RealEX/textures/waternormal.tga", 3.75f, 110.0f);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the water object.", L"Error", MB_OK);
	//	return false;
	//}

	// Create the sound object.
	m_Sound = new SoundClass;
	if (!m_Sound)
	{
		return false;
	}

	// Initialize the sound object.
	result = m_Sound->Initialize(hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sound object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void ApplicationClass::Shutdown()
{
	// Release the water object.
	if (m_Water)
	{
		m_Water->Shutdown();
		delete m_Water;
		m_Water = 0;
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

	// Release the render to texture object.
	if (m_RenderTexture)
	{
		m_RenderTexture->Shutdown();
		delete m_RenderTexture;
		m_RenderTexture = 0;
	}

	// Release the debug window bitmap object.
	if (m_DebugWindow)
	{
		m_DebugWindow->Shutdown();
		delete m_DebugWindow;
		m_DebugWindow = 0;
	}

	// Release the sky dome object.
	if (m_SkyPlane)
	{
		m_SkyPlane->Shutdown();
		delete m_SkyPlane;
		m_SkyPlane = 0;
	}

	// Release the sky dome object.
	if (m_SkyDome)
	{
		m_SkyDome->Shutdown();
		delete m_SkyDome;
		m_SkyDome = 0;
	}

	// Release the mini map object.
	if (m_MiniMap)
	{
		m_MiniMap->Shutdown();
		delete m_MiniMap;
		m_MiniMap = 0;
	}

	// Release the quad tree object.
	if (m_QuadTree)
	{
		m_QuadTree->Shutdown();
		delete m_QuadTree;
		m_QuadTree = 0;
	}

	// Release the frustum object.
	if (m_Frustum)
	{
		delete m_Frustum;
		m_Frustum = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the font shader object.
	if (m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}

	// Release the cpu object.
	if (m_Cpu)
	{
		m_Cpu->Shutdown();
		delete m_Cpu;
		m_Cpu = 0;
	}

	// Release the fps object.
	if (m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}

	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the color shader object.
	if (m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the terrain object.
	if (m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the Direct3D object.
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	// Release the input object.
	if (m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}

	return;
}

bool ApplicationClass::Frame()
{
	bool result, foundHeight;
	DXFLOAT3 position;
	float height;

	// Read the user input.
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	// Update the system stats.
	m_Timer->Frame();
	m_Fps->Frame();
	m_Cpu->Frame();

	// Update the FPS value in the text object.
	result = m_Text->SetFps(m_Fps->GetFps(), m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Update the CPU usage value in the text object.
	result = m_Text->SetCpu(m_Cpu->GetCpuPercentage(), m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Do the frame input processing.
	result = HandleInput(m_Timer->GetTime());
	if (!result)
	{
		return false;
	}

	// Do the water frame processing.
	//m_Water->Frame();

	// Do the sky plane frame processing.
	m_SkyPlane->Frame(m_Timer->GetTime());

	// Get the current position of the camera.
	position = m_Camera->GetPosition();

	// Get the height of the triangle that is directly underneath the given camera position.
	foundHeight = m_QuadTree->GetHeightAtPosition(position.x, position.z, height);
	if (foundHeight)
	{
		// If there was a triangle under the camera then position the camera at least two units above.
		m_Camera->SetPosition(position.x, max(position.y, height + 2.0f), position.z);
	}

	// Render the graphics.
	result = RenderGraphics();
	if (!result)
	{
		return false;
	}

	return result;
}

bool ApplicationClass::HandleInput(float frameTime)
{
	bool keyDown, leftClickState, result;
	float posX, posY, posZ, rotX, rotY, rotZ;
	int mouseX, mouseY;

	// Get the location of the mouse from the input object.
	m_Input->GetMouseLocation(mouseX, mouseY);

	// Get the left mouse button click state.
	leftClickState = m_Input->IsLeftMouseButtonDown();

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(m_Timer->GetTime());

	// Check if movement keys are being pressed, and move the cam accordingly
	keyDown = m_Input->IsKeyDown('A');
	m_Position->MoveLeft(keyDown);

	keyDown = m_Input->IsKeyDown('D');
	m_Position->MoveRight(keyDown);

	keyDown = m_Input->IsKeyDown('W');
	m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsKeyDown('S');
	m_Position->MoveBackward(keyDown);

	keyDown = m_Input->IsKeyDown(VK_PRIOR);
	m_Position->MoveUp(keyDown);

	keyDown = m_Input->IsKeyDown(VK_NEXT);
	m_Position->MoveDown(keyDown);

	keyDown = m_Input->IsKeyDown(VK_LEFT);
	m_Position->TurnLeft(keyDown);

	keyDown = m_Input->IsKeyDown(VK_RIGHT);
	m_Position->TurnRight(keyDown);

	keyDown = m_Input->IsKeyDown(VK_UP);
	m_Position->TurnUp(keyDown);

	keyDown = m_Input->IsKeyDown(VK_DOWN);
	m_Position->TurnDown(keyDown);

	// Get the current view point rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	// Update the position values in the text object.
	result = m_Text->SetCameraPosition(posX, posY, posZ, m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Update the rotation values in the text object.
	result = m_Text->SetCameraRotation(rotX, rotY, rotZ, m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Update the position of listener in sound system.
	result = m_Sound->Frame(posX, posY, posZ, leftClickState);
	if (!result)
	{
		return false;
	}

	// Update the location of the camera on the mini map.
	m_MiniMap->PositionUpdate(posX, posZ);

	return true;
}

bool ApplicationClass::RenderGraphics()
{
	DXMATRIX worldMatrix, viewMatrix, baseViewMatrix, projectionMatrix, orthoMatrix, reflectionViewMatrix;
	DXFLOAT3 cameraPos;
	bool result;
	int mouseX, mouseY;
	static float time = 0;
	ID3D11ShaderResourceView* textureArray[3];

	//// First render the scene to a texture.
	//result = RenderSceneToTexture();
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

	// Get mouse location from input system.
	m_Input->GetMouseLocation(mouseX, mouseY);

	// Clear the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Generate the reflection matrix based on the camera's position and the height of the water.
	//m_Camera->RenderReflection(m_Water->GetWaterHeight());

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);
	//m_Camera->GetReflectionViewMatrix(reflectionViewMatrix);

	// Get the position of the camera.
	cameraPos= m_Camera->GetPosition();

	// Translate the sky dome to be centered around the camera position.
	worldMatrix = XMMatrixTranslation(cameraPos.x, cameraPos.y, cameraPos.z);

	// Turn off back face culling.
	m_Direct3D->TurnOffBackCulling();

	// Turn off the Z buffer.
	m_Direct3D->TurnZBufferOff();

	// Render the sky dome using the sky dome shader.
	m_SkyDome->Render(m_Direct3D->GetDeviceContext(), time / 1000);
	result = m_ShaderManager->RenderSkyDomeShader(m_Direct3D->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());
	if (!result)
	{
		return false;
	}
	time+=m_Timer->GetTime() * 0.01f;
	if (time > 24000) time = 0;

	// Turn back face culling back on.
	m_Direct3D->TurnOnBackCulling();

	// Enable additive blending so the clouds blend with the sky dome color.
	m_Direct3D->EnableAdditiveBlendState();

	// Render the sky plane using the sky plane shader.
	m_SkyPlane->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderSkyPlaneShader(m_Direct3D->GetDeviceContext(), m_SkyPlane->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_SkyPlane->GetCloudTexture0(), m_SkyPlane->GetCloudTexture1(), m_SkyPlane->GetPerturbTexture(), m_SkyPlane->GetFirstTranslation(), m_SkyPlane->GetSecondTranslation(),
		m_SkyPlane->GetScale(), m_SkyPlane->GetBrightness());
	if (!result)
	{
		return false;
	}

	// Turn off blending.
	m_Direct3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on.
	m_Direct3D->TurnZBufferOn();

	// Reset the world matrix.
	m_Direct3D->GetWorldMatrix(worldMatrix);

	// Construct the frustum.
	m_Frustum->ConstructFrustum(SCREEN_DEPTH, projectionMatrix, viewMatrix);

	// Send the matrices, lighting and textures to the quad tree object.
	m_QuadTree->SetShaderParameters(worldMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(),
		m_Light->GetDiffuseColor(), m_Light->GetDirection());

	// Set up the texture array to send into quad tree object.
	textureArray[0] = m_Terrain->GetTexture();
	textureArray[1] = m_Terrain->GetDetailMapTexture();
	textureArray[2] = m_Terrain->GetNormalMapTexture();

	// Send the texture array to quad tree object.
	m_QuadTree->InitializeTextureArray(textureArray, 3);

	// Render the terrain using the quad tree and terrain shader.
	m_QuadTree->Render(m_Frustum, m_Direct3D->GetDeviceContext(), m_ShaderManager, cameraPos);

	// Set the number of rendered terrain triangles since some were culled.
	result = m_Text->SetRenderCount(m_QuadTree->GetDrawCount(), m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	//// Translate to the location of the water and render it.
	//worldMatrix = XMMatrixTranslation(240.0f, m_Water->GetWaterHeight(), 250.0f);
	//m_Water->Render(m_Direct3D->GetDeviceContext());
	//m_ShaderManager->RenderWaterShader(m_Direct3D->GetDeviceContext(), m_Water->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, reflectionViewMatrix,
	//	m_RefractionTexture->GetShaderResourceView(), m_ReflectionTexture->GetShaderResourceView(), m_Water->GetTexture(),
	//	m_Camera->GetPosition(), m_Water->GetNormalMapTiling(), m_Water->GetWaterTranslation(), m_Water->GetReflectRefractScale(),
	//	m_Water->GetRefractionTint(), m_Light->GetDirection(), m_Water->GetSpecularShininess());

	//// Reset the world matrix.
	//m_Direct3D->GetWorldMatrix(worldMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_Direct3D->TurnZBufferOff();

	//// Put the debug window on the graphics pipeline to prepare it for drawing.
	//result = m_DebugWindow->Render(m_Direct3D->GetDeviceContext(), 520, 320);
	//if (!result)
	//{
	//	return false;
	//}

	//// Render the bitmap model using the texture shader and the render to texture resource.
	//result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_DebugWindow->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix,
	//	m_RenderTexture->GetShaderResourceView());
	//if (!result)
	//{
	//	return false;
	//}

	// Render the mini map.
	result = m_MiniMap->Render(m_Direct3D->GetDeviceContext(), worldMatrix, orthoMatrix, m_ShaderManager);
	if (!result)
	{
		return false;
	}

	// Turn on the alpha blending before rendering the text.
	m_Direct3D->TurnOnAlphaBlending();

	// Render the cursor.
	result = m_Cursor->RenderWithInstancing(m_Direct3D->GetDeviceContext(), mouseX, mouseY);
	if (!result)
	{
		return false;
	}

	// Render the cursor with the texture shader.
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Cursor->GetVertexCount(), m_Cursor->GetInstanceCount(), worldMatrix, baseViewMatrix,
		orthoMatrix, m_Cursor->GetTexture());
	if (!result)
	{
		return false;
	}

	// Render the text user interface elements.
	result = m_Text->Render(m_Direct3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_Direct3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_Direct3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}

bool ApplicationClass::RenderSceneToTexture()
{
	DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;


	// Set the render target to be the render to texture.
	m_RenderTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());

	// Clear the render to texture.
	m_RenderTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, projection, ortho, and base view matrices from the camera and Direct3D objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	// Render the terrain using the depth shader.
	m_Terrain->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderDepthShader(m_Direct3D->GetDeviceContext(), m_Terrain->GetMedQualityIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_Direct3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_Direct3D->ResetViewport();

	return true;
}

bool ApplicationClass::RenderReflectionToTexture()
{
	DXFLOAT4 clipPlane;
	DXMATRIX reflectionViewMatrix, worldMatrix, projectionMatrix;
	DXFLOAT3 cameraPosition;
	bool result;

	// Setup a clipping plane based on the height of the water to clip everything below it.
	clipPlane = DXFLOAT4(0.0f, 1.0f, 0.0f, -m_Water->GetWaterHeight());

	// Set the render target to be the reflection render to texture.
	m_ReflectionTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());

	// Clear the reflection render to texture.
	m_ReflectionTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Use the camera to render the reflection and create a reflection view matrix.
	m_Camera->RenderReflection(m_Water->GetWaterHeight());

	// Get the camera reflection view matrix instead of the normal view matrix.
	m_Camera->GetReflectionViewMatrix(reflectionViewMatrix);

	// Get the world and projection matrices from the d3d object.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	// Get the position of the camera.
	cameraPosition = m_Camera->GetPosition();

	// Invert the Y coordinate of the camera around the water plane height for the reflected camera position.
	cameraPosition.y = -cameraPosition.y + (m_Water->GetWaterHeight() * 2.0f);

	// Translate the sky dome and sky plane to be centered around the reflected camera position.
	worldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	// Turn off back face culling and the Z buffer.
	m_Direct3D->TurnOffBackCulling();
	m_Direct3D->TurnZBufferOff();

	// Render the sky dome using the reflection view matrix.
	m_SkyDome->Render(m_Direct3D->GetDeviceContext(), m_SkyDome->GetIndexCount());
	result = m_ShaderManager->RenderSkyDomeShader(m_Direct3D->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix,
		m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());
	if (!result)
	{
		return false;
	}

	// Enable back face culling.
	m_Direct3D->TurnOnBackCulling();

	// Enable additive blending so the clouds blend with the sky dome color.
	m_Direct3D->EnableAdditiveBlendState();

	// Render the sky plane using the sky plane shader.
	m_SkyPlane->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderSkyPlaneShader(m_Direct3D->GetDeviceContext(), m_SkyPlane->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix,
		m_SkyPlane->GetCloudTexture0(), m_SkyPlane->GetCloudTexture1(), m_SkyPlane->GetPerturbTexture(), m_SkyPlane->GetFirstTranslation(), m_SkyPlane->GetSecondTranslation(),
		m_SkyPlane->GetScale(), m_SkyPlane->GetBrightness());
	if (!result)
	{
		return false;
	}

	// Turn off blending and enable the Z buffer again.
	m_Direct3D->TurnOffAlphaBlending();
	m_Direct3D->TurnZBufferOn();

	// Reset the world matrix.
	m_Direct3D->GetWorldMatrix(worldMatrix);

	// Render the terrain using the reflection view matrix and reflection clip plane.
	m_Terrain->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderReflectionShader(m_Direct3D->GetDeviceContext(), m_Terrain->GetMedQualityIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix,
		m_Terrain->GetTexture(), m_Terrain->GetNormalMapTexture(), m_Light->GetDiffuseColor(), m_Light->GetDirection(), 2.0f,
		clipPlane);
	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_Direct3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_Direct3D->ResetViewport();

	return true;
}

bool ApplicationClass::RenderRefractionToTexture()
{
	DXFLOAT4 clipPlane;
	DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	// Setup a clipping plane based on the height of the water to clip everything above it to create a refraction.
	clipPlane = DXFLOAT4(0.0f, -1.0f, 0.0f, m_Water->GetWaterHeight() + 0.1f);

	// Set the render target to be the refraction render to texture.
	m_RefractionTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());

	// Clear the refraction render to texture.
	m_RefractionTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	// Render the terrain using the reflection shader and the refraction clip plane to produce the refraction effect.
	m_Terrain->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderReflectionShader(m_Direct3D->GetDeviceContext(), m_Terrain->GetMedQualityIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Terrain->GetTexture(), m_Terrain->GetNormalMapTexture(), m_Light->GetDiffuseColor(), m_Light->GetDirection(), 2.0f,
		clipPlane);
	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	//m_Direct3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	//m_Direct3D->ResetViewport();

	return true;
}

InputClass* ApplicationClass::GetInputInstance()
{
	return m_Input;
}