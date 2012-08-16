/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Linux Window class
//
// $File: //nextgendev/Framework_080/src/linux/FWLinuxGLWindow.cpp $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include "linux/FWLinuxGLWindow.h"
#include "FWApplication.h"
#include "FWInput.h"
#include "FWTime.h"
#include "FWDebugFont.h"
#include "FWDebugConsole.h"
#include <stdio.h>
#include <stdlib.h>

// Horizontal resolutions
static int sXResolutions[] =
{
	0,	// VGA
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
	0,	// VGA
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

// window delete message atom
static Atom			sWmDeleteWindow;

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters:	argc - Number of arguments
//				ppArgv - Argument list
//				dispInfo - Display info class
//				startupInfo - Startup info class
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
FWLinuxGLWindow::FWLinuxGLWindow(int argc, char **ppArgv, const FWDisplayInfo &dispInfo, const FWStartupInfo &startupInfo) :
FWWindow(argc, ppArgv, dispInfo, startupInfo)
{
	// get X display
	mXInfo.mpDisplay = XOpenDisplay(NULL);

	// get screen
	int screen = DefaultScreen(mXInfo.mpDisplay);
	// get root window
	Window	rootWindow = RootWindow(mXInfo.mpDisplay, screen);
	// set glx attributes
	int attrib[] =
	{
		GLX_RGBA,
		GLX_RED_SIZE, 8,
		GLX_GREEN_SIZE, 8,
		GLX_BLUE_SIZE, 8,
		GLX_ALPHA_SIZE, 8,
		GLX_DEPTH_SIZE, 24,
		GLX_STENCIL_SIZE, 8,
		GLX_DOUBLEBUFFER,
		None
	};

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

	mDispInfo.mColorBits = dispInfo.mColorBits;
	mDispInfo.mAlphaBits = dispInfo.mAlphaBits;
	mDispInfo.mDepthBits = dispInfo.mDepthBits;
	mDispInfo.mStencilBits = dispInfo.mStencilBits;
	mDispInfo.mAntiAlias = dispInfo.mAntiAlias;
	mDispInfo.mVSync = dispInfo.mVSync;

	mXInfo.mXPos = mXInfo.mYPos = 0;
	mXInfo.mWidth = mDispInfo.mWidth;
	mXInfo.mHeight = mDispInfo.mHeight;
	mXInfo.mWindowMoved = false;
	mXInfo.mWindowFocus = true;

	// try to get a visual
	XVisualInfo	*pVisInfo = glXChooseVisual(mXInfo.mpDisplay, screen, attrib);
	if(!pVisInfo)
	{
		fprintf(stderr, "glXChooseVisual() returned NULL\n");
		exit(-1);
	}

	// set window attributes	
	XSetWindowAttributes	windowAttrib;
	
	windowAttrib.background_pixel = 0;
	windowAttrib.border_pixel = 0;
	windowAttrib.colormap = XCreateColormap(mXInfo.mpDisplay, rootWindow, pVisInfo->visual, AllocNone);
	windowAttrib.event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask;
	
	unsigned long mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;
	
	// create the window
	mXInfo.mWindow = XCreateWindow(mXInfo.mpDisplay, rootWindow, 0, 0, mDispInfo.mWidth, mDispInfo.mHeight, 0, pVisInfo->depth,
							InputOutput, pVisInfo->visual, mask, &windowAttrib);

	XSizeHints	sizeHints;

	sizeHints.x = 0;
	sizeHints.y = 0;
	sizeHints.width = mDispInfo.mWidth;
	sizeHints.height = mDispInfo.mHeight;
	sizeHints.flags = USPosition;

	XSetNormalHints(mXInfo.mpDisplay, mXInfo.mWindow, &sizeHints);
	XSetStandardProperties(mXInfo.mpDisplay, mXInfo.mWindow, FWApplication::getApplication()->getStartupInfo().mWindowTitle, FWApplication::getApplication()->getStartupInfo().mWindowTitle, None, NULL, 0, &sizeHints);
	
	// create glx context
	if(!(mDispInfo.mGlContext = glXCreateContext(mXInfo.mpDisplay, pVisInfo, NULL, True)))
	{
		fprintf(stderr, "glXCreateContext() returned NULL\n");
		exit(-1);
	}


	XFree(pVisInfo);

	XMapWindow(mXInfo.mpDisplay, mXInfo.mWindow);

	// handle window manager close message
	sWmDeleteWindow = XInternAtom(mXInfo.mpDisplay, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(mXInfo.mpDisplay, mXInfo.mWindow, &sWmDeleteWindow, 1);

	// make context current
	setRenderingContext();

	// enable vsync or not
	// glXSwapIntervalSGI(mDispInfo.m_bVSync ? 1 : 0);

	// set default server and client texture units
	glActiveTexture(GL_TEXTURE0);
	glClientActiveTexture(GL_TEXTURE0);

	// initialize input
	FWInput::init((void *)&mXInfo);

	// init rest of application	
	FWWindow::init();

	if(mInit)
		resize(mDispInfo.mWidth, mDispInfo.mHeight);
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWLinuxGLWindow::~FWLinuxGLWindow()
{
}

//-----------------------------------------------------------------------------
// Description: Window update function
// Parameters:
// Returns: True if continuing to run, false otherwise
// Notes:
//-----------------------------------------------------------------------------
bool FWLinuxGLWindow::update()
{
	bool xRet;
	if(mInit && mUpdate)
	{
		// run X message loop
		xRet = xUpdate();

		FWWindow::update();

		return xRet && mUpdate;
	}
	else
		return false;
}

//-----------------------------------------------------------------------------
// Description: Sets rendering context
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWLinuxGLWindow::setRenderingContext()
{
	// make glx context current
	glXMakeCurrent(mXInfo.mpDisplay, mXInfo.mWindow, mDispInfo.mGlContext);
}

//-----------------------------------------------------------------------------
// Description: Clears rendering context
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWLinuxGLWindow::clearRenderingContext()
{
	glXMakeCurrent(mXInfo.mpDisplay, None, NULL);
}

//-----------------------------------------------------------------------------
// Description: Do buffer flip
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWLinuxGLWindow::flip()
{
	// do flip
	glXSwapBuffers(mXInfo.mpDisplay, mXInfo.mWindow);
}

//-----------------------------------------------------------------------------
// Description: Gets called on application shutdown
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWLinuxGLWindow::destroy()
{
	FWWindow::destroy();

	// destroy glx context & X window
	glXDestroyContext(mXInfo.mpDisplay, mDispInfo.mGlContext);
	XDestroyWindow(mXInfo.mpDisplay, mXInfo.mWindow);
	XCloseDisplay(mXInfo.mpDisplay);
}

//-----------------------------------------------------------------------------
// Description: Process X messages
// Parameters:
// Returns: True if running, false if quitting
// Notes:
//-----------------------------------------------------------------------------
bool FWLinuxGLWindow::xUpdate()
{
	// reset window moved status
	mXInfo.mWindowMoved = false;

	while(XPending(mXInfo.mpDisplay))
	{
		XEvent	xEvent;

		XNextEvent(mXInfo.mpDisplay, &xEvent);

		switch(xEvent.type)
		{
		case ClientMessage:
			// check for WM_DELETE_WINDOW message from window manager
			if((Atom)xEvent.xclient.data.l[0] == sWmDeleteWindow)
				return false;
			break;
		case ConfigureNotify:
			// check for window resize
			if(	(xEvent.xconfigure.width != mXInfo.mWidth) ||
				(xEvent.xconfigure.height != mXInfo.mHeight))
			{
				mXInfo.mWidth = xEvent.xconfigure.width;
				mXInfo.mHeight = xEvent.xconfigure.height;

				// set this so the input doesn't get updated
				mXInfo.mWindowMoved = true;

				resize(xEvent.xconfigure.width, xEvent.xconfigure.height);
			}

			// check for window move
			if(	(xEvent.xconfigure.x != mXInfo.mXPos) ||
				(xEvent.xconfigure.y != mXInfo.mYPos))
			{
				mXInfo.mXPos = xEvent.xconfigure.x;
				mXInfo.mYPos = xEvent.xconfigure.y;
				mXInfo.mWindowMoved = true;
			}
			break;
		case FocusIn:
			mXInfo.mWindowFocus = true;
			break;
		case FocusOut:
			mXInfo.mWindowFocus = false;
			break;
		}
	}
	return true;
}

//-----------------------------------------------------------------------------
// Description: Get the display info
// Parameters: 
// Returns: Display info
// Notes:
//-----------------------------------------------------------------------------
FWDisplayInfo &FWLinuxGLWindow::getDisplayInfo()
{
	return mDispInfo;
}

//-----------------------------------------------------------------------------
// Description: Returns the X window handle
// Parameters: 
// Returns: X window handle
// Notes:
//-----------------------------------------------------------------------------
void *FWLinuxGLWindow::getWindowSystemContext()
{
	return (void *)mXInfo.mWindow;
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
