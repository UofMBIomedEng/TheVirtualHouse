/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Linux entry point
//
// $File: //nextgendev/Framework_080/src/linux/FWLinuxMain.cpp $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#if defined(__linux__) && !defined(PSGL)
#include "linux/FWLinuxGLWindow.h"
#endif//defined(__linux__) && !defined(PSGL)
#include "FWApplication.h"

//-----------------------------------------------------------------------------
// Description: Linux entry point
// Parameters:	argc - Number of command line arguments
//				argv - Array of command line arguments
// Returns:
// Notes:
//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
#if defined(__linux__) && !defined(PSGL)
	// create a new FWLinuxGLWindow object
	FWLinuxGLWindow *pWindow = new FWLinuxGLWindow(argc - 1, &argv[1], FWApplication::getApplication()->getDisplayInfo(), FWApplication::getApplication()->getStartupInfo());
#endif//defined(__linux__) && !defined(PSGL)

	bool IsRunning = true;
	while(IsRunning)
	{
		// call the update and render functions
		IsRunning = pWindow->update();
		pWindow->render();
	}

	// call the window's destroy function
	pWindow->destroy();
	// delete it
	delete pWindow;
	return 0;
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
