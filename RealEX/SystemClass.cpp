////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "systemclass.h"

SystemClass::SystemClass()
{
	/*m_Input = 0;
	m_Graphics = 0;
	m_Sound = 0;
	m_Fps = 0;
	m_Cpu = 0;
	m_Timer = 0;
	m_Position = 0;*/
	m_Application = 0;
}

SystemClass::SystemClass(const SystemClass& other)
{
}


SystemClass::~SystemClass()
{
}

bool SystemClass::Initialize()
{
	int screenWidth, screenHeight;
	bool result;


	// Initialize the width and height of the screen to zero before sending the variables into the function.
	screenWidth = 0;
	screenHeight = 0;

	// Initialize the windows api.
	InitializeWindows(screenWidth, screenHeight);

	//// Create the input object.  This object will be used to handle reading the keyboard input from the user.
	//m_Input = new InputClass;
	//if (!m_Input)
	//{
	//	return false;
	//}

	//// Initialize the input object.
	//result = m_Input->Initialize(screenWidth, screenHeight);
	//if (!result)
	//{
	//	MessageBox(m_hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
	//	return false;
	//};

	//// Create the graphics object.  This object will handle rendering all the graphics for this application.
	//m_Graphics = new GraphicsClass;
	//if (!m_Graphics)
	//{
	//	return false;
	//}

	//// Initialize the graphics object.
	//result = m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd);
	//if (!result)
	//{
	//	return false;
	//}

	//// Create the sound object.
	//m_Sound = new SoundClass;
	//if (!m_Sound)
	//{
	//	return false;
	//}

	//// Initialize the sound object.
	//result = m_Sound->Initialize(m_hwnd);
	//if (!result)
	//{
	//	return false;
	//}

	//// Create the fps object.
	//m_Fps = new FpsClass;
	//if (!m_Fps)
	//{
	//	return false;
	//}

	//// Initialize the fps object.
	//m_Fps->Initialize();

	//// Create the cpu object.
	//m_Cpu = new CpuClass;
	//if (!m_Cpu)
	//{
	//	return false;
	//}

	//// Initialize the cpu object.
	//m_Cpu->Initialize();

	//// Create the timer object.
	//m_Timer = new TimerClass;
	//if (!m_Timer)
	//{
	//	return false;
	//}

	//// Initialize the timer object.
	//result = m_Timer->Initialize();
	//if (!result)
	//{
	//	MessageBox(m_hwnd, L"Could not initialize the Timer object.", L"Error", MB_OK);
	//	return false;
	//}
	//
	//// Create the position object.
	//m_Position = new PositionClass;
	//if (!m_Position)
	//{
	//	return false;
	//}

	//m_Position->SetPosition(0.0f, 0.0f, -10.0f);
	/*m_Position->SetRotation(0.0f, 0.0f, 0.0f);*/

	// Create the application wrapper object.
	m_Application = new ApplicationClass;
	if (!m_Application)
	{
		return false;
	}

	// Initialize the application wrapper object.
	result = m_Application->Initialize(m_hinstance, m_hwnd, screenWidth, screenHeight);
	if (!result)
	{
		return false;
	}


	return true;
}

void SystemClass::Shutdown()
{
	//// Release the position object.
	//if (m_Position)
	//{
	//	delete m_Position;
	//	m_Position = 0;
	//}

	//// Release the timer object.
	//if (m_Timer)
	//{
	//	delete m_Timer;
	//	m_Timer = 0;
	//}

	//// Release the cpu object.
	//if (m_Cpu)
	//{
	//	m_Cpu->Shutdown();
	//	delete m_Cpu;
	//	m_Cpu = 0;
	//}

	//// Release the fps object.
	//if (m_Fps)
	//{
	//	delete m_Fps;
	//	m_Fps = 0;
	//}

	//// Release the graphics object.
	//if (m_Graphics)
	//{
	//	m_Graphics->Shutdown();
	//	delete m_Graphics;
	//	m_Graphics = 0;
	//}

	//// Release the input object.
	//if (m_Input)
	//{
	//	delete m_Input;
	//	m_Input = 0;
	//}

	//// Release the sound object
	//if (m_Sound)
	//{
	//	m_Sound->Shutdown();
	//	delete m_Sound;
	//	m_Sound = 0;
	//}

	// Release the application wrapper object.
	if (m_Application)
	{
		m_Application->Shutdown();
		delete m_Application;
		m_Application = 0;
	}

	// Shutdown the window.
	ShutdownWindows();

	return;
}

void SystemClass::Run()
{
	MSG msg;
	bool result;


	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));

	// Loop until there is a quit message from the window or the user.
	while (true)
	{
		// Handle the windows messages.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT)
		{
			return;
		}
		else
		{
			// Otherwise do the frame processing.
			result = Frame();
			if (!result)
			{
				return;
			}
		}

	}

	return;
}

bool SystemClass::Frame()
{
	bool result;

	// Do the frame processing for the application object.
	result = m_Application->Frame();
	if (!result)
	{
		return false;
	}

	return true;
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
		// Check if a character key has been pressed on the keyboard.
		case WM_CHAR:
		{
			// TO DO PAITONE: Use a global input carriage to pass this on later down the line...
			// For now, we'll just pass this to the TextClass as the char array (or string) is there
			/*m_Graphics->UpdateText(wparam);*/
			return 0;
		}

		// Check if a key has been pressed on the keyboard.
		case WM_KEYDOWN:
		{
			// If a key is pressed send it to the input object so it can record that state.
			m_Application->GetInputInstance()->KeyDown((unsigned int)wparam);
			return 0;
		}

		// Check if a key has been released on the keyboard.
		case WM_KEYUP:
		{
			// If a key is released then send it to the input object so it can unset the state for that key.
			m_Application->GetInputInstance()->KeyUp((unsigned int)wparam);
			return 0;
		}

		// Check if left mouse button has been clicked on.
		case WM_LBUTTONDOWN:
		{
			// If it is clicked, set the click state to true.
			m_Application->GetInputInstance()->LeftMouseDown();
			return 0;
		}

		// Check if left mouse button has been released.
		case WM_LBUTTONUP:
		{
			// If it is released, set the click state to false.
			m_Application->GetInputInstance()->LeftMouseUp();
			return 0;
		}

		// Any other messages send to the default message handler as our application won't make use of them.
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}

void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;


	// Get an external pointer to this object.	
	ApplicationHandle = this;

	// Get the instance of this application.
	m_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	m_applicationName = L"RealEX";

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 64;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		screenWidth = 800;
		screenHeight = 600;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Hide the mouse cursor.
	ShowCursor(false);

	return;
}

void SystemClass::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}
