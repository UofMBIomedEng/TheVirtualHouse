/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// win32 input device support
//
// $File: //nextgendev/Framework_080/src/win32/FWWin32Input.cpp $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include "FWInput.h"
#include "FWWindow.h"
#include "win32/FWWin32Input.h"

// pointer to direct input device
static LPDIRECTINPUT8		g_pDirectInput = NULL;

//-----------------------------------------------------------------------------
// Description: Platform specific mouse initialization
// Parameters:	pDIDInstance - Pointer to dinput device instance
// Returns:
// Notes:
//-----------------------------------------------------------------------------
static void initMouse(const DIDEVICEINSTANCE* pDIDInstance)
{
	LPDIRECTINPUTDEVICE8	pDevice;
	// Obtain an interface to the device
	if(FAILED(g_pDirectInput->CreateDevice(pDIDInstance->guidInstance, &pDevice, NULL)))
		return;

	if(FAILED(pDevice->SetDataFormat(&c_dfDIMouse2)))
		return;

	// set coop level
	if(pDevice->SetCooperativeLevel((HWND)FWWindow::getWindow()->getWindowSystemContext(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE) == DIERR_UNSUPPORTED)
		return;

	// acquire the device
	pDevice->Acquire();

	FWWin32MouseInfo	*pWin32MouseInfo = new FWWin32MouseInfo;
	pWin32MouseInfo->mIsWithinClientArea = false;
	pWin32MouseInfo->mpDevice = pDevice;

	// create our mouse device
	FWInputDeviceMouse	*pMouse = new FWInputDeviceMouse(pWin32MouseInfo);
}

//-----------------------------------------------------------------------------
// Description: Platform specific keyboard initialization
// Parameters:	pDIDInstance - Pointer to dinput device instance
// Returns: Pointer to keyboard device
// Notes:
//-----------------------------------------------------------------------------
static void initKeyboard(const DIDEVICEINSTANCE* pDIDInstance)
{
	LPDIRECTINPUTDEVICE8	pDevice;
	// Obtain an interface to the device
	if(FAILED(g_pDirectInput->CreateDevice(pDIDInstance->guidInstance, &pDevice, NULL)))
		return;

	if(FAILED(pDevice->SetDataFormat(&c_dfDIKeyboard)))
		return;

	// set coop level
	if(pDevice->SetCooperativeLevel((HWND)FWWindow::getWindow()->getWindowSystemContext(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE) == DIERR_UNSUPPORTED)
		return;

	// acquire the keyboard
	pDevice->Acquire();

	// create our keyboard device
	FWInputDeviceKeyboard	*pKeybd = new FWInputDeviceKeyboard(pDevice);
}

//-----------------------------------------------------------------------------
// Description: Gets pDIObjInstance by DirectInput to report joystick objects
// Parameters:	pDIObjInstance - Pointer to device object instance
//				pContext - Unused in this implementation
// Returns: Continue enumerating
// Notes:
//-----------------------------------------------------------------------------
static BOOL CALLBACK enumJoystickObjectsCallback(const DIDEVICEOBJECTINSTANCE* pDIObjInstance, VOID *pContext)
{
	LPDIRECTINPUTDEVICE8 pDevice = (LPDIRECTINPUTDEVICE8)pContext;

	// set min & max range for axis
	if(pDIObjInstance->dwType & DIDFT_AXIS)
	{
		DIPROPRANGE diPropRange;
		diPropRange.diph.dwSize			= sizeof(DIPROPRANGE);
		diPropRange.diph.dwHeaderSize	= sizeof(DIPROPHEADER);
		diPropRange.diph.dwHow			= DIPH_BYID;
		// Specify the enumerated axis
		diPropRange.diph.dwObj			= pDIObjInstance->dwType;
		diPropRange.lMin				= -255;
		diPropRange.lMax				= 255;

		// Set the range for the axis
		if(FAILED(pDevice->SetProperty(DIPROP_RANGE, &diPropRange.diph)))
			return DIENUM_STOP;
	}

	return DIENUM_CONTINUE;
}

//-----------------------------------------------------------------------------
// Description: Platform specific pad initialization
// Parameters:	pDIDInstance - Pointer to dinput device instance
// Returns:
// Notes:
//-----------------------------------------------------------------------------
static void initPad(const DIDEVICEINSTANCE* pDIDInstance)
{
	LPDIRECTINPUTDEVICE8	pDevice;
	// Obtain an interface to the device
	if(FAILED(g_pDirectInput->CreateDevice(pDIDInstance->guidInstance, &pDevice, NULL)))
		return;

	if(FAILED(pDevice->SetDataFormat(&c_dfDIJoystick2)))
		return;

	// set coop level
	if(pDevice->SetCooperativeLevel((HWND)FWWindow::getWindow()->getWindowSystemContext(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE) == DIERR_UNSUPPORTED)
		return;

	if(FAILED(pDevice->EnumObjects(enumJoystickObjectsCallback, pDevice, DIDFT_ALL)))
		return;

	pDevice->Acquire();

	// create our pad device
	FWInputDevicePad	*pPad = new FWInputDevicePad(pDevice);
}

//-----------------------------------------------------------------------------
// Description: Gets called by DirectInput to report connected joysticks
// Parameters:	pDIDInstance - Pointer to device instance
//				pContext - Unused in this implementation
// Returns: Stop or continue enumerating
// Notes:
//-----------------------------------------------------------------------------
static BOOL CALLBACK enumDevicesCallback(const DIDEVICEINSTANCE* pDIDInstance, VOID *pContext)
{
	switch(LOBYTE(pDIDInstance->dwDevType))
	{
	case DI8DEVTYPE_MOUSE:
		initMouse(pDIDInstance);
		break;

	case DI8DEVTYPE_KEYBOARD:
		initKeyboard(pDIDInstance);
		break;

	case DI8DEVTYPE_JOYSTICK:
	case DI8DEVTYPE_GAMEPAD:
		initPad(pDIDInstance);
		break;

	default:
		break;
	}

	return DIENUM_CONTINUE;
}

//-----------------------------------------------------------------------------
// Description: Platform specific input initialization
// Parameters:	pPlatformData - Platform specific data
// Returns: True if ok, false if not
// Notes:
//-----------------------------------------------------------------------------
bool FWInput::platformInit(void *pPlatformData)
{
	// create dinput device
	if(FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
									IID_IDirectInput8, (VOID **)&g_pDirectInput, NULL)))
		return false;

	// enumerate all attached devices
	if(FAILED(g_pDirectInput->EnumDevices(DI8DEVCLASS_ALL, enumDevicesCallback, NULL, DIEDFL_ATTACHEDONLY)))
		return false;
	
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
	if(g_pDirectInput)
		g_pDirectInput->Release();
}

//-----------------------------------------------------------------------------
// Description: Platform specific input update
// Parameters: 
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWInput::platformUpdate()
{
	// don't need to do anything here
	// everything is handled in the device update
}

//-----------------------------------------------------------------------------
// Description: Updates this device
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWInputDeviceMouse::update()
{
	// DirectInput mouse state structure
	DIMOUSESTATE2	dims2;

	FWWin32MouseInfo	*pWin32MouseInfo;

	// get di device pointer
	if(mpPlatformData)
		pWin32MouseInfo = (FWWin32MouseInfo *)mpPlatformData;
	else
		return;

	memset(&dims2, 0, sizeof(DIMOUSESTATE2));

	// get state of the device
	HRESULT hResult;
	hResult = pWin32MouseInfo->mpDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &dims2);
	if(FAILED(hResult))
	{
		// try to acquire the device
		hResult = pWin32MouseInfo->mpDevice->Acquire();

		while(hResult == DIERR_INPUTLOST)
			hResult = pWin32MouseInfo->mpDevice->Acquire();

		// we've only just acquired it, so the results will be invalid
		return;
	}

	// if we want client relative coordinates
	if(mIsClientRelative == true)
	{
		POINT	point;

		// get cursor position in screen space
		if(GetCursorPos(&point))
		{
			RECT	windowRect;

			// subtract window position, window frame and caption
			if(GetWindowRect((HWND)FWWindow::getWindow()->getWindowSystemContext(), &windowRect))
			{
				int iX, iY, iXFrame, iYFrame;
				iXFrame = GetSystemMetrics(SM_CXSIZEFRAME);
				iYFrame = GetSystemMetrics(SM_CYSIZEFRAME);
				iX = (point.x - (windowRect.left + iXFrame));
				iY = (point.y - (windowRect.top + iYFrame + GetSystemMetrics(SM_CYCAPTION)));
				mXAxis[0] = iX * 255;
				mYAxis[0] = iY * 255;
				mZAxis[0] = 0;

				// is the cursor within client area?
				if(	(iX >= 0) && (iX < (windowRect.right - iXFrame - windowRect.left)) &&
					(iY >= 0) && (iY < (windowRect.bottom - iYFrame - windowRect.top)))
				{
					// if within client area on last update, process as normal
					if(pWin32MouseInfo->mIsWithinClientArea == true)
					{
						mButtons[0] = dims2.rgbButtons[0] & 0x80 ? true : false;
						mButtons[1] = dims2.rgbButtons[2] & 0x80 ? true : false;
						mButtons[2] = dims2.rgbButtons[1] & 0x80 ? true : false;
					}
					else
					{
						// outside client area on last update, only update if the button is already down
						// i.e. process button ups and button holds
						if(mButtons[0])
							mButtons[0] = dims2.rgbButtons[0] & 0x80 ? true : false;
						if(mButtons[1])
							mButtons[1] = dims2.rgbButtons[2] & 0x80 ? true : false;
						if(mButtons[2])
							mButtons[2] = dims2.rgbButtons[1] & 0x80 ? true : false;
					}
					pWin32MouseInfo->mIsWithinClientArea = true;
				}
				else
				{
					// outside client area, only update if the button is already down
					// i.e. process button ups and button holds
					if(mButtons[0])
						mButtons[0] = dims2.rgbButtons[0] & 0x80 ? true : false;
					if(mButtons[1])
						mButtons[1] = dims2.rgbButtons[2] & 0x80 ? true : false;
					if(mButtons[2])
						mButtons[2] = dims2.rgbButtons[1] & 0x80 ? true : false;

					pWin32MouseInfo->mIsWithinClientArea = false;
				}
			}
		}
	}
	else
	{
		// map dinput into our format
		mXAxis[0] = dims2.lX * 255;
		mYAxis[0] = dims2.lY * 255;
		mZAxis[0] = dims2.lZ * 255;

		// get mouse button state
		mButtons[0] = dims2.rgbButtons[0] & 0x80 ? true : false;
		mButtons[1] = dims2.rgbButtons[2] & 0x80 ? true : false;
		mButtons[2] = dims2.rgbButtons[1] & 0x80 ? true : false;
	}

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
	if(mpPlatformData)
	{
		FWWin32MouseInfo	*pWin32MouseInfo = (FWWin32MouseInfo *)mpPlatformData;
		pWin32MouseInfo->mpDevice->Unacquire();
		pWin32MouseInfo->mpDevice->Release();
		delete pWin32MouseInfo;
	}
}

//-----------------------------------------------------------------------------
// Description: Updates this device
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWInputDeviceKeyboard::update()
{
	// DirectInput keyboard state buffer
	BYTE	diks[256];

	LPDIRECTINPUTDEVICE8 pDevice;

	if(mpPlatformData)
		pDevice = (LPDIRECTINPUTDEVICE8)mpPlatformData;
	else
		return;

	memset(diks, 0, sizeof(diks));

	HRESULT hResult;
	hResult = pDevice->GetDeviceState(sizeof(diks), diks);
	if(FAILED(hResult))
	{
		hResult = pDevice->Acquire();

		while(hResult == DIERR_INPUTLOST)
			hResult = pDevice->Acquire();

		return;
	}

	int i;
	for(i = 0; i < 256; i ++)
	{
		mKeys[i] = false;
		if(sKeyboardMap[i])
		{
			if(diks[sKeyboardMap[i]] & 0x80)
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
	if(mpPlatformData)
	{
		LPDIRECTINPUTDEVICE8 pDevice = (LPDIRECTINPUTDEVICE8)mpPlatformData;
		pDevice->Unacquire();
		pDevice->Release();
	}
}

//-----------------------------------------------------------------------------
// Description: Updates this device
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWInputDevicePad::update()
{
	// DirectInput joystick state structure
	DIJOYSTATE2	dijs2;

	LPDIRECTINPUTDEVICE8 pDevice;

	if(mpPlatformData)
		pDevice = (LPDIRECTINPUTDEVICE8)mpPlatformData;
	else
		return;

	memset(&dijs2, 0, sizeof(DIJOYSTATE2));

	HRESULT	hResult;
	hResult = pDevice->Poll();
	if(FAILED(hResult))
	{
		hResult = pDevice->Acquire();
        while(hResult == DIERR_INPUTLOST) 
            hResult = pDevice->Acquire();

		return;
	}

	// Get the input's device state
    if(FAILED(hResult = pDevice->GetDeviceState(sizeof(DIJOYSTATE2), &dijs2)))
        return;	// The device should have been acquired during the Poll()

	// map dinput into our format
	// left stick maps to x & y axis
	// right stick maps to z axis & z rotation
	mXAxis[0] = dijs2.lX;
	mYAxis[0] = dijs2.lY;
	mXAxis[1] = dijs2.lZ;
	mYAxis[1] = dijs2.lRz;

	int i;
	for(i = 0; i < 16; i ++)
		mButtons[i] = dijs2.rgbButtons[i] & 0x80 ? true : false;

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
	if(mpPlatformData)
	{
		LPDIRECTINPUTDEVICE8 pDevice = (LPDIRECTINPUTDEVICE8)mpPlatformData;
		pDevice->Unacquire();
		pDevice->Release();
	}
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
