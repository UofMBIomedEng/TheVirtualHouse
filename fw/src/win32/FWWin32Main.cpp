/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Win32 entry point
//
// $File: //nextgendev/Framework_080/src/win32/FWWin32Main.cpp $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include <windows.h>
#if defined(_WIN32) && !defined(PSGL)
#include "win32/FWWin32GLWindow.h"
#endif//defined(_WIN32) && !defined(PSGL)
#ifdef _NULLWINDOW
#include "FWNullWindow.h"
#endif//_NULLWINDOW
#include "FWApplication.h"

//-----------------------------------------------------------------------------
// WinMain()
// Description: Win32 entry point
// Parameters:	hInstance - Win32 application instance
//				hPrevInstance - Previous win32 application instance, NULL
//				lpszCmdLine - Win32 command line, excluding app name
//				nCmdShow - How the window is to be shown
// Returns:
// Notes:
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	MSG					msg;
#if defined(_WIN32) && !defined(PSGL)
	FWWin32GLWindow		*pWindow;
#endif//defined(_WIN32) && !defined(PSGL)
#ifdef _NULLWINDOW
	FWNullWindow		*pWindow;
#endif//_NULLWINDOW

#ifdef _DEBUG
	// enable memory tracing if in debug
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif //_DEBUG

	// Make a conservative guess at the number of arguments
	int numArgs = 1;
	char *pArg = lpszCmdLine;
	while((pArg = strchr(pArg, ' ')) != NULL)
	{
		pArg ++;
		numArgs ++;
	}

	// Generate an argument list
	int argc;
	char **ppArgv = new char *[numArgs];
	pArg = lpszCmdLine;
	bool inQuote = false;
	for(argc = 0; argc < numArgs; argc ++)
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
				ppArgv[argc] = pArg;
			else
				ppArgv[argc] = ++ pArg;

			// find closing quote
			while(*pArg && *pArg != '\"')
				pArg ++;

			// check for end of string
			if(*pArg == '\0')
			{
				argc ++;
				break;
			}

			// replace closing quote with null terminator
			*pArg ++ ='\0';
			inQuote = false;
		}
		else
		{
			// set pointer to start of string
			ppArgv[argc] = pArg;

			// consume non-whitespace
			while(*pArg && (*pArg != ' ') && (*pArg != '\t') && (*pArg != '\n') && (*pArg != '\"'))
				pArg ++;

			// check for end of string
			if(*pArg == '\0')
			{
				argc ++;
				break;
			}

			if(*pArg == '\"')
				inQuote = true;
			
			// replace whitespace with null terminator
			*pArg ++ ='\0';
		}
	}

#if defined(_WIN32) && !defined(PSGL)
	// create new FWWin32GLWindow object
	pWindow = new FWWin32GLWindow(argc, ppArgv, FWApplication::getApplication()->getDisplayInfo(), FWApplication::getApplication()->getStartupInfo());
#endif//defined(_WIN32) && !defined(PSGL)

#ifdef _NULLWINDOW
	// create new FWNullWindow object
	pWindow = new FWNullWindow(iArgs, ppArgv, FWApplication::getApplication()->getDisplayInfo(), FWApplication::getApplication()->getStartupInfo());
#endif//_NULLWINDOW

	while(TRUE)
	{
		// while messages to process
		while(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == TRUE)
		{
			// get message
			if(GetMessage(&msg, NULL, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				// got a quit message
				pWindow->destroy();
				delete pWindow;
				delete []ppArgv;
				return TRUE;
			}
		}

		// call update & render functions
		pWindow->update();
		pWindow->render();
	}

	delete pWindow;
	delete []ppArgv;
	return TRUE;
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
