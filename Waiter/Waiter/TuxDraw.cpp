#include "stdafx.h"
#include "TuxPts.h"
#include "TuxDraw.h"



TuxDraw::TuxDraw()
{
}


TuxDraw::~TuxDraw()
{
}


void TuxDraw::DrawSuite(const TuxPts *pTuxedo,
	ID2D1SolidColorBrush* pSuiteColor,
	ID2D1SolidColorBrush* pShirtColor,
	ID2D1HwndRenderTarget*  pRenderTarget)
{
	DrawJacket(pTuxedo, pSuiteColor, pShirtColor, pRenderTarget);
	DrawPants(pTuxedo, pSuiteColor, pRenderTarget);
}


void TuxDraw::DrawJacket(const TuxPts *pTuxedo,
	ID2D1SolidColorBrush* pSuiteColor,
	ID2D1SolidColorBrush* pShirtColor,
	ID2D1HwndRenderTarget*  pRenderTarget)
{

	//ID2D1Mesh* pMesh;
	//ID2D1TessellationSink *pSink;
	//pMesh->Open(&pSink);
	//pSink->AddTriangles();
	//pRenderTarget->CreateMesh(&pMesh);
	//pRenderTarget->Cre

	//pRenderTarget->FillGeometry(, pSuiteColor);
	int strokeWidth = 3;
	FLOAT hipSpan = (pTuxedo->pts[JointType_HipRight].x - pTuxedo->pts[JointType_HipLeft].x) / 2.0f;
	FLOAT shoulderSpan = pTuxedo->pts[JointType_ShoulderRight].x - pTuxedo->pts[JointType_ShoulderLeft].x;
	shoulderSpan = shoulderSpan < 0.1 ? 1 : shoulderSpan;

	int shirtWidth = (int)hipSpan;
	int deltaShirtX = 0;
	D2D1_POINT_2F suitPtTop = pTuxedo->pts[JointType_SpineShoulder];
	D2D1_POINT_2F suitPtBottom = pTuxedo->pts[JointType_SpineBase];

	int deltaSuitX = shirtWidth;
	int suitWidth = (int)(shoulderSpan / 2);
	D2D1_POINT_2F suiteTop = pTuxedo->pts[JointType_SpineShoulder];
	D2D1_POINT_2F suiteBottom = pTuxedo->pts[JointType_SpineBase];

	bool drawSuit = true;
	bool drawShirt = true;

	while (drawShirt || drawSuit)
	{
		//draw the shirt
		drawShirt = deltaShirtX < shirtWidth;
		drawSuit = deltaSuitX < suitWidth;
		if (drawShirt)
		{
			suitPtTop.x += deltaShirtX;
			pRenderTarget->DrawLine(suitPtTop, suitPtBottom, pShirtColor,  strokeWidth);

			suitPtTop.x += -2 * deltaShirtX;
			pRenderTarget->DrawLine(suitPtTop, suitPtBottom, pShirtColor, strokeWidth);
			suitPtTop.x = suitPtTop.x +deltaShirtX;
		}

		if (drawSuit)
		{
			suitPtTop.x += deltaSuitX;
			suitPtBottom.x += deltaShirtX;
			pRenderTarget->DrawLine(suitPtTop, suitPtBottom, pSuiteColor, strokeWidth);

			suitPtTop.x -= 2 * deltaSuitX;
			suitPtBottom.x -= 2 * deltaShirtX;
			pRenderTarget->DrawLine(suitPtTop, suitPtBottom, pSuiteColor, strokeWidth);

			suitPtTop.x += deltaSuitX;
			suitPtBottom.x += deltaShirtX;
		}

		deltaSuitX++;
		deltaShirtX++;
	}
	
	DrawArm(pTuxedo->pts[JointType_ShoulderLeft], pTuxedo->pts[JointType_ElbowLeft], pTuxedo->pts[JointType_WristLeft],
		pSuiteColor, pRenderTarget);
	DrawArm(pTuxedo->pts[JointType_ShoulderRight], pTuxedo->pts[JointType_ElbowRight], pTuxedo->pts[JointType_WristRight],
		pSuiteColor, pRenderTarget);
		
	
}

void TuxDraw::DrawPants(const TuxPts *pTuxedo, 
	ID2D1SolidColorBrush* pSuiteColor,
	ID2D1HwndRenderTarget*  pRenderTarget)
{
	FLOAT hipSpan = (pTuxedo->pts[JointType_HipRight].x - pTuxedo->pts[JointType_HipLeft].x) / 2.0f;
	DrawLeg(pTuxedo->pts[JointType_HipRight], pTuxedo->pts[JointType_KneeRight], pTuxedo->pts[JointType_AnkleRight],
		pSuiteColor,pRenderTarget);

	DrawLeg(pTuxedo->pts[JointType_HipLeft], pTuxedo->pts[JointType_KneeLeft], pTuxedo->pts[JointType_AnkleLeft],
		pSuiteColor, pRenderTarget);
}

void TuxDraw::DrawLeg(D2D1_POINT_2F pHip,
	D2D1_POINT_2F pKnee,
	D2D1_POINT_2F pAnkle,
	ID2D1SolidColorBrush* pSuiteColor,
	ID2D1HwndRenderTarget*  pRenderTarget)
{
	FLOAT hipW = (pHip.y - pKnee.y)* 0.2f;
	D2D1_ELLIPSE jointHip = D2D1::Ellipse(pHip, hipW, hipW);
	pRenderTarget->FillEllipse(jointHip, pSuiteColor);

	FLOAT kneeW = hipW* 0.2f;
	D2D1_ELLIPSE jointKnee = D2D1::Ellipse(pKnee, kneeW, kneeW);
	pRenderTarget->FillEllipse(jointKnee, pSuiteColor);

	FLOAT ankleW = kneeW* 0.5f;
	D2D1_ELLIPSE jointAnkle = D2D1::Ellipse(pAnkle, ankleW, ankleW);
	pRenderTarget->FillEllipse(jointAnkle, pSuiteColor);
}


void TuxDraw::DrawArm(D2D1_POINT_2F pShoulder,
	D2D1_POINT_2F pElbow,
	D2D1_POINT_2F pWrist,
	ID2D1SolidColorBrush* pSuiteColor,
	ID2D1HwndRenderTarget*  pRenderTarget)
{
	int strokeWidth = 3;

	FLOAT shoulderW = (pShoulder.x - pElbow.x )* 0.2f;
	FLOAT shoulderH = (pShoulder.y - pElbow.y)* 0.2f;
	FLOAT shldrMax = max(abs(shoulderW), abs(shoulderH));
	D2D1_ELLIPSE jointShldr = D2D1::Ellipse(pShoulder, shldrMax, shldrMax);
	pRenderTarget->FillEllipse(jointShldr, pSuiteColor);

	FLOAT elbowW = shldrMax* 0.8f;
	D2D1_ELLIPSE jointElbow = D2D1::Ellipse(pElbow, elbowW, elbowW);
	pRenderTarget->FillEllipse(jointElbow, pSuiteColor);

	FLOAT wristW = elbowW* 0.5f;
	D2D1_ELLIPSE wristJoint = D2D1::Ellipse(pWrist, wristW, wristW);
	pRenderTarget->FillEllipse(wristJoint, pSuiteColor);

	FLOAT elbowD = pElbow.x<pWrist.x ? 1 : (pElbow.x - pWrist.x);
	FLOAT elbowZ = (pElbow.y - pWrist.y);
	FLOAT elbowMax = max(abs(elbowD), abs(elbowZ));

	FLOAT deltaShoulderX = shoulderH / shldrMax;
	FLOAT deltaShoulderY = -shoulderW / shldrMax;
	FLOAT deltaWristX = deltaShoulderX;
	FLOAT deltaWristY = abs(deltaShoulderY);

	D2D1_POINT_2F suitPtLeftTop = pShoulder;
	D2D1_POINT_2F suitPtLeftBottom = pElbow;
	D2D1_POINT_2F suitPtRightTop = pShoulder;
	D2D1_POINT_2F suitPtRightBottom = pElbow;

	D2D1_POINT_2F suitPtWristRightBottom = pWrist;
	D2D1_POINT_2F suitPtWristLeftBottom = pWrist;
	int step = 1;
	
	while (step < shldrMax)
	{
		//shoulder to elbow
		pRenderTarget->DrawLine(suitPtLeftBottom, suitPtLeftTop, pSuiteColor, strokeWidth);

		//elbow to wrist
		pRenderTarget->DrawLine(suitPtWristLeftBottom, suitPtLeftBottom, pSuiteColor, strokeWidth);

		suitPtLeftTop.x += deltaShoulderX;
		suitPtLeftTop.y += deltaShoulderY;
		suitPtLeftBottom.x += deltaShoulderX;
		suitPtLeftBottom.y += deltaShoulderY;
		suitPtWristLeftBottom.x += deltaWristX;
		suitPtWristLeftBottom.y += deltaWristY;

		suitPtRightTop.x -= deltaShoulderX;
		suitPtRightTop.y -= deltaShoulderY;
		suitPtRightBottom.x -= deltaShoulderX;
		suitPtRightBottom.y -= deltaShoulderY;
		suitPtWristRightBottom.x -= deltaWristX;
		suitPtWristRightBottom.y -= deltaWristY;

		//shoulder to elbow
		pRenderTarget->DrawLine(suitPtRightTop, suitPtRightBottom, pSuiteColor, strokeWidth);
		//elbow to wrist
		pRenderTarget->DrawLine(suitPtWristRightBottom, suitPtRightBottom, pSuiteColor, strokeWidth);

		step++;
	}

}