/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// GL & Controlled Camera Application class
//
// $File: //nextgendev/Framework_080/src/FWGLCamControlApplication.cpp $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include "psgl/FWGLCamControlApplication.h"

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters: 
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWGLCamControlApplication::FWGLCamControlApplication() :
mLastUpdate(FWTime::sZero),
mTurnRate(FWGLCAMAPP_DEFAULT_TURN_RATE),
mMoveRate(FWGLCAMAPP_DEFAULT_MOVE_RATE)
{
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters: 
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWGLCamControlApplication::~FWGLCamControlApplication()
{
}

//-----------------------------------------------------------------------------
// Description: Overloadable initialization function
// Parameters:	argc - Number of arguments
//				ppArgv - Argument list
// Returns: True if application initialized ok, false otherwise
// Notes: 
//-----------------------------------------------------------------------------
bool FWGLCamControlApplication::onInit(int argc, char **ppArgv)
{
	if(FWGLCamApplication::onInit(argc, ppArgv) == false)
		return false;

	FWInputDevice	*pPad = FWInput::getDevice(FWInput::DeviceType_Pad, 0);

	if(pPad != NULL)
	{
		mpInputX0 = pPad->bindFilter();
		mpInputX0->setChannel(FWInput::Channel_XAxis_0);
		mpInputX0->setGain(0.001f);
		mpInputX0->setDeadzone(0.0002f);

		mpInputY0 = pPad->bindFilter();
		mpInputY0->setChannel(FWInput::Channel_YAxis_0);
		mpInputY0->setGain(0.001f);
		mpInputY0->setDeadzone(0.0002f);

		mpInputX1 = pPad->bindFilter();
		mpInputX1->setChannel(FWInput::Channel_XAxis_1);
		mpInputX1->setGain(0.1f);
		mpInputX1->setDeadzone(0.02f);

		mpInputY1 = pPad->bindFilter();
		mpInputY1->setChannel(FWInput::Channel_YAxis_1);
		mpInputY1->setGain(-0.1f);
		mpInputY1->setDeadzone(0.02f);
	}
	else
	{
		mpInputX0 = mpInputY0 = mpInputX1 = mpInputY1 = NULL;
	}

	return true;
}

//-----------------------------------------------------------------------------
// Description: Overloadable shutdown function
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWGLCamControlApplication::onShutdown()
{
	// Call parent class
	FWGLCamApplication::onShutdown();

	// unbind input filters
	FWInputDevice	*pPad = FWInput::getDevice(FWInput::DeviceType_Pad, 0);

	if(pPad != NULL)
	{
		pPad->unbindFilter(mpInputX0);
		pPad->unbindFilter(mpInputY0);
		pPad->unbindFilter(mpInputX1);
		pPad->unbindFilter(mpInputY1);
	}
}

//-----------------------------------------------------------------------------
// Description: Overloadable update function
// Parameters: 
// Returns: True if the application wants to continue, false otherwise
// Notes: This implementation routes the inputs to the camera
//-----------------------------------------------------------------------------
bool FWGLCamControlApplication::onUpdate()
{
	FWTimeVal	time;
	float		deltaTime;
	
	time = FWTime::getCurrentTime();
	if(mLastUpdate == FWTime::sZero)
	{
		deltaTime = 0.f;
		mLastUpdate = time;
	}
	else
	{
		deltaTime = (float)(time - mLastUpdate);
		mLastUpdate = time;
	}

	switch(mCamera.getMode())
	{
	case FWCamera::Mode_FlyThru:
		setInputsFlyThru(deltaTime);
		break;
	case FWCamera::Mode_LookAt:
		setInputsLookAt(deltaTime);
		break;
	}

	if(FWGLCamApplication::onUpdate() == false)
		return false;

	return true;
}

//-----------------------------------------------------------------------------
// Description: Overloadable render function
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWGLCamControlApplication::onRender()
{
	FWGLCamApplication::onRender();
}

//-----------------------------------------------------------------------------
// Description: Overloadable size function
// Parameters:	dispInfo - Reference to display info class
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWGLCamControlApplication::onSize(const FWDisplayInfo &dispInfo)
{
	FWGLCamApplication::onSize(dispInfo);
}

//-----------------------------------------------------------------------------
// Description: Feed inputs to camera in fly thru mode
// Parameters: deltaTime - Time since last update in seconds
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWGLCamControlApplication::setInputsFlyThru(float deltaTime)
{
	mCamera.setPan(mCamera.getPan() + (mpInputX0 ? mpInputX0->getFloatValue() : 0.f) * deltaTime * mTurnRate);
	mCamera.setTilt(mCamera.getTilt() + (mpInputY0 ? mpInputY0->getFloatValue() : 0.f) * deltaTime * mTurnRate);

	Vector3	zVec, xVec;
	Matrix3	xRot, yRot;

	xRot = Matrix3::rotationX(-mCamera.getTilt());
	yRot = Matrix3::rotationY(-mCamera.getPan());

	zVec = (yRot * xRot) * -Vector3::zAxis();
	xVec = (yRot * xRot) * Vector3::xAxis();

	mCamera.setPosition(mCamera.getPosition() + (xVec * (mpInputX1 ? mpInputX1->getFloatValue() : 0.f) + zVec * (mpInputY1 ? mpInputY1->getFloatValue() : 0.f)) * deltaTime * mMoveRate);
}

//-----------------------------------------------------------------------------
// Description: Feed inputs to camera in look at mode
// Parameters: deltaTime - Time since last update in seconds
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWGLCamControlApplication::setInputsLookAt(float deltaTime)
{
	mCamera.setPan(mCamera.getPan() - (mpInputX0 ? mpInputX0->getFloatValue() : 0.f) * deltaTime * mTurnRate);
	mCamera.setTilt(mCamera.getTilt() - (mpInputY0 ? mpInputY0->getFloatValue() : 0.f) * deltaTime * mTurnRate);
	mCamera.setDistance(mCamera.getDistance() + (mpInputY1 ? -mpInputY1->getFloatValue() : 0.f) * deltaTime * mMoveRate);
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
