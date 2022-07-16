////////////////////////////////////////////////////////////////////////////////
// Filename: frustumclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FRUSTUMCLASS_H_
#define _FRUSTUMCLASS_H_
//https://stackoverflow.com/questions/17475929/access-floats-of-xmmatrix-operator-not-working
//#define _XM_NO_INTRINSICS_
// Refer to GraphicsClass.h on why you shouldn't use this or at least how you should use it


//////////////
// INCLUDES //
//////////////
#include <DirectXMath.h>
using namespace DirectX;

//////////////
// TYPEDEFS //
//////////////

typedef XMMATRIX DXMATRIX;
typedef XMVECTOR DXVECTOR;
typedef XMVECTORF32 DXVECTORF32;

////////////////////////////////////////////////////////////////////////////////
// Class name: FrustumClass
////////////////////////////////////////////////////////////////////////////////
class FrustumClass
{
public:
	FrustumClass();
	FrustumClass(const FrustumClass&);
	~FrustumClass();

	void ConstructFrustum(float, DXMATRIX, DXMATRIX);

	bool CheckPoint(float, float, float);
	bool CheckCube(float, float, float, float);
	bool CheckSphere(float, float, float, float);
	bool CheckRectangle(float, float, float, float, float, float);

private:
	DXVECTOR m_planes[6];
};

#endif