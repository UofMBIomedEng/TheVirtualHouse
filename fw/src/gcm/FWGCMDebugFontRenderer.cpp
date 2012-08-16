/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// GCM debug font rendering
//
// $File: //nextgendev/Framework_050/src/FWGCMDebugFontRenderer.cpp $
// $Author: asidwell $
// $Date: 2005/09/28 $
// $Revision: #2 $
//
// Copyright (C) 2005 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <cell/gcm.h>
#include <sys/timer.h>
#include <vectormath_aos.h>

#include "FWGCMDebugFontRenderer.h"
#include "gcmutil.h"

using namespace cell::Gcm;

using namespace Vectormath;
using namespace Vectormath::Aos;

uint8_t *FWGCMDebugFontRenderer::spTextureData;

// shader
extern struct _CGprogram _binary_dbgfont_vpshader_vpo_start;
extern struct _CGprogram _binary_dbgfont_fpshader_fpo_start;

uint8_t* FWGCMDebugFontRenderer::mpTexture = NULL;
uint8_t* FWGCMDebugFontRenderer::mPosition = NULL;
uint8_t* FWGCMDebugFontRenderer::mTexCoord = NULL;
uint8_t* FWGCMDebugFontRenderer::mColor = NULL;
CGresource FWGCMDebugFontRenderer::mPosIndex;
CGresource FWGCMDebugFontRenderer::mTexIndex;
CGresource FWGCMDebugFontRenderer::mColIndex;
CGresource FWGCMDebugFontRenderer::mTexUnit;

CGprogram FWGCMDebugFontRenderer::mCGVertexProgram;				// CG binary program
CGprogram FWGCMDebugFontRenderer::mCGFragmentProgram;			// CG binary program

void *FWGCMDebugFontRenderer::mVertexProgramUCode;				// this is sysmem
void *FWGCMDebugFontRenderer::mFragmentProgramUCode;			// this is vidmem

CGparameter FWGCMDebugFontRenderer::mModelViewProj;
float FWGCMDebugFontRenderer::mMVPMatrix[16];
uint32_t *FWGCMDebugFontRenderer::mLabel = NULL;
uint32_t FWGCMDebugFontRenderer::mLabelValue = 0;


uint32_t FWGCMDebugFontRenderer::mFragmentProgramOffset;
uint32_t FWGCMDebugFontRenderer::mTextureOffset;
uint32_t FWGCMDebugFontRenderer::mPositionOffset;
uint32_t FWGCMDebugFontRenderer::mTexCoordOffset;
uint32_t FWGCMDebugFontRenderer::mColorOffset;

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters:	
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWGCMDebugFontRenderer::FWGCMDebugFontRenderer()
{
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters:	
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWGCMDebugFontRenderer::~FWGCMDebugFontRenderer()
{
}

void FWGCMDebugFontRenderer::initShader()
{
	mCGVertexProgram   = &_binary_dbgfont_vpshader_vpo_start;
	mCGFragmentProgram = &_binary_dbgfont_fpshader_fpo_start;

	// init
	cellGcmCgInitProgram(mCGVertexProgram);
	cellGcmCgInitProgram(mCGFragmentProgram);

	// allocate video memory for fragment program
	unsigned int ucodeSize;
	void *ucode;

	// get and copy 
	cellGcmCgGetUCode(mCGFragmentProgram, &ucode, &ucodeSize);
	mFragmentProgramUCode = cellGcmUtilAllocateLocalMemory(ucodeSize, 64);
	cellGcmAddressToOffset(mFragmentProgramUCode, &mFragmentProgramOffset);

	memcpy(mFragmentProgramUCode, ucode, ucodeSize); 

	// get and copy
	cellGcmCgGetUCode(mCGVertexProgram, &ucode, &ucodeSize);
	mVertexProgramUCode = ucode;
}

//-----------------------------------------------------------------------------
// Description: Initialize debug font renderer
// Parameters:	
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWGCMDebugFontRenderer::init()
{
	// reset sempahore
	mLabel = cellGcmGetLabelAddress(sLabelId);
	*mLabel = mLabelValue; // initial value: 0

	initShader();

	CGparameter position
		= cellGcmCgGetNamedParameter(mCGVertexProgram, "position");
	CGparameter texcoord
		= cellGcmCgGetNamedParameter(mCGVertexProgram, "texcoord");
	CGparameter color
		= cellGcmCgGetNamedParameter(mCGVertexProgram, "color");

	// get vertex attribute index
	mPosIndex = (CGresource)(cellGcmCgGetParameterResource(mCGVertexProgram, position) - CG_ATTR0);
	mTexIndex = (CGresource)(cellGcmCgGetParameterResource(mCGVertexProgram, texcoord) - CG_ATTR0);
	mColIndex = (CGresource)(cellGcmCgGetParameterResource(mCGVertexProgram, color) - CG_ATTR0);

	// set texture parameters
	CGparameter texture
		= cellGcmCgGetNamedParameter(mCGFragmentProgram, "texture");
	mTexUnit = (CGresource)(cellGcmCgGetParameterResource(mCGFragmentProgram, texture) - CG_TEXUNIT0);

#ifdef FWGCMDEBUGFONTRENDERER_USE_32BIT
	// convert texture to 32-bit
	// since CELL_GCM_ALPHA texture doesn't work on GCM out of the box
	// align to 128 byte boundary for speed
	cellGcmAllocateLinearLocalMemory(FWDEBUGFONT_DATA_SIZE * 4,
									 (void **)&spTextureData, &BytesAllocated);
	assert(((size_t)spTextureData % 128) == 0);

	mpTexture = (uint8_t *)(((long)spTextureData + 127) & ~127);
	uint8_t *pFontData = (uint8_t *)getFontData();

	cellGcmAddressToOffset(mpTexture, &mTextureOffset);

	for(int i = 0; i < FWDEBUGFONT_DATA_SIZE; i ++)
	{
      mpTexture[i * 4] = 255;
      mpTexture[i * 4 + 1] = 255;
      mpTexture[i * 4 + 2] = 255;
	  mpTexture[i * 4 + 3] = pFontData[i];
    }
#else
	spTextureData = (uint8_t*)cellGcmUtilAllocateLocalMemory(FWDEBUGFONT_DATA_SIZE, 128);
	assert(((size_t)spTextureData % 128) == 0);
	mpTexture = (uint8_t *)(((long)spTextureData + 127) & ~127);

	uint8_t *pFontData = (uint8_t *)getFontData();

	for(int i = 0; i < FWDEBUGFONT_DATA_SIZE; i ++)
	{
	  mpTexture[i] = pFontData[i];
	}
#endif//FWGCMDEBUGFONTRENDERER_USE_32BIT

	cellGcmAddressToOffset(mpTexture, &mTextureOffset);

	mPosition = (uint8_t*)cellGcmUtilAllocateLocalMemory(
		FWDEBUGFONT_MAX_CHAR_COUNT * NUM_VERTS_PER_GLYPH * sizeof(float) * 3, 128);
	mTexCoord = (uint8_t*)cellGcmUtilAllocateLocalMemory(
		FWDEBUGFONT_MAX_CHAR_COUNT * NUM_VERTS_PER_GLYPH * sizeof(float) * 2, 128);
	mColor    = (uint8_t*)cellGcmUtilAllocateLocalMemory(
		FWDEBUGFONT_MAX_CHAR_COUNT * NUM_VERTS_PER_GLYPH * sizeof(float) * 4, 128);

	cellGcmAddressToOffset(mPosition, &mPositionOffset);
	cellGcmAddressToOffset(mTexCoord, &mTexCoordOffset);
	cellGcmAddressToOffset(mColor, &mColorOffset);
}

//-----------------------------------------------------------------------------
// Description: Shutdown debug font renderer
// Parameters:	
// Returns:
// Notes: Frees font texture
//-----------------------------------------------------------------------------
void FWGCMDebugFontRenderer::shutdown()
{
#ifdef FWGCMDEBUGFONTRENDERER_USE_32BIT
	delete []spTextureData;
#endif//FWGCMDEBUGFONTRENDERER_USE_32BIT
}

//-----------------------------------------------------------------------------
// Description: Prepare for rendering text
// Parameters:	r - red
//				g - green
//				b - blue
//				a - alpha
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWGCMDebugFontRenderer::printStart(float r, float g, float b, float a)
{
	// set color
	sR = r;
	sG = g;
	sB = b;
	sA = a;

	// setup render states
	// set alpha blending
	cellGcmSetBlendFunc(CELL_GCM_SRC_ALPHA, CELL_GCM_ONE_MINUS_SRC_ALPHA,
						CELL_GCM_SRC_ALPHA, CELL_GCM_ONE_MINUS_SRC_ALPHA);
    cellGcmSetBlendEquation(CELL_GCM_FUNC_ADD, CELL_GCM_FUNC_ADD);
	cellGcmSetBlendEnable(CELL_GCM_TRUE);
	cellGcmSetLogicOpEnable(CELL_GCM_FALSE);

	// no depth test
	cellGcmSetDepthTestEnable(CELL_GCM_FALSE);

	// bind Cg programs
	// NOTE: vertex program constants are copied here
	cellGcmSetVertexProgram(mCGVertexProgram, mVertexProgramUCode);
	cellGcmSetFragmentProgram(mCGFragmentProgram, mFragmentProgramOffset);

#ifdef FWGCMDEBUGFONTRENDERER_USE_32BIT
	CellGcmTexture tex;
	tex.format = CELL_GCM_TEXTURE_B8 | CELL_GCM_TEXTURE_LN | CELL_GCM_TEXTURE_NR;
	tex.mipmap = 1;
	tex.dimention = CELL_GCM_TEXTURE_DIMENSION_2;
	tex.cubemap = CELL_GCM_FALSE;
	tex.remap = CELL_GCM_TEXTURE_REMAP_REMAP << 14 |
		CELL_GCM_TEXTURE_REMAP_REMAP << 12 |
		CELL_GCM_TEXTURE_REMAP_REMAP << 10 |
		CELL_GCM_TEXTURE_REMAP_REMAP << 8 |
		CELL_GCM_TEXTURE_REMAP_FROM_A << 6 |
		CELL_GCM_TEXTURE_REMAP_FROM_B << 4 |
		CELL_GCM_TEXTURE_REMAP_FROM_G << 2 |
		CELL_GCM_TEXTURE_REMAP_FROM_R;
	tex.width = FWDEBUGFONT_TEXTURE_WIDTH;
	tex.height = FWDEBUGFONT_TEXTURE_HEIGHT;
	tex.depth = 1;
	tex.pitch = FWDEBUGFONT_TEXTURE_WIDTH*4;
	tex.location = CELL_GCM_LOCATION_LOCAL;
	tex.offset = mTextureOffset;
	cellGcmSetTexture(mTexUnit, &tex);
#else
	CellGcmTexture tex;
	tex.format = CELL_GCM_TEXTURE_B8 | CELL_GCM_TEXTURE_LN | CELL_GCM_TEXTURE_NR;
	tex.mipmap = 1;
	tex.dimension = CELL_GCM_TEXTURE_DIMENSION_2;
	tex.cubemap = CELL_GCM_FALSE;
	tex.remap = CELL_GCM_TEXTURE_REMAP_REMAP << 14 |
		CELL_GCM_TEXTURE_REMAP_REMAP << 12 |
		CELL_GCM_TEXTURE_REMAP_REMAP << 10 |
		CELL_GCM_TEXTURE_REMAP_REMAP << 8 |
		CELL_GCM_TEXTURE_REMAP_FROM_B << 6 |
		CELL_GCM_TEXTURE_REMAP_FROM_B << 4 |
		CELL_GCM_TEXTURE_REMAP_FROM_B << 2 |
		CELL_GCM_TEXTURE_REMAP_FROM_B;
	tex.width = FWDEBUGFONT_TEXTURE_WIDTH;
	tex.height = FWDEBUGFONT_TEXTURE_HEIGHT;
	tex.depth = 1;
	tex.pitch = FWDEBUGFONT_TEXTURE_WIDTH;
	tex.location = CELL_GCM_LOCATION_LOCAL;
	tex.offset = mTextureOffset;
	cellGcmSetTexture(mTexUnit, &tex);
#endif//FWGCMDEBUGFONTRENDERER_USE_32BIT

	// bind texture and set filter
	cellGcmSetTextureControl(mTexUnit, CELL_GCM_TRUE,
							 1*0xff, 13*0xff, CELL_GCM_TEXTURE_MAX_ANISO_1); // MIN:1,MAX:13,ANISO:1
	cellGcmSetTextureFilter(mTexUnit, 0,
							CELL_GCM_TEXTURE_NEAREST_LINEAR,
							CELL_GCM_TEXTURE_LINEAR, CELL_GCM_TEXTURE_CONVOLUTION_QUINCUNX);
	cellGcmSetTextureAddress(mTexUnit, CELL_GCM_TEXTURE_WRAP,
							 CELL_GCM_TEXTURE_WRAP, CELL_GCM_TEXTURE_WRAP,
							 CELL_GCM_TEXTURE_UNSIGNED_REMAP_NORMAL,
							 CELL_GCM_TEXTURE_ZFUNC_LESS, 0);
}

//-----------------------------------------------------------------------------
// Description: Do a single pass of text rendering
// Parameters:	pPositions - vertex position array
//				pTexCoords - vertex texture co-ord array
//				pColors - vertex color array
//				numVerts - number of vertices
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWGCMDebugFontRenderer::printPass(FWDebugFont::Position *pPositions, FWDebugFont::TexCoord *pTexCoords, FWDebugFont::Color *pColors, int numVerts)
{
	// wait for ROP completion
	while (*((volatile uint32_t *)mLabel) != mLabelValue) {
		sys_timer_usleep(10);
	}
	mLabelValue++;

	// XXX need to modify to use system memory after RSX is available
	memcpy(mPosition, pPositions, numVerts * sizeof(float)*3);
	memcpy(mTexCoord, pTexCoords, numVerts * sizeof(float)*2);
	memcpy(mColor, pColors, numVerts * sizeof(float)*4);

	// set vertex pointer and draw
	cellGcmSetVertexDataArray(mPosIndex, 0, sizeof(float)*3, 3,
							  CELL_GCM_VERTEX_F, CELL_GCM_LOCATION_LOCAL,
							  mPositionOffset);
	cellGcmSetVertexDataArray(mTexIndex, 0, sizeof(float)*2, 2,
							  CELL_GCM_VERTEX_F, CELL_GCM_LOCATION_LOCAL,
							  mTexCoordOffset);
	cellGcmSetVertexDataArray(mColIndex, 0, sizeof(float)*4, 4,
							  CELL_GCM_VERTEX_F, CELL_GCM_LOCATION_LOCAL,
							  mColorOffset);
	// draw vertex arrays
	cellGcmSetDrawArrays(FWDEBUGFONT_PRIMITIVE, 0, numVerts);
	cellGcmSetInvalidateVertexCache();
	cellGcmSetWriteBackEndLabel(sLabelId, mLabelValue);

	// flush semaphore command bacause semaphore value is not updated
	cellGcmFlush();
}

//-----------------------------------------------------------------------------
// Description: Stop text rendering
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWGCMDebugFontRenderer::printEnd()
{
	// reenable depth test
	cellGcmSetDepthTestEnable(CELL_GCM_TRUE);

	// disable alpha blend
	cellGcmSetBlendEnable(CELL_GCM_FALSE);
}
