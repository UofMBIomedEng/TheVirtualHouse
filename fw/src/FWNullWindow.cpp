/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Null Window class
//
// $File: //nextgendev/Framework_080/src/FWNullWindow.cpp $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include "FWNullWindow.h"
#include "FWApplication.h"

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters:	argc - Number of arguments
//				ppArgv - Argument list
//				dispInfo - Display info class
//				startupInfo - Startup info class
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
FWNullWindow::FWNullWindow(int argc, char **ppArgv, const FWDisplayInfo &dispInfo, const FWStartupInfo &startupInfo) :
FWWindow(argc, ppArgv, dispInfo, startupInfo)
{
	// initialize application
	FWWindow::init();

	if(mInit)
	{
		// call size callback to set projection matrix etc.
		FWApplication::getApplication()->onSize(mDispInfo);
	}
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWNullWindow::~FWNullWindow()
{
}

//-----------------------------------------------------------------------------
// Description: Window update function
// Parameters:
// Returns: True if continuing to run, false otherwise
// Notes:
//-----------------------------------------------------------------------------
bool FWNullWindow::update()
{
	if(mInit && mUpdate)
	{
		FWWindow::update();
		return mUpdate;
	}
	else
		return false;
}

//-----------------------------------------------------------------------------
// Description: Sets rendering context
// Parameters:
// Returns:
// Notes: Doesn't actually do anything
//-----------------------------------------------------------------------------
void FWNullWindow::setRenderingContext()
{
}

//-----------------------------------------------------------------------------
// Description: Clears rendering context
// Parameters:
// Returns:
// Notes: Doesn't actually do anything
//-----------------------------------------------------------------------------
void FWNullWindow::clearRenderingContext()
{
}

//-----------------------------------------------------------------------------
// Description: Do buffer flip
// Parameters:
// Returns:
// Notes: Doesn't actually do anything
//-----------------------------------------------------------------------------
void FWNullWindow::flip()
{
}

//-----------------------------------------------------------------------------
// Description: Gets called on shutdown
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWNullWindow::destroy()
{
}

//-----------------------------------------------------------------------------
// Description: Returns the window system context
// Parameters: 
// Returns: <c>NULL</c> pointer
// Notes: Returns <c>NULL</c> since this is the null implementation
//-----------------------------------------------------------------------------
void *FWNullWindow::getWindowSystemContext()
{
	return (void *)0;
}

//-----------------------------------------------------------------------------
// Description: Get display info struct
// Parameters: 
// Returns: Reference to display info
// Notes: 
//-----------------------------------------------------------------------------
FWDisplayInfo &FWNullWindow::getDisplayInfo()
{
	return mDispInfo;
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
