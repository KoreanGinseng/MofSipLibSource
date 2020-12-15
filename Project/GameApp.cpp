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

Flags32 gFlags;

CFreeCamera gFreeCamera;

CTexture gUVScroll;
LPGeometry gpBox;

void RenderDebug(void)
{
	CGraphicsUtilities::RenderString(0, 0, "Time : %.3f(s)", CMyTime::Time());
}

CToonShader* gToon;

CSprite3D gSprite3d;

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


	gSprite3d.CreateSprite("shima.png");
	float h = gSprite3d.m_pTexture->GetHeight();
	float w = gSprite3d.m_pTexture->GetWidth();
	gSprite3d.SetImageRect(CRectangle(0, 0, w, h * 10));
	gSprite3d.Update();

	gToon = new CToonShader();
	gToon->Create();
	gToon->LoadToonMap("shima.png");

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

	if (g_pInput->IsKeyPush(MOFKEY_SPACE))
	{
		gToon->Release();
		delete gToon;
		gToon = new CToonShader();

		gToon->Create();
		gToon->LoadToonMap("shima.png");
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

	gToon->Begin();

	CBoxOBB box(Vector3(0, 0, 0), Vector3(2, 0, 1), Vector3(0, MOF_ToRadian(45), 0));
	for (int i = 0; i < 10; i++)
	{
		//box.Position.y = (CPeriodic::Sawtooth0_1(1.0f, nowTime) + i) * 0.05f;
		//CGraphicsUtilities::RenderLineBox(box);
	}
	CMatrix44 matWorld;
	static float t = 0;
	t += 0.01f;
	gSprite3d.m_Position.y = CPeriodic::Sawtooth0_1(1.0f / 3.f) * 0.1f;
	gSprite3d.m_Scale;
	gSprite3d.m_Angle;
	gSprite3d.Update();
	//gpBox->Render(matWorld,Vector4(1,1,1,1),Vector2(0,t));
	gSprite3d.Render();

	gToon->End();

	g_pGraphics->SetDepthEnable(FALSE);

	// Render_DEBUG
	if (gFlags.Check(SipDebugFlags::SIP_DEBUG))
	{
		RenderDebug();
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
	
	gSprite3d.Release();

	return TRUE;
}