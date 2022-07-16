///////////////////////////////////////////////////////////////////////////////
// Filename: modellistclass.h
///////////////////////////////////////////////////////////////////////////////
#ifndef _MODELLISTCLASS_H_
#define _MODELLISTCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <DirectXMath.h>
#include <stdlib.h>
#include <time.h>
using namespace DirectX;

//////////////
// TYPEDEFS //
//////////////

typedef XMFLOAT4 DXFLOAT4;


///////////////////////////////////////////////////////////////////////////////
// Class name: ModelListClass
///////////////////////////////////////////////////////////////////////////////
class ModelListClass
{
private:
	struct ModelInfoType
	{
		DXFLOAT4 color;
		float positionX, positionY, positionZ;
	};

public:
	ModelListClass();
	ModelListClass(const ModelListClass&);
	~ModelListClass();

	bool Initialize(int);
	void Shutdown();

	int GetModelCount();
	void GetData(int, float&, float&, float&, DXFLOAT4&);

private:
	int m_modelCount;
	ModelInfoType* m_ModelInfoList;
};

#endif