////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "inputclass.h"


InputClass::InputClass()
{
}


InputClass::InputClass(const InputClass& other)
{
}


InputClass::~InputClass()
{
}


bool InputClass::Initialize(HWND hwnd, int screenWidth, int screenHeight)
{
	// Initialize all the keys to being released and not pressed.
	for (int i = 0; i < 256; i++)
	{
		m_keys[i] = false;
	}

	// Initialize left mouse button to not pressed
	m_leftClickDown = false;

	// Store the screen size which will be used for positioning the mouse cursor.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Store the window handle.
	m_hwnd = hwnd;

	// Initialize the location of the mouse on the screen.
	m_mouseX = 0;
	m_mouseY = 0;

	return true;
}

bool InputClass::Frame()
{
	bool result;

	// Get the distance of window from the top left of the screen
	RECT rect;
	GetWindowRect(m_hwnd, &rect);
	int height = rect.top;
	int width = rect.left;

	// Process the changes in the mouse and keyboard.
	ProcessInput(height, width);

	return true;
}

void InputClass::ProcessInput(int height, int width)
{
	POINT mousePos;
	GetCursorPos(&mousePos);

	// Update the location of the mouse cursor based on the change of the mouse location during the frame.
	m_mouseX = mousePos.x - width;
	m_mouseY = mousePos.y - height;

	// Ensure the mouse location doesn't exceed the screen width or height.
	if (m_mouseX < 0) { m_mouseX = 0; }
	if (m_mouseY < 0) { m_mouseY = 0; }

	if (m_mouseX > m_screenWidth) { m_mouseX = m_screenWidth; }
	if (m_mouseY > m_screenHeight) { m_mouseY = m_screenHeight; }

	return;
}

void InputClass::KeyDown(unsigned int input)
{
	// If a key is pressed then save that state in the key array.
	m_keys[input] = true;
	return;
}


void InputClass::KeyUp(unsigned int input)
{
	// If a key is released then clear that state in the key array.
	m_keys[input] = false;
	return;
}


bool InputClass::IsKeyDown(unsigned int key)
{
	// Return what state the key is in (pressed/not pressed).
	return m_keys[key];
}

void InputClass::GetMouseLocation(int& mouseX, int& mouseY)
{
	mouseX = m_mouseX;
	mouseY = m_mouseY;
	return;
}

void InputClass::LeftMouseDown()
{
	// Set the left click pressed state to true.
	m_leftClickDown = true;

	return;
}

void InputClass::LeftMouseUp()
{
	// Set the left click pressed state to false.
	m_leftClickDown = false;

	return;
}

bool InputClass::IsLeftMouseButtonDown()
{
	// Return what state the key is in (pressed/not pressed).
	return m_leftClickDown;
}