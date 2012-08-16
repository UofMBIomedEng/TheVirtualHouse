/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Win32 Time class
//
// $File: //nextgendev/Framework_080/src/win32/FWWin32Time.cpp $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include "FWTime.h"

// Counter frequency
LARGE_INTEGER	FWTime::sPerfCountFreq;
// Current time
FWTimeVal		FWTime::sCurrentTime;
// Counter frequency as double
double			FWTime::sFreq;
// Is time stopped?
bool			FWTime::sIsStopped;
// Zero value time
FWTimeVal		FWTime::sZero;

//-----------------------------------------------------------------------------
// Description: Initialize the time class
// Parameters:	
// Returns:
// Notes: Gets counter frequency and sets up some variables
//-----------------------------------------------------------------------------
void FWTime::init()
{
	// get number of ticks per second
	QueryPerformanceFrequency(&sPerfCountFreq);
	// get as a double
	sFreq = (double)sPerfCountFreq.QuadPart;
	// time isn't stopped
	sIsStopped = false;
	// set zero time value
	sZero.mVal.QuadPart = 0;

	// get initial value
	update();
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
