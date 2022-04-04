#include "Window.h"
#include "IHF.h"
//��ʼ�� EasyX Graphics Library ����;
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

//��ȡ�������Ļ���������;
void Window::GetScreenMouse() { GetCursorPos(&m_Mouse_Screen); }
//��ȡ����ڴ��ڵ���������Ϣ;
void Window::GetWindowMouse() { m_Mouse_Window = getmessage(EM_MOUSE | EM_KEY); }

int Window::GetWidth() { return ::getwidth(); }
int Window::GetHeight() { return ::getheight(); }

void Window::GetWindowRect() { ::GetWindowRect(Handle, &Rect); }