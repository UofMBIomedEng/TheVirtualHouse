/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Debug font functionality
//
// $File: //nextgendev/Framework_080/src/FWDebugFont.cpp $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include "FWDebug.h"
#include "FWDebugFont.h"
#include "FWDebugFontRenderer.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#ifdef FWDEBUGFONT_USE_QUADS
#define NUM_VERTS_PER_GLYPH	4
#else
#define NUM_VERTS_PER_GLYPH	6
#endif

// font data
unsigned char FWDebugFont::sFontData[FWDEBUGFONT_DATA_SIZE] =
{

	#include "FWDebugFontData.h"

};

// screen position
int		FWDebugFont::sXPos;
int		FWDebugFont::sYPos;
// screen res
int		FWDebugFont::sXRes;
int		FWDebugFont::sYRes;
// safe area positions
int		FWDebugFont::sLeftSafe;
int		FWDebugFont::sRightSafe;
int		FWDebugFont::sTopSafe;
int		FWDebugFont::sBottomSafe;
// text color
float	FWDebugFont::sR;
float	FWDebugFont::sG;
float	FWDebugFont::sB;
float	FWDebugFont::sA;
// vertex arrays for rendering
FWDebugFont::Position	*FWDebugFont::spPositions[2];
FWDebugFont::TexCoord	*FWDebugFont::spTexCoords[2];
FWDebugFont::Color		*FWDebugFont::spColors[2];
// control code colors
FWDebugFont::Color		FWDebugFont::sDefaultColors[8] =
{
	{ 0.f, 0.f, 0.f, 1.f },	// black
	{ 0.f, 0.f, 1.f, 1.f },	// blue
	{ 1.f, 0.f, 0.f, 1.f },	// red
	{ 1.f, 0.f, 1.f, 1.f },	// magenta
	{ 0.f, 1.f, 0.f, 1.f },	// green
	{ 0.f, 1.f, 1.f, 1.f },	// cyan
	{ 1.f, 1.f, 0.f, 1.f },	// yellow
	{ 1.f, 1.f, 1.f, 1.f },	// white
};
// font renderer
FWDebugFontRenderer	*FWDebugFont::spRenderer = NULL;

//-----------------------------------------------------------------------------
// Description: Initializes the debug font class
// Parameters:	
// Returns:
// Notes: Creates texture and allocates vertex arrays
//-----------------------------------------------------------------------------
void FWDebugFont::init()
{
	// initialize renderer
	if(!spRenderer)
		return;
	
	spRenderer->init();

	// initialize various bits	
	sXPos = sYPos = 0;
	sLeftSafe = sRightSafe = sTopSafe = sBottomSafe = FWDEBUGFONT_DEFAULT_SAFE_AREA;
	sR = sG = sB = 1.f;

	// allocate vertex arrays
	spPositions[0] = new Position[FWDEBUGFONT_MAX_CHAR_COUNT * NUM_VERTS_PER_GLYPH];
	spTexCoords[0] = new TexCoord[FWDEBUGFONT_MAX_CHAR_COUNT * NUM_VERTS_PER_GLYPH];
	spPositions[1] = new Position[FWDEBUGFONT_MAX_CHAR_COUNT * NUM_VERTS_PER_GLYPH];
	spTexCoords[1] = new TexCoord[FWDEBUGFONT_MAX_CHAR_COUNT * NUM_VERTS_PER_GLYPH];
	spColors[0] = new Color[FWDEBUGFONT_MAX_CHAR_COUNT * NUM_VERTS_PER_GLYPH];
	spColors[1] = new Color[FWDEBUGFONT_MAX_CHAR_COUNT * NUM_VERTS_PER_GLYPH];
}

//-----------------------------------------------------------------------------
// Description: Shutdown the debug font class
// Parameters:	
// Returns:
// Notes: Frees texture and vertex arrays
//-----------------------------------------------------------------------------
void FWDebugFont::shutdown()
{
	// shutdown renderer
	if(!spRenderer)
		return;
	
	spRenderer->shutdown();

	// delete vertex arrays
	delete []spPositions[0];
	delete []spTexCoords[0];
	delete []spPositions[1];
	delete []spTexCoords[1];
	delete []spColors[0];
	delete []spColors[1];
}

//-----------------------------------------------------------------------------
// Description: Print formatted text on screen
// Parameters:	pText - Format string
//				... - Variable number of arguments following
// Returns:
// Notes: Uses vsprintf
//-----------------------------------------------------------------------------
void FWDebugFont::printf(const char *pText, ...)
{
	va_list	arglist;
	char	tempstr[1024];

	//build the output string
	va_start(arglist, pText);
	vsprintf(tempstr, pText, arglist);
	va_end(arglist);

	print(tempstr, strlen(tempstr));
}

//-----------------------------------------------------------------------------
// Description: Print some text on screen
// Parameters:	pText - Text string
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWDebugFont::print(const char *pText)
{
	print(pText, strlen(pText));
}

//-----------------------------------------------------------------------------
// Description: Print some text on screen
// Parameters:	pText - Text string
//				numChars - Number of characters in string
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWDebugFont::print(const char *pText, int numChars)
{
	int	c;
	int	offset;
	int	pass;
	int	numPasses;

	if(!spRenderer)
		return;

	numPasses = (numChars / FWDEBUGFONT_MAX_CHAR_COUNT) + 1;
	offset = 0;

	spRenderer->printStart(sR, sG, sB, sA);

	// for each pass
	for(pass = 0; pass < numPasses; pass ++)
	{
		FWDebugFont::TexCoord *pTexCoords = spTexCoords[pass & 1];
		FWDebugFont::Position *pPositions = spPositions[pass & 1];
		FWDebugFont::Color *pColors = spColors[pass & 1];
		int numVerts = 0;
		// for each character in the pass
		for(c = 0; ((offset + c) < numChars) && (c < FWDEBUGFONT_MAX_CHAR_COUNT); c ++)
		{
			// if it's a printable character
			if(getPrintable(pText[offset + c]))
			{
				// top left
				pPositions[numVerts].mX = calcPos(sXPos + sLeftSafe, sXRes);
				pPositions[numVerts].mY = calcPos(sYPos + sTopSafe, sYRes) * -1.f;
				pPositions[numVerts].mZ = 0.f;
				pTexCoords[numVerts].mS = calcS0((unsigned char)pText[offset + c]);
				pTexCoords[numVerts].mT = calcT0((unsigned char)pText[offset + c]);
				pColors[numVerts].mR = sR;
				pColors[numVerts].mG = sG;
				pColors[numVerts].mB = sB;
				pColors[numVerts].mA = sA;
				numVerts ++;

				// top right
				pPositions[numVerts].mX = calcPos(sXPos + sLeftSafe + getGlyphWidth(), sXRes);
				pPositions[numVerts].mY = calcPos(sYPos + sTopSafe, sYRes) * -1.f;
				pPositions[numVerts].mZ = 0.f;
				pTexCoords[numVerts].mS = calcS1((unsigned char)pText[offset + c]);
				pTexCoords[numVerts].mT = calcT0((unsigned char)pText[offset + c]);
				pColors[numVerts].mR = sR;
				pColors[numVerts].mG = sG;
				pColors[numVerts].mB = sB;
				pColors[numVerts].mA = sA;
				numVerts ++;

				// bottom right
				pPositions[numVerts].mX = calcPos(sXPos + sLeftSafe + getGlyphWidth(), sXRes);
				pPositions[numVerts].mY = calcPos(sYPos + sTopSafe + getGlyphHeight(), sYRes) * -1.f;
				pPositions[numVerts].mZ = 0.f;
				pTexCoords[numVerts].mS = calcS1((unsigned char)pText[offset + c]);
				pTexCoords[numVerts].mT = calcT1((unsigned char)pText[offset + c]);
				pColors[numVerts].mR = sR;
				pColors[numVerts].mG = sG;
				pColors[numVerts].mB = sB;
				pColors[numVerts].mA = sA;
				numVerts ++;

#ifndef FWDEBUGFONT_USE_QUADS
				// bottom right
				pPositions[numVerts].mX = calcPos(sXPos + sLeftSafe + getGlyphWidth(), sXRes);
				pPositions[numVerts].mY = calcPos(sYPos + sTopSafe + getGlyphHeight(), sYRes) * -1.f;
				pPositions[numVerts].mZ = 0.f;
				pTexCoords[numVerts].mS = calcS1((unsigned char)pText[offset + c]);
				pTexCoords[numVerts].mT = calcT1((unsigned char)pText[offset + c]);
				pColors[numVerts].mR = sR;
				pColors[numVerts].mG = sG;
				pColors[numVerts].mB = sB;
				pColors[numVerts].mA = sA;
				numVerts ++;
#endif

				// bottom left
				pPositions[numVerts].mX = calcPos(sXPos + sLeftSafe, sXRes);
				pPositions[numVerts].mY = calcPos(sYPos + sTopSafe + getGlyphHeight(), sYRes) * -1.f;
				pPositions[numVerts].mZ = 0.f;
				pTexCoords[numVerts].mS = calcS0((unsigned char)pText[offset + c]);
				pTexCoords[numVerts].mT = calcT1((unsigned char)pText[offset + c]);
				pColors[numVerts].mR = sR;
				pColors[numVerts].mG = sG;
				pColors[numVerts].mB = sB;
				pColors[numVerts].mA = sA;
				numVerts ++;

#ifndef FWDEBUGFONT_USE_QUADS
				// top left
				pPositions[numVerts].mX = calcPos(sXPos + sLeftSafe, sXRes);
				pPositions[numVerts].mY = calcPos(sYPos + sTopSafe, sYRes) * -1.f;
				pPositions[numVerts].mZ = 0.f;
				pTexCoords[numVerts].mS = calcS0((unsigned char)pText[offset + c]);
				pTexCoords[numVerts].mT = calcT0((unsigned char)pText[offset + c]);
				pColors[numVerts].mR = sR;
				pColors[numVerts].mG = sG;
				pColors[numVerts].mB = sB;
				pColors[numVerts].mA = sA;
				numVerts ++;
#endif

				// advance along the line one character width
				sXPos += (getGlyphWidth() + 1);
			}
			else if(pText[offset + c] == '\n')
			{
				// newline, wrap the cursor pos
				sXPos = 0;
				sYPos += (getGlyphHeight() + 1);
			}
			else if(pText[offset + c] == '\t')
			{
				// tab, increment FWDEBUGFONT_TAB_SIZE characters
				sXPos += FWDEBUGFONT_TAB_SIZE * (getGlyphWidth() + 1);
			}
			else if((signed char)pText[offset + c] < 0)
			{
				int iCode = (unsigned char)pText[offset + c] - 128;
				if(iCode >= 0 && iCode < 8)
				{
					// color control code
					sR = sDefaultColors[iCode].mR;
					sG = sDefaultColors[iCode].mG;
					sB = sDefaultColors[iCode].mB;
				}
			}
			else
			{
				// unprintable character, skip it
				sXPos += (getGlyphWidth() + 1);
			}

			// check for screen wrap
			if((sXPos + (getGlyphWidth() + 1)) >= (sXRes - (sLeftSafe + sRightSafe)))
			{
				sXPos = 0;
				sYPos += (getGlyphHeight() + 1);
			}
		}

		offset += FWDEBUGFONT_MAX_CHAR_COUNT;

		FWASSERT(spRenderer);
		spRenderer->printPass(pPositions, pTexCoords, pColors, numVerts);
	}

	FWASSERT(spRenderer);
	spRenderer->printEnd();
}

//-----------------------------------------------------------------------------
// Description: Get the screen extents of a string
// Parameters:	pText - Text string
//				pWidth - Pointer to int to return width in pixels
//				pHeight - Pointer to int to return height in pixels
//				scrWidth - Screen width in pixels
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWDebugFont::getExtents(const char *pText, int *pWidth, int *pHeight, int scrWidth)
{
	bool linefeed = true;
	int len;
	int	x;
	int	y;

	len = strlen(pText);
	x = y = 0;
	*pWidth = *pHeight = 0;

	int i;
	for(i = 0; i < len; i ++)
	{
		if(getPrintable(pText[i]))
		{
			x += (getGlyphWidth() + 1);
			if(linefeed)
			{
				linefeed = false;
				y += (getGlyphHeight() + 1);
			}
		}
		else if(pText[i] == '\n')
		{
			x = 0;
			linefeed = true;
		}
		else if(pText[i] == '\t')
		{
			x += FWDEBUGFONT_TAB_SIZE * (getGlyphWidth() + 1);
		}
		else if((signed char)pText[i] < 0)
		{
		}
		else
		{
			x += (getGlyphWidth() + 1);
		}

		// check for screen wrap
		if((x + (getGlyphWidth() + 1)) >= (scrWidth - (sLeftSafe + sRightSafe)))
		{
			x = 0;
			linefeed = true;
		}

		if(x > *pWidth)
			*pWidth = x;

		if(y > *pHeight)
			*pHeight = y;
	}
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
