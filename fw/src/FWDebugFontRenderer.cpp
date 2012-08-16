/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Debug font rendering
//
// $File: //nextgendev/Framework_080/src/FWDebugFontRenderer.cpp $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include "FWDebugFontRenderer.h"
#include "FWDebugFont.h"

// color passed by FWDebugFont
float	FWDebugFontRenderer::sR;
float	FWDebugFontRenderer::sG;
float	FWDebugFontRenderer::sB;
float	FWDebugFontRenderer::sA;

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters: 
// Returns:
// Notes: Sets static pointer for renderer instance
//-----------------------------------------------------------------------------
FWDebugFontRenderer::FWDebugFontRenderer()
{
	FWDebugFont::spRenderer = this;
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters: 
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWDebugFontRenderer::~FWDebugFontRenderer()
{
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
