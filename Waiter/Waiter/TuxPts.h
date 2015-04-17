#pragma once
class TuxPts
{
public:
	TuxPts();
	~TuxPts();

	const int TUXPTS();
	D2D1_POINT_2F* pts;
	bool LoadPoints(const D2D1_POINT_2F* pJointPoints);
protected:
	void ClearPoints();
	void InitPointArray();

};

