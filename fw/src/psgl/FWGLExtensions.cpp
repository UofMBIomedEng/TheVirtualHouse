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
// $File: //nextgendev/Framework_080/src/FWGLExtensions.cpp $
// $Author: asidwell $
// $Date: 2006/01/30 $
// $Revision: #3 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include "FWDebug.h"
#include "psgl/FWGLInclude.h"

#ifndef GL_VERSION_1_2

void APIENTRY FWGLExtension::initCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	spCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3D)FW_GETGLPROC("glCopyTexSubImage3D");
	if(!spCopyTexSubImage3D)
		reportError("glCopyTexSubImage3D");
	glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}

void APIENTRY FWGLExtension::initDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices)
{
	spDrawRangeElements = (PFNGLDRAWRANGEELEMENTS)FW_GETGLPROC("glDrawRangeElements");
	if(!spDrawRangeElements)
		reportError("glDrawRangeElements");
	glDrawRangeElements(mode, start, end, count, type, indices);
}

void APIENTRY FWGLExtension::initTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
	spTexImage3D = (PFNGLTEXIMAGE3D)FW_GETGLPROC("glTexImage3D");
	if(!spTexImage3D)
		reportError("glTexImage3D");
	glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
}

void APIENTRY FWGLExtension::initTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels)
{
	spTexSubImage3D = (PFNGLTEXSUBIMAGE3D)FW_GETGLPROC("glTexSubImage3D");
	if(!spTexSubImage3D)
		reportError("glTexSubImage3D");
	glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

FWGLExtension::PFNGLCOPYTEXSUBIMAGE3D			FWGLExtension::spCopyTexSubImage3D	= FWGLExtension::initCopyTexSubImage3D;
FWGLExtension::PFNGLDRAWRANGEELEMENTS			FWGLExtension::spDrawRangeElements	= FWGLExtension::initDrawRangeElements;
FWGLExtension::PFNGLTEXIMAGE3D					FWGLExtension::spTexImage3D			= FWGLExtension::initTexImage3D;
FWGLExtension::PFNGLTEXSUBIMAGE3D				FWGLExtension::spTexSubImage3D		= FWGLExtension::initTexSubImage3D;

#endif//GL_VERSION_1_2

#ifndef GL_VERSION_1_3

void APIENTRY FWGLExtension::initActiveTexture(GLenum texture)
{
	spActiveTexture = (PFNGLACTIVETEXTURE)FW_GETGLPROC("glActiveTexture");
	if(!spActiveTexture)
		reportError("glActiveTexture");
	glActiveTexture(texture);
}

void APIENTRY FWGLExtension::initClientActiveTexture(GLenum texture)
{
	spClientActiveTexture = (PFNGLCLIENTACTIVETEXTURE)FW_GETGLPROC("glClientActiveTexture");
	if(!spClientActiveTexture)
		reportError("glClientActiveTexture");
	glClientActiveTexture(texture);
}

void APIENTRY FWGLExtension::initCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data)
{
	spCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2D)FW_GETGLPROC("glCompressedTexImage2D");
	if(!spCompressedTexImage2D)
		reportError("glCompressedTexImage2D");
	glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
}

void APIENTRY FWGLExtension::initCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data)
{
	spCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3D)FW_GETGLPROC("glCompressedTexImage3D");
	if(!spCompressedTexImage3D)
		reportError("glCompressedTexImage3D");
	glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
}

void APIENTRY FWGLExtension::initCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data)
{
	spCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2D)FW_GETGLPROC("glCompressedTexSubImage2D");
	if(!spCompressedTexSubImage2D)
		reportError("glCompressedTexSubImage2D");
	glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

void APIENTRY FWGLExtension::initCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data)
{
	spCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3D)FW_GETGLPROC("glCompressedTexSubImage3D");
	if(!spCompressedTexSubImage3D)
		reportError("glCompressedTexSubImage3D");
	glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

void APIENTRY FWGLExtension::initMultiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
	spMultiTexCoord4f = (PFNGLMULTITEXCOORD4F)FW_GETGLPROC("glMultiTexCoord4f");
	if(!spMultiTexCoord4f)
		reportError("glMultiTexCoord4f");
	glMultiTexCoord4f(target, s, t, r, q);
}

void APIENTRY FWGLExtension::initSampleCoverage(GLclampf value, GLboolean invert)
{
	spSampleCoverage = (PFNGLSAMPLECOVERAGE)FW_GETGLPROC("glSampleCoverage");
	if(!spSampleCoverage)
		reportError("glSampleCoverage");
	glSampleCoverage(value, invert);
}

FWGLExtension::PFNGLACTIVETEXTURE			FWGLExtension::spActiveTexture				= FWGLExtension::initActiveTexture;
FWGLExtension::PFNGLCLIENTACTIVETEXTURE		FWGLExtension::spClientActiveTexture		= FWGLExtension::initClientActiveTexture;
FWGLExtension::PFNGLCOMPRESSEDTEXIMAGE2D	FWGLExtension::spCompressedTexImage2D		= FWGLExtension::initCompressedTexImage2D;
FWGLExtension::PFNGLCOMPRESSEDTEXIMAGE3D	FWGLExtension::spCompressedTexImage3D		= FWGLExtension::initCompressedTexImage3D;
FWGLExtension::PFNGLCOMPRESSEDTEXSUBIMAGE2D	FWGLExtension::spCompressedTexSubImage2D	= FWGLExtension::initCompressedTexSubImage2D;
FWGLExtension::PFNGLCOMPRESSEDTEXSUBIMAGE3D	FWGLExtension::spCompressedTexSubImage3D	= FWGLExtension::initCompressedTexSubImage3D;
FWGLExtension::PFNGLMULTITEXCOORD4F			FWGLExtension::spMultiTexCoord4f			= FWGLExtension::initMultiTexCoord4f;
FWGLExtension::PFNGLSAMPLECOVERAGE			FWGLExtension::spSampleCoverage				= FWGLExtension::initSampleCoverage;

#endif//GL_VERSION_1_3

#ifndef GL_VERSION_1_5

void APIENTRY FWGLExtension::initBindBuffer(GLenum target, GLuint buffer)
{
	spBindBuffer = (PFNGLBINDBUFFER)FW_GETGLPROC("glBindBuffer");
	if(!spBindBuffer)
		reportError("glBindBuffer");
	glBindBuffer(target, buffer);
}

void APIENTRY FWGLExtension::initBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)
{
	spBufferData = (PFNGLBUFFERDATA)FW_GETGLPROC("glBufferData");
	if(!spBufferData)
		reportError("glBufferData");
	glBufferData(target, size, data, usage);
}

void APIENTRY FWGLExtension::initBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data)
{
	spBufferSubData = (PFNGLBUFFERSUBDATA)FW_GETGLPROC("glBufferSubData");
	if(!spBufferSubData)
		reportError("glBufferSubData");
	glBufferSubData(target, offset, size, data);
}

void APIENTRY FWGLExtension::initDeleteBuffers(GLsizei n, const GLuint *buffers)
{
	spDeleteBuffers = (PFNGLDELETEBUFFERS)FW_GETGLPROC("glDeleteBuffers");
	if(!spDeleteBuffers)
		reportError("glDeleteBuffers");
	glDeleteBuffers(n, buffers);
}

void APIENTRY FWGLExtension::initGenBuffers(GLsizei n, GLuint *buffers)
{
	spGenBuffers = (PFNGLGENBUFFERS)FW_GETGLPROC("glGenBuffers");
	if(!spGenBuffers)
		reportError("glGenBuffers");
	glGenBuffers(n, buffers);
}

GLvoid* APIENTRY FWGLExtension::initMapBuffer(GLenum target, GLenum access)
{
	spMapBuffer = (PFNGLMAPBUFFER)FW_GETGLPROC("glMapBuffer");
	if(!spMapBuffer)
		reportError("glMapBuffer");
	return glMapBuffer(target, access);
}

GLboolean APIENTRY FWGLExtension::initUnmapBuffer(GLenum target)
{
	spUnmapBuffer = (PFNGLUNMAPBUFFER)FW_GETGLPROC("glUnmapBuffer");
	if(!spUnmapBuffer)
		reportError("glUnmapBuffer");
	return glUnmapBuffer(target);
}

FWGLExtension::PFNGLBINDBUFFER		FWGLExtension::spBindBuffer		= FWGLExtension::initBindBuffer;
FWGLExtension::PFNGLBUFFERDATA		FWGLExtension::spBufferData		= FWGLExtension::initBufferData;
FWGLExtension::PFNGLBUFFERSUBDATA	FWGLExtension::spBufferSubData	= FWGLExtension::initBufferSubData;
FWGLExtension::PFNGLDELETEBUFFERS	FWGLExtension::spDeleteBuffers	= FWGLExtension::initDeleteBuffers;
FWGLExtension::PFNGLGENBUFFERS		FWGLExtension::spGenBuffers		= FWGLExtension::initGenBuffers;
FWGLExtension::PFNGLMAPBUFFER		FWGLExtension::spMapBuffer		= FWGLExtension::initMapBuffer;
FWGLExtension::PFNGLUNMAPBUFFER		FWGLExtension::spUnmapBuffer	= FWGLExtension::initUnmapBuffer;

#endif//GL_VERSION_1_5

#ifndef GL_NV_primitive_restart

void APIENTRY FWGLExtension::initPrimitiveRestartIndexNV(GLuint index)
{
	spPrimitiveRestartIndexNV = (PFNGLPRIMITIVERESTARTINDEXNV)FW_GETGLPROC("glPrimitiveRestartIndexNV");
	if(!spPrimitiveRestartIndexNV)
		reportError("glPrimitiveRestartIndexNV");
	glPrimitiveRestartIndexNV(index);
}

FWGLExtension::PFNGLPRIMITIVERESTARTINDEXNV	FWGLExtension::spPrimitiveRestartIndexNV = FWGLExtension::initPrimitiveRestartIndexNV;

#endif//GL_NV_primitive_restart

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
