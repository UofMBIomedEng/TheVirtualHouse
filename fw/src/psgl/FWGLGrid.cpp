/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// debug grid rendering
//
// $File: //nextgendev/Framework_080/src/FWGLGrid.cpp $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include "FWDebug.h"
#include "psgl/FWGLGrid.h"
#include "psgl/FWGLInclude.h"

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWGLGrid::FWGLGrid() :
mPlane(Plane_XZ),
mSize(100.f),
mSpacing(10.f),
mSubLines(2),
mAxisR(0.f),
mAxisG(0.f),
mAxisB(0.f),
mLineR(0.5f),
mLineG(0.5f),
mLineB(0.5f),
mSubR(1.f),
mSubG(1.f),
mSubB(1.f),
mpVerts(NULL),
mpCols(NULL),
mNumVerts(0),
mNumGridLines(0),
mNumSubLines(0),
mLineWidth(1.f),
mBuildGrid(true)
{
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWGLGrid::~FWGLGrid()
{
	if(mpVerts)
		delete []mpVerts;
	if(mpCols)
		delete []mpCols;
}

//-----------------------------------------------------------------------------
// Description: Render the grid
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWGLGrid::render()
{
	if(mBuildGrid)
		buildGrid();

	// set up for line rendering
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(mLineWidth);
	glEnable(GL_LINE_SMOOTH);
	glDepthMask(1);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, mpVerts);
	glColorPointer(4, GL_FLOAT, 0, mpCols);

	glDrawArrays(GL_LINES, 0, mNumVerts);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glLineWidth(1.f);
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(0);
}

//-----------------------------------------------------------------------------
// Description: Build the grid's vertices
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWGLGrid::buildGrid()
{
	// allocate space for verts
	if(mpVerts)
		delete []mpVerts;
	if(mpCols)
		delete []mpCols;

	mNumVerts = calcNumVerts();

	mpVerts = new float[mNumVerts * 3];
	mpCols = new float[mNumVerts * 4];

	float *pVert = mpVerts;
	float *pCol = mpCols;

	// get which plane we are building the grid in
	int axis0 = 0, axis1 = 2, zeroAxis = 1;
	switch(mPlane)
	{
	case Plane_Undefined:
		FWASSERT(0);
		break;
	case Plane_XY:
		axis0 = 0;
		axis1 = 1;
		zeroAxis = 2;
		break;
	case Plane_XZ:
		axis0 = 0;
		zeroAxis = 1;
		axis1 = 2;
		break;
	case Plane_YZ:
		zeroAxis = 0;
		axis0 = 1;
		axis1 = 2;
		break;
	}

	float subSpacing = mSpacing / (float)mSubLines;
	float pos = subSpacing;
	int i;
	while(pos < mSize)
	{
		for(i = 0; i < (mSubLines - 1); i ++)
		{
			pVert[axis0] = -mSize;
			pVert[axis1] = pos;
			pVert[zeroAxis] = 0.f;
			pVert += 3;
			pCol[0] = mSubR;
			pCol[1] = mSubG;
			pCol[2] = mSubB;
			pCol[3] = 1.f;
			pCol += 4;

			pVert[axis0] = mSize;
			pVert[axis1] = pos;
			pVert[zeroAxis] = 0.f;
			pVert += 3;
			pCol[0] = mSubR;
			pCol[1] = mSubG;
			pCol[2] = mSubB;
			pCol[3] = 1.f;
			pCol += 4;

			pVert[axis0] = -mSize;
			pVert[axis1] = -pos;
			pVert[zeroAxis] = 0.f;
			pVert += 3;
			pCol[0] = mSubR;
			pCol[1] = mSubG;
			pCol[2] = mSubB;
			pCol[3] = 1.f;
			pCol += 4;

			pVert[axis0] = mSize;
			pVert[axis1] = -pos;
			pVert[zeroAxis] = 0.f;
			pVert += 3;
			pCol[0] = mSubR;
			pCol[1] = mSubG;
			pCol[2] = mSubB;
			pCol[3] = 1.f;
			pCol += 4;

			pVert[axis1] = -mSize;
			pVert[axis0] = pos;
			pVert[zeroAxis] = 0.f;
			pVert += 3;
			pCol[0] = mSubR;
			pCol[1] = mSubG;
			pCol[2] = mSubB;
			pCol[3] = 1.f;
			pCol += 4;

			pVert[axis1] = mSize;
			pVert[axis0] = pos;
			pVert[zeroAxis] = 0.f;
			pVert += 3;
			pCol[0] = mSubR;
			pCol[1] = mSubG;
			pCol[2] = mSubB;
			pCol[3] = 1.f;
			pCol += 4;

			pVert[axis1] = -mSize;
			pVert[axis0] = -pos;
			pVert[zeroAxis] = 0.f;
			pVert += 3;
			pCol[0] = mSubR;
			pCol[1] = mSubG;
			pCol[2] = mSubB;
			pCol[3] = 1.f;
			pCol += 4;

			pVert[axis1] = mSize;
			pVert[axis0] = -pos;
			pVert[zeroAxis] = 0.f;
			pVert += 3;
			pCol[0] = mSubR;
			pCol[1] = mSubG;
			pCol[2] = mSubB;
			pCol[3] = 1.f;
			pCol += 4;

			pos += subSpacing;
			if(pos > mSize)
				break;
		}

		pos += subSpacing;
	}

	if((mSize / mSpacing) - (float)mNumGridLines)
	{
		pVert[axis0] = -mSize;
		pVert[axis1] = -mSize;
		pVert[zeroAxis] = 0.f;
		pVert += 3;
		pCol[0] = mSubR;
		pCol[1] = mSubG;
		pCol[2] = mSubB;
		pCol[3] = 1.f;
		pCol += 4;

		pVert[axis0] = -mSize;
		pVert[axis1] = mSize;
		pVert[zeroAxis] = 0.f;
		pVert += 3;
		pCol[0] = mSubR;
		pCol[1] = mSubG;
		pCol[2] = mSubB;
		pCol[3] = 1.f;
		pCol += 4;

		pVert[axis0] = mSize;
		pVert[axis1] = -mSize;
		pVert[zeroAxis] = 0.f;
		pVert += 3;
		pCol[0] = mSubR;
		pCol[1] = mSubG;
		pCol[2] = mSubB;
		pCol[3] = 1.f;
		pCol += 4;

		pVert[axis0] = mSize;
		pVert[axis1] = mSize;
		pVert[zeroAxis] = 0.f;
		pVert += 3;
		pCol[0] = mSubR;
		pCol[1] = mSubG;
		pCol[2] = mSubB;
		pCol[3] = 1.f;
		pCol += 4;

		pVert[axis0] = -mSize;
		pVert[axis1] = -mSize;
		pVert[zeroAxis] = 0.f;
		pVert += 3;
		pCol[0] = mSubR;
		pCol[1] = mSubG;
		pCol[2] = mSubB;
		pCol[3] = 1.f;
		pCol += 4;

		pVert[axis0] = mSize;
		pVert[axis1] = -mSize;
		pVert[zeroAxis] = 0.f;
		pVert += 3;
		pCol[0] = mSubR;
		pCol[1] = mSubG;
		pCol[2] = mSubB;
		pCol[3] = 1.f;
		pCol += 4;

		pVert[axis0] = -mSize;
		pVert[axis1] = mSize;
		pVert[zeroAxis] = 0.f;
		pVert += 3;
		pCol[0] = mSubR;
		pCol[1] = mSubG;
		pCol[2] = mSubB;
		pCol[3] = 1.f;
		pCol += 4;

		pVert[axis0] = mSize;
		pVert[axis1] = mSize;
		pVert[zeroAxis] = 0.f;
		pVert += 3;
		pCol[0] = mSubR;
		pCol[1] = mSubG;
		pCol[2] = mSubB;
		pCol[3] = 1.f;
		pCol += 4;
	}

	// grid lines
	pos = mSpacing;
	for(i = 0; i < mNumGridLines; i ++)
	{
		pVert[axis0] = -mSize;
		pVert[axis1] = pos;
		pVert[zeroAxis] = 0.f;
		pVert += 3;
		pCol[0] = mLineR;
		pCol[1] = mLineG;
		pCol[2] = mLineB;
		pCol[3] = 1.f;
		pCol += 4;

		pVert[axis0] = mSize;
		pVert[axis1] = pos;
		pVert[zeroAxis] = 0.f;
		pVert += 3;
		pCol[0] = mLineR;
		pCol[1] = mLineG;
		pCol[2] = mLineB;
		pCol[3] = 1.f;
		pCol += 4;

		pVert[axis0] = -mSize;
		pVert[axis1] = -pos;
		pVert[zeroAxis] = 0.f;
		pVert += 3;
		pCol[0] = mLineR;
		pCol[1] = mLineG;
		pCol[2] = mLineB;
		pCol[3] = 1.f;
		pCol += 4;

		pVert[axis0] = mSize;
		pVert[axis1] = -pos;
		pVert[zeroAxis] = 0.f;
		pVert += 3;
		pCol[0] = mLineR;
		pCol[1] = mLineG;
		pCol[2] = mLineB;
		pCol[3] = 1.f;
		pCol += 4;

		pVert[axis1] = -mSize;
		pVert[axis0] = pos;
		pVert[zeroAxis] = 0.f;
		pVert += 3;
		pCol[0] = mLineR;
		pCol[1] = mLineG;
		pCol[2] = mLineB;
		pCol[3] = 1.f;
		pCol += 4;

		pVert[axis1] = mSize;
		pVert[axis0] = pos;
		pVert[zeroAxis] = 0.f;
		pVert += 3;
		pCol[0] = mLineR;
		pCol[1] = mLineG;
		pCol[2] = mLineB;
		pCol[3] = 1.f;
		pCol += 4;

		pVert[axis1] = -mSize;
		pVert[axis0] = -pos;
		pVert[zeroAxis] = 0.f;
		pVert += 3;
		pCol[0] = mLineR;
		pCol[1] = mLineG;
		pCol[2] = mLineB;
		pCol[3] = 1.f;
		pCol += 4;

		pVert[axis1] = mSize;
		pVert[axis0] = -pos;
		pVert[zeroAxis] = 0.f;
		pVert += 3;
		pCol[0] = mLineR;
		pCol[1] = mLineG;
		pCol[2] = mLineB;
		pCol[3] = 1.f;
		pCol += 4;

		pos += mSpacing;
	}

	// axis lines
	pVert[axis0] = -mSize;
	pVert[axis1] = 0.f;
	pVert[zeroAxis] = 0.f;
	pVert += 3;
	pCol[0] = mAxisR;
	pCol[1] = mAxisG;
	pCol[2] = mAxisB;
	pCol[3] = 1.f;
	pCol += 4;

	pVert[axis0] = mSize;
	pVert[axis1] = 0.f;
	pVert[zeroAxis] = 0.f;
	pVert += 3;
	pCol[0] = mAxisR;
	pCol[1] = mAxisG;
	pCol[2] = mAxisB;
	pCol[3] = 1.f;
	pCol += 4;

	pVert[axis0] = 0.f;
	pVert[axis1] = -mSize;
	pVert[zeroAxis] = 0.f;
	pVert += 3;
	pCol[0] = mAxisR;
	pCol[1] = mAxisG;
	pCol[2] = mAxisB;
	pCol[3] = 1.f;
	pCol += 4;

	pVert[axis0] = 0.f;
	pVert[axis1] = mSize;
	pVert[zeroAxis] = 0.f;
	pVert += 3;
	pCol[0] = mAxisR;
	pCol[1] = mAxisG;
	pCol[2] = mAxisB;
	pCol[3] = 1.f;
	pCol += 4;

#ifdef _DEBUG
	int numVertsWritten = (((long)pVert - (long)mpVerts) / (sizeof(float) * 3));

	FWASSERT(numVertsWritten == mNumVerts);
#endif//_DEBUG

	mBuildGrid = false;
}

//-----------------------------------------------------------------------------
// Description: Calculate the number of vertices required
// Parameters:
// Returns: The number of vertices required to render the grid
// Notes:
//-----------------------------------------------------------------------------
int FWGLGrid::calcNumVerts()
{
	mNumGridLines = (int)(mSize / mSpacing);
	mNumSubLines = (int)(mSize / (mSpacing / (float)mSubLines)) - mNumGridLines;

	int numVerts = (2 + (mNumGridLines + mNumSubLines) * 4) * 2;

	if((mSize / mSpacing) - (float)mNumGridLines)
		numVerts += 8;

	return numVerts;
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
