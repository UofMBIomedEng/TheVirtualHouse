/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/timer.h>
#include <sys/return_code.h>
#include <cell/gcm.h>
#include <sysutil/sysutil_sysparam.h>

#include "FWCellGCMWindow.h"
#include "FWGCMApplication.h"
#include "FWInput.h"
#include "FWTime.h"

#include "gcmutil.h"

using namespace cell::Gcm;

// Window instance
FWCellGCMWindow *FWCellGCMWindow::spCellGCMWindow = NULL;
sys_event_port_t  FWCellGCMWindow::sFlipEventPort;


//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters:	argc - number of arguments
//				ppArgv - argument list
//				dispInfo - display info
//				startupInfo - startup info
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
FWCellGCMWindow::FWCellGCMWindow(int argc, char **ppArgv,
								 const FWDisplayInfo &dispInfo,
								 const FWStartupInfo &startupInfo,
								 const FWGCMConfiguration &gcmConfig)  :
	FWWindow(argc, ppArgv, dispInfo, startupInfo), mFrameIndex(0), mLabel(NULL)
{
	FWASSERT(spCellGCMWindow == NULL);
	spCellGCMWindow = this;

	mConfig.mDefaultCBSize = gcmConfig.mDefaultCBSize;
	mConfig.mColorFormat = gcmConfig.mColorFormat;
	mStateCmdSize = gcmConfig.mDefaultStateCmdSize;

	mDefaultCB = (uint32_t)memalign(0x100000, mConfig.mDefaultCBSize + mStateCmdSize); // 1MB boundary

	// init
	// size_t workSize = 0x1000; // 4KB hw fifo buffer
	if (cellGcmInit(mConfig.mDefaultCBSize /* - workSize */,
					(mConfig.mDefaultCBSize+mStateCmdSize+((1<<20)-1))&(1<<20),  // Multiple of 1MB
					(void *)mDefaultCB) != CELL_OK) {
		printf("cellGcmInit failed\n");
		exit(1);
	}


    CellGcmConfig config;
    cellGcmGetConfiguration(&config);

	size_t reservedSize = 0x2000000; // 32MB system reserved memory
	cellGcmUtilInitializeLocalMemory((size_t)config.localAddress,
									 (size_t)config.localSize
									 - reservedSize);

	// set default state buffer used in fwgcm
	mStateCmdAddress = (uint32_t*)(mDefaultCB + mConfig.mDefaultCBSize);
	if( cellGcmAddressToOffset((void*)mStateCmdAddress, &mStateCmdOffset) != CELL_OK) {
		printf("cellGcmAddressToOffset failed\n");
		exit(1);
	}

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

	// set TV resolution and set TV mode
	mDispInfo.mWidth = resolution.width;
	mDispInfo.mHeight = resolution.height;
	mDispInfo.mWideScreen
		= (videoState.displayMode.aspect == CELL_VIDEO_OUT_ASPECT_16_9);
	printf("Display resolution: %dx%d ",
		   mDispInfo.mWidth, mDispInfo.mHeight);
	printf(mDispInfo.mWideScreen ? "(16:9)\n" : "(4:3)\n");

	mDispInfo.mColorBits = dispInfo.mColorBits;
	mDispInfo.mAlphaBits = dispInfo.mAlphaBits;
	mDispInfo.mDepthBits = dispInfo.mDepthBits;
	mDispInfo.mStencilBits = dispInfo.mStencilBits;
	mDispInfo.mAntiAlias = dispInfo.mAntiAlias;
	mDispInfo.mVSync = dispInfo.mVSync;

	uint32_t cDepth = 4;
	uint32_t zsDepth = 4;
	uint8_t dispColorFormat = CELL_VIDEO_OUT_BUFFER_COLOR_FORMAT_X8R8G8B8;
	switch (mConfig.mColorFormat) {
	case CELL_GCM_SURFACE_A8R8G8B8:
		cDepth = 4;
		dispColorFormat = CELL_VIDEO_OUT_BUFFER_COLOR_FORMAT_X8R8G8B8;
		break;
	case CELL_GCM_SURFACE_F_W16Z16Y16X16:
		cDepth = 8;
		dispColorFormat = CELL_VIDEO_OUT_BUFFER_COLOR_FORMAT_R16G16B16X16_FLOAT;
		break;
	default:
		assert(false && "invalid color format");
	}

	// Height must be 32 aligned for local memory tiled region, 64 for main memory
	mFramePitch[0] = mFramePitch[1]
		= cellGcmGetTiledPitchSize(mDispInfo.mWidth*cDepth);
	mFrameSize = mFramePitch[0] * ((mDispInfo.mHeight+31)&~31);
	mFramePitch[2] = cellGcmGetTiledPitchSize(mDispInfo.mWidth*zsDepth);
	mDepthSize = mFramePitch[2] * ((mDispInfo.mHeight+31)&~31);

	// set display  configuration to the driver via sysutil
	CellVideoOutConfiguration videocfg;
	memset(&videocfg, 0, sizeof(CellVideoOutConfiguration));
	videocfg.resolutionId = videoState.displayMode.resolutionId;
	videocfg.format = dispColorFormat;
	videocfg.aspect = videoState.displayMode.aspect;
	videocfg.pitch = mFramePitch[0];
	if (cellVideoOutConfigure(CELL_VIDEO_OUT_PRIMARY, &videocfg, NULL, 0) != CELL_OK){
		printf("cellVideoOutConfigure failed\n");
		exit(1);
	}
	cellGcmSetFlipMode(mDispInfo.mVSync ? CELL_GCM_DISPLAY_VSYNC : CELL_GCM_DISPLAY_HSYNC);

	// round up to 64KB size
	mFrameSize = (mFrameSize+0xffff) & ~0xffff;
	mDepthSize = (mDepthSize+0xffff) & ~0xffff;
	// frame address must be on 64KB boundary
	mFrameAddress[0] = cellGcmUtilAllocateLocalMemory(mFrameSize, 0x10000);
	mFrameAddress[1] = cellGcmUtilAllocateLocalMemory(mFrameSize, 0x10000);
	mFrameAddress[2] = cellGcmUtilAllocateLocalMemory(mDepthSize, 0x10000);

	for (uint32_t i = 0; i < 3; ++i) {
		cellGcmAddressToOffset(mFrameAddress[i], &mFrameOffset[i]);
	}
	// XXX ctag base must be fixed for RSX and NV47
	cellGcmSetTileInfo(0, CELL_GCM_LOCATION_LOCAL, mFrameOffset[0], mFrameSize,
				   mFramePitch[0], CELL_GCM_COMPMODE_DISABLED, 0, 0);
	cellGcmBindTile(0);
	cellGcmSetTileInfo(1, CELL_GCM_LOCATION_LOCAL, mFrameOffset[1], mFrameSize,
				   mFramePitch[1], CELL_GCM_COMPMODE_DISABLED, 0, 0);
	cellGcmBindTile(1);
	cellGcmSetTileInfo(2, CELL_GCM_LOCATION_LOCAL, mFrameOffset[2], mDepthSize,
				   mFramePitch[2], CELL_GCM_COMPMODE_Z32_SEPSTENCIL, 0, 0);
	cellGcmBindTile(2);

	// zcull width & height must be 64 aligned
	cellGcmBindZcull(0, mFrameOffset[2],
					(mDispInfo.mWidth+0x3f)&(~0x3f), (mDispInfo.mHeight+0x3f)&(~0x3f), 0,
					CELL_GCM_ZCULL_Z24S8, CELL_GCM_SURFACE_CENTER_1,
					CELL_GCM_ZCULL_LESS, CELL_GCM_ZCULL_LONES,
					CELL_GCM_LESS, 0x80, 0xff);
	// regist surface
	if (cellGcmSetDisplayBuffer(0, mFrameOffset[0], mFramePitch[0], mDispInfo.mWidth, mDispInfo.mHeight) != CELL_OK) {
		printf("cellGcmSetDisplayBuffer failed\n");
		exit(1);
	}
	if (cellGcmSetDisplayBuffer(1, mFrameOffset[1], mFramePitch[1], mDispInfo.mWidth, mDispInfo.mHeight) != CELL_OK) {
		printf("cellGcmSetDisplayBuffer failed\n");
		exit(1);
	}

	initFlipEvent();

	// set inital target
	setRenderTarget(0);

	// set display information to FWApplication
	FWGCMApplication *app;
	app = (FWGCMApplication*)FWApplication::getApplication();
	app->FWGCMApplication::onSize(mDispInfo);

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
FWCellGCMWindow::~FWCellGCMWindow()
{
	spCellGCMWindow = NULL;
}

//-----------------------------------------------------------------------------
// Description: Set GCM rendering context
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWCellGCMWindow::setRenderingContext()
{
}

//-----------------------------------------------------------------------------
// Description: Clear GCM rendering context
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWCellGCMWindow::clearRenderingContext()
{
}

void FWCellGCMWindow::setRenderTarget(const uint32_t index)
{
	CellGcmSurface surface;

	memset(&surface, 0, sizeof(surface));
	surface.colorFormat 	 = mConfig.mColorFormat;
	surface.colorTarget		 = CELL_GCM_SURFACE_TARGET_0;
	surface.colorLocation[0] = CELL_GCM_LOCATION_LOCAL;
	surface.colorOffset[0]   = mFrameOffset[index];
	surface.colorPitch[0] 	 = mFramePitch[index];
	surface.colorLocation[1] = CELL_GCM_LOCATION_LOCAL;
	surface.colorOffset[1]   = 0;
	surface.colorPitch[1] 	 = 64;
	surface.colorLocation[2] = CELL_GCM_LOCATION_LOCAL;
	surface.colorOffset[2]   = 0;
	surface.colorPitch[2] 	 = 64;
	surface.colorLocation[3] = CELL_GCM_LOCATION_LOCAL;
	surface.colorOffset[3]   = 0;
	surface.colorPitch[3] 	 = 64;
	surface.depthFormat 	= CELL_GCM_SURFACE_Z24S8;
	surface.depthLocation 	= CELL_GCM_LOCATION_LOCAL;
	surface.depthOffset 	= mFrameOffset[2];
	surface.depthPitch 		= mFramePitch[2];
	surface.type			= CELL_GCM_SURFACE_PITCH;
	surface.antialias 		= CELL_GCM_SURFACE_CENTER_1;
	surface.width 			= mDispInfo.mWidth;
	surface.height 			= mDispInfo.mHeight;
	surface.x 		 		= 0;
	surface.y 		 		= 0;

	cellGcmSetSurface(&surface);
}

//-----------------------------------------------------------------------------
// Description: Window update function
// Parameters:
// Returns: True if continuing to run, false otherwise
// Notes:
//-----------------------------------------------------------------------------
bool FWCellGCMWindow::update()
{
	if(mInit && mUpdate)
	{
		FWWindow::update();
		return mUpdate;
	}
	else
		return false;
}

// have CPU wait if CPU runs too fast than GPU, or GPU is too slow than CPU
void FWCellGCMWindow::getCpuGpuSync(void)
{
    static uint32_t cpuCounter = 0;
	const uint32_t countMax=16;
    static bool firstTime = true;

    if (firstTime) {
		// initialize GPU-progress counter (label #label_for_counter)
		mLabel = cellGcmGetLabelAddress(sLabelId);
		*mLabel = 0;
    }

    cellGcmSetWriteCommandLabel(sLabelId, cpuCounter);
    cellGcmFlush();

    // not to let CPU work too fast
    // this code would not work when 32bit counter overflows
	//    while (cpuCounter > *((volatile uint32_t*)mLabel) + 1) {
	while ((cpuCounter - *((volatile uint32_t*)mLabel) + countMax ) % countMax > 1) {
		sys_event_t event;
		int ret;
		ret = sys_event_queue_receive(mFlipEventQueue, &event, SYS_NO_TIMEOUT);
		if (ret != CELL_OK) {
			printf("flip event receive failed (%#x)\n", ret);
			assert(0);
		}
		ret = sys_event_queue_drain(mFlipEventQueue);
		if (ret != CELL_OK) {
			printf("flip event drain failed (%#x)\n", ret);
			assert(0);
		}
    }

	cpuCounter=( cpuCounter + 1 ) % countMax;

	firstTime = false;
}

//-----------------------------------------------------------------------------
// Description: Do buffer flip
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWCellGCMWindow::flip()
{
	// FWASSERT(mpDevice);

	while (cellGcmGetFlipStatus() != 0) {
		sys_timer_usleep(100);
	}
	cellGcmResetFlipStatus();

	if (cellGcmSetFlip(mFrameIndex) != CELL_OK) {
		return;
	}
	cellGcmFlush();
	cellGcmSetWaitFlip();

	// new render target 
	mFrameIndex = (mFrameIndex + 1) & 0x1;
	setRenderTarget(mFrameIndex);
}

//-----------------------------------------------------------------------------
// Description: buffer flip handler
// Parameters:
// Returns:
// Notes: this function is called from libgcm interrupt thread
//-----------------------------------------------------------------------------
void FWCellGCMWindow::onFlip(const uint32_t arg)
{
	(void)arg;

	FWGCMApplication::getApplication()->onFlip();

	int ret = sys_event_port_send(sFlipEventPort, 0, 0, 0);
	if (!((ret == CELL_OK) || (ret == EBUSY))) {
		assert(0 && "Event send failure");
	}
}

//-----------------------------------------------------------------------------
// Description: Gets called on shutdown
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWCellGCMWindow::destroy()
{
	FWWindow::destroy();

	cellGcmSetFlipHandler(NULL);
}

//-----------------------------------------------------------------------------
// Description: Get the display info
// Parameters: 
// Returns: Reference to display info
// Notes:
//-----------------------------------------------------------------------------
FWDisplayInfo& FWCellGCMWindow::getDisplayInfo()
{
	return mDispInfo;
}

void FWCellGCMWindow::initFlipEvent(void)
{
	int ret;
	int queueSize =32;
	sys_event_queue_attribute_t queueAttr;

	sys_event_queue_attribute_initialize(queueAttr);

	ret = sys_event_queue_create(&mFlipEventQueue, &queueAttr, SYS_EVENT_QUEUE_LOCAL,
								 queueSize);
	if (ret != CELL_OK) {
		printf("Event queue create failure (%#x)\n", ret);
		assert(0);
	}

	ret = sys_event_port_create(&sFlipEventPort, SYS_EVENT_PORT_LOCAL, SYS_EVENT_PORT_NO_NAME);
	if (ret != CELL_OK) {
		printf("Event port create failure (%#x)\n", ret);
		assert(0);
	}

	ret = sys_event_port_connect_local(sFlipEventPort, mFlipEventQueue);
	if (ret != CELL_OK) {
		printf("Event port connect failure (%#x)\n", ret);
		printf("sender(%#x): Destroy the event port: ", mFlipEventId);
		ret = sys_event_port_destroy(sFlipEventPort);
		if (ret != CELL_OK) {
			printf("Failure\n");
		}
		assert(0);
	}

	cellGcmSetFlipHandler(FWCellGCMWindow::onFlip);
}
