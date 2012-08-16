/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// OGL debug font rendering
//
// $File: //nextgendev/Framework_080/src/FWGLDebugFontRenderer.cpp $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include "psgl/FWGLDebugFontRenderer.h"

#ifdef FWGLDEBUGFONTRENDERER_USE_32BIT
GLubyte *FWGLDebugFontRenderer::spTextureData;
#endif//FWGLDEBUGFONTRENDERER_USE_32BIT

// ogl handle
GLuint	FWGLDebugFontRenderer::sTextureHandle;

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters:	
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWGLDebugFontRenderer::FWGLDebugFontRenderer()
{
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters:	
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWGLDebugFontRenderer::~FWGLDebugFontRenderer()
{
}

//-----------------------------------------------------------------------------
// Description: Initialize debug font renderer
// Parameters:	
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWGLDebugFontRenderer::init()
{
#ifdef FWGLDEBUGFONTRENDERER_USE_32BIT
	// convert texture to 32-bit
	// since GL_ALPHA texture doesn't work on PSGL out of the box
	// align to 128 byte boundary for speed
	spTextureData = new GLubyte[FWDEBUGFONT_DATA_SIZE * 4 + 127];
	GLubyte *pTexture = (GLubyte *)(((long)spTextureData + 127) & ~127);
	GLubyte *pFontData = (GLubyte *)getFontData();

	for(int i = 0; i < FWDEBUGFONT_DATA_SIZE; i ++)
	{
      pTexture[i * 4] = 255;
      pTexture[i * 4 + 1] = 255;
      pTexture[i * 4 + 2] = 255;
	  pTexture[i * 4 + 3] = pFontData[i];
    }
#endif//FWGLDEBUGFONTRENDERER_USE_32BIT

	// bind the font texture
  	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &sTextureHandle);
	glBindTexture(GL_TEXTURE_2D, sTextureHandle);

#ifdef FWGLDEBUGFONTRENDERER_USE_32BIT
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, FWDEBUGFONT_TEXTURE_WIDTH, FWDEBUGFONT_TEXTURE_HEIGHT, 0,
				GL_RGBA, GL_UNSIGNED_BYTE, (const void *)pTexture);
#else
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, FWDEBUGFONT_TEXTURE_WIDTH, FWDEBUGFONT_TEXTURE_HEIGHT, 0,
			GL_ALPHA, GL_UNSIGNED_BYTE, (const void *)sFontData);
#endif//FWGLDEBUGFONTRENDERER_USE_32BIT

	glDisable(GL_TEXTURE_2D);
}

//-----------------------------------------------------------------------------
// Description: Shutdown debug font renderer
// Parameters:	
// Returns:
// Notes: Frees font texture
//-----------------------------------------------------------------------------
void FWGLDebugFontRenderer::shutdown()
{
#ifdef FWGLDEBUGFONTRENDERER_USE_32BIT
	delete []spTextureData;
#endif//FWGLDEBUGFONTRENDERER_USE_32BIT

	glDeleteTextures(1, &sTextureHandle);
}

//-----------------------------------------------------------------------------
// Description: Prepare for rendering text
// Parameters:	r - Red
//				g - Green
//				b - Blue
//				a - Alpha
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWGLDebugFontRenderer::printStart(float r, float g, float b, float a)
{
	// set color
	sR = r;
	sG = g;
	sB = b;
	sA = a;

	// set all matrices to identity
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// setup render states
	// set alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// no depth test
	glDisable(GL_DEPTH_TEST);

	// set client & server side texture unit
	glClientActiveTexture(GL_TEXTURE0);
	glActiveTexture(GL_TEXTURE0);

	// modulate texture color
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// bind texture and set filter
	glBindTexture(GL_TEXTURE_2D, sTextureHandle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// enable texturing and vertex arrays
	glEnable(GL_TEXTURE_2D);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
}

//-----------------------------------------------------------------------------
// Description: Do a single pass of text rendering
// Parameters:	pPositions - Vertex position array
//				pTexCoords - Vertex texture co-ord array
//				pColors - Vertex color array
//				numVerts - Number of vertices
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWGLDebugFontRenderer::printPass(FWDebugFont::Position *pPositions, FWDebugFont::TexCoord *pTexCoords, FWDebugFont::Color *pColors, int numVerts)
{
	// set pointers to vertex data
	glVertexPointer(3, GL_FLOAT, 0, pPositions);
	glTexCoordPointer(2, GL_FLOAT, 0, pTexCoords);
	glColorPointer(4, GL_FLOAT, 0, pColors);
	// draw vertex arrays
	glDrawArrays(FWDEBUGFONT_PRIMITIVE, 0, numVerts);
}

//-----------------------------------------------------------------------------
// Description: Stop text rendering
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWGLDebugFontRenderer::printEnd()
{
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	// restore matrices
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	// reenable depth test
	glEnable(GL_DEPTH_TEST);

	// disable alpha blend
	glDisable(GL_BLEND);
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
