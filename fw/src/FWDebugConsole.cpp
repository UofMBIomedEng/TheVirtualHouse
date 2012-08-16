/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Debug console
//
// $File: //nextgendev/Framework_080/src/FWDebugConsole.cpp $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "FWDebug.h"

bool							FWDebugConsole::sInit = false;
FWDebugConsole::ConsoleString	FWDebugConsole::sStrings[FWDEBUGCONSOLE_NUMBER_OF_STRINGS];
int								FWDebugConsole::sCurrentString;
float							FWDebugConsole::sTimeout;
int								FWDebugConsole::sScrWidth;
int								FWDebugConsole::sScrHeight;

//-----------------------------------------------------------------------------
// Description: Initializes the debug console
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWDebugConsole::init()
{
	sInit = true;
	sTimeout = FWDEBUGCONSOLE_DEFAULT_TIMEOUT;
	sCurrentString = 0;
	int i;
	for(i = 0; i < FWDEBUGCONSOLE_NUMBER_OF_STRINGS; i ++)
	{
		sStrings[i].mIsAlive = false;
		memset(sStrings[i].mString, 0, FWDEBUGCONSOLE_STRING_LENGTH);
	}
}

//-----------------------------------------------------------------------------
// Description: Shutdown debug console
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWDebugConsole::shutdown()
{
}

//-----------------------------------------------------------------------------
// Description: Update the debug console
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWDebugConsole::update()
{
	if(!sInit)
		return;

	int i;
	for(i = 0; i < FWDEBUGCONSOLE_NUMBER_OF_STRINGS; i ++)
	{
		if(sStrings[i].mIsAlive == true)
		{
			float age = (float)(FWTime::getCurrentTime() - sStrings[i].mTimeOfBirth);
			if(age >= sTimeout)
				sStrings[i].mIsAlive = false;
		}
	}
}

//-----------------------------------------------------------------------------
// Description: Renders the console text
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWDebugConsole::render()
{
	if(!sInit)
		return;

	int left, right, top, bottom;
	FWDebugFont::getSafeArea(&left, &right, &top, &bottom);

	int i = ((sCurrentString - 1) + FWDEBUGCONSOLE_NUMBER_OF_STRINGS) % FWDEBUGCONSOLE_NUMBER_OF_STRINGS;
	int y = sScrHeight - (top + bottom);
	int glyphHeight = FWDebugFont::getGlyphHeight();

	while((sStrings[i].mIsAlive == true) && ((y - glyphHeight) >= 0))
	{
		y -= sStrings[i].mHeight;
		FWDebugFont::setPosition(0, y);
		FWDebugFont::setColor(FWDEBUGCONSOLE_DEFAULT_COLOR, 1.f - ((float)(FWTime::getCurrentTime() - sStrings[i].mTimeOfBirth) / sTimeout));
		FWDebugFont::print(sStrings[i].mString, sStrings[i].mLength);

		i --;
		if(i < 0)
			i = FWDEBUGCONSOLE_NUMBER_OF_STRINGS - 1;
	}
}

//-----------------------------------------------------------------------------
// Description: Adds a string to the console
// Parameters:	pText - Text string
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWDebugConsole::print(const char *pText)
{
	if(!sInit)
		return;

	int width;

	sStrings[sCurrentString % FWDEBUGCONSOLE_NUMBER_OF_STRINGS].mIsAlive = true;
	sStrings[sCurrentString % FWDEBUGCONSOLE_NUMBER_OF_STRINGS].mTimeOfBirth = FWTime::getCurrentTime();
	FWDebugFont::getExtents(pText, &width, &sStrings[sCurrentString % FWDEBUGCONSOLE_NUMBER_OF_STRINGS].mHeight, sScrWidth);
	strncpy(sStrings[sCurrentString % FWDEBUGCONSOLE_NUMBER_OF_STRINGS].mString, pText, FWDEBUGCONSOLE_STRING_LENGTH - 1);
	sStrings[sCurrentString % FWDEBUGCONSOLE_NUMBER_OF_STRINGS].mLength = strlen(sStrings[sCurrentString % FWDEBUGCONSOLE_NUMBER_OF_STRINGS].mString);
	sCurrentString = (sCurrentString + 1) % FWDEBUGCONSOLE_NUMBER_OF_STRINGS;
}

//-----------------------------------------------------------------------------
// Description: Adds a formatted string to the console
// Parameters:	pText - Text string
//				... - Variable number of arguments following
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWDebugConsole::printf(const char *pText, ...)
{
	va_list	arglist;
	char	tempstr[FWDEBUGCONSOLE_STRING_LENGTH];

	//build the output string
	va_start(arglist, pText);
	vsprintf(tempstr, pText, arglist);
	va_end(arglist);

	print(tempstr);
}

//-----------------------------------------------------------------------------
// Description: Called on display resize
// Parameters:	dispInfo - Display info class
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWDebugConsole::resize(const FWDisplayInfo &dispInfo)
{
	if(!sInit)
		return;

	sScrWidth = dispInfo.mWidth;
	sScrHeight = dispInfo.mHeight;

	// recalculate extents of alive strings
	int i;
	int	width;
	for(i = 0; i < FWDEBUGCONSOLE_NUMBER_OF_STRINGS; i ++)
	{
		if(sStrings[i].mIsAlive == true)
			FWDebugFont::getExtents(sStrings[i].mString, &width, &sStrings[i].mHeight, sScrWidth);
	}
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
