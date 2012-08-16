#include "generic/drawprimatives.h"
#include "generic/genericmath.h"
#include "generic/loadbmp.h"
#include "generic/loadtga.h"
#include "generic/loadobj.h"
#include "generic/loadms3d.h"
#include "generic/quaternions.h"
#include "generic/savescreenshot.h"
#include "generic/spherebumpmesh.h"
#include "generic/camera.h"
#include "generic/text.h"
#include "generic/buttons.h"

void TestApp::bindcontrols(){
	//keyboard
	FWInputDevice	*pKeybd = FWInput::getDevice(FWInput::DeviceType_Keyboard, 0);
	if(pKeybd != NULL){
		for(int a=0; a<256; a++){
			mpKey[a] = pKeybd->bindFilter();
			mpKey[a]->setChannel((FWInput::Channel)a);
		}
	}else{
		for(int a=0; a<256; a++)mpKey[a] = NULL;
	}
	//mouse
	FWInputDevice	*pMouse = FWInput::getDevice(FWInput::DeviceType_Mouse, 0);
	if(pMouse != NULL){
		((FWInputDeviceMouse *)pMouse)->setClientRelative(true);
		mpMouseX = pMouse->bindFilter();
		mpMouseX->setChannel(FWInput::Channel_XAxis_0);
		mpMouseY = pMouse->bindFilter();
		mpMouseY->setChannel(FWInput::Channel_YAxis_0);
		mpMouseLeft = pMouse->bindFilter();
		mpMouseLeft->setChannel(FWInput::Channel_Button_LeftMB);
		mpMouseMiddle = pMouse->bindFilter();
		mpMouseMiddle->setChannel(FWInput::Channel_Button_MiddleMB);
		mpMouseRight = pMouse->bindFilter();
		mpMouseRight->setChannel(FWInput::Channel_Button_RightMB);
	}else{
		mpMouseX = mpMouseY = mpMouseLeft = mpMouseMiddle = mpMouseRight = NULL;
	}
	//ps3 controller
	for(int a=0; a<4; a++){
		FWInputDevice	*pPad = FWInput::getDevice(FWInput::DeviceType_Pad, a);
		if(pPad != NULL){
			mpLeftX[a] = pPad->bindFilter();
			mpLeftX[a]->setChannel(FWInput::Channel_XAxis_0);
			mpLeftY[a] = pPad->bindFilter();
			mpLeftY[a]->setChannel(FWInput::Channel_YAxis_0);
			mpRightX[a] = pPad->bindFilter();
			mpRightX[a]->setChannel(FWInput::Channel_XAxis_1);
			mpRightY[a] = pPad->bindFilter();
			mpRightY[a]->setChannel(FWInput::Channel_YAxis_1);
			mpUp[a] = pPad->bindFilter();
			mpUp[a]->setChannel(FWInput::Channel_Button_Up);
			mpRight[a] = pPad->bindFilter();
			mpRight[a]->setChannel(FWInput::Channel_Button_Right);
			mpDown[a] = pPad->bindFilter();
			mpDown[a]->setChannel(FWInput::Channel_Button_Down);
			mpLeft[a] = pPad->bindFilter();
			mpLeft[a]->setChannel(FWInput::Channel_Button_Left);
			mpTriangle[a] = pPad->bindFilter();
			mpTriangle[a]->setChannel(FWInput::Channel_Button_Triangle);
			mpCircle[a] = pPad->bindFilter();
			mpCircle[a]->setChannel(FWInput::Channel_Button_Circle);
			mpCross[a] = pPad->bindFilter();
			mpCross[a]->setChannel(FWInput::Channel_Button_Cross);
			mpSquare[a] = pPad->bindFilter();
			mpSquare[a]->setChannel(FWInput::Channel_Button_Square);
			mpL1[a] = pPad->bindFilter();
			mpL1[a]->setChannel(FWInput::Channel_Button_L1);
			mpL2[a] = pPad->bindFilter();
			mpL2[a]->setChannel(FWInput::Channel_Button_L2);
			mpL3[a] = pPad->bindFilter();
			mpL3[a]->setChannel(FWInput::Channel_Button_L3);
			mpR1[a] = pPad->bindFilter();
			mpR1[a]->setChannel(FWInput::Channel_Button_R1);
			mpR2[a] = pPad->bindFilter();
			mpR2[a]->setChannel(FWInput::Channel_Button_R2);
			mpR3[a] = pPad->bindFilter();
			mpR3[a]->setChannel(FWInput::Channel_Button_R3);
			mpSelect[a] = pPad->bindFilter();
			mpSelect[a]->setChannel(FWInput::Channel_Button_Select);
			mpStart[a] = pPad->bindFilter();
			mpStart[a]->setChannel(FWInput::Channel_Button_Start);
			mpSensorX[a] = pPad->bindFilter();
			mpSensorX[a]->setChannel(FWInput::Channel_XAxis_2);
			mpSensorY[a] = pPad->bindFilter();
			mpSensorY[a]->setChannel(FWInput::Channel_YAxis_2);
			mpSensorZ[a] = pPad->bindFilter();
			mpSensorZ[a]->setChannel(FWInput::Channel_ZAxis_2);
			mpGyro[a] = pPad->bindFilter();
			mpGyro[a]->setChannel(FWInput::Channel_Gyro);
		}
	}
}

void TestApp::unbindcontrols(){
	//unbind keyboard
	FWInputDevice	*pKeybd = FWInput::getDevice(FWInput::DeviceType_Keyboard, 0);
	if(pKeybd != NULL){
		for(int a=0; a<256; a++)pKeybd->unbindFilter(mpKey[a]);
	}
	//unbind mouse
	FWInputDevice	*pMouse = FWInput::getDevice(FWInput::DeviceType_Mouse, 0);
	if(pMouse != NULL){
		pMouse->unbindFilter(mpMouseX);
		pMouse->unbindFilter(mpMouseY);
		pMouse->unbindFilter(mpMouseLeft);
		pMouse->unbindFilter(mpMouseMiddle);
		pMouse->unbindFilter(mpMouseRight);
	}
	//unbind ps3 controller
	for(int a=0; a<4; a++){
		FWInputDevice	*pPad = FWInput::getDevice(FWInput::DeviceType_Pad, a);
		if(pPad != NULL){
			pPad->unbindFilter(mpLeftX[a]);
			pPad->unbindFilter(mpLeftY[a]);
			pPad->unbindFilter(mpRightX[a]);
			pPad->unbindFilter(mpRightY[a]);
			pPad->unbindFilter(mpUp[a]);
			pPad->unbindFilter(mpRight[a]);
			pPad->unbindFilter(mpDown[a]);
			pPad->unbindFilter(mpLeft[a]);
			pPad->unbindFilter(mpTriangle[a]);
			pPad->unbindFilter(mpCircle[a]);
			pPad->unbindFilter(mpCross[a]);
			pPad->unbindFilter(mpSquare[a]);
			pPad->unbindFilter(mpL1[a]);
			pPad->unbindFilter(mpL2[a]);
			pPad->unbindFilter(mpL3[a]);
			pPad->unbindFilter(mpR1[a]);
			pPad->unbindFilter(mpR2[a]);
			pPad->unbindFilter(mpR3[a]);
			pPad->unbindFilter(mpSelect[a]);
			pPad->unbindFilter(mpStart[a]);
			pPad->unbindFilter(mpSensorX[a]);
			pPad->unbindFilter(mpSensorY[a]);
			pPad->unbindFilter(mpSensorZ[a]);
			pPad->unbindFilter(mpGyro[a]);
		}
	}
}

void TestApp::setmouseclientrelativetrue(){
	FWInputDevice	*pMouse = FWInput::getDevice(FWInput::DeviceType_Mouse, 0);
	((FWInputDeviceMouse *)pMouse)->setClientRelative(true);
}

void TestApp::setmouseclientrelativefalse(){
	FWInputDevice	*pMouse = FWInput::getDevice(FWInput::DeviceType_Mouse, 0);
	((FWInputDeviceMouse *)pMouse)->setClientRelative(false);
}
