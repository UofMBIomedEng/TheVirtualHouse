/*   SCE CONFIDENTIAL                                       */
/*   PLAYSTATION(R)3 Programmer Tool Runtime Library 170.003 */
/*   Copyright (C) 2006 Sony Computer Entertainment Inc.    */
/*   All Rights Reserved.                                   */

#include <cell/keyboard.h>
#include <cell/pad.h>
#include <cell/mouse.h>
#include <sys/synchronization.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FWInput.h"
#include "cell/FWCellInput.h"

// Pad data
static CellPadInfo		sPadInfo;						// pad connection information buffer
static unsigned char 	sOldPadStatus[FW_MAX_PAD_NUM];	// old pad status

// Keyboard data
static CellKbInfo		sKeybdInfo;							// keyboard connection information buffer			
static unsigned char 	sOldKeybdStatus[FW_MAX_KEYBD_NUM];	// old keyboard status

// Mouse data
static CellMouseInfo	sMouseInfo;							// mouse connection information buffer			
static unsigned char 	sOldMouseStatus[FW_MAX_MOUSE_NUM];	// old mouse status

//-----------------------------------------------------------------------------
// Description: Platform specific input initialization
// Parameters:	pPlatformData - Platform specific data
// Returns:
// Notes:
//-----------------------------------------------------------------------------
bool FWInput::platformInit(void *pPlatformData)
{
	FWInputDevicePad		*pPad;
	FWInputDeviceKeyboard	*pKeybd;
	FWInputDeviceMouse		*pMouse;
	long				i;

	// stop unused parameter warning
	(void)pPlatformData;

	cellPadInit(FW_MAX_PAD_NUM);

	for(i = 0; i < FW_MAX_PAD_NUM; i ++)
	{
		sOldPadStatus[i] = 0;
		pPad = new FWInputDevicePad((void *)new FWCellPadInfo(i));
	}

	cellKbInit(FW_MAX_KEYBD_NUM);

	for(i = 0; i < FW_MAX_KEYBD_NUM; i ++)
	{
		sOldKeybdStatus[i] = 0;
		pKeybd = new FWInputDeviceKeyboard((void *)i);

		cellKbSetCodeType(i, CELL_KB_CODETYPE_RAW);
	}

	cellMouseInit(FW_MAX_MOUSE_NUM);

	for(i = 0; i < FW_MAX_MOUSE_NUM; i ++)
	{
		sOldMouseStatus[i] = 0;
		pMouse = new FWInputDeviceMouse((void *)i);
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
	cellPadEnd();
	cellKbEnd();
	cellMouseEnd();
}

//-----------------------------------------------------------------------------
// Description: Platform specific input update
// Parameters: 
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWInput::platformUpdate()
{
	// update pad connection status
	cellPadGetInfo(&sPadInfo);
	// update keybd connection status
	cellKbGetInfo(&sKeybdInfo);
	// update mouse connection status
	cellMouseGetInfo(&sMouseInfo);
}

//-----------------------------------------------------------------------------
// Description: Updates this device
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWInputDeviceMouse::update()
{
	CellMouseData mouseData;
	int device = (int)mpPlatformData;

	if((sMouseInfo.status[device]) &&
	   (sMouseInfo.status[device] != CELL_MOUSE_STATUS_DISCONNECTED))
	{
		/*E  a mouse has been connected */
		if (sOldMouseStatus[device] == CELL_MOUSE_STATUS_DISCONNECTED)
		{
			/*E  the previous data shows that mouse was not
			 *E  yet connected, so it is a new connection
			 */
			printf("New Mouse %d is connected: VENDOR_ID=%d PRODUCT_ID=%d\n", device, sMouseInfo.vendor_id[device], sMouseInfo.product_id[device]);
		}

		int ret = cellMouseGetData(device, &mouseData);
		if ((ret == CELL_OK) && (mouseData.update == CELL_MOUSE_DATA_UPDATE))
		{
			// if we want client relative coordinates
			if(mIsClientRelative == true)
			{
				mXAxis[0] += mouseData.x_axis;
				mYAxis[0] += mouseData.y_axis;
			} else {
				mXAxis[0] = mouseData.x_axis;
				mYAxis[0] = mouseData.y_axis;
			}
			mButtons[0] = mouseData.buttons & 0x1 ? true : false;
			mButtons[1] = mouseData.buttons & 0x4 ? true : false;
			mButtons[2] = mouseData.buttons & 0x2 ? true : false;
		}
	}

	// Update device status for next time
	sOldMouseStatus[device] = sMouseInfo.status[device];

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
}

//-----------------------------------------------------------------------------
// Description: Updates this device
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWInputDeviceKeyboard::update()
{
	long device = (long)mpPlatformData;

	if(sKeybdInfo.status[device])
	{
		if(sOldKeybdStatus[device] == 0)
		{
#ifdef _DEBUG		
			printf("Keyboard (%ld) detected\n", device);
#endif//_DEBUG
			cellKbClearBuf(device);
		}

		sOldKeybdStatus[device] = sKeybdInfo.status[device];
		
		CellKbData	keybdData;

		int ret = cellKbRead(device, &keybdData);
		if (ret == CELL_OK)
		{
			int i;
			if(keybdData.len > 0)
			{
				for(i = 0; i < 256; i ++)
					mKeys[i] = false;
			}

			for(i = 0; i < keybdData.len; i ++)
			{
				int key = sKeyboardMap[keybdData.keycode[i] & ~CELL_KB_RAWDAT];
				if(key)
					mKeys[key - FWInput::Channel_Key_A] = true;
			}
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
	FWCellPadInfo	*pPadInfo = (FWCellPadInfo *)mpPlatformData;
	int device = pPadInfo->mDevice;

	if(sPadInfo.status[device])
	{
		// Device is plugged in
		if(sOldPadStatus[device] == 0)
		{
			bool bNewPad = false;

			// Device is new, see if it's supported by libusbpad
			int ret = cellPadGetData(device, &padData);

			if(ret == CELL_PAD_OK)
			{
				printf("libusbpad supported pad (%d) detected\n", device);
				printf("VENDOR_ID=(0x%x), PRODUCT_ID=(0x%x)\n", sPadInfo.vendor_id[device], sPadInfo.product_id[device]);
				pPadInfo->mPadId = 0;
				bNewPad = true;
			}
			else
			{
				pPadInfo->mPadId = -1;
				for(int i = 1; i < FWINPUT_MAX_PAD_IDS; i ++)
				{
					if(((int)sPadInfo.vendor_id[device] == sPadIds[i][0]) &&
						((int)sPadInfo.product_id[device] == sPadIds[i][1]))
					{
						// Found a matching device
						printf("framework supported pad (%d) detected\n", device);
						printf("VENDOR_ID=(0x%x), PRODUCT_ID=(0x%x)\n", sPadInfo.vendor_id[device], sPadInfo.product_id[device]);
						pPadInfo->mPadId = i;
						bNewPad = true;
						break;
					}
				}
			}

			if (bNewPad) {
				// enable sensor mode if each pad supports it
				if (cellPadInfoSensorMode(device) == CELL_PAD_INFO_SUPPORTED_SENSOR_MODE) {
					cellPadSetSensorMode(device, CELL_PAD_SENSOR_MODE_ON);
					printf("sensor supported pad\n");
				}
			}
		}

		int ret;
		if(pPadInfo->mPadId == 0)
			ret = cellPadGetData(device, &padData);
		else
			ret = cellPadGetRawData(device, &padData);

		if(ret == CELL_PAD_OK)
		{
			if((padData.len > 0) && (pPadInfo->mPadId != -1))
			{
				// Read the analog axes
				if(sPadMappings[pPadInfo->mPadId][0] >= 0)
				{
					mXAxis[0] = padData.button[sPadMappings[pPadInfo->mPadId][0]] * 2 - 255;
				}
				else
				{
					mXAxis[0] = 0;
				}

				if(sPadMappings[pPadInfo->mPadId][1] >= 0)
				{
					mYAxis[0] = padData.button[sPadMappings[pPadInfo->mPadId][1]] * 2 - 255;
				}
				else
				{
					mYAxis[0] = 0;
				}

				if(sPadMappings[pPadInfo->mPadId][2] >= 0)
				{
					mXAxis[1] = padData.button[sPadMappings[pPadInfo->mPadId][2]] * 2 - 255;
				}
				else
				{
					mXAxis[1] = 0;
				}

				if(sPadMappings[pPadInfo->mPadId][3] >= 0)
				{
					mYAxis[1] = padData.button[sPadMappings[pPadInfo->mPadId][3]] * 2 - 255;
				}
				else
				{
					mYAxis[1] = 0;
				}

				if(sPadMappings[pPadInfo->mPadId][36] >= 0)
				{
					mXAxis[2] = padData.button[sPadMappings[pPadInfo->mPadId][36]] * 2 - 1023;
				}
				else
				{
					mXAxis[2] = 0;
				}

				if(sPadMappings[pPadInfo->mPadId][37] >= 0)
				{
					mYAxis[2] = padData.button[sPadMappings[pPadInfo->mPadId][37]] * 2 - 1023;
				}
				else
				{
					mYAxis[2] = 0;
				}

				if(sPadMappings[pPadInfo->mPadId][38] >= 0)
				{
					mZAxis[2] = padData.button[sPadMappings[pPadInfo->mPadId][38]] * 2 - 1023;
				}
				else
				{
					mZAxis[2] = 0;
				}

				if(sPadMappings[pPadInfo->mPadId][39] >= 0)
				{
					mGyro = padData.button[sPadMappings[pPadInfo->mPadId][39]] * 2 - 1023;
				}
				else
				{
					mGyro = 0;
				}

				// Buttons
				for(int i = 0; i < 16; i ++)
				{
					if(sPadMappings[pPadInfo->mPadId][i * 2 + 4] >= 0)
					{				
						mButtons[i] = padData.button[sPadMappings[pPadInfo->mPadId][i * 2 + 4]] &
							(1 << sPadMappings[pPadInfo->mPadId][i * 2 + 5]) ? true : false;
					}
					else
					{
						mButtons[i] = false;
					}
				}

				// map pads which use discrete values for digital direction control
				// rather than a bit per button
				if(sPadIds[pPadInfo->mPadId][2] != -1)
				{
					switch(padData.button[sPadIds[pPadInfo->mPadId][2]] & 0xf)
					{
					// no direction
					case 0x0:
					default:
						mButtons[12] = false;
						mButtons[13] = false;
						mButtons[14] = false;
						mButtons[15] = false;
						break;
					// up
					case 0x1:
						mButtons[12] = true;
						mButtons[13] = false;
						mButtons[14] = false;
						mButtons[15] = false;
						break;
					// right-up
					case 0x2:
						mButtons[12] = true;
						mButtons[13] = true;
						mButtons[14] = false;
						mButtons[15] = false;
						break;
					// right
					case 0x3:
						mButtons[12] = false;
						mButtons[13] = true;
						mButtons[14] = false;
						mButtons[15] = false;
						break;
					// right-down
					case 0x4:
						mButtons[12] = false;
						mButtons[13] = true;
						mButtons[14] = true;
						mButtons[15] = false;
						break;
					// down
					case 0x5:
						mButtons[12] = false;
						mButtons[13] = false;
						mButtons[14] = true;
						mButtons[15] = false;
						break;
					// left-down
					case 0x6:
						mButtons[12] = false;
						mButtons[13] = false;
						mButtons[14] = true;
						mButtons[15] = true;
						break;
					// left
					case 0x7:
						mButtons[12] = false;
						mButtons[13] = false;
						mButtons[14] = false;
						mButtons[15] = true;
						break;
					// left-up
					case 0x8:
						mButtons[12] = true;
						mButtons[13] = false;
						mButtons[14] = false;
						mButtons[15] = true;
						break;
					}
				}
			}
		}
	}
	else
	{
		// No device, set all inputs to zero
		mXAxis[0] = mXAxis[1] = mYAxis[0] = mYAxis[1] = 0;

		for(int i = 0; i < 16; i ++)
		{
			mButtons[i] = false;
		}
	}

	// Update device status for next time
	sOldPadStatus[device] = sPadInfo.status[device];

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
