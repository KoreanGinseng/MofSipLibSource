/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include    "MofSip.h"

enum SipDebugFlags : MofU32
{
	SIP_DEBUG = 1 << 0,
};

Flags32 gFlags;

/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {

	CMyTime::InitTime();

	gFlags.Set(SipDebugFlags::SIP_DEBUG);

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
	g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);

	CGraphicsUtilities::RenderFillArc(100, 100, 50, MOF_ToRadian(90), MOF_ToRadian(90 + 360 * CPeriodic::Triangle0_1(10.0f)), MOF_COLOR_WHITE, MOF_COLOR_BLACK);

	// Render_DEBUG
	if (gFlags.Check(SipDebugFlags::SIP_DEBUG))
	{
		CGraphicsUtilities::RenderString(0, 0, "Time : %.3f(s)", CMyTime::Time());
	}
	
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