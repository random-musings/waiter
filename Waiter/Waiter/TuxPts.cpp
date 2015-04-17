#include "stdafx.h"
#include "TuxPts.h"



TuxPts::TuxPts()
{
	InitPointArray();
}


TuxPts::~TuxPts()
{
	ClearPoints();
}


void TuxPts::ClearPoints()
{
	if (pts != NULL)
		delete[] pts;
}


void TuxPts::InitPointArray()
{
	if  (pts == NULL)
	{
		ClearPoints();
		pts = new D2D1_POINT_2F[TUXPTS()];
	}
}


bool TuxPts::LoadPoints(const D2D1_POINT_2F* pJointPoints)
{
	InitPointArray();
	size_t memBlock = sizeof(D2D1_POINT_2F)* TUXPTS();
	errno_t err = memcpy_s(pts, memBlock, pJointPoints, memBlock);
	return err;
}

const int TuxPts::TUXPTS()
{
	return 25;
}