#pragma once
class TuxDraw
{
public:
	TuxDraw();
	~TuxDraw();

	static void DrawSuite(const TuxPts *pTuxedo,
		ID2D1SolidColorBrush* pSuiteColor,
		ID2D1SolidColorBrush* pShirtColor,
		ID2D1HwndRenderTarget*  pRenderTarget);

	static void DrawJacket(const TuxPts *pTuxedo,
		ID2D1SolidColorBrush* pSuiteColor,
		ID2D1SolidColorBrush* pShirtColor,
		ID2D1HwndRenderTarget*  pRenderTarget);

	static void DrawPants(const TuxPts *pTuxedo,
		ID2D1SolidColorBrush* pSuiteColor,
		ID2D1HwndRenderTarget*  pRenderTarget);

	static void DrawArm(D2D1_POINT_2F pShoulder,
		D2D1_POINT_2F pElbow,
		D2D1_POINT_2F pWrist,
		ID2D1SolidColorBrush* pSuiteColor,
		ID2D1HwndRenderTarget*  pRenderTarget);

	static void DrawLeg(D2D1_POINT_2F pHip,
		D2D1_POINT_2F pKnee,
		D2D1_POINT_2F pAnkle,
		ID2D1SolidColorBrush* pSuiteColor,
		ID2D1HwndRenderTarget*  pRenderTarget);
};

