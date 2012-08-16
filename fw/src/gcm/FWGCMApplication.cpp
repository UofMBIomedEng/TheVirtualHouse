/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// GCM Application class
//
// $File: //nextgendev/Framework_050/src/FWGLApplication.cpp $
// $Author: aoki $
// $Date: 2006/01/12 07:41:36 $
// $Revision: 1.2 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <cell/gcm.h>
#include <assert.h>
#include "FWGCMApplication.h"
#include "gcmutil.h"

using namespace cell::Gcm;

// Static pointer to the application
FWGCMApplication *FWGCMApplication::spApplication = NULL;
// shader for buffer clear
extern struct _CGprogram _binary_clear_vpshader_vpo_start;
extern struct _CGprogram _binary_clear_fpshader_fpo_start;

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters: 
// Returns:
// Notes: Sets default clip distances and field-of-view for OpenGCM applications
//-----------------------------------------------------------------------------
FWGCMApplication::FWGCMApplication() :
mProjMode(FWGCMAPPLICATION_DEFAULT_PROJECTIONMODE),
mFOV(FWGCMAPPLICATION_DEFAULT_FOV),
mNear(FWGCMAPPLICATION_DEFAULT_NEARCLIP),
mFar(FWGCMAPPLICATION_DEFAULT_FARCLIP),
mClearRed(FWGCMAPPLICATION_DEFAULT_CLEAR_RED),
mClearGreen(FWGCMAPPLICATION_DEFAULT_CLEAR_GREEN),
mClearBlue(FWGCMAPPLICATION_DEFAULT_CLEAR_BLUE),
mClearAlpha(FWGCMAPPLICATION_DEFAULT_CLEAR_ALPHA),
mClearDepth(FWGCMAPPLICATION_DEFAULT_CLEAR_DEPTH)
{
	// Set view matrix to identity
	mViewMatrix = Matrix4::identity();

	spApplication = this;
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters: 
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWGCMApplication::~FWGCMApplication()
{
}

void FWGCMApplication::initClearShader()
{
	mClearVertexCount= 4;
	mClearPosDimension=2;
	mClearColDimension=4;

	mClearPositionBuffer =
		(float *)cellGcmUtilAllocateLocalMemory(
			mClearPosDimension*mClearVertexCount*sizeof(float), 64);
	mClearColorBuffer =
		(float *)cellGcmUtilAllocateLocalMemory(
			mClearColDimension*sizeof(float), 64);

	float *pos =  mClearPositionBuffer;
	float posClearX[] = {-1.0f,  -1.0f, 1.0f,  1.0f};
	float posClearY[] = {1.0f, -1.0f,  -1.0f,  1.0f};

	*pos++ = posClearX[0]; *pos++ = posClearY[0];
	*pos++ = posClearX[1]; *pos++ = posClearY[1];
	*pos++ = posClearX[2]; *pos++ = posClearY[2];
	*pos++ = posClearX[3]; *pos++ = posClearY[3];


	mClearCGVertexProgram   = &_binary_clear_vpshader_vpo_start;
	mClearCGFragmentProgram = &_binary_clear_fpshader_fpo_start;

	cellGcmCgInitProgram(mClearCGVertexProgram);
	cellGcmCgInitProgram(mClearCGFragmentProgram);

	unsigned int ucodeSize;
	void *ucode;
	cellGcmCgGetUCode(mClearCGFragmentProgram, &ucode, &ucodeSize);

	mClearFragmentProgramUCode = cellGcmUtilAllocateLocalMemory(ucodeSize, 64);

	memcpy(mClearFragmentProgramUCode, ucode, ucodeSize); 

	cellGcmCgGetUCode(mClearCGVertexProgram, &ucode, &ucodeSize);
	mClearVertexProgramUCode = ucode;

	CGparameter position	= cellGcmCgGetNamedParameter(mClearCGVertexProgram, "position");
	CGparameter color	= cellGcmCgGetNamedParameter(mClearCGVertexProgram, "color");

	// get vertex attribute index
	mClearPosIndex	= (CGresource)(cellGcmCgGetParameterResource(mClearCGVertexProgram, position) - CG_ATTR0);
	mClearColIndex	= (CGresource)(cellGcmCgGetParameterResource(mClearCGVertexProgram, color) - CG_ATTR0);

	// set vertex pointer
	cellGcmAddressToOffset(mClearPositionBuffer, &mClearPosOffset);
	cellGcmAddressToOffset(mClearColorBuffer, &mClearColOffset);

	// fragment program offset
	cellGcmAddressToOffset(mClearFragmentProgramUCode, &mClearFragmentOffset);
}

void FWGCMApplication::renderClear()
{
	float *C =  mClearColorBuffer;
	C[0]=mClearRed;
	C[1]=mClearGreen;
	C[2]=mClearBlue;
	C[3]=mClearAlpha;

	cellGcmSetVertexProgram(mClearCGVertexProgram, mClearVertexProgramUCode);
	cellGcmSetFragmentProgram(mClearCGFragmentProgram, mClearFragmentOffset);

	cellGcmSetVertexDataArray(
		mClearPosIndex, 0, mClearPosDimension*sizeof(float), mClearPosDimension,
		CELL_GCM_VERTEX_F, CELL_GCM_LOCATION_LOCAL, mClearPosOffset);
	cellGcmSetVertexDataArray(
		mClearColIndex, mClearVertexCount, mClearColDimension*sizeof(float), mClearColDimension,
		CELL_GCM_VERTEX_F, CELL_GCM_LOCATION_LOCAL, mClearColOffset);

	cellGcmSetDrawArrays(CELL_GCM_PRIMITIVE_QUADS, 0, mClearVertexCount);
}


//-----------------------------------------------------------------------------
// Description: Overloadable init function
// Parameters:	argc - Number of arguments
//				ppArgv - Argument list
// Returns: True if ok, false if not
// Notes: 
//-----------------------------------------------------------------------------
bool FWGCMApplication::onInit(int argc, char **ppArgv)
{
	switch (mConfig.mColorFormat) {
	case CELL_GCM_SURFACE_A8R8G8B8:
		mClearByShader=false;
		break;
	case CELL_GCM_SURFACE_F_W16Z16Y16X16:
		mClearByShader=true;
		break;
	default:
		assert(false && "invalid color format");
	}

	if (mClearByShader) {
		initClearShader();
	}

	return FWApplication::onInit(argc, ppArgv);
}

//-----------------------------------------------------------------------------
// Description: Overloadable shutdown function
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWGCMApplication::onShutdown()
{
	FWApplication::onShutdown();
}

//-----------------------------------------------------------------------------
// Description: Overloadable update function
// Parameters: 
// Returns: False if want to quit, true otherwise
// Notes: 
//-----------------------------------------------------------------------------
bool FWGCMApplication::onUpdate()
{
	return FWApplication::onUpdate();
}

//-----------------------------------------------------------------------------
// Description: Overloadable render function
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWGCMApplication::setViewport()
{
	uint16_t x,y,w,h;
	float min, max;
	float scale[4],offset[4];

	x = 0;
	y = 0;
	w = mDispInfo.mWidth;
	h = mDispInfo.mHeight;
	min = 0.0f;
	max = 1.0f;
	scale[0] = w * 0.5f;
	scale[1] = h * -0.5f;
	scale[2] = (max - min) * 0.5f;
	scale[3] = 0.0f;
	offset[0] = x + scale[0];
	offset[1] = h - y + scale[1];
	offset[2] = (max + min) * 0.5f;
	offset[3] = 0.0f;

	cellGcmSetViewport(x, y, w, h, min, max, scale, offset);
	cellGcmSetScissor(x, y, w, h);
}

//-----------------------------------------------------------------------------
// Description: Overloadable render function
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWGCMApplication::onRender()
{
	if (mClearByShader)
	{
		cellGcmSetDepthTestEnable(CELL_GCM_FALSE);
		renderClear();
		cellGcmSetDepthTestEnable(CELL_GCM_TRUE);

		cellGcmSetClearDepthStencil((uint32_t)(mClearDepth*0xffffff) << 8);
		cellGcmSetClearSurface(CELL_GCM_CLEAR_Z | CELL_GCM_CLEAR_S);
	}
	else
	{
		cellGcmSetClearColor((uint32_t)(255.0f*mClearAlpha) << 24 |
							 (uint32_t)(255.0f*mClearRed)   << 16 |
							 (uint32_t)(255.0f*mClearGreen) <<  8 |
							 (uint32_t)(255.0f*mClearBlue)); // A8R8G8B8
		cellGcmSetClearDepthStencil((uint32_t)(mClearDepth*0xffffff) << 8);
		cellGcmSetClearSurface(CELL_GCM_CLEAR_R | CELL_GCM_CLEAR_G |
							   CELL_GCM_CLEAR_B | CELL_GCM_CLEAR_A |
							   CELL_GCM_CLEAR_Z | CELL_GCM_CLEAR_S);
	}

	// reset viewport and scissor
	setViewport();
}

//-----------------------------------------------------------------------------
// Description: Overloadable size function
// Parameters:	dispInfo - Reference to display info class
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWGCMApplication::onSize(const FWDisplayInfo &dispInfo)
{
	// copy disp info class
	mDispInfo.mWidth = dispInfo.mWidth;
	mDispInfo.mHeight = dispInfo.mHeight;
	mDispInfo.mWideScreen = dispInfo.mWideScreen;

	// set new viewport size and scissor bounds

	uint16_t x,y,w,h;
	float min, max;
	float scale[4],offset[4];

	x = 0;
	y = 0;
	w = mDispInfo.mWidth;
	h = mDispInfo.mHeight;
	min = 0.0f;
	max = 1.0f;
	scale[0] = w * 0.5f;
	scale[1] = h * -0.5f;
	scale[2] = (max - min) * 0.5f;
	scale[3] = 0.0f;
	offset[0] = x + scale[0];
	offset[1] = h - y + scale[1];
	offset[2] = (max + min) * 0.5f;
	offset[3] = 0.0f;

	cellGcmSetViewport(x, y, w, h, min, max, scale, offset);
	cellGcmSetScissor(x, y, w, h);

	// set projection matrix
	switch(mProjMode)
	{
	case ProjectionMode_Perspective:
		mProjMatrix = Matrix4::perspective(mFOV, mDispInfo.mWideScreen ? 16.f/9.f : 4.f/3.f, mNear, mFar);
		break;
	case ProjectionMode_Orthographic:
		mProjMatrix = Matrix4::orthographic(0, mDispInfo.mWideScreen ? 16.f : 4.f, 0, mDispInfo.mWideScreen ? 9.f : 3.f, 0, 0);
		break;
	}

	// notify the debug font component
	FWDebugFont::setScreenRes(mDispInfo.mWidth, mDispInfo.mHeight);
}

//-----------------------------------------------------------------------------
// Description: Capture the screen
// Parameters:	pFilename - Filename to save capture as (Targa format)
// Returns:
// Notes: Uses a default numbered name if pFilename is NULL
//-----------------------------------------------------------------------------
void FWGCMApplication::captureScreen(const char *pFilename)
{
	(void)pFilename;
}
