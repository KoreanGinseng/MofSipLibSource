/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"

enum SipDebugFlags : MofU32
{
	SIP_DEBUG = 1 << 0,
};

Flags32     gFlags;

CFreeCamera gFreeCamera;

/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {

	CUtilities::SetCurrentDirectory("Resource");

	gFlags.Set(SipDebugFlags::SIP_DEBUG);

	gFreeCamera.Initialize();

	CGraphicsUtilities::SetCamera(gFreeCamera.GetCamera());

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void) {
	//キーの更新
	g_pInput->RefreshKey();

	gFreeCamera.Update();
	float v = (CPeriodic::Sine0_1(0.15f) * 2.0f - 1.0f) * 0.05f;
	//gFreeCamera.SetPosition(gFreeCamera.GetPosition() + Vector3(v, 0, 0));

	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		if (gFlags.Check(SipDebugFlags::SIP_DEBUG))
		{
			gFlags.Reset(SipDebugFlags::SIP_DEBUG);
		}
		else
		{
			gFlags.Set(SipDebugFlags::SIP_DEBUG);
		}
	}

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void) {
	//描画開始
	g_pGraphics->RenderStart();
	//画面のクリア
	g_pGraphics->ClearTarget(0.2f, 0.2f, 0.8f, 0.0f, 1.0f, 0);

	g_pGraphics->SetDepthEnable(TRUE);

	float nowTime = CMyTime::Time();

	g_pGraphics->SetDepthEnable(FALSE);

	// Render_DEBUG
	if (gFlags.Check(SipDebugFlags::SIP_DEBUG))
	{
	}

	CGraphicsUtilities::RenderFillRect(CRectangle(100, 100, 200, 200), CHSVUtilities::ToRGB(HSV(CMyTime::Time() * 60, 255, 255)));
	
	//描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void) {
	

	return TRUE;
}