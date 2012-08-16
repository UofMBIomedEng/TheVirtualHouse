/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2007 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Application class
//
// $File: //nextgendev/Framework_080/src/FWApplication.cpp $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

//#include "FWGLInclude.h"
#include "FWApplication.h"
#include "FWTime.h"

// Static pointer to the application
FWApplication *FWApplication::spApplication = NULL;

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters: 
// Returns:
// Notes: Sets static pointer to application object
//-----------------------------------------------------------------------------
FWApplication::FWApplication()
{
	// set the static pointer to ourselves
	spApplication = this;
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
FWApplication::~FWApplication()
{
}


//-----------------------------------------------------------------------------
// Description: Overloadable initialization function
// Parameters:	argc - Number of arguments
//				ppArgv - Argument list
// Returns: True if application initialized ok, false otherwise
// Notes: 
//-----------------------------------------------------------------------------
bool FWApplication::onInit(int argc, char **ppArgv)
{
	// stop unused parameter warnings
	(void)argc;
	(void)ppArgv;

	return true;
}

//-----------------------------------------------------------------------------
// Description: Overloadable shutdown function
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWApplication::onShutdown()
{
}

//-----------------------------------------------------------------------------
// Description: Overloadable update function
// Parameters: 
// Returns: True if the application wants to continue, false otherwise
// Notes:
//-----------------------------------------------------------------------------
bool FWApplication::onUpdate()
{
	return true;
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
