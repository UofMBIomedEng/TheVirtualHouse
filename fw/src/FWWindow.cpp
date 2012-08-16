/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Generic Window class
//
// $File: //nextgendev/Framework_080/src/FWWindow.cpp $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#ifdef __CELLOS_LV2__
#include <sys/paths.h>
#endif
#include "FWWindow.h"
#include "FWApplication.h"
#include "FWInput.h"

// Pointer to the window object
FWWindow *FWWindow::spWindow = NULL;

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters:	argc - Number of arguments
//				ppArgv - Argument list
//				dispInfo - Display info class
//				startupInfo - Startup info class
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
FWWindow::FWWindow(int argc, char **ppArgv, const FWDisplayInfo &dispInfo, const FWStartupInfo &startupInfo) :
mArgc(argc),
mppArgv(ppArgv),
mpArgFile(NULL)
{
	// set static window pointer
	spWindow = this;

	// parse arguments file if it exists
	parseArgumentsFile(startupInfo.mArgumentsFilename);

	// stop unused parameter warning
	(void)dispInfo;
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
FWWindow::~FWWindow()
{
	if(mpArgFile)
	{
		delete []mpArgFile;
		delete []mppArgv;
	}
}

//-----------------------------------------------------------------------------
// Description: Init framework
// Parameters: 
// Returns:
// Notes: Called by window class
//-----------------------------------------------------------------------------
void FWWindow::init()
{
	// initialize timer functions
	FWTime::init();

	// initialize font functions
	FWDebugFont::init();

	// initialize debug console
	mUseDebugConsole = FWApplication::getApplication()->getStartupInfo().mUseDebugConsole;
	if(mUseDebugConsole)
		FWDebugConsole::init();

	// call application init function
	mInit = mUpdate = FWApplication::getApplication()->onInit(mArgc, mppArgv);
}

//-----------------------------------------------------------------------------
// Description: Update framework
// Parameters: 
// Returns:
// Notes: Called by window class
//-----------------------------------------------------------------------------
void FWWindow::update()
{
	// update timer function
	FWTime::update();
	// update input devices
	FWInput::update();
	// update console
	if(mUseDebugConsole)
		FWDebugConsole::update();
	// call application update
	mUpdate = FWApplication::getApplication()->onUpdate();
}

//-----------------------------------------------------------------------------
// Description: Render scene
// Parameters: 
// Returns:
// Notes: Called by window class once per frame
//-----------------------------------------------------------------------------
void FWWindow::render()
{
	if(mInit && mUpdate)
	{
		// set rendering context in case it's not set
		setRenderingContext();

		// call application render
		FWApplication::getApplication()->onRender();

		// render console
		if(mUseDebugConsole)
			FWDebugConsole::render();

		// swap buffers
		flip();

		// we did clear the rendering context here
		// but removed it by popular request
	}
}

//-----------------------------------------------------------------------------
// Description: Destroy everything
// Parameters: 
// Returns:
// Notes: Called by window class on shutdown
//-----------------------------------------------------------------------------
void FWWindow::destroy()
{
	// call application shutdown function
	if(mInit)
		FWApplication::getApplication()->onShutdown();

	// shutdown input
	FWInput::shutdown();

	// free font resources
	FWDebugFont::shutdown();
}

//-----------------------------------------------------------------------------
// Description: Get command line args from file and parse them
// Parameters:	pArgumentsFile - Name of arguments file
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWWindow::parseArgumentsFile(const char *pArgumentsFile)
{
#ifdef __CELLOS_LV2__
	char	fileName[256];
	sprintf(fileName, "%s/%s", SYS_APP_HOME, pArgumentsFile);
	
	FILE	*fp = fopen(fileName, "r");
#else
	FILE	*fp = fopen(pArgumentsFile, "r");
#endif

	if(fp == NULL)
		return;

	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);

	// allocate an extra byte, in case the file doesn't terminate
	// with a '\0'
	mpArgFile = new char[size + 1];
	memset(mpArgFile, 0, size + 1);

	fseek(fp, 0, SEEK_SET);
	fread(mpArgFile, 1, size, fp);
	fclose(fp);

	// Make a conservative guess at the number of arguments
	int numArgs = 1;
	char *pArg = mpArgFile;
	while((pArg = strchr(pArg, ' ')) != NULL)
	{
		pArg ++;
		numArgs ++;
	}

	// Generate an argument list
	mppArgv = new char *[numArgs];
	pArg = mpArgFile;
	bool inQuote = false;
	for(mArgc = 0; mArgc < numArgs; mArgc ++)
	{
		// consume whitespace
		while((*pArg == ' ') || (*pArg == '\t') || (*pArg == '\n'))
			pArg ++;

		// check for end of string
		if(*pArg == '\0')
			break;

		// is it a quote?
		if((*pArg == '\"') || (inQuote == true))
		{
			// set pointer to start of quoted string
			if(inQuote == true)
				mppArgv[mArgc] = pArg;
			else
				mppArgv[mArgc] = ++ pArg;

			// find closing quote
			while(*pArg && *pArg != '\"')
				pArg ++;

			// check for end of string
			if(*pArg == '\0')
			{
				mArgc ++;
				break;
			}

			// replace closing quote with null terminator
			*pArg ++ ='\0';
			inQuote = false;
		}
		else
		{
			// set pointer to start of string
			mppArgv[mArgc] = pArg;

			// consume non-whitespace
			while(*pArg && (*pArg != ' ') && (*pArg != '\t') && (*pArg != '\n') && (*pArg != '\"'))
				pArg ++;

			// check for end of string
			if(*pArg == '\0')
			{
				mArgc ++;
				break;
			}

			if(*pArg == '\"')
				inQuote = true;
			
			// replace whitespace with null terminator
			*pArg ++ ='\0';
		}
	}
}

//-----------------------------------------------------------------------------
// Description: Called on window resize
// Parameters:	width - New width of window
//				height - New height of window
// Returns:
// Notes: Called by window class
//-----------------------------------------------------------------------------
void FWWindow::resize(int width, int height)
{
	if(mInit && mUpdate)
	{
		// set rendering context in case it's not set
		setRenderingContext();

		FWDisplayInfo &dispInfo = getDisplayInfo();

		dispInfo.mWidth = width;
		dispInfo.mHeight = height;

		// refresh debug console
		if(mUseDebugConsole)
			FWDebugConsole::resize(dispInfo);

		// call application resize
		FWApplication::getApplication()->onSize(dispInfo);

		// we did clear the rendering context here
		// but removed it by popular request
	}
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
