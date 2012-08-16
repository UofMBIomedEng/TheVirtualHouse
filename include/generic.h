#include "generic/drawprimatives.h"
#include "generic/genericmath.h"
#include "generic/loadbmp.h"
#include "generic/loadtga.h"
#include "generic/loadobj.h"
#include "generic/loadms3d.h"
#include "sky/skybox.h"
#include "generic/quaternions.h"
#include "generic/savescreenshot.h"
#include "generic/spherebumpmesh.h"
#include "generic/camera.h"
#include "generic/text.h"
#include "generic/buttons.h"

SKYBOX * skybox; 

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
}

void TestApp::setmouseclientrelativetrue(){
	FWInputDevice	*pMouse = FWInput::getDevice(FWInput::DeviceType_Mouse, 0);
	((FWInputDeviceMouse *)pMouse)->setClientRelative(true);
}

void TestApp::setmouseclientrelativefalse(){
	FWInputDevice	*pMouse = FWInput::getDevice(FWInput::DeviceType_Mouse, 0);
	((FWInputDeviceMouse *)pMouse)->setClientRelative(false);
}
