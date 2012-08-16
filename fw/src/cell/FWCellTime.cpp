/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Cell Time class
//
// $File: //nextgendev/Framework_080/src/cell/FWCellTime.cpp $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include "FWTime.h"
#include <sys/sys_time.h>

// the current time value
FWTimeVal	FWTime::sCurrentTime;
// whether the timer is stopped
bool		FWTime::sIsStopped;
// zero value time
FWTimeVal	FWTime::sZero;
// timer frequency
double FWTime::sFreq;

//-----------------------------------------------------------------------------
// Description: Initialize the time class
// Parameters:	
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWTime::init()
{
	uint64_t freq;
	freq = sys_time_get_timebase_frequency();
	sFreq = (double)freq;
	sIsStopped = false;
	sZero.mVal = 0;
	// get initial value
	update();
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
