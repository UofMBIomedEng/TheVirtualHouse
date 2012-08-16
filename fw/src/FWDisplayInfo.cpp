/*   SCE CONFIDENTIAL                                       */
/*   PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001 */
/*   Copyright (C) 2006 Sony Computer Entertainment Inc.    */
/*   All Rights Reserved.                                   */

#include "FWDisplayInfo.h"

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters: 
// Returns:
// Notes: Sets up default values for display
//-----------------------------------------------------------------------------
FWDisplayInfo::FWDisplayInfo() :
mDisplayMode(FWDISPLAYINFO_DEFAULT_MODE),
mColorBits(FWDISPLAYINFO_DEFAULT_COLOR),
mAlphaBits(FWDISPLAYINFO_DEFAULT_ALPHA),
mDepthBits(FWDISPLAYINFO_DEFAULT_DEPTH),
mStencilBits(FWDISPLAYINFO_DEFAULT_STENCIL),
mAntiAlias(FWDISPLAYINFO_DEFAULT_ANTIALIAS),
mVSync(FWDISPLAYINFO_DEFAULT_VSYNC)
{
	// Set width and height given a particular display mode
	switch(mDisplayMode)
	{
	case DisplayMode_VGA:
		mWidth = FWDISPLAYINFO_DEFAULT_WIDTH;
		mHeight = FWDISPLAYINFO_DEFAULT_HEIGHT;
		break;
	case DisplayMode_480i:
	case DisplayMode_480p:
		mWidth = 720;
		mHeight = 480;
		break;
	case DisplayMode_576i:
	case DisplayMode_576p:
		mWidth = 720;
		mHeight = 576;
		break;
	case DisplayMode_720p:
	case DisplayMode_WXGA_720p:
	case DisplayMode_SXGA_720p:
		mWidth = 1280;
		mHeight = 720;
		break;
	case DisplayMode_1080i:
	case DisplayMode_1080p:
	case DisplayMode_WUXGA_1080p:
		mWidth = 1920;
		mHeight = 1080;
		break;
	}

#ifdef PSGL
	// set default PSGL initialization options
	// these can be overridden by the application in its constructor if required
	mPSGLInitOptions.enable = PSGL_INIT_MAX_SPUS | PSGL_INIT_INITIALIZE_SPUS | PSGL_INIT_PERSISTENT_MEMORY_SIZE | PSGL_INIT_HOST_MEMORY_SIZE;
	mPSGLInitOptions.maxSPUs = FWDISPLAYINFO_DEFAULT_PSGL_RAW_SPUS;
	mPSGLInitOptions.initializeSPUs = GL_FALSE;
	mPSGLInitOptions.persistentMemorySize = FWDISPLAYINFO_DEFAULT_PERSISTENT_MEMORY_SIZE;
	mPSGLInitOptions.hostMemorySize = FWDISPLAYINFO_DEFAULT_HOST_MEMORY_SIZE;
#endif//PSGL
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
FWDisplayInfo::~FWDisplayInfo()
{
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
