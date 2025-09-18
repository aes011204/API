#include "pch.h"
#include "CScene.h"
#include "CCamera.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::RenderBG(HDC hdc, HDC	hGroundDC,Vector2 startPos, Vector2 size)
{
	{
		// gpt의 도움...
		Vector2 RenderPos = CCamera::Get_Instance()->GetRenderPos(startPos);
		Vector2 brS = CCamera::Get_Instance()->GetRenderPos(size);

		float dstX = RenderPos.x;
		float dstY = RenderPos.y;
		float dstW = (brS.x - RenderPos.x);
		float dstH = (brS.y - RenderPos.y);

		// 필요하면 dstW/dstH가 음수면 tl/br 스왑
		if (dstW < 0) { dstX += dstW; dstW = -dstW; }
		if (dstH < 0) { dstY += dstH; dstH = -dstH; }

		StretchBlt(hdc, dstX, dstY, dstW, dstH, hGroundDC, 0, 0, 1920, 1280, SRCCOPY);
	}
}
