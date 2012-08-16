/*   SCE CONFIDENTIAL                                       */
/*   PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001 */
/*   Copyright (C) 2006 Sony Computer Entertainment Inc.    */
/*   All Rights Reserved.                                   */

#include <stdio.h>
#include <sys/process.h>
#include <sys/spu_initialize.h>
#include <sysutil/sysutil_common.h>
#include <sys/process.h>
#include <cell/sysmodule.h>
#include <cell/cell_fs.h>

#ifdef PSGL
#include "psgl/FWCellGLWindow.h"
#endif//PSGL

#include "FWApplication.h"
#include "cell/FWCellSystemCallback.h"

enum {
	SLOT_FW = 0,		// callback handler in FW
};

static bool receivedExitGameRequest = false;

static void systemCallback(const uint64_t status, const uint64_t param,
						   void *userdata)
{
	(void)param;
	(void)userdata;

	// call user defined callback function
	FWCellSystemCallback::userCallback(status, param, userdata);

	switch (status) {
	case CELL_SYSUTIL_REQUEST_EXITGAME:
		printf("system notification: CELL_SYSUTIL_REQUEST_EXITGAME\n");
		receivedExitGameRequest = true;
		break;

	case CELL_SYSUTIL_DRAWING_BEGIN:
	case CELL_SYSUTIL_DRAWING_END:
	default:
		// ignore
		break;
	}
}

SYS_PROCESS_PARAM( 1001, 0x10000 );

//-----------------------------------------------------------------------------
// Description: Cell entry point
// Parameters:	argc - Number of command line arguments
//				argv - Array of command line arguments
// Returns:
// Notes:
//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	// load prx modules
	cellSysmoduleLoadModule(CELL_SYSMODULE_NET);
	cellSysmoduleLoadModule(CELL_SYSMODULE_IO);
	cellSysmoduleLoadModule(CELL_SYSMODULE_USBD);
	cellSysmoduleLoadModule(CELL_SYSMODULE_GCM_SYS);
	cellSysmoduleLoadModule(CELL_SYSMODULE_RESC);

	sys_spu_initialize(6, FWApplication::getApplication()->getStartupInfo().mNumRawSPUs);

#ifdef PSGL
	// create a new FWCellGLWindow object
	FWCellGLWindow *pWindow = new FWCellGLWindow(argc - 1, &argv[1], FWApplication::getApplication()->getDisplayInfo(), FWApplication::getApplication()->getStartupInfo());
#endif//PSGL

	int ret = cellSysutilRegisterCallback(SLOT_FW, systemCallback, NULL);
	if (ret != CELL_OK) {
		printf( "error: cellSysutilRegisterCallback() = 0x%x\n", ret);
		exit(1);
	}

	bool isRunning = true;
	while(isRunning && !receivedExitGameRequest) {
		ret = cellSysutilCheckCallback();
		if (ret != CELL_OK) {
			printf("error: cellSysutilCheckCallback() = 0x%x\n", ret);
			return ret;
		}

		// call the update and render functions
		isRunning = pWindow->update();
		pWindow->render();
	}

	// wait for rsx completing all commands
	glFinish();

	// call the window's destroy function
	pWindow->destroy();
	// delete it
	delete pWindow;

	// unload prx modules
	cellSysmoduleUnloadModule(CELL_SYSMODULE_NET);
	cellSysmoduleUnloadModule(CELL_SYSMODULE_IO);
	cellSysmoduleUnloadModule(CELL_SYSMODULE_USBD);
	cellSysmoduleUnloadModule(CELL_SYSMODULE_GCM_SYS);
	cellSysmoduleUnloadModule(CELL_SYSMODULE_RESC);

	return 0;
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
