////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_

///////////////////////
// INCLUDES //
///////////////////////
#include <Windows.h>
#include <WinUser.h>

////////////////////////////////////////////////////////////////////////////////
// Class name: InputClass
////////////////////////////////////////////////////////////////////////////////
class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	bool Initialize(HWND, int, int);
	bool Frame();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);
	void LeftMouseDown();
	void LeftMouseUp();

	bool IsKeyDown(unsigned int);
	bool IsLeftMouseButtonDown();
	void GetMouseLocation(int&, int&);

private:
	void ProcessInput(int, int);

private:
	bool m_keys[256], m_leftClickDown;
	HWND m_hwnd;
	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
};

#endif