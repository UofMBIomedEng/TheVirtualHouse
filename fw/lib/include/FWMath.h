/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Math functions
//
// $File: //nextgendev/Framework_080/include/FWMath.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_MATH_H__
#define __FW_MATH_H__

#ifdef _WIN32
#define __attribute__(x)
#include <scalar/cpp/vectormath_aos.h>
#endif//_WIN32

#ifdef __linux__
#include <scalar/cpp/vectormath_aos.h>
#endif//__linux__

#ifdef __CELLOS_LV2__
#include <vectormath/cpp/vectormath_aos.h>
#endif//__CELLOS_LV2__

using namespace Vectormath::Aos;

#endif //__FW_MATH_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
