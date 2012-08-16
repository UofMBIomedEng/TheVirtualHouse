const float version = 4.5;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <string>

// for wave palyer
#include <Windows.h>
#include <MMSystem.h>
#pragma comment(lib,"Winmm.lib")

#include "testapp.h"

#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
#include <fstream>
using std::ofstream;
using std::ifstream;
#include <cstdlib>

int screenw=800;
int screenh=600;
float screenfov=60;          //the field of view
float screenaspect=16.f/9.f;
double elapsedtime=0;
double elapseddist=0;
double expectdist=0;
double starttime=0;
double start_time=0;
double motion_time=0;
bool starttimeflag=1;
bool init_sky_flag=1;
int countdownjoystickstart=0;

char win_clue;

float camxpos,camypos,camzpos;
float camxang,camyang,camzang,tmpcamyang;
float camxposmov,camyposmov,camzposmov;
float camxangmov,camyangmov,camzangmov;
int trial=1;
int latency=1;
int sound_delay=10;
bool kidmode=0;
bool animal_background_sound=0;
float JoyAngVel=2.36;
float JoyTransVel=0.1;

int lang=1;   // 1=English 2=Spanish 3=French 4=German

#define max_latency 1000
int control_buffer[4][max_latency];
int latency_write_pointer=0;
int latency_read_pointer=0;
int stairtype=6;   //1=stairs at 180degrees, 2=stairs at 90 degrees, 3=ramp at 180degrees, 4=ramp at 90 degrees, 5=double stairs at 180degrees, 6= double ramps at 180degrees

//int temp;

const char mediadir[] = "Media/";
char* logfilename="default.txt";
char* total_logfilename="total.txt";
char logfilename_2[100];
FILE * pFile;
FILE * pFile_2;
FILE * pFile_3;


#include "generic.h"
#include "gamespecific\tilenames.h"
#include "setup.h"
#include "judgement.h"
#include "play.h"
#include "drawworld.h"
#include "drawhud.h"


// instantiate the class
TestApp app;

//-----------------------------------------------------------------------------
// Description: Constructor
//-----------------------------------------------------------------------------
TestApp::TestApp(){
	// set window title for Win32/Linux
	char windowtitle[30];
	sprintf(windowtitle,"%s[Version %.1f]","The Virtual House ",version);
	strcpy(mStartupInfo.mWindowTitle, windowtitle);
	// enable antialiasing
	mDispInfo.mAntiAlias = false;
}

//-----------------------------------------------------------------------------
// Description: Initialization callback
//-----------------------------------------------------------------------------
bool TestApp::onInit(int argc, char **ppArgv){
	if(argc>0)
		logfilename=ppArgv[0];
	for(int i=1;i<argc;i++){
		if(!strcmp(ppArgv[i],"/NOINFO")) showinfo=0;
		if(!strcmp(ppArgv[i],"/TESTMODE")) testmode=1;
		if(!strcmp(ppArgv[i],"/SHOWPLAYER")) showplayer=1;
		if(!strcmp(ppArgv[i],"/USEMOUSE")) freecamera=1;
		if(!strcmp(ppArgv[i],"/AUTOEXIT")) autoexit=1;
		if(!strcmp(ppArgv[i],"/USEJOYSTICK")) countdownjoystickstart=5;
		if(!strcmp(ppArgv[i],"/TRIAL")) trial=atoi(ppArgv[i+1]);                    
		if(!strcmp(ppArgv[i],"/LATENCY")) latency=atoi(ppArgv[i+1]);
		if(!strcmp(ppArgv[i],"/ALLOCENTRIC")) allocentric=1;
		if(!strcmp(ppArgv[i],"/JOYANGVEL")) JoyAngVel*=atof(ppArgv[i+1]);
		if(!strcmp(ppArgv[i],"/JOYTRANSVEL")) JoyTransVel*=atof(ppArgv[i+1]);
		if(!strcmp(ppArgv[i],"/LANGUAGE")) lang*=atoi(ppArgv[i+1]);
		if(!strcmp(ppArgv[i],"/KIDMODE")) kidmode=1;
		if(!strcmp(ppArgv[i],"/SHOWSKY")) showsky=1;
		if(!strcmp(ppArgv[i],"/ANIMSOUND")) animal_background_sound=1;
		if(!strcmp(ppArgv[i],"/PERPSTAIR")) stairtype=atoi(ppArgv[i+1]);
		if(!strcmp(ppArgv[i],"/LOGTOTAL")) total_logfilename=ppArgv[i+1];
    }

	ShowCursor(0);  // added to hide the mouse cursor

	if(testmode)
	{
		showinfo=0;
		countdownjoystickstart=5;
	}

	for(int temp1=0;temp1<4;temp1++)
		for(int temp2=0;temp2<max_latency;temp2++)
			control_buffer[temp1][temp2]=0;

	pFile = fopen (logfilename,"w");
	sprintf(logfilename_2,"%s%s",logfilename,"_Int.txt");
	pFile_2 = fopen ((char *)logfilename_2,"w");
	
	if(trial==1)
		pFile_3 = fopen ((char *)total_logfilename,"w");		//open a new total file
	else if(trial>1)
		pFile_3 = fopen ((char *)total_logfilename,"a");		//append to the existing total file
	
	srand(time(NULL));
	if(allocentric)
		targetwin=(int)(trial-1)%3;
	else
		targetwin=(int)rand()%3;
	FWGLApplication::onInit(argc, ppArgv);
	glEnable(GL_DEPTH_TEST);
	
	glDepthFunc(GL_LESS);
	glClearColor(0.0,0.0,0.0,0.0);
	glClearDepthf(1000.f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER,0.0f);
	srand((int)time(NULL));
	bindcontrols();
	gamestate=0;
	lastgamestate=0;
	menustate=0;
	waitforscreenrefresh=0;
	return true;
}

//-----------------------------------------------------------------------------
// Description: Update callback
//-----------------------------------------------------------------------------
bool TestApp::onUpdate(){

	//get frame rate and adjust game speed
	FWTimeVal time=FWTime::getCurrentTime();
	if(starttimeflag){
		starttimeflag=0;
		starttime=(double)time;
	}
	elapsedtime=((double)time-starttime);
	fFPS=1.f/(float)(time-mLastTime);
	mLastTime=time;
	float gamespeed=60.f/fFPS;
	if(gamespeed<0.01)gamespeed=0.01;
	if(gamespeed>2.0)gamespeed=2.0;

	int templastgamestate;
	int templastmenustate;
	if(!waitforscreenrefresh){
		templastgamestate=gamestate;
		templastmenustate=menustate;
	}

	if(waitforscreenrefresh){//damn you screen buffering
	}else if(gamestate==0){//load the loading screen
		setuptext();
		gamestate=1;
	}else if(gamestate==1){//loading screen for media
		setupbuttons();
		setupmedia();
		gamestate=2;
	}else if(gamestate==2){//main menu
		gamestate=3;
	}else if(gamestate==3){//setup the game world
		setupgame();
		gamestate=4;
	}else if(gamestate==4){//play
		play(gamespeed);				
	}else if(gamestate==5){//pause menu
	}else if(gamestate==6){//save screenshot
	}else if(gamestate==7){//save game
	}else if(gamestate==8){//load game
	}

	if(!waitforscreenrefresh){
		lastgamestate=templastgamestate;
		lastmenustate=templastmenustate;
		if(gamestate==1)waitforscreenrefresh=1;
		if(gamestate==3)waitforscreenrefresh=1;
	}else{
		waitforscreenrefresh=0;
	}

	return true;

}

//-----------------------------------------------------------------------------
// Description: Render callback
//-----------------------------------------------------------------------------
void TestApp::onRender(){

	//clear screen and set the viewport to the full screen
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,(GLsizei)screenw,(GLsizei)screenh);

	//draw the loading text
	if(gamestate==1 || gamestate==3){
		set2dcamera();
		switch(lang){
			case 1:
				drawtextcentered(0,0,(char*)"Loading Virtual House...",5);
				break;
			case 2:
				drawtextcentered(0,0,(char*)"Chargement Virtuelle Maison...",5);
				break;
			case 3:
				drawtextcentered(0,0,(char*)"Cargando Casa Virtual...",5);
				break;
			case 4:
				drawtextcentered(0,0,(char*)"Virtuelle Haus Aufladung...",5);
				break;
		}
		unset2dcamera();
	}
	//draw the game world
	if(gamestate==4){
		set3dcamera(
			camxpos,camypos,camzpos,
			camxang,camyang,camzang,
			screenfov,screenaspect);
		drawworld();
		set2dcamera();
		drawhud();
		unset2dcamera();
	}

}

//-----------------------------------------------------------------------------
// Description: Resize callback
//-----------------------------------------------------------------------------
void TestApp::onSize(const FWDisplayInfo &dispInfo){
	FWGLApplication::onSize(dispInfo);
	screenw = dispInfo.mWidth;
	screenh = dispInfo.mHeight;
	screenaspect = (float)screenw/(float)screenh;
}

//-----------------------------------------------------------------------------
// Description: Shutdown callback
//-----------------------------------------------------------------------------
void TestApp::onShutdown(){
	unbindcontrols();
	fclose (pFile);
	fprintf(pFile_2,"_______________________________________________________________________________________________________________________\n");
	fclose (pFile_2);
	fclose (pFile_3);
	if(showsky)
		skybox->Finalize();
}
