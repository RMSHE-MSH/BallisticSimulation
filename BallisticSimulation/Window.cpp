#include "Window.h"
#include "IHF.h"
//初始化 EasyX Graphics Library 画版;
void Window::Initialize_Window(int Width, int Height, int Flag) {
	Handle = ::initgraph(Width, Height, Flag);
	setorigin(40, Height - 40);
	setbkcolor(RGB(241, 243, 245));
	cleardevice();
	setaspectratio(1, -1);
	::setbkmode(TRANSPARENT);
}

void Window::Reset_Window(int Width, int Height, COLORREF Window_Color) {
	Resize(NULL, Width, Height);
	setbkcolor(Window_Color);
	cleardevice();
}

void Window::SetWindowTilte(const string& Title) { ::SetWindowText(Handle, Title.c_str()); }

void Window::MoveWindow(int X, int Y) { ::MoveWindow(Handle, X, Y, GetWidth(), GetHeight(), 0); }

//获取相对于屏幕的鼠标坐标;
void Window::GetScreenMouse() { GetCursorPos(&m_Mouse_Screen); }
//获取相对于窗口的鼠标键盘消息;
void Window::GetWindowMouse() { m_Mouse_Window = getmessage(EM_MOUSE | EM_KEY); }

int Window::GetWidth() { return ::getwidth(); }
int Window::GetHeight() { return ::getheight(); }

void Window::GetWindowRect() { ::GetWindowRect(Handle, &Rect); }