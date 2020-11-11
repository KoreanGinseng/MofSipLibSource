#include "EffectBase.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <created>���̂���,2020/08/31</created>
	/// <changed>���̂���,2020/08/31</changed>
	// ********************************************************************************
	CEffectBase::CEffectBase(void) :
		m_Emitter(),
		m_CreateInfo(),
		m_ParticleList()
	{
		//�G�~�b�^�[�̓���p�����[�^�[�ݒ�
		m_CreateInfo.UpdateBehavior.Color.SetDefaultParameter(Vector4(0, 0, 0, -1 / 60.0f));

		m_CreateInfo.ParameterBehavior.Existance.SetDefaultParameter(60);
		m_CreateInfo.ParameterBehavior.Blending = BLEND_ADD;
		m_CreateInfo.ParameterBehavior.Flag     = sip::CParticle::BillBoard;
		m_CreateInfo.ParameterBehavior.pTexture = nullptr;
		m_CreateInfo.ParameterBehavior.pMesh    = nullptr;

		m_CreateInfo.CreateBehavior.Position.Min.SetValue(-5, -5, -5);
		m_CreateInfo.CreateBehavior.Position.Max.SetValue(5, 5, 5);
		m_CreateInfo.CreateBehavior.Color.SetDefaultParameter(Vector4(1, 1, 1, 1));
		m_CreateInfo.CreateBehavior.Scale.SetDefaultParameter(Vector3(1, 1, 1));
		m_CreateInfo.CreateBehavior.Time  = 30;
		m_CreateInfo.CreateBehavior.Count = 10;
		m_Emitter.Initialize(m_CreateInfo);
	}

	// ********************************************************************************
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	/// <created>���̂���,2020/08/31</created>
	/// <changed>���̂���,2020/08/31</changed>
	// ********************************************************************************
	CEffectBase::~CEffectBase(void)
	{
	}

	// ********************************************************************************
	/// <summary>
	/// �ǂݍ���
	/// </summary>
	/// <param name="pFileName">�t�@�C����</param>
	/// <returns>�����������ǂ���</returns>
	/// <created>���̂���,2020/08/31</created>
	/// <changed>���̂���,2020/08/31</changed>
	// ********************************************************************************
	bool CEffectBase::Load(LPCMofChar pFileName)
	{
		FILE* fp = fopen(pFileName, "rb");
		if (fp == NULL)
		{
			return false;
		}

		//�������
		MOF_SAFE_RELEASE(m_CreateInfo.ParameterBehavior.pTexture);
		MOF_SAFE_RELEASE(m_CreateInfo.ParameterBehavior.pMesh);

		//�\���̓ǂݍ���
		fread(&m_CreateInfo, sizeof(m_CreateInfo), 1, fp);

		char pattern = 0;

		fread(&pattern, sizeof(char), 1, fp);

		char* str  = nullptr;
		int length = 0;
		switch (pattern)
		{
		case 0:
			break;
		case 1:
			//�e�N�X�`���ǂݍ���
			fread(&length, sizeof(int), 1, fp);
			str = new char[length + 1];
			fread(str, sizeof(char), length, fp);
			str[length] = '\0';
			m_CreateInfo.ParameterBehavior.pTexture = std::make_shared<CTexture>();
			if (!m_CreateInfo.ParameterBehavior.pTexture->Load(str))
			{
				MOF_SAFE_RELEASE(m_CreateInfo.ParameterBehavior.pTexture);
			}
			MOF_SAFE_DELETE_ARRAY(str);
			break;
		case 2:
			//���b�V���ǂݍ���
			fread(&length, sizeof(int), 1, fp);
			str = new char[length + 1];
			fread(str, sizeof(char), length, fp);
			str[length] = '\0';
			m_CreateInfo.ParameterBehavior.pMesh = std::make_shared<CMeshContainer>();
			if (!m_CreateInfo.ParameterBehavior.pMesh->Load(str))
			{
				MOF_SAFE_RELEASE(m_CreateInfo.ParameterBehavior.pMesh);
			}
			MOF_SAFE_DELETE_ARRAY(str);
			break;
		}

		//�t�@�C�������
		fclose(fp);

		RestartEmitter();
		return true;
	}

	// ********************************************************************************
	/// <summary>
	/// �G�~�b�^�[�̍ăX�^�[�g
	/// </summary>
	/// <param name="pos">�������W</param>
	/// <param name="t">����(�P�ʂ͕b)</param>
	/// <returns>this</returns>
	/// <created>���̂���,2020/08/07</created>
	/// <changed>���̂���,2020/08/31</changed>
	// ********************************************************************************
	CEffectBase& CEffectBase::RestartEmitter(const Vector3 & pos, const float & t)
	{
		m_Emitter.Initialize(m_CreateInfo);
		SetPos(pos);
		SetLifeTime(t);
		m_ParticleList.clear();
		return *this;
	}

	// ********************************************************************************
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pos">�������W</param>
	/// <param name="t">����(�P�ʂ͕b)</param>
	/// <returns>this</returns>
	/// <created>���̂���,2020/08/31</created>
	/// <changed>���̂���,2020/08/31</changed>
	// ********************************************************************************
	CEffectBase & CEffectBase::Initialize(const Vector3 & pos, const float & t)
	{
		RestartEmitter(pos, t);
		return *this;
	}

	// ********************************************************************************
	/// <summary>
	/// �X�V
	/// </summary>
	/// <created>���̂���,2020/08/31</created>
	/// <changed>���̂���,2020/08/31</changed>
	// ********************************************************************************
	void CEffectBase::Update(void)
	{
		// �����̌��� �������}�C�i�X�w�肵�Ă���ꍇ�͒ʂ�Ȃ��B
		if (0 < m_LifeTime)
		{
			m_LifeTime -= CUtilities::GetFrameSecond();
			
			if (m_LifeTime < 0)
			{
				m_LifeTime = 0;
			}
		}

		m_Emitter.Update(&m_ParticleList);

		// �C�e���[�g���ɗv�f�폜������悤�ȏꍇ�ɂ́A
		// �͈�for���͎g�p�ł��Ȃ�
		for (auto it = m_ParticleList.begin(); it != m_ParticleList.end();)
		{
			(*it)->Update();
			// ������v�����v�f���폜����
			if ((*it)->IsEnd())
			{
				// �폜���ꂽ�v�f�̎����w���C�e���[�^���Ԃ����B
				*it = nullptr;
				it  = m_ParticleList.erase(it);
			}
			// �v�f�폜�����Ȃ��ꍇ�ɁA�C�e���[�^��i�߂�
			else 
			{
				++it;
			}
		}

		// �\�[�g�̎��s
		for (const auto& it : m_ParticleList)
		{
			it->UpdateViewPosition();
		}
		m_ParticleList.sort(CParticle::ViewComp);
	}

	// ********************************************************************************
	/// <summary>
	/// �`��
	/// </summary>
	/// <created>���̂���,2020/08/31</created>
	/// <changed>���̂���,2020/08/31</changed>
	// ********************************************************************************
	void CEffectBase::Render(void) const
	{
		// �����I�����Ă���Ȃ�`�悵�Ȃ�
		if (m_LifeTime == 0)
		{
			return;
		}

		// �p�[�e�B�N���̕`��
		for (const auto& it : m_ParticleList)
		{
			it->Render();
		}
		g_pGraphics->SetBlending(BLEND_NORMAL);
	}

	// ********************************************************************************
	/// <summary>
	/// ���
	/// </summary>
	/// <created>���̂���,2020/08/31</created>
	/// <changed>���̂���,2020/08/31</changed>
	// ********************************************************************************
	void CEffectBase::Release(void)
	{
		MOF_SAFE_RELEASE(m_CreateInfo.ParameterBehavior.pMesh);
		MOF_SAFE_RELEASE(m_CreateInfo.ParameterBehavior.pTexture);
	}

	// ********************************************************************************
	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="pos">�������W</param>
	/// <returns>this</returns>
	/// <created>���̂���,2020/08/31</created>
	/// <changed>���̂���,2020/08/31</changed>
	// ********************************************************************************
	CEffectBase & CEffectBase::SetPos(const Vector3 & pos)
	{
		m_Emitter.SetPosition(pos);
		return *this;
	}

	// ********************************************************************************
	/// <summary>
	/// �����̐ݒ�
	/// </summary>
	/// <param name="t">����(�P�ʂ͕b)</param>
	/// <returns>this</returns>
	/// <created>���̂���,2020/08/31</created>
	/// <changed>���̂���,2020/08/31</changed>
	// ********************************************************************************
	CEffectBase & CEffectBase::SetLifeTime(const float & t)
	{
		m_LifeTime = t;
		return *this;
	}

	// ********************************************************************************
	/// <summary>
	/// �����̎擾
	/// </summary>
	/// <returns>����(�P�ʂ͕b)</returns>
	/// <created>���̂���,2020/08/31</created>
	/// <changed>���̂���,2020/08/31</changed>
	// ********************************************************************************
	float CEffectBase::GetLifeTime(void) const
	{
		return m_LifeTime;
	}

	// ********************************************************************************
	/// <summary>
	/// �e�N�X�`���̎擾
	/// </summary>
	/// <returns>�e�N�X�`���̃|�C���^</returns>
	/// <created>���̂���,2020/08/31</created>
	/// <changed>���̂���,2020/08/31</changed>
	// ********************************************************************************
	std::shared_ptr<CTexture> CEffectBase::GetTexture(void)
	{
		return m_CreateInfo.ParameterBehavior.pTexture;
	}

	// ********************************************************************************
	/// <summary>
	/// ���b�V���̎擾
	/// </summary>
	/// <returns>���b�V���̃|�C���^</returns>
	/// <created>���̂���,2020/08/31</created>
	/// <changed>���̂���,2020/08/31</changed>
	// ********************************************************************************
	std::shared_ptr<CMeshContainer> CEffectBase::GetMesh(void)
	{
		return m_CreateInfo.ParameterBehavior.pMesh;
	}
}