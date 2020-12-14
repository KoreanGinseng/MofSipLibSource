/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
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

CFreeCamera gFreeCamera;

void RenderDebug(void)
{
	CGraphicsUtilities::RenderString(0, 0, "Time : %.3f(s)", CMyTime::Time());
}

/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {

	CMyTime::InitTime();

	gFlags.Set(SipDebugFlags::SIP_DEBUG);

	gFreeCamera.Initialize();

	CGraphicsUtilities::SetCamera(gFreeCamera.GetCamera());

	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̍X�V
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void) {
	//�L�[�̍X�V
	g_pInput->RefreshKey();

	gFreeCamera.Update();
	float v = (CPeriodic::Sine0_1(0.15f) * 2.0f - 1.0f) * 0.05f;
	gFreeCamera.SetPosition(gFreeCamera.GetPosition() + Vector3(v, 0, 0));

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
		@brief			�A�v���P�[�V�����̕`��
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void) {
	//�`��J�n
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0);

	g_pGraphics->SetDepthEnable(TRUE);

	float nowTime = CMyTime::Time();

	CBoxOBB box(Vector3(0, 0, 0), Vector3(2, 0, 1), Vector3(0, MOF_ToRadian(45), 0));
	for (int i = 0; i < 10; i++)
	{
		//box.Position.y = (CPeriodic::Sawtooth0_1(1.0f, nowTime) + i) * 0.05f;
		CGraphicsUtilities::RenderLineBox(box);
	}

	g_pGraphics->SetDepthEnable(FALSE);

	// Render_DEBUG
	if (gFlags.Check(SipDebugFlags::SIP_DEBUG))
	{
		RenderDebug();
	}

	CGraphicsUtilities::RenderFillRect(CRectangle(100, 100, 200, 200), CHSVUtilities::ToRGB(HSV(CMyTime::Time() * 60, 255, 255)));
	
	//�`��̏I��
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̉��
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Release(void) {
	return TRUE;
}