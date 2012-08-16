/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// GL Application class
//
// $File: //nextgendev/Framework_080/src/FWGLApplication.cpp $
// $Author: asidwell $
// $Date: 2006/01/30 $
// $Revision: #2 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include "psgl/FWGLApplication.h"
#include <stdio.h>

#ifdef __CELLOS_LV2__
#include <sys/paths.h>
#endif//__CELLOS_LV2__

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters: 
// Returns:
// Notes: Sets default clip distances and field-of-view for OpenGL applications
//-----------------------------------------------------------------------------
FWGLApplication::FWGLApplication() :
mProjMode(FWGLAPPLICATION_DEFAULT_PROJECTIONMODE),
mFOV(FWGLAPPLICATION_DEFAULT_FOV),
mNear(FWGLAPPLICATION_DEFAULT_NEARCLIP),
mFar(FWGLAPPLICATION_DEFAULT_FARCLIP),
mClearRed(FWGLAPPLICATION_DEFAULT_CLEAR_RED),
mClearGreen(FWGLAPPLICATION_DEFAULT_CLEAR_GREEN),
mClearBlue(FWGLAPPLICATION_DEFAULT_CLEAR_BLUE),
mClearAlpha(FWGLAPPLICATION_DEFAULT_CLEAR_ALPHA),
mClearDepth(FWGLAPPLICATION_DEFAULT_CLEAR_DEPTH)
{
	// Set view matrix to identity
	mViewMatrix = Matrix4::identity();
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters: 
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWGLApplication::~FWGLApplication()
{
}

//-----------------------------------------------------------------------------
// Description: Overloadable init function
// Parameters:	argc - Number of arguments
//				ppArgv - Argument list
// Returns: True if ok, false if not
// Notes: 
//-----------------------------------------------------------------------------
bool FWGLApplication::onInit(int argc, char **ppArgv)
{
	return FWApplication::onInit(argc, ppArgv);
}

//-----------------------------------------------------------------------------
// Description: Overloadable shutdown function
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWGLApplication::onShutdown()
{
	FWApplication::onShutdown();
}

//-----------------------------------------------------------------------------
// Description: Overloadable update function
// Parameters: 
// Returns: False if want to quit, true otherwise
// Notes: 
//-----------------------------------------------------------------------------
bool FWGLApplication::onUpdate()
{
	return FWApplication::onUpdate();
}

//-----------------------------------------------------------------------------
// Description: Overloadable render function
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWGLApplication::onRender()
{
	glClearColor(mClearRed, mClearGreen, mClearBlue, mClearAlpha);
	glClearDepthf(mClearDepth);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf((float *)&mViewMatrix);
}

//-----------------------------------------------------------------------------
// Description: Overloadable size function
// Parameters:	dispInfo - Reference to display info class
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWGLApplication::onSize(const FWDisplayInfo &dispInfo)
{
	// copy disp info class
	mDispInfo.mWidth = dispInfo.mWidth;
	mDispInfo.mHeight = dispInfo.mHeight;
	mDispInfo.mWideScreen = dispInfo.mWideScreen;

	// set new viewport size and scissor bounds
	glViewport(0, 0, mDispInfo.mWidth, mDispInfo.mHeight);
	glScissor(0, 0, mDispInfo.mWidth, mDispInfo.mHeight);

	// set projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	switch(mProjMode)
	{
	case ProjectionMode_Perspective:
		gluPerspectivef(mFOV, mDispInfo.mWideScreen ? 16.f/9.f : 4.f/3.f, mNear, mFar);
		break;
	case ProjectionMode_Orthographic:
		gluOrtho2Df(0, (float)mDispInfo.mWidth, 0, (float)mDispInfo.mHeight);
		break;
	}

	// notify the debug font component
	FWDebugFont::setScreenRes(mDispInfo.mWidth, mDispInfo.mHeight);
}

//-----------------------------------------------------------------------------
// Description: Capture the screen
// Parameters:	pFilename - Filename to save capture as (Targa format)
// Returns:
// Notes: Uses a default numbered name if <i><c>pFilename</c></i> is <c>NULL</c>
//-----------------------------------------------------------------------------
void FWGLApplication::captureScreen(const char *pFilename)
{
	unsigned char	header[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	unsigned char	bpp = 32;
	unsigned char	id = 8;
	unsigned short	width;
	unsigned short	height;
	unsigned char	*pPixels;
	FILE			*fp = NULL;

	if(pFilename)
	{
		fp = fopen(pFilename, "wb");
		if(!fp)
			return;
	}
	else
	{
		char	filename[256];
		int		i = 0;

		do
		{
			if(fp)
				fclose(fp);

#ifdef __CELLOS_LV2__
			sprintf(filename, SYS_APP_HOME"/screen%04d.tga", i);
#else
			sprintf(filename, "screen%04d.tga", i);
#endif
			fp = fopen(filename, "rb");
			i ++;
		} while(fp);
		
		fp = fopen(filename, "wb");
	}

	pPixels = new unsigned char[mDispInfo.mWidth * mDispInfo.mHeight * 4];
	glReadPixels(0, 0, mDispInfo.mWidth, mDispInfo.mHeight, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, pPixels);
	unsigned int	*pIntPix = (unsigned int *)pPixels;
	for(int i = 0; i < mDispInfo.mWidth * mDispInfo.mHeight; i ++)
	{
		*pIntPix = LITTLE_INT(*pIntPix);
		pIntPix ++;
	}

	fwrite(header, 1, sizeof(header), fp);

	width = LITTLE_SHORT(mDispInfo.mWidth);
	height = LITTLE_SHORT(mDispInfo.mHeight);

	fwrite(&width, 1, sizeof(unsigned short), fp);
	fwrite(&height, 1, sizeof(unsigned short), fp);
	fwrite(&bpp, 1, sizeof(unsigned char), fp);
	fwrite(&id, 1, sizeof(unsigned char), fp);

	fwrite(pPixels, 4, mDispInfo.mWidth * mDispInfo.mHeight, fp);
	fclose(fp);

	delete []pPixels;
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
