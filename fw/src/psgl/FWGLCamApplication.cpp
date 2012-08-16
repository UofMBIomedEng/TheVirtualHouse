/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// GL & Camera Application class
//
// $File: //nextgendev/Framework_080/src/FWGLCamApplication.cpp $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include "psgl/FWGLCamApplication.h"

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters: 
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWGLCamApplication::FWGLCamApplication()
{
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters: 
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWGLCamApplication::~FWGLCamApplication()
{
}

//-----------------------------------------------------------------------------
// Description: Overloadable init function
// Parameters:	argc - Number of arguments
//				ppArgv - Argument list
// Returns: True if ok, false if not
// Notes: 
//-----------------------------------------------------------------------------
bool FWGLCamApplication::onInit(int argc, char **ppArgv)
{
	return FWGLApplication::onInit(argc, ppArgv);
}

//-----------------------------------------------------------------------------
// Description: Overloadable shutdown function
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWGLCamApplication::onShutdown()
{
	FWGLApplication::onShutdown();
}

//-----------------------------------------------------------------------------
// Description: Overloadable update function
// Parameters: 
// Returns: True if the application wants to continue, false otherwise
// Notes: This implementation updates the modelview matrix
//-----------------------------------------------------------------------------
bool FWGLCamApplication::onUpdate()
{
	if(FWGLApplication::onUpdate() == false)
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
void FWGLCamApplication::onRender()
{
	FWGLApplication::onRender();
}

//-----------------------------------------------------------------------------
// Description: Overloadable size function
// Parameters:	dispInfo - Reference to display info class
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWGLCamApplication::onSize(const FWDisplayInfo &dispInfo)
{
	FWGLApplication::onSize(dispInfo);
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
