/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Generic test application
//
// $File: //nextgendev/Framework_080/testapp/src/testapp.cpp $
// $Author: asidwell $
// $Date: 2006/02/14 $
// $Revision: #3 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include "testapp.h"
#include "FWDebugFont.h"
#include "FWTime.h"

// instantiate the class
TestApp app;

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
TestApp::TestApp()
{
	// set window title for Win32/Linux
	strcpy(mStartupInfo.mWindowTitle, "Test Application");
	// set command line args filename
	strcpy(mStartupInfo.mArgumentsFilename, "fwArgs.txt");
	// enable antialiasing
	mDispInfo.mAntiAlias = true;
}

//-----------------------------------------------------------------------------
// Description: Initialization callback
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
bool TestApp::onInit(int argc, char **ppArgv)
{
	FWGLCamControlApplication::onInit(argc, ppArgv);
	
	// get pointer to keyboard device
	FWInputDevice	*pKeybd = FWInput::getDevice(FWInput::DeviceType_Keyboard, 0);

	// bind a filter to the space key
	if(pKeybd != NULL)
	{
		mpSpaceKey = pKeybd->bindFilter();
		mpSpaceKey->setChannel(FWInput::Channel_Key_Space);
	}
	else
	{
		mpSpaceKey = NULL;
	}

	FWInputDevice	*pMouse = FWInput::getDevice(FWInput::DeviceType_Mouse, 0);

	if(pMouse != NULL)
	{
		((FWInputDeviceMouse *)pMouse)->setClientRelative(true);
		mpMouseX = pMouse->bindFilter();
		mpMouseX->setChannel(FWInput::Channel_XAxis_0);

		mpMouseY = pMouse->bindFilter();
		mpMouseY->setChannel(FWInput::Channel_YAxis_0);

		mpMouseLeft = pMouse->bindFilter();
		mpMouseLeft->setChannel(FWInput::Channel_Button_LeftMB);

		mpMouseMiddle = pMouse->bindFilter();
		mpMouseMiddle->setChannel(FWInput::Channel_Button_MiddleMB);

		mpMouseRight = pMouse->bindFilter();
		mpMouseRight->setChannel(FWInput::Channel_Button_RightMB);
	}
	else
	{
		mpMouseX = mpMouseY = mpMouseLeft = mpMouseMiddle = mpMouseRight = NULL;
	}

	FWInputDevice	*pPad = FWInput::getDevice(FWInput::DeviceType_Pad, 0);

	if(pPad != NULL)
	{
		mpLeftX = pPad->bindFilter();
		mpLeftX->setChannel(FWInput::Channel_XAxis_0);
		mpLeftY = pPad->bindFilter();
		mpLeftY->setChannel(FWInput::Channel_YAxis_0);
		mpRightX = pPad->bindFilter();
		mpRightX->setChannel(FWInput::Channel_XAxis_1);
		mpRightY = pPad->bindFilter();
		mpRightY->setChannel(FWInput::Channel_YAxis_1);
		mpUp = pPad->bindFilter();
		mpUp->setChannel(FWInput::Channel_Button_Up);
		mpRight = pPad->bindFilter();
		mpRight->setChannel(FWInput::Channel_Button_Right);
		mpDown = pPad->bindFilter();
		mpDown->setChannel(FWInput::Channel_Button_Down);
		mpLeft = pPad->bindFilter();
		mpLeft->setChannel(FWInput::Channel_Button_Left);
		mpTriangle = pPad->bindFilter();
		mpTriangle->setChannel(FWInput::Channel_Button_Triangle);
		mpCircle = pPad->bindFilter();
		mpCircle->setChannel(FWInput::Channel_Button_Circle);
		mpCross = pPad->bindFilter();
		mpCross->setChannel(FWInput::Channel_Button_Cross);
		mpSquare = pPad->bindFilter();
		mpSquare->setChannel(FWInput::Channel_Button_Square);
		mpL1 = pPad->bindFilter();
		mpL1->setChannel(FWInput::Channel_Button_L1);
		mpL2 = pPad->bindFilter();
		mpL2->setChannel(FWInput::Channel_Button_L2);
		mpL3 = pPad->bindFilter();
		mpL3->setChannel(FWInput::Channel_Button_L3);
		mpR1 = pPad->bindFilter();
		mpR1->setChannel(FWInput::Channel_Button_R1);
		mpR2 = pPad->bindFilter();
		mpR2->setChannel(FWInput::Channel_Button_R2);
		mpR3 = pPad->bindFilter();
		mpR3->setChannel(FWInput::Channel_Button_R3);
		mpSelect = pPad->bindFilter();
		mpSelect->setChannel(FWInput::Channel_Button_Select);
		mpStart = pPad->bindFilter();
		mpStart->setChannel(FWInput::Channel_Button_Start);
	}

	// print command line args to the debug console
	for(int i = 0; i < argc; i ++)
	{
		FWDebugConsole::print(ppArgv[i]);
	}

	// set default camera position
	mCamera.setPosition(Point3(0.f, 20.f, 150.f));
	return true;
}

//-----------------------------------------------------------------------------
// Description: Render callback
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void TestApp::onRender()
{
	// base implementation clears screen and sets up camera
	FWGLCamControlApplication::onRender();

	// render debug grid
	mGrid.render();

	// setup some verts and colors
	static float verts[] =
	{
		-5.f, 0.f, 0.f,
		0.f, 8.66f, 0.f,
		5.f, 0.f, 0.f,
	};

	static float colors[] =
	{
	  1.f, 0.f, 0.f, 1.f,
	  0.f, 1.f, 0.f, 1.f,
	  0.f, 0.f, 1.f, 1.f
	};

	// render triangle
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, verts);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, colors);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glFlush();
	
	// print some messages
	FWDebugFont::setPosition(0, 0);
	FWDebugFont::setColor(1.f, 1.f, 1.f, 1.f);

	// calc fps
	FWTimeVal	time = FWTime::getCurrentTime();
	float fFPS = 1.f / (float)(time - mLastTime);
	mLastTime = time;

	FWDebugFont::print("Sample Framework Test Application\n"
					   "This demonstrates use of the Sample Framework on multiple platforms and some\n"
					   "of its features including device input, debug text and graphics rendering.\n");

	FWDebugFont::printf("FPS: %.2f\n", fFPS);

	FWDebugFont::printf("MouseX = %.2f, MouseY = %.2f\n\n", mpMouseX ? mpMouseX->getFloatValue() : 0.f,
					mpMouseY ? mpMouseY->getFloatValue() : 0.f);

	FWDebugFont::printf("LeftMB = %s, MiddleMB = %s, RightMB = %s\n\n",
		mpMouseLeft ? (mpMouseLeft->getBoolValue() ? "true" : "false") : "false",
		mpMouseMiddle ? (mpMouseMiddle->getBoolValue() ? "true" : "false") : "false",
		mpMouseRight ? (mpMouseRight->getBoolValue() ? "true" : "false") : "false");

	FWDebugFont::printf("X0 = %.2f, Y0 = %.2f\n\n", mpLeftX ? mpLeftX->getFloatValue() : 0.f,
					mpLeftY ? mpLeftY->getFloatValue() : 0.f);

	FWDebugFont::printf("X1 = %.2f, Y1 = %.2f\n\n", mpRightX ? mpRightX->getFloatValue() : 0.f,
					mpRightY ? mpRightY->getFloatValue() : 0.f);

	FWDebugFont::printf("Up = %s, Right = %s, Down = %s, Left = %s\n\n",
		mpUp ? (mpUp->getBoolValue() ? "true" : "false") : "false",
		mpRight ? (mpRight->getBoolValue() ? "true" : "false") : "false",
		mpDown ? (mpDown->getBoolValue() ? "true" : "false") : "false",
		mpLeft ? (mpLeft->getBoolValue() ? "true" : "false") : "false");

	FWDebugFont::printf("Triangle = %s, Circle = %s, Cross = %s, Square = %s\n\n",
		mpTriangle ? (mpTriangle->getBoolValue() ? "true" : "false") : "false",
		mpCircle ? (mpCircle->getBoolValue() ? "true" : "false") : "false",
		mpCross ? (mpCross->getBoolValue() ? "true" : "false") : "false",
		mpSquare ? (mpSquare->getBoolValue() ? "true" : "false") : "false");

	FWDebugFont::printf("L1 = %s, L2 = %s, L3 = %s\n\n",
		mpL1 ? (mpL1->getBoolValue() ? "true" : "false") : "false",
		mpL2 ? (mpL2->getBoolValue() ? "true" : "false") : "false",
		mpL3 ? (mpL3->getBoolValue() ? "true" : "false") : "false");

	FWDebugFont::printf("R1 = %s, R2 = %s, R3 = %s\n\n",
		mpR1 ? (mpR1->getBoolValue() ? "true" : "false") : "false",
		mpR2 ? (mpR2->getBoolValue() ? "true" : "false") : "false",
		mpR3 ? (mpR3->getBoolValue() ? "true" : "false") : "false");

	FWDebugFont::printf("Select = %s, Start = %s\n\n",
		mpSelect ? (mpSelect->getBoolValue() ? "true" : "false") : "false",
		mpStart ? (mpStart->getBoolValue() ? "true" : "false") : "false");

	// print message if key is down
	if(mpSpaceKey->getBoolValue())
		FWDebugFont::print("Space key is down...\n");
}

//-----------------------------------------------------------------------------
// Description: Resize callback
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void TestApp::onSize(const FWDisplayInfo& rDispInfo)
{
	FWGLCamControlApplication::onSize(rDispInfo);
}

//-----------------------------------------------------------------------------
// Description: Shutdown callback
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void TestApp::onShutdown()
{
	FWGLCamControlApplication::onShutdown();

	// unbind input filters
	FWInputDevice	*pKeybd = FWInput::getDevice(FWInput::DeviceType_Keyboard, 0);

	if(pKeybd != NULL)
	{
		pKeybd->unbindFilter(mpSpaceKey);
	}

	FWInputDevice	*pMouse = FWInput::getDevice(FWInput::DeviceType_Mouse, 0);

	if(pMouse != NULL)
	{
		pMouse->unbindFilter(mpMouseX);
		pMouse->unbindFilter(mpMouseY);
		pMouse->unbindFilter(mpMouseLeft);
		pMouse->unbindFilter(mpMouseMiddle);
		pMouse->unbindFilter(mpMouseRight);
	}

	FWInputDevice	*pPad = FWInput::getDevice(FWInput::DeviceType_Pad, 0);

	if(pPad != NULL)
	{
		pPad->unbindFilter(mpLeftX);
		pPad->unbindFilter(mpLeftY);
		pPad->unbindFilter(mpRightX);
		pPad->unbindFilter(mpRightY);
		pPad->unbindFilter(mpUp);
		pPad->unbindFilter(mpRight);
		pPad->unbindFilter(mpDown);
		pPad->unbindFilter(mpLeft);
		pPad->unbindFilter(mpTriangle);
		pPad->unbindFilter(mpCircle);
		pPad->unbindFilter(mpCross);
		pPad->unbindFilter(mpSquare);
		pPad->unbindFilter(mpL1);
		pPad->unbindFilter(mpL2);
		pPad->unbindFilter(mpL3);
		pPad->unbindFilter(mpR1);
		pPad->unbindFilter(mpR2);
		pPad->unbindFilter(mpR3);
		pPad->unbindFilter(mpSelect);
		pPad->unbindFilter(mpStart);
	}
}
