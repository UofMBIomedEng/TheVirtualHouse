/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Linux input device support
//
// $File: //nextgendev/Framework_080/src/linux/FWLinuxInput.cpp $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "FWInput.h"
#include "linux/FWLinuxInput.h"
#include "linux/FWLinuxXInfo.h"

// pointer to FWLinuxXInfo
static FWLinuxXInfo	*spXInfo;

//-----------------------------------------------------------------------------
// Description: Platform specific input initialization
// Parameters:	pPlatformData - Pointer to platform specific data
// Returns:
// Notes:
//-----------------------------------------------------------------------------
bool FWInput::platformInit(void *pPlatformData)
{
	FWInputDeviceMouse		*pMouse;
	FWInputDeviceKeyboard	*pKeybd;
	FWLinuxMouseInfo		*pMouseInfo;

	// get passed X display and window
	spXInfo = (FWLinuxXInfo *)pPlatformData;

	pMouseInfo = new FWLinuxMouseInfo;
	pMouseInfo->mInit = true;
	pMouse = new FWInputDeviceMouse((void *)pMouseInfo);
	pKeybd = new FWInputDeviceKeyboard(NULL);

	// convert symbols to keycodes
	int i;
	for(i = 0; i < 256; i ++)
	{
		if(sKeyboardMap[i])
			sKeyboardMap[i] = XKeysymToKeycode(spXInfo->mpDisplay, sKeyboardMap[i]);
	}

	return true;
}

//-----------------------------------------------------------------------------
// Description: Platform specific input shutdown
// Parameters: 
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWInput::platformShutdown()
{
}

//-----------------------------------------------------------------------------
// Description: Platform specific input update
// Parameters: 
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWInput::platformUpdate()
{
}

//-----------------------------------------------------------------------------
//  Description: Updates this device
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWInputDeviceMouse::update()
{
	FWLinuxMouseInfo	*pMouseInfo;
	Window				root;
	Window				child;
	int					rootX;
	int					rootY;
	int					winX;
	int					winY;
	unsigned int		buttons;

	// query the pointer
	XQueryPointer(spXInfo->mpDisplay, spXInfo->mWindow, &root, &child, &rootX, &rootY, &winX, &winY, &buttons);

	// cast mouse info class to get old positions
	pMouseInfo = (FWLinuxMouseInfo *)mpPlatformData;
	// if not initialized, then don't calculate deltas
	if(pMouseInfo->mInit == true)
		pMouseInfo->mInit = false;
	else
	{
		// update if window isn't moving and has focus
		if((spXInfo->mWindowMoved == false) && (spXInfo->mWindowFocus == true))
		{
			if(mIsClientRelative == true)
			{
				// get client relative coordinates
				mXAxis[0] = winX * 255;
				mYAxis[0] = winY * 255;
				mZAxis[0] = 0;
			}
			else
			{
				// get motion vector
				mXAxis[0] = (rootX - pMouseInfo->mLastX) * 255;
				mYAxis[0] = (rootY - pMouseInfo->mLastY) * 255;
				mZAxis[0] = 0;
			}

			// set buttons
			mButtons[0] = (buttons & 0x100) ? true : false;
			mButtons[1] = (buttons & 0x200) ? true : false;
			mButtons[2] = (buttons & 0x400) ? true : false;
		}
		else
		{
			// zero everything
			mXAxis[0] = mYAxis[0] = mZAxis[0] = 0;
			mButtons[0] = mButtons[1] = mButtons[2] = false;
		}
	}

	// save last positions so we can get deltas next time around
	pMouseInfo->mLastX = rootX;
	pMouseInfo->mLastY = rootY;

	FWInputDevice::update();
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWInputDeviceMouse::~FWInputDeviceMouse()
{
	FWLinuxMouseInfo		*pMouseInfo;

	pMouseInfo = (FWLinuxMouseInfo *)mpPlatformData;

	delete pMouseInfo;
}

//-----------------------------------------------------------------------------
// Description: Updates this device
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWInputDeviceKeyboard::update()
{
	char	keys[32];

	XQueryKeymap(spXInfo->mpDisplay, keys);

	int i;
	for(i = 0; i < 256; i ++)
	{
		mKeys[i] = false;
		if(sKeyboardMap[i])
		{
			if(keys[sKeyboardMap[i] >> 3] & (1 << (sKeyboardMap[i] & 7)))
				mKeys[i] = true;
		}
	}

	FWInputDevice::update();
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWInputDeviceKeyboard::~FWInputDeviceKeyboard()
{
}

//-----------------------------------------------------------------------------
// Description: Updates this device
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWInputDevicePad::update()
{
	FWInputDevice::update();
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWInputDevicePad::~FWInputDevicePad()
{
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
