/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// OpenGL Extensions - functions supported by PSGL not present in OGL 1.1
//
// $File: //nextgendev/Framework_080/src/win32/FWWin32GLExtensions.cpp $
// $Author: asidwell $
// $Date: 2006/01/30 $
// $Revision: #2 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include "FWGLInclude.h"

void FWGLExtension::reportError(char *extensionName)
{
	char	errorString[2048];

	sprintf(errorString, "Your graphics hardware (%s, %s, OpenGL v%s) does not support the '%s' API call.\nTo ensure correct execution, please use a hardware accelerated OpenGL graphics card with recent drivers.", 
			glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION), extensionName);

	MessageBox(NULL, errorString, "OpenGL Error!", MB_ICONERROR);

	exit(0);
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
