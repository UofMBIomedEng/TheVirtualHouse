/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/

#include <assert.h>
#include "FWDebug.h"
#include "FWInput.h"
#include "FWMath.h"

// Device pointers
FWInputDevice *FWInput::sppDevices[FWINPUT_MAX_DEVICES];
// Ascii lookup table
unsigned char FWInput::sAsciiLookup[128] =
{
	#include "FWInputAsciiLookup.h"
};

//-----------------------------------------------------------------------------
// Description: Initialize input devices
// Parameters:	pPlatformData - Platform specific data
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWInput::init(void *pPlatformData)
{
	int i;
	for(i = 0; i < FWINPUT_MAX_DEVICES; i ++)
		sppDevices[i] = NULL;

	platformInit(pPlatformData);
}

//-----------------------------------------------------------------------------
// Description: Shutdown input devices
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWInput::shutdown()
{
	int i;
	for(i = 0; i < FWINPUT_MAX_DEVICES; i ++)
	{
		if(sppDevices[i] != NULL)
			delete sppDevices[i];
	}

	platformShutdown();
}

//-----------------------------------------------------------------------------
// Description: Update input devices
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWInput::update()
{
	int i;
	for(i = 0; i < FWINPUT_MAX_DEVICES; i ++)
	{
		if(sppDevices[i] != NULL)
			sppDevices[i]->update();
	}

	platformUpdate();
}

//-----------------------------------------------------------------------------
// Description: Get list of input devices
// Parameters:	ppDevices - Array to receive pointers to devices
// Returns: Number of devices
// Notes: <i><c>ppDevices</c></i> should be at least <c>INPUT_MAX_DEVICES</c> entries large
//-----------------------------------------------------------------------------
int FWInput::enumerateDevices(FWInputDevice **ppDevices)
{
	int numDevices = 0;

	while((numDevices < FWINPUT_MAX_DEVICES) && (sppDevices[numDevices] != NULL))
	{
		ppDevices[numDevices] = sppDevices[numDevices];
		numDevices ++;
	}

	return numDevices;
}

//-----------------------------------------------------------------------------
// Description: Get instance of an input devices
// Parameters:	type - Type of device desired
//				instance - Which instance of that type of device
// Returns: Pointer to device, or <c>NULL</c> if not found
// Notes:
//-----------------------------------------------------------------------------
FWInputDevice *FWInput::getDevice(DeviceType type, int instance)
{
	int i, instanceSeen = 0;
	for(i = 0; i < FWINPUT_MAX_DEVICES; i ++)
	{
		if(sppDevices[i] != NULL)
		{
			if(sppDevices[i]->getType() == type)
			{
				if(instanceSeen == instance)
					return sppDevices[i];

				instanceSeen ++;
			}
		}
	}

	return NULL;
}

//-----------------------------------------------------------------------------
// Description: Convert ascii code to input channel enum
// Parameters:	ascii - Ascii code
// Returns:	Input channel enum
// Notes:
//-----------------------------------------------------------------------------
FWInput::Channel FWInput::asciiToChannel(int ascii)
{
	FWASSERT((ascii >= 0) && (ascii <= 127));
	return (FWInput::Channel)sAsciiLookup[ascii];
}

//-----------------------------------------------------------------------------
// Description: Add a device
// Parameters:	pDevice - Device to add
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWInput::addDevice(FWInputDevice *pDevice)
{
	int i;
	for(i = 0; i < FWINPUT_MAX_DEVICES; i ++)
	{
		if(sppDevices[i] == NULL)
		{
			sppDevices[i] = pDevice;
			break;
		}
	}
}

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWInputFilter::FWInputFilter() :
mpBoundDevice(NULL),
mDeviceBinding(-1),
mGain(1.f),
mBias(0.f),
mDeadzone(0.f),
mFloatValue(0.f),
mRawValue(0),
mBoolValue(false),
mBoolTrue(false),
mBoolFalse(false)
{
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWInputFilter::~FWInputFilter()
{
}

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWInputDevice::FWInputDevice(void *pPlatformData) :
mpPlatformData(pPlatformData)
{
	int i;
	for(i = 0; i < FWINPUT_MAX_FILTERS; i ++)
		mppFilters[i] = NULL;

	mXAxis[0] = mXAxis[1] = mXAxis[2] = 0;
	mYAxis[0] = mYAxis[1] = mYAxis[2] = 0;
	mZAxis[0] = mZAxis[1] = mZAxis[2] = 0;
	mGyro = 0;

	for(i = 0; i < 16; i ++)
		mButtons[i] = false;

	for(i = 0; i < 256; i ++)
		mKeys[i] = false;

	FWInput::addDevice(this);
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWInputDevice::~FWInputDevice()
{
}

//-----------------------------------------------------------------------------
// Description: Creates and binds a filter to this device
// Parameters:
// Returns: Pointer to new filter
// Notes:
//-----------------------------------------------------------------------------
FWInputFilter *FWInputDevice::bindFilter()
{
	FWInputFilter	*pFilter = new FWInputFilter;
	addFilter(pFilter);
	return pFilter;
}

//-----------------------------------------------------------------------------
// Description: Add a filter to this device
// Parameters:	pFilter - Pointer to filter to add
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWInputDevice::addFilter(FWInputFilter *pFilter)
{
	if(pFilter->mpBoundDevice != NULL)
		return;

	int i;
	for(i = 0; i < FWINPUT_MAX_FILTERS; i ++)
	{
		if(mppFilters[i] == NULL)
		{
			mppFilters[i] = pFilter;
			pFilter->mpBoundDevice = this;
			pFilter->mDeviceBinding = i;
			return;
		}
	}
}

//-----------------------------------------------------------------------------
// Description: Unbind a filter from this device
// Parameters:	pFilter - Pointer to filter to unbind
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWInputDevice::unbindFilter(FWInputFilter *pFilter)
{
	if(pFilter->mpBoundDevice != this)
		return;

	mppFilters[pFilter->mDeviceBinding] = NULL;
	
	delete pFilter;
}

//-----------------------------------------------------------------------------
// Description: Get raw device value as bool
// Parameters:	channel - Input channel to read
// Returns: Device value as bool
// Notes: Value will be false if device channel does not exist
//-----------------------------------------------------------------------------
bool FWInputDevice::getRawBool(FWInput::Channel channel)
{
	if(channel >= FWInput::Channel_Key_A)
	{
		return mKeys[channel - FWInput::Channel_Key_A];
	}
	else if((channel >= FWInput::Channel_Button_0) && (channel <= FWInput::Channel_Button_15))
	{
		return mButtons[channel - FWInput::Channel_Button_0];
	}
	else
		return false;
}

//-----------------------------------------------------------------------------
// Description: Get raw device value as float
// Parameters:	channel - Channel to read
// Returns: Device value as float
// Notes: Value will be 0.f if device channel does not exist
//-----------------------------------------------------------------------------
float FWInputDevice::getRawFloat(FWInput::Channel channel)
{
	switch(channel)
	{
	case FWInput::Channel_XAxis_0:
		return (float)mXAxis[0] / 255.f;
	case FWInput::Channel_YAxis_0:
		return (float)mYAxis[0] / 255.f;
	case FWInput::Channel_ZAxis_0:
		return (float)mZAxis[0] / 255.f;
	case FWInput::Channel_XAxis_1:
		return (float)mXAxis[1] / 255.f;
	case FWInput::Channel_YAxis_1:
		return (float)mYAxis[1] / 255.f;
	case FWInput::Channel_ZAxis_1:
		return (float)mZAxis[1] / 255.f;
	case FWInput::Channel_XAxis_2:
		return (float)mXAxis[2] / 1023.f;
	case FWInput::Channel_YAxis_2:
		return (float)mYAxis[2] / 1023.f;
	case FWInput::Channel_ZAxis_2:
		return (float)mZAxis[2] / 1023.f;
	case FWInput::Channel_Gyro:
		return (float)mGyro / 1023.f;
	default:
		return 0.f;
	}
}

//-----------------------------------------------------------------------------
// Description: Updates this device and the bound filters
// Parameters:
// Returns:
// Notes: Called by the derived <c>update</c> function
//-----------------------------------------------------------------------------
void FWInputDevice::update()
{
	int i;
	for(i = 0; i < FWINPUT_MAX_FILTERS; i ++)
	{
		if(mppFilters[i] != NULL)
			mppFilters[i]->update();
	}
}

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters:	pPlatformData - Pointer to platform specific data
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWInputDeviceMouse::FWInputDeviceMouse(void *pPlatformData) :
FWInputDevice(pPlatformData),
mIsClientRelative(false)
{
}

//-----------------------------------------------------------------------------
// Description: Returns the device type
// Parameters:
// Returns: Type of device
// Notes:
//-----------------------------------------------------------------------------
FWInput::DeviceType FWInputDeviceMouse::getType() const
{
	return FWInput::DeviceType_Mouse;
}

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters:	pPlatformData - Pointer to platform specific data
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWInputDeviceKeyboard::FWInputDeviceKeyboard(void *pPlatformData) :
FWInputDevice(pPlatformData)
{
}

//-----------------------------------------------------------------------------
// Description: Returns the device type
// Parameters:
// Returns: Type of device
// Notes:
//-----------------------------------------------------------------------------
FWInput::DeviceType FWInputDeviceKeyboard::getType() const
{
	return FWInput::DeviceType_Keyboard;
}

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters:	pPlatformData - Pointer to platform specific data
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWInputDevicePad::FWInputDevicePad(void *pPlatformData) :
FWInputDevice(pPlatformData)
{
}

//-----------------------------------------------------------------------------
// Description: Returns the device type
// Parameters:
// Returns: Type of device
// Notes:
//-----------------------------------------------------------------------------
FWInput::DeviceType FWInputDevicePad::getType() const
{
	return FWInput::DeviceType_Pad;
}

//-----------------------------------------------------------------------------
// Description: Update input filter
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWInputFilter::update()
{
	// do keys
	if(mChannel >= FWInput::Channel_Key_A)
	{
		calcValues(mpBoundDevice->mKeys[mChannel - FWInput::Channel_Key_A]);
		return;
	}

	// do button array
	if((mChannel >= FWInput::Channel_Button_0) && (mChannel <= FWInput::Channel_Button_15))
	{
		calcValues(mpBoundDevice->mButtons[mChannel - FWInput::Channel_Button_0]);
		return;
	}

	// do axes
	switch(mChannel)
	{
	case FWInput::Channel_XAxis_0:
		calcValues(mpBoundDevice->mXAxis[0]);
		mRawValue = (mpBoundDevice->mXAxis[0] + 255) / 2;
		return;
	case FWInput::Channel_YAxis_0:
		calcValues(mpBoundDevice->mYAxis[0]);
		mRawValue = (mpBoundDevice->mYAxis[0] + 255) / 2;
		return;
	case FWInput::Channel_ZAxis_0:
		calcValues(mpBoundDevice->mZAxis[0]);
		mRawValue = (mpBoundDevice->mZAxis[0] + 255) / 2;
		return;
	case FWInput::Channel_XAxis_1:
		calcValues(mpBoundDevice->mXAxis[1]);
		mRawValue = (mpBoundDevice->mXAxis[1] + 255) / 2;
		return;
	case FWInput::Channel_YAxis_1:
		calcValues(mpBoundDevice->mYAxis[1]);
		mRawValue = (mpBoundDevice->mYAxis[1] + 255) / 2;
		return;
	case FWInput::Channel_ZAxis_1:
		calcValues(mpBoundDevice->mZAxis[1]);
		mRawValue = (mpBoundDevice->mZAxis[1] + 255) / 2;
		return;
	case FWInput::Channel_XAxis_2:
		calcValues(mpBoundDevice->mXAxis[2]);
		mRawValue = (mpBoundDevice->mXAxis[2] + 1023) / 2;
		return;
	case FWInput::Channel_YAxis_2:
		calcValues(mpBoundDevice->mYAxis[2]);
		mRawValue = (mpBoundDevice->mYAxis[2] + 1023) / 2;
		return;
	case FWInput::Channel_ZAxis_2:
		calcValues(mpBoundDevice->mZAxis[2]);
		mRawValue = (mpBoundDevice->mZAxis[2] + 1023) / 2;
		return;
	case FWInput::Channel_Gyro:
		calcValues(mpBoundDevice->mGyro);
		mRawValue = (mpBoundDevice->mGyro + 1023) / 2;
		return;
	default:
		return;
	}
}

//-----------------------------------------------------------------------------
// Description: Calculate filter values
// Parameters:	val - Value from device
// Returns:
// Notes: Applies gain, bias and deadzone to value
//-----------------------------------------------------------------------------
void FWInputFilter::calcValues(int val)
{
	// normalize value
	float fVal = 0.f;

	switch(mChannel)
	{
	case FWInput::Channel_XAxis_0:
	case FWInput::Channel_YAxis_0:
	case FWInput::Channel_ZAxis_0:
	case FWInput::Channel_XAxis_1:
	case FWInput::Channel_YAxis_1:
	case FWInput::Channel_ZAxis_1:
		fVal = (float)val / 255.f;
		break;
	case FWInput::Channel_XAxis_2:
	case FWInput::Channel_YAxis_2:
	case FWInput::Channel_ZAxis_2:
	case FWInput::Channel_Gyro:
		fVal = (float)val / 1023.f;
		break;
	default:
		assert(false);
	}

	// apply gain and bias
	fVal = fVal * mGain + mBias;
	// apply deadzone
	if(fabsf(fVal) < mDeadzone)
		fVal = 0.f;

	mFloatValue = fVal;
}

//-----------------------------------------------------------------------------
// Description: Calculate filter values
// Parameters:	val - Value from device
// Returns:
// Notes: Sets bool change variables and copies boolean value
//-----------------------------------------------------------------------------
void FWInputFilter::calcValues(bool val)
{
	// change from false to true
	if((mBoolValue == false) && (val == true))
		mBoolTrue = true;
	else
		mBoolTrue = false;
	
	// change from true to false
	if((mBoolValue == true) && (val == false))
		mBoolFalse = true;
	else
		mBoolFalse = false;

	// set the value
	mBoolValue = val;
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
