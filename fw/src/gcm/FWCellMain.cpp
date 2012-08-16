/*   SCE CONFIDENTIAL                                       */
/*   PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001 */
/*   Copyright (C) 2006 Sony Computer Entertainment Inc.    */
/*   All Rights Reserved.                                   */

#include <stdio.h>
#include <stdlib.h>
#include <cell/sysmodule.h>
#include <sysutil/sysutil_common.h>
#include <sys/process.h>       // For SYS_PROCESS_PARAM
#include "FWCellGCMWindow.h"
#include "FWGCMApplication.h"
#include "cell/FWCellSystemCallback.h"

using namespace cell::Gcm;

enum {
	SLOT_FW = 0,		// callback handler in FW
};

static bool receivedExitGameRequest = false;

void systemCallback(uint64_t status, uint64_t param, void *userdata)
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
		break;
	}
}

SYS_PROCESS_PARAM( 1001, 0x10000 );

//-----------------------------------------------------------------------------
// Description: Cell entry point
// Parameters:	argc - number of command line arguments
//				argv - array of command line arguments
// Returns:
// Notes:
//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	// create a new CellGLWindow object
	FWCellGCMWindow *pWindow = new FWCellGCMWindow(argc - 1, &argv[1], FWApplication::getApplication()->getDisplayInfo(), FWApplication::getApplication()->getStartupInfo(), FWGCMApplication::getApplication()->getConfiguration());

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
	// check reference register twice to avoid wrong hehavior due to
	// the conflict of the reference value an application is using
	cellGcmFinish(0x00000000);
	cellGcmFinish(0xffffffff);

	// call the window's destroy function
	pWindow->destroy();
	// delete it
	delete pWindow;

	return 0;
}
