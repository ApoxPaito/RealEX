////////////////////////////////////////////////////////////////////////////////
// Filename: frustumclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "frustumclass.h"


FrustumClass::FrustumClass()
{
}


FrustumClass::FrustumClass(const FrustumClass& other)
{
}


FrustumClass::~FrustumClass()
{
}

void FrustumClass::ConstructFrustum(float screenDepth, DXMATRIX projectionMatrix, DXMATRIX viewMatrix)
{
	float zMinimum, r;
	DXMATRIX matrix;


	// Calculate the minimum Z distance in the frustum.
	zMinimum = -projectionMatrix.r[3].m128_f32[2] / projectionMatrix.r[2].m128_f32[2];
	r = screenDepth / (screenDepth - zMinimum);
	projectionMatrix.r[2].m128_f32[2] = r;
	projectionMatrix.r[3].m128_f32[2] = -r * zMinimum;

	// Create the frustum matrix from the view matrix and updated projection matrix.
	matrix = viewMatrix * projectionMatrix;

	// Calculate near plane of frustum.
	m_planes[0].m128_f32[0] = matrix.r[0].m128_f32[3] + matrix.r[0].m128_f32[2];
	m_planes[0].m128_f32[1] = matrix.r[1].m128_f32[3] + matrix.r[1].m128_f32[2];
	m_planes[0].m128_f32[2] = matrix.r[2].m128_f32[3] + matrix.r[2].m128_f32[2];
	m_planes[0].m128_f32[3] = matrix.r[3].m128_f32[3] + matrix.r[3].m128_f32[2];
	m_planes[0] = XMPlaneNormalize(m_planes[0]);

	// Calculate far plane of frustum.
	m_planes[1].m128_f32[0] = matrix.r[0].m128_f32[3] - matrix.r[0].m128_f32[2];
	m_planes[1].m128_f32[1] = matrix.r[1].m128_f32[3] - matrix.r[1].m128_f32[2];
	m_planes[1].m128_f32[2] = matrix.r[2].m128_f32[3] - matrix.r[2].m128_f32[2];
	m_planes[1].m128_f32[3] = matrix.r[3].m128_f32[3] - matrix.r[3].m128_f32[2];
	m_planes[1] = XMPlaneNormalize(m_planes[1]);

	// Calculate left plane of frustum.
	m_planes[2].m128_f32[0] = matrix.r[0].m128_f32[3] + matrix.r[0].m128_f32[0];
	m_planes[2].m128_f32[1] = matrix.r[1].m128_f32[3] + matrix.r[1].m128_f32[0];
	m_planes[2].m128_f32[2] = matrix.r[2].m128_f32[3] + matrix.r[2].m128_f32[0];
	m_planes[2].m128_f32[3] = matrix.r[3].m128_f32[3] + matrix.r[3].m128_f32[0];
	m_planes[2] = XMPlaneNormalize(m_planes[2]);

	// Calculate right plane of frustum.
	m_planes[3].m128_f32[0] = matrix.r[0].m128_f32[3] - matrix.r[0].m128_f32[0];
	m_planes[3].m128_f32[1] = matrix.r[1].m128_f32[3] - matrix.r[1].m128_f32[0];
	m_planes[3].m128_f32[2] = matrix.r[2].m128_f32[3] - matrix.r[2].m128_f32[0];
	m_planes[3].m128_f32[3] = matrix.r[3].m128_f32[3] - matrix.r[3].m128_f32[0];
	m_planes[3] = XMPlaneNormalize(m_planes[3]);

	// Calculate top plane of frustum.
	m_planes[4].m128_f32[0] = matrix.r[0].m128_f32[3] - matrix.r[0].m128_f32[1];
	m_planes[4].m128_f32[1] = matrix.r[1].m128_f32[3] - matrix.r[1].m128_f32[1];
	m_planes[4].m128_f32[2] = matrix.r[2].m128_f32[3] - matrix.r[2].m128_f32[1];
	m_planes[4].m128_f32[3] = matrix.r[3].m128_f32[3] - matrix.r[3].m128_f32[1];
	m_planes[4] = XMPlaneNormalize(m_planes[4]);

	// Calculate bottom plane of frustum.
	m_planes[5].m128_f32[0] = matrix.r[0].m128_f32[3] + matrix.r[0].m128_f32[1];
	m_planes[5].m128_f32[1] = matrix.r[1].m128_f32[3] + matrix.r[1].m128_f32[1];
	m_planes[5].m128_f32[2] = matrix.r[2].m128_f32[3] + matrix.r[2].m128_f32[1];
	m_planes[5].m128_f32[3] = matrix.r[3].m128_f32[3] + matrix.r[3].m128_f32[1];
	m_planes[5] = XMPlaneNormalize(m_planes[5]);

	return;
}

bool FrustumClass::CheckPoint(float x, float y, float z)
{
	int i;
	DXVECTOR vector;

	// Check if the point is inside all six planes of the view frustum.
	for (i = 0; i < 6; i++)
	{
		if (XMPlaneDotCoord(m_planes[i], DXVECTORF32{ x, y, z }).m128_f32[0] < 0.0f)
		{
			return false;
		}
	}

	return true;
}

bool FrustumClass::CheckCube(float xCenter, float yCenter, float zCenter, float radius)
{
	int i;
	DXVECTOR vector;

	// Check if any one point of the cube is in the view frustum.
	for (i = 0; i < 6; i++)
	{
		if (XMPlaneDotCoord(m_planes[i], DXVECTOR{ (xCenter - radius), (yCenter - radius), (zCenter - radius) }).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(m_planes[i], DXVECTOR{ (xCenter + radius), (yCenter - radius), (zCenter - radius) }).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(m_planes[i], DXVECTOR{ (xCenter - radius), (yCenter + radius), (zCenter - radius) }).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(m_planes[i], DXVECTOR{ (xCenter + radius), (yCenter + radius), (zCenter - radius) }).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(m_planes[i], DXVECTOR{ (xCenter - radius), (yCenter - radius), (zCenter + radius) }).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(m_planes[i], DXVECTOR{ (xCenter + radius), (yCenter - radius), (zCenter + radius) }).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(m_planes[i], DXVECTOR{ (xCenter - radius), (yCenter + radius), (zCenter + radius) }).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(m_planes[i], DXVECTOR{ (xCenter + radius), (yCenter + radius), (zCenter + radius) }).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
}

bool FrustumClass::CheckSphere(float xCenter, float yCenter, float zCenter, float radius)
{
	int i;


	// Check if the radius of the sphere is inside the view frustum.
	for (i = 0; i < 6; i++)
	{
		if (XMPlaneDotCoord(m_planes[i], DXVECTORF32{ xCenter, yCenter, zCenter }).m128_f32[0] < -radius)
		{
			return false;
		}
	}

	return true;
}

bool FrustumClass::CheckRectangle(float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize)
{
	int i;


	// Check if any of the 6 planes of the rectangle are inside the view frustum.
	for (i = 0; i < 6; i++)
	{
		if (XMPlaneDotCoord(m_planes[i], DXVECTORF32{ (xCenter - xSize), (yCenter - ySize), (zCenter - zSize) }).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(m_planes[i], DXVECTORF32{ (xCenter + xSize), (yCenter - ySize), (zCenter - zSize) }).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(m_planes[i], DXVECTORF32{ (xCenter - xSize), (yCenter + ySize), (zCenter - zSize) }).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(m_planes[i], DXVECTORF32{ (xCenter - xSize), (yCenter - ySize), (zCenter + zSize) }).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(m_planes[i], DXVECTORF32{ (xCenter + xSize), (yCenter + ySize), (zCenter - zSize) }).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(m_planes[i], DXVECTORF32{ (xCenter + xSize), (yCenter - ySize), (zCenter + zSize) }).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(m_planes[i], DXVECTORF32{ (xCenter - xSize), (yCenter + ySize), (zCenter + zSize) }).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(m_planes[i], DXVECTORF32{ (xCenter + xSize), (yCenter + ySize), (zCenter + zSize) }).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
}