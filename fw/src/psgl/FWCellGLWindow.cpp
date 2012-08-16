/*   SCE CONFIDENTIAL                                       */
/*   PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001 */
/*   Copyright (C) 2006 Sony Computer Entertainment Inc.    */
/*   All Rights Reserved.                                   */

#include <sys/return_code.h>
#include <sysutil/sysutil_sysparam.h>
#include <stdio.h>

#include "psgl/FWCellGLWindow.h"
#include "psgl/FWGLApplication.h"
#include "FWInput.h"
#include "FWTime.h"
#include "FWDebugFont.h"
#include "FWDebugConsole.h"

// Window instance
FWCellGLWindow *FWCellGLWindow::spCellGLWindow = NULL;

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters:	argc - Number of arguments
//				ppArgv - Argument list
//				dispInfo - Display info
//				startupInfo - Startup info
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
FWCellGLWindow::FWCellGLWindow(int argc, char **ppArgv, const FWDisplayInfo &dispInfo, const FWStartupInfo &startupInfo) :
FWWindow(argc, ppArgv, dispInfo, startupInfo)
{
	FWASSERT(spCellGLWindow == NULL);
	spCellGLWindow = this;

	// setup video
	// read the current video status
	// INITIAL DISPLAY MODE HAS TO BE SET BY RUNNING SETMONITOR.SELF
	CellVideoOutState videoState;
	if (cellVideoOutGetState(CELL_VIDEO_OUT_PRIMARY, 0, &videoState) != CELL_OK){
		printf("cellVideoOutGetState failed\n");
		exit(1);
	}

	// keep the current resolution
	// get width and height in pixels from resolutionId
	CellVideoOutResolution resolution;
	if (cellVideoOutGetResolution(videoState.displayMode.resolutionId,
								  &resolution) != CELL_OK) {
		printf("cellVideoOutGetResolution failed\n");
		exit(1);
	}

	mDispInfo.mWideScreen
		= (videoState.displayMode.aspect == CELL_VIDEO_OUT_ASPECT_16_9);

	// init graphics
	PSGLinitOptions	psglInitOptions;
	psglInitOptions = dispInfo.mPSGLInitOptions;	
	psglInit(&psglInitOptions);
	psglFXInit();

	mDispInfo.mColorBits = dispInfo.mColorBits;
	mDispInfo.mAlphaBits = dispInfo.mAlphaBits;
	mDispInfo.mDepthBits = dispInfo.mDepthBits;
	mDispInfo.mStencilBits = dispInfo.mStencilBits;
	mDispInfo.mAntiAlias = dispInfo.mAntiAlias;
	mDispInfo.mVSync = dispInfo.mVSync;
	mDispInfo.mPSGLInitOptions = dispInfo.mPSGLInitOptions;

	// create it and surfaces
	createDeviceAndSurfaces();

	printf("Display resolution: %dx%d ",
		   mDispInfo.mWidth, mDispInfo.mHeight);
	printf(mDispInfo.mWideScreen ? "(16:9)\n" : "(4:3)\n");

	// set display information to FWApplication
	FWGLApplication *app;
	app = (FWGLApplication*)FWApplication::getApplication();
	app->FWGLApplication::onSize(mDispInfo);

	// initialize input
	FWInput::init(NULL);

	// initialize application
	FWWindow::init();

	if(mInit)
		resize(mDispInfo.mWidth, mDispInfo.mHeight);
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWCellGLWindow::~FWCellGLWindow()
{
	spCellGLWindow = NULL;
}

//-----------------------------------------------------------------------------
// Description: Window update function
// Parameters:
// Returns: True if continuing to run, false otherwise
// Notes:
//-----------------------------------------------------------------------------
bool FWCellGLWindow::update()
{
	if(mInit && mUpdate)
	{
		FWWindow::update();
		return mUpdate;
	}
	else
		return false;
}

//-----------------------------------------------------------------------------
// Description: Set OGL rendering context
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWCellGLWindow::setRenderingContext()
{
	psglMakeCurrent(mDispInfo.mGlContext, mpDevice);
}

//-----------------------------------------------------------------------------
// Description: Clear OGL rendering context
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWCellGLWindow::clearRenderingContext()
{
	psglMakeCurrent(NULL, mpDevice);
}

//-----------------------------------------------------------------------------
// Description: Do buffer flip
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWCellGLWindow::flip()
{
	FWASSERT(mpDevice);

	psglSwap();
}

//-----------------------------------------------------------------------------
// Description: Gets called on shutdown
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWCellGLWindow::destroy()
{
	FWWindow::destroy();
}

//-----------------------------------------------------------------------------
// Description: Get the display info
// Parameters: 
// Returns: Reference to display info
// Notes:
//-----------------------------------------------------------------------------
FWDisplayInfo& FWCellGLWindow::getDisplayInfo()
{
	return mDispInfo;
}

//-----------------------------------------------------------------------------
// Description: Create PSGL device and rendering sirfaces
// Parameters: 
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWCellGLWindow::createDeviceAndSurfaces()
{
	GLenum colorFormat = (mDispInfo.mColorBits == 24) ?
		GL_ARGB_SCE : GL_RGBA16F_ARB;
		//UINT8 when mColorBits are 24, FP16 in other case
	GLenum depthFormat = (mDispInfo.mDepthBits == 24) ?
		GL_DEPTH_COMPONENT24 : GL_NONE;
	GLenum multisamplingMode = (mDispInfo.mAntiAlias == true) ?
		GL_MULTISAMPLING_4X_SQUARE_CENTERED_SCE : GL_MULTISAMPLING_NONE_SCE;

	// create PSGL device and context
	mpDevice = psglCreateDeviceAuto(colorFormat, depthFormat, multisamplingMode);
	mDispInfo.mGlContext = psglCreateContext();
	psglMakeCurrent(mDispInfo.mGlContext, mpDevice);

	// reset the context and setup buffers
	psglResetCurrentContext();

	glBindFramebufferOES(GL_FRAMEBUFFER_OES, 0);

	// enable vsync
	if(mDispInfo.mVSync)
		glEnable(GL_VSYNC_SCE);
	else
		glDisable(GL_VSYNC_SCE);

	// set default server and client texture units
	glActiveTexture(GL_TEXTURE0);
	glClientActiveTexture(GL_TEXTURE0);

	psglGetDeviceDimensions(mpDevice,
							(GLuint*)&mDispInfo.mWidth,
							(GLuint*)&mDispInfo.mHeight);
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
