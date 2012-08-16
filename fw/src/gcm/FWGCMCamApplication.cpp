/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// GCM & Camera Application class
//
// $File: //nextgendev/Framework_050/src/FWGLCamApplication.cpp $
// $Author: asidwell $
// $Date: 2005/09/28 $
// $Revision: #2 $
//
// Copyright (C) 2005 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include "FWGCMCamApplication.h"

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters: 
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWGCMCamApplication::FWGCMCamApplication()
{
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters: 
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWGCMCamApplication::~FWGCMCamApplication()
{
}

//-----------------------------------------------------------------------------
// Description: Overloadable init function
// Parameters:	argc - Number of arguments
//				ppArgv - Argument list
// Returns: True if ok, false if not
// Notes: 
//-----------------------------------------------------------------------------
bool FWGCMCamApplication::onInit(int argc, char **ppArgv)
{
	return FWGCMApplication::onInit(argc, ppArgv);
}

//-----------------------------------------------------------------------------
// Description: Overloadable shutdown function
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWGCMCamApplication::onShutdown()
{
	FWGCMApplication::onShutdown();
}

//-----------------------------------------------------------------------------
// Description: Overloadable update function
// Parameters: 
// Returns: True if the application wants to continue, false otherwise
// Notes: This implementation updates the modelview matrix
//-----------------------------------------------------------------------------
bool FWGCMCamApplication::onUpdate()
{
	if(FWGCMApplication::onUpdate() == false)
		return false;

	mCamera.update();
	setViewMatrix(mCamera.getMatrix());

	return true;
}

//-----------------------------------------------------------------------------
// Description: Overloadable render function
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWGCMCamApplication::onRender()
{
	FWGCMApplication::onRender();
}

//-----------------------------------------------------------------------------
// Description: Overloadable size function
// Parameters:	dispInfo - Reference to display info class
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWGCMCamApplication::onSize(const FWDisplayInfo &dispInfo)
{
	FWGCMApplication::onSize(dispInfo);
}
