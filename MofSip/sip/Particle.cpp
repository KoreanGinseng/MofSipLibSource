#include "Particle.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="info">�������</param>
	/// <created>���̂���,2020/07/28</created>
	/// <changed>���̂���,2020/07/28</changed>
	// ********************************************************************************
	CParticle::CParticle(const CreateInfo& info) :
		m_Time(0.0f),
		m_State(),
		m_InitState(),
		m_UpdateBehavior(),
		m_ParameterBehavior(),
		m_EnvironmentBehavior(),
		m_pTexture(nullptr),
		m_pMesh(nullptr)
	{
		Initialize(info);
	}

	// ********************************************************************************
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	/// <created>���̂���,2020/07/28</created>
	/// <changed>���̂���,2020/07/28</changed>
	// ********************************************************************************
	CParticle::~CParticle(void)
	{
		Release();
	}
	
	// ********************************************************************************
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="info">�������</param>
	/// <created>���̂���,2020/07/28</created>
	/// <changed>���̂���,2020/07/28</changed>
	// ********************************************************************************
	void CParticle::Initialize(const CreateInfo & info)
	{
		m_Time                = 0.0f;
		m_InitState           = m_State = info.State;
		m_UpdateBehavior      = info.UpdateBehavior;
		m_ParameterBehavior   = info.ParameterBehavior;
		m_EnvironmentBehavior = info.EnvironmentBehavior;
		m_pTexture            = info.pTexture;
		m_pMesh               = info.pMesh;
	}
	
	// ********************************************************************************
	/// <summary>
	/// �X�V
	/// </summary>
	/// <created>���̂���,2020/07/28</created>
	/// <changed>���̂���,2020/07/28</changed>
	// ********************************************************************************
	void CParticle::Update(void)
	{
		// ���ݎ��Ԃ̍X�V
		m_Time++;

		// �I������
		if (IsEnd())
		{
			return;
		}

		// �����ɍ��킹�čX�V
		m_State.Position += m_UpdateBehavior.Move + m_EnvironmentBehavior.Gravity * m_Time;
		m_State.Scale    += m_UpdateBehavior.Scale;
		m_State.Rotation += m_UpdateBehavior.Rotation;
		m_State.Color    += m_UpdateBehavior.Color;

		// �s��̍X�V
		m_State.World.RotationZXY(m_State.Rotation);
		m_State.World.Scaling(m_State.Scale, m_State.World);
		m_State.World.SetTranslation(m_State.Position);
	}
	
	// ********************************************************************************
	/// <summary>
	/// �`��
	/// </summary>
	/// <created>���̂���,2020/07/28</created>
	/// <changed>���̂���,2020/07/28</changed>
	// ********************************************************************************
	void CParticle::Render(void)
	{
		if (IsEnd())
		{
			return;
		}
		if (m_State.Color.a <= 0.0f)
		{
			return;
		}
		g_pGraphics->SetBlending(m_ParameterBehavior.Blending);
		// �`��p�}�g���N�X�錾
		CMatrix44 rMat = m_State.World;
		// �r���{�[�h�}�g���N�X�����[���h�}�g���N�X�ɓK�p����
		if (m_ParameterBehavior.Flag & Flag::BillBoard)
		{
			// �J�������擾����
			LPCamera pCam = CGraphicsUtilities::GetCamera();
			rMat.Multiply3x3(pCam->GetBillBoardMatrix());
		}
		if (m_pMesh)
		{
			m_pMesh->Render(rMat, m_State.Color);
		}
		if (m_pTexture)
		{
			m_pTexture->Render(rMat, m_State.Color.ToU32Color());
		}
	}
	
	// ********************************************************************************
	/// <summary>
	/// ���
	/// </summary>
	/// <created>���̂���,2020/07/28</created>
	/// <changed>���̂���,2020/07/28</changed>
	// ********************************************************************************
	void CParticle::Release(void)
	{
	}

	// ********************************************************************************
	/// <summary>
	/// �r���[�|�W�V�����̍X�V
	/// </summary>
	/// <created>���̂���,2020/08/04</created>
	/// <changed>���̂���,2020/08/04</changed>
	// ********************************************************************************
	void CParticle::UpdateViewPosition(void)
	{
		LPCamera pCam = CGraphicsUtilities::GetCamera();
		m_State.World.GetTranslation(m_ViewPosition);
		m_ViewPosition *= pCam->GetViewMatrix();
	}
	
	// ********************************************************************************
	/// <summary>
	/// �I���t���O�̎擾
	/// </summary>
	/// <returns>�I���t���O</returns>
	/// <created>���̂���,2020/07/28</created>
	/// <changed>���̂���,2020/07/28</changed>
	// ********************************************************************************
	MofBool CParticle::IsEnd(void) const
	{
		return m_Time >= m_ParameterBehavior.Existance ? TRUE : FALSE;
	}

	// ********************************************************************************
	/// <summary>
	/// Z�\�[�g�p��r�֐�
	/// </summary>
	/// <param name="v1">�l�P</param>
	/// <param name="v2">�l�Q</param>
	/// <returns>�召�̔�r����</returns>
	/// <created>���̂���,2020/08/04</created>
	/// <changed>���̂���,2020/08/04</changed>
	// ********************************************************************************
	bool CParticle::ViewComp(ParticlePtr & v1, ParticlePtr & v2)
	{
		if (v1->m_ViewPosition.z > v2->m_ViewPosition.z)
		{
			return true;
		}
		return false;
	}
}