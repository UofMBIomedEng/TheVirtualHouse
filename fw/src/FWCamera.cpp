/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// camera class
//
// $File: //nextgendev/Framework_080/src/FWCamera.cpp $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#include "FWCamera.h"

//-----------------------------------------------------------------------------
// Description: Updates the camera matrix
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWCamera::update()
{
	switch(mMode)
	{
	case Mode_FlyThru:
		updateFlyThru();
		break;
	case Mode_LookAt:
		updateLookAt();
		break;
	}
}

//-----------------------------------------------------------------------------
// Description: Updates the camera matrix in fly thru mode
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWCamera::updateFlyThru()
{
	Matrix4	xRot;
	Matrix4	yRot;
	Matrix4	pos;
	
	xRot = Matrix4::rotationX(mTilt);
	yRot = Matrix4::rotationY(mPan);
	pos = Matrix4::translation(-Vector3(mPosition));

	mMatrix = xRot * yRot * pos; 

	// inv(AB) = inv(B) * inv(A)
	mInvMatrix = -pos * transpose(xRot) * transpose(yRot);
}

//-----------------------------------------------------------------------------
// Description: Updates the camera matrix in look at mode
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWCamera::updateLookAt()
{
	// update the camera position based on angles and distance
	Vector3	zVec3;
	Matrix3	xRot3;
	Matrix3 yRot3;

	xRot3 = Matrix3::rotationX(-mTilt);
	yRot3 = Matrix3::rotationY(-mPan);

	zVec3 = (yRot3 * xRot3) * Vector3::zAxis();

	mPosition = mTarget + zVec3 * mDist;

	// calculate rotation axes
	Vector3	zAxis = normalize(mTarget - mPosition);
	Vector3 xAxis = normalize(cross(zAxis, Vector3(0.f, 1.f, 0.f)));
	Vector3 yAxis = normalize(cross(xAxis, zAxis));

	// rotation matrix
	Matrix4	rotate;
	rotate.setCol0(Vector4(xAxis, 0.f));
	rotate.setCol1(Vector4(yAxis, 0.f));
	rotate.setCol2(-Vector4(zAxis, 0.f));
	rotate.setCol3(Vector4(0.f, 0.f, 0.f, 1.f));

	// translaiton matrix
	Matrix4	translate = Matrix4::translation(-Vector3(mPosition));

	// final matrix is transpose of rotation * translation
	mMatrix = transpose(rotate) * translate;

	// inverse of view matrix
	//   inv(AB) = inv(B) * inv(A)
	//   inv(rot(A)) = transpose(A)
	//   inv(trans(A)) = negate(A)
	mInvMatrix = (-translate) * rotate;
}

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
