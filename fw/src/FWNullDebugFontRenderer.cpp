/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Null debug font rendering
//
// $File: //nextgendev/Framework_080/src/FWNullDebugFontRenderer.cpp $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include "FWNullDebugFontRenderer.h"

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters:	
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWNullDebugFontRenderer::FWNullDebugFontRenderer()
{
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters:	
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWNullDebugFontRenderer::~FWNullDebugFontRenderer()
{
}

//-----------------------------------------------------------------------------
// Description: Initialize debug font renderer
// Parameters:	
// Returns:
// Notes: Doesn't actually do anything
//-----------------------------------------------------------------------------
void FWNullDebugFontRenderer::init()
{
}

//-----------------------------------------------------------------------------
// Description: Shutdown debug font renderer
// Parameters:	
// Returns:
// Notes: Doesn't actually do anything
//-----------------------------------------------------------------------------
void FWNullDebugFontRenderer::shutdown()
{
}

//-----------------------------------------------------------------------------
// Description: Prepare for rendering text
// Parameters:	r - Red
//				g - Green
//				b - Blue
//				a - Alpha
// Returns:
// Notes: Doesn't actually do anything
//-----------------------------------------------------------------------------
void FWNullDebugFontRenderer::printStart(float r, float g, float b, float a)
{
	// stop unused parameter warnings
	(void)r;
	(void)g;
	(void)b;
	(void)a;
}

//-----------------------------------------------------------------------------
// Description: Do a single pass of text rendering
// Parameters:	pPositions - Vertex position array
//				pTexCoords - Vertex texture co-ord array
//				pColors - Vertex color array
//				numVerts - Number of vertices
// Returns:
// Notes: Doesn't actually do anything
//-----------------------------------------------------------------------------
void FWNullDebugFontRenderer::printPass(FWDebugFont::Position *pPositions, FWDebugFont::TexCoord *pTexCoords, FWDebugFont::Color *pColors, int numVerts)
{
	// stop unused parameter warnings
	(void)pPositions;
	(void)pTexCoords;
	(void)pColors;
	(void)numVerts;
}

//-----------------------------------------------------------------------------
// Description: Stop text rendering
// Parameters:
// Returns:
// Notes: Doesn't actually do anything
//-----------------------------------------------------------------------------
void FWNullDebugFontRenderer::printEnd()
{
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
