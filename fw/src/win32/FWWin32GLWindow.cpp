/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Win32 OGL Window class
//
// $File: //nextgendev/Framework_080/src/win32/FWWin32GLWindow.cpp $
// $Author: asidwell $
// $Date: 2006/02/14 $
// $Revision: #2 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include <windowsx.h>
#include "FWDebug.h"
#include "win32/FWWin32GLWindow.h"
#include "FWApplication.h"
#include "FWInput.h"
#include "FWTime.h"
#include "FWDebugFont.h"
#include "FWDebugConsole.h"

// Horizontal resolutions
static int sXResolutions[] =
{
	0,		// VGA
	720,	// 480i
	720,	// 480p
	720,	// 576i
	720,	// 576p
	1280,	// 720p
	1920,	// 1080i
	1920,	// 1080p
	1280,	// 720p on VESA 1280x768
	1280,	// 720p on VESA 1280x1024
	1920,	// 1080p on VESA 1920x1200
};

// Vertical resolutions
static int sYResolutions[] =
{
	0,		// VGA
	480,	// 480i
	480,	// 480p
	576,	// 576i
	576,	// 576p
	720,	// 720p
	1080,	// 1080i
	1080,	// 1080p
	720,	// 720p on VESA 1280x768
	720,	// 720p on VESA 1280x1024
	1080,	// 1080p on VESA 1920x1200
};

#ifndef WGL_ARB_pixel_format
typedef BOOL (WINAPI * PFNWGLCHOOSEPIXELFORMATARBPROC) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
#define WGL_DRAW_TO_WINDOW_ARB		0x2001
#define WGL_ACCELERATION_ARB		0x2003
#define WGL_SUPPORT_OPENGL_ARB		0x2010
#define WGL_DOUBLE_BUFFER_ARB		0x2011
#define WGL_COLOR_BITS_ARB			0x2014
#define WGL_ALPHA_BITS_ARB			0x201B
#define WGL_DEPTH_BITS_ARB			0x2022
#define WGL_STENCIL_BITS_ARB		0x2023
#define WGL_FULL_ACCELERATION_ARB	0x2027
#endif//WGL_ARB_pixel_format

#ifndef GL_ARB_multisample
#define WGL_SAMPLE_BUFFERS_ARB		0x2041
#define WGL_SAMPLES_ARB				0x2042
#define GL_MULTISAMPLE_ARB			0x809D
#endif//GL_ARB_multisample

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters:	argc - Number of arguments
//				ppArgv - Argument list
//				dispInfo - Display info class
//				startupInfo - Startup info class
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
FWWin32GLWindow::FWWin32GLWindow(int argc, char **ppArgv, const FWDisplayInfo &dispInfo, const FWStartupInfo &startupInfo) :
FWWindow(argc, ppArgv, dispInfo, startupInfo),
mDontQuit(false),
mAAPixelFormat(0)
{
	// set up pfd
	memset(&mPfdPreferredFormat, 0, sizeof(PIXELFORMATDESCRIPTOR));
	mPfdPreferredFormat.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	mPfdPreferredFormat.nVersion = 1;
	mPfdPreferredFormat.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	mPfdPreferredFormat.iPixelType = PFD_TYPE_RGBA;
	mDispInfo.mColorBits = mPfdPreferredFormat.cColorBits = dispInfo.mColorBits;
	mDispInfo.mAlphaBits = mPfdPreferredFormat.cAlphaBits = dispInfo.mAlphaBits;
	mDispInfo.mDepthBits = mPfdPreferredFormat.cDepthBits = dispInfo.mDepthBits;
	mDispInfo.mStencilBits = mPfdPreferredFormat.cStencilBits = dispInfo.mStencilBits;
	mPfdPreferredFormat.iLayerType = PFD_MAIN_PLANE;

	// copy other options
	if(dispInfo.mDisplayMode != FWDisplayInfo::DisplayMode_VGA)
	{
		// set TV resolution
		mDispInfo.mWidth = sXResolutions[dispInfo.mDisplayMode];
		mDispInfo.mHeight = sYResolutions[dispInfo.mDisplayMode];
	}
	else
	{
		// use set resolution
		mDispInfo.mWidth = dispInfo.mWidth;
		mDispInfo.mHeight = dispInfo.mHeight;
	}

	mDispInfo.mAntiAlias = dispInfo.mAntiAlias;
	mDispInfo.mVSync = dispInfo.mVSync;

	createWindow();
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
FWWin32GLWindow::~FWWin32GLWindow()
{
}

//-----------------------------------------------------------------------------
// Description: Calls win32 DestroyWindow on this window
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWWin32GLWindow::destroy()
{
	DestroyWindow(mHwnd);
}

//-----------------------------------------------------------------------------
// Description: Window update function
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWWin32GLWindow::update()
{
	// while initialization was ok and the app still wants to run
	if(mInit && mUpdate)
	{
		FWWindow::update();
	}
	else
		onClose();	// send close message
}

//-----------------------------------------------------------------------------
// Description: Sets rendering context
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWWin32GLWindow::setRenderingContext()
{
	FWASSERT(mHDc != NULL);
	FWASSERT(mHRc != NULL);
	wglMakeCurrent(mHDc, mHRc);

	// enable multisampling if application requested it
	if(mAAPixelFormat)
		glEnable(GL_MULTISAMPLE_ARB);
}

//-----------------------------------------------------------------------------
// Description: Clears rendering context
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWWin32GLWindow::clearRenderingContext()
{
	wglMakeCurrent(NULL, NULL);
}

//-----------------------------------------------------------------------------
// Description: Does buffer flip
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWWin32GLWindow::flip()
{
	// flip buffers
	FWASSERT(mHDc != NULL);
	SwapBuffers(mHDc);
}

//-----------------------------------------------------------------------------
// Description: Get display info struct
// Parameters: 
// Returns: reference to display info
// Notes: 
//-----------------------------------------------------------------------------
FWDisplayInfo &FWWin32GLWindow::getDisplayInfo()
{
	return mDispInfo;
}

//-----------------------------------------------------------------------------
// Description: Returns the win32 window handle
// Parameters: 
// Returns: win32 window handle
// Notes:
//-----------------------------------------------------------------------------
void *FWWin32GLWindow::getWindowSystemContext()
{
	return (void *)mHwnd;
}

//-----------------------------------------------------------------------------
// Description: Win32 window proc
// Parameters:	hwnd - Window handle
//				msg - Message
//				wParam - Parameter
//				lParam - Parameter
// Returns: lResult from DefWindowProc()
// Notes: 
//-----------------------------------------------------------------------------
LRESULT WINAPI FWWin32GLWindow::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT		lResult = 1;
	RECT		rect;
	PAINTSTRUCT	ps;

	if (NULL != hwnd)
	{
		FWWin32GLWindow *pWindow;
		// the window long won't have been set when we get the create message, so we have to use the CREATESTRUCT method instead
		if(msg == WM_CREATE)
			pWindow = (FWWin32GLWindow *)((LPCREATESTRUCT)lParam)->lpCreateParams;
		else
			pWindow = (FWWin32GLWindow *)GetWindowLong(hwnd, GWL_USERDATA);

		if(NULL != pWindow)
		{
			switch(msg)
			{
			case WM_CREATE:
				pWindow->onCreate(hwnd);
				break;

			case WM_CLOSE:
				pWindow->onClose();
				break;

			case WM_DESTROY:
				pWindow->onDestroy();
				break;

			case WM_PAINT:
				BeginPaint(hwnd, &ps);
				pWindow->onPaint();
				EndPaint(hwnd, &ps);
				break;

			case WM_SIZE:
				GetClientRect(hwnd, &rect);
				pWindow->onSize(rect.right, rect.bottom);
				break;

			default:
				lResult = DefWindowProc(hwnd, msg, wParam, lParam);
				break;
			}
		}
		else
		{
			lResult = DefWindowProc(hwnd, msg, wParam, lParam);
		}
	}
	
	return lResult;
}

//-----------------------------------------------------------------------------
// Description: Gets called on WM_CREATE message
// Parameters:	hwnd - Window handle
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWWin32GLWindow::onCreate(HWND hwnd)
{
	// assign mHwnd here, since it could be needed by the application
	mHwnd = hwnd;

	// get device context
	mHDc = GetDC(hwnd);
	FWASSERT(mHDc != NULL);

	int iFormat;

	// get matching dc pixel format
	if(mAAPixelFormat == 0)
	{
		iFormat = ChoosePixelFormat(mHDc, &mPfdPreferredFormat);
		FWASSERT(iFormat != 0);
	}
	else
		iFormat = mAAPixelFormat;

	// set the pixel format
	BOOL bSetPix = SetPixelFormat(mHDc, iFormat, &mPfdPreferredFormat);
	FWASSERT(bSetPix != FALSE);

	// create gl render context
	mHRc = wglCreateContext(mHDc);
	FWASSERT(mHRc != NULL);

	// save gl context
	mDispInfo.mGlContext = mHRc;

	// set rendering context
	setRenderingContext();

	// enable antialiasing if required
	if(mDispInfo.mAntiAlias)
		enableAA();

	// enable vsync or not
	//wglSwapIntervalEXT(mDispInfo.m_bVSync ? 1 : 0);

	if(!mDontQuit)
	{
		// initialize input
		FWInput::init(NULL);
	
		// init rest of application
		FWWindow::init();
	}

	// we did clear the rendering context here
	// but removed it by popular request
}

//-----------------------------------------------------------------------------
// Description: Gets called on WM_SIZE message
// Parameters:	width - New client width
//				height - New client height
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWWin32GLWindow::onSize(int width, int height)
{
	resize(width, height);
}

//-----------------------------------------------------------------------------
// Description: Gets called on WM_CLOSE message
// Parameters:	iKeycode - Keycode
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWWin32GLWindow::onClose()
{
	FWWindow::destroy();

	destroyWindow();

	// delete the ogl context
	FWASSERT(mHRc != NULL);
	wglDeleteContext(mHRc);

	// release the device context
	FWASSERT(mHDc != NULL);
	ReleaseDC(mHwnd, mHDc);

	// send a WM_DESTROY message to this window
	FWASSERT(mHwnd != NULL);
	DestroyWindow(mHwnd);
}

//-----------------------------------------------------------------------------
// Description: Gets called on WM_DESTROY message
// Parameters:
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWWin32GLWindow::onDestroy()
{
	// unregister window class
	UnregisterClass(WIN32_CLASSNAME, GetModuleHandle(0));

	// send a quit message
	if(!mDontQuit)
		PostQuitMessage(0);
}

//-----------------------------------------------------------------------------
// Description: Gets called on WM_PAINT message
// Parameters:
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWWin32GLWindow::onPaint()
{
	// call the update & render functions
	// these are commented out at present, since dragging a window
	// on screen causes multiple paint messages and mouse inputs
	//Update();
	//Render();
}

//-----------------------------------------------------------------------------
// Description: Function to create window.
// Parameters:
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWWin32GLWindow::createWindow()
{
	// register the window class
	WNDCLASS wc;

	wc.style			= CS_DBLCLKS;
	wc.lpfnWndProc		= (WNDPROC)FWWin32GLWindow::wndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= GetModuleHandle(0);
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor			= LoadCursor(0, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName		= 0;
	wc.lpszClassName	= WIN32_CLASSNAME;

	RegisterClass(&wc);
	
	// add on width and height of window frame
	int width = mDispInfo.mWidth + GetSystemMetrics(SM_CXSIZEFRAME) * 2;
	int height = mDispInfo.mHeight + GetSystemMetrics(SM_CYSIZEFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);

	// create the window
	// mHwnd gets assigned in onCreate()
	CreateWindow(
			WIN32_CLASSNAME,													// registered class name
			FWApplication::getApplication()->getStartupInfo().mWindowTitle,		// window name
			WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,			// window style
			CW_USEDEFAULT,														// horizontal position of window
 			CW_USEDEFAULT,														// vertical position of window
			width,																// window width
			height,																// window height
			0,																	// handle to parent or owner window
			NULL,																// handle to menu or child-window identifier
			GetModuleHandle(0),													// handle to application instance
			this);																// pointer to window-creation data

	FWASSERT(mHwnd != NULL);

	// set pointer to this object
	SetWindowLong(mHwnd, GWL_USERDATA, (LONG)this);

	// show the window
	ShowWindow(mHwnd, SW_SHOWNORMAL);

	// paint the window
	UpdateWindow(mHwnd);
}

//-----------------------------------------------------------------------------
// Description: Function to destroy window.
// Parameters:
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWWin32GLWindow::destroyWindow()
{
	// delete the ogl context
	FWASSERT(mHRc != NULL);
	wglDeleteContext(mHRc);

	// release the device context
	FWASSERT(mHDc != NULL);
	ReleaseDC(mHwnd, mHDc);

	// send a WM_DESTROY message to this window
	FWASSERT(mHwnd != NULL);
	DestroyWindow(mHwnd);
}

//-----------------------------------------------------------------------------
// Description: Function to enable multisampling AA.
// Parameters:
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWWin32GLWindow::enableAA()
{
	if(mAAPixelFormat)
		return;

	// try to get extension
	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = 
		(PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");

	// just return if not available
	if(!wglChoosePixelFormatARB)
		return;

	int				iPixelFormat;
	BOOL			bValid;
	unsigned int	iNumFormats;

	float			fAttributes[] =
	{
		0.f,
		0.f,
	};

	int iAttributes[] =
	{
		WGL_DRAW_TO_WINDOW_ARB,	GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB,	GL_TRUE,
		WGL_ACCELERATION_ARB,	WGL_FULL_ACCELERATION_ARB,
		WGL_COLOR_BITS_ARB,		mDispInfo.mColorBits,
		WGL_ALPHA_BITS_ARB,		mDispInfo.mAlphaBits, 
		WGL_DEPTH_BITS_ARB,		mDispInfo.mDepthBits,
		WGL_STENCIL_BITS_ARB,	mDispInfo.mStencilBits,
		WGL_DOUBLE_BUFFER_ARB,	GL_TRUE,
		WGL_SAMPLE_BUFFERS_ARB,	GL_TRUE,
		WGL_SAMPLES_ARB,		4,
		0,						0,
	};

	// see if 4x multisampling is supported
	bValid = wglChoosePixelFormatARB(mHDc, iAttributes, fAttributes, 1, &iPixelFormat, &iNumFormats);

	if(bValid && iNumFormats >= 1)
	{
		// we got a valid format, so delete the current ogl context and recreate it

		mDontQuit = true;
		destroyWindow();
		mAAPixelFormat = iPixelFormat;
		createWindow();
		mDontQuit = false;
		return;
	}

	// see if 2x multisampling is supported
	iAttributes[19] = 2;
	bValid = wglChoosePixelFormatARB(mHDc, iAttributes, fAttributes, 1, &iPixelFormat, &iNumFormats);

	if(bValid && iNumFormats >= 1)
	{
		// we got a valid format, so delete the current ogl context and recreate it

		mDontQuit = true;
		destroyWindow();
		mAAPixelFormat = iPixelFormat;
		createWindow();
		mDontQuit = false;
		return;
	}

	// couldn't create AA buffer
	mDispInfo.mAntiAlias = false;
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
