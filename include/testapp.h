#ifndef _TESTAPP_H_
#define _TESTAPP_H_

#include "psgl/FWGLApplication.h"
#include "FWInput.h"

class TestApp : public FWGLApplication{

public:
					TestApp();
	virtual	bool	onInit(int argc, char **ppArgv);
	virtual	bool	onUpdate();
	virtual	void	onRender();
	virtual	void	onShutdown();
	virtual	void	onSize(const FWDisplayInfo & dispInfo);
	virtual	void	bindcontrols();
	virtual	void	unbindcontrols();
	virtual	void	setmouseclientrelativetrue();
	virtual	void	setmouseclientrelativefalse();
	virtual	void	setupmedia();
	virtual	void	setupgame();
	virtual	void	play(float gamespeed);
	virtual	void	drawworld();
	virtual	void	drawhud();

private:
	FWInputFilter	*mpKey[256], *mpMouseX, *mpMouseY, *mpMouseLeft, *mpMouseMiddle, *mpMouseRight;
	FWInputFilter	*mpLeftX[4], *mpLeftY[4], *mpRightX[4], *mpRightY[4];
	FWInputFilter	*mpUp[4], *mpRight[4], *mpDown[4], *mpLeft[4];
	FWInputFilter	*mpTriangle[4], *mpCircle[4], *mpCross[4], *mpSquare[4];
	FWInputFilter	*mpL1[4], *mpL2[4], *mpL3[4];
	FWInputFilter	*mpR1[4], *mpR2[4], *mpR3[4];
	FWInputFilter	*mpSelect[4], *mpStart[4];
	FWInputFilter	*mpSensorX[4], *mpSensorY[4], *mpSensorZ[4], *mpGyro[4];
	FWTimeVal		mLastTime;
	float			fFPS;
	int				gamestate,lastgamestate;
	int				menustate,lastmenustate;
	bool			waitforscreenrefresh;

};

#endif//_TESTAPP_H_
