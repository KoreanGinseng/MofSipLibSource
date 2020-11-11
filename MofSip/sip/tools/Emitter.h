#pragma once

#include "Particle.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// �ŏ��ő�l��ێ������N���X
	/// </summary>
	// ********************************************************************************
	template < typename T >
	class CMinMaxParameter
	{
	public:
		T                  Min;  //! �ŏ��l
		T                  Max;  //! �ő�l

		// ********************************************************************************
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		CMinMaxParameter(void) :
			Min(),
			Max()
		{
		}

		// ********************************************************************************
		/// <summary>
		/// �p�����[�^�̐ݒ�
		/// </summary>
		/// <param name="min">�ŏ��l</param>
		/// <param name="max">�ő�l</param>
		/// <returns>this</returns>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		CMinMaxParameter& SetParameter(const T& min, const T& max)
		{
			Min = min;
			Max = max;

			return *this;
		}

		// ********************************************************************************
		/// <summary>
		/// �f�t�H���g�l�̐ݒ�
		/// </summary>
		/// <param name="v">�f�t�H���g�l</param>
		/// <returns>this</returns>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		CMinMaxParameter& SetDefaultParameter(const T& v)
		{
			Min = Max = v;
			return *this;
		}

		// ********************************************************************************
		/// <summary>
		/// �����_���p�����[�^�̎擾
		/// </summary>
		/// <param name="out">�o��</param>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		template< typename PT = T >
		void GetParameterImpl(PT& out)
		{
			out = Min + (Max - Min) * CUtilities::Random(1001) * 0.001f;
		}

		// ********************************************************************************
		/// <summary>
		/// �����_���p�����[�^�̎擾
		/// </summary>
		/// <param name="out">�o��</param>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		template<>
		void GetParameterImpl(CVector3& out)
		{
			out.x = Min.x + (Max.x - Min.x) * CUtilities::Random(1001) * 0.001f;
			out.y = Min.y + (Max.y - Min.y) * CUtilities::Random(1001) * 0.001f;
			out.z = Min.z + (Max.z - Min.z) * CUtilities::Random(1001) * 0.001f;
		}

		// ********************************************************************************
		/// <summary>
		/// �����_���p�����[�^�̎擾
		/// </summary>
		/// <param name="out">�o��</param>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		template<>
		void GetParameterImpl(CVector4& out)
		{
			out.x = Min.x + (Max.x - Min.x) * CUtilities::Random(1001) * 0.001f;
			out.y = Min.y + (Max.y - Min.y) * CUtilities::Random(1001) * 0.001f;
			out.z = Min.z + (Max.z - Min.z) * CUtilities::Random(1001) * 0.001f;
			out.z = Min.w + (Max.w - Min.w) * CUtilities::Random(1001) * 0.001f;
		}

		// ********************************************************************************
		/// <summary>
		/// �����_���p�����[�^�̎擾
		/// </summary>
		/// <param name="out">�o��</param>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		void GetParameter(T& out)
		{
			GetParameterImpl(out);
		}

		// ********************************************************************************
		/// <summary>
		/// �����_���p�����[�^�̎擾
		/// </summary>
		/// <returns>�p�����[�^</returns>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		T GetParameter(void) const
		{
			T value;
			GetParameterImpl(value);
			return T;
		}
	};

	template< template < typename > class PT >
	class CEmitter
	{
	public:

		using ParticleList = std::list<CParticle::ParticlePtr>;

		// ********************************************************************************
		/// <summary>
		/// �X�V�p�\����
		/// </summary>
		// ********************************************************************************
		struct UpdateBehavior
		{
			PT< CVector3 >   Move;
			PT< CVector3 >   Scale;
			PT< CVector3 >   Rotation;
			PT< CVector4 >   Color;
		};

		// ********************************************************************************
		/// <summary>
		/// �ݒ�\����
		/// </summary>
		// ********************************************************************************
		struct ParameterBehavior
		{
			PT< MofFloat >        Existance;
			Blending              Blending;
			CParticle::Flag       Flag;
			CParticle::TexturePtr pTexture;
			CParticle::MeshPtr    pMesh;
		};

		// ********************************************************************************
		/// <summary>
		/// �����p�\����
		/// </summary>
		// ********************************************************************************
		struct CreateBehavior
		{
			MofFloat         Time;
			MofU32           Count;
			PT< CVector3 >   Position;
			PT< CVector3 >   Scale;
			PT< CVector3 >   Rotation;
			PT< CVector4 >   Color;
		};

		// ********************************************************************************
		/// <summary>
		/// �����p���
		/// </summary>
		// ********************************************************************************
		struct CreateInfo
		{
			UpdateBehavior                 UpdateBehavior;
			ParameterBehavior              ParameterBehavior;
			CParticle::EnvironmentBehavior EnvironmentBehavior;
			CreateBehavior                 CreateBehavior;
		};

	protected:
		
		MofFloat                           m_Time;
		CParticle::State                   m_State;
		UpdateBehavior                     m_UpdateBehavior;
		ParameterBehavior                  m_ParameterBehavior;
		CParticle::EnvironmentBehavior     m_EnvironmentBehavior;
		CreateBehavior                     m_CreateBehavior;

	public:
		
		// ********************************************************************************
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="info">�������</param>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		CEmitter(void) :
			m_Time(0.0f),
			m_State(),
			m_UpdateBehavior(),
			m_ParameterBehavior(),
			m_EnvironmentBehavior(),
			m_CreateBehavior()
		{
		}

		// ********************************************************************************
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="info">�������</param>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		CEmitter(const CreateInfo& info) :
			m_Time(0.0f),
			m_State(),
			m_UpdateBehavior(),
			m_ParameterBehavior(),
			m_EnvironmentBehavior(),
			m_CreateBehavior()
		{
			Initialize(info);
		}

		// ********************************************************************************
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		~CEmitter(void)
		{
		}

		// ********************************************************************************
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="info">�������</param>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		void Initialize(const CreateInfo& info)
		{
			m_Time = 0.0f;
			m_UpdateBehavior      = info.UpdateBehavior;
			m_ParameterBehavior   = info.ParameterBehavior;
			m_EnvironmentBehavior = info.EnvironmentBehavior;
			m_CreateBehavior      = info.CreateBehavior;
		}

		// ********************************************************************************
		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="pList">�p�[�e�B�N�����X�g</param>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		void Update(ParticleList* pList)
		{
			// ���ݎ��Ԃ̍X�V
			m_Time++;

			// �s��̍X�V
			m_State.World.RotationZXY(m_State.Rotation);
			m_State.World.Scaling(m_State.Scale, m_State.World);
			m_State.World.SetTranslation(m_State.Position);

			// �������Ԍo��
			if (m_Time < m_CreateBehavior.Time)
			{
				return;
			}

			// �p�[�e�B�N���̐������
			CParticle::CreateInfo cinfo;
			for (MofU32 i = 0; i < m_CreateBehavior.Count; i++)
			{
				// ������Ԃ̐ݒ�
				m_CreateBehavior.Position.GetParameter(cinfo.State.Position);
				m_CreateBehavior.Scale.GetParameter(cinfo.State.Scale);
				m_CreateBehavior.Rotation.GetParameter(cinfo.State.Rotation);
				m_CreateBehavior.Color.GetParameter(cinfo.State.Color);

				cinfo.State.Position *= m_State.World;
				cinfo.State.Scale    *= m_State.Scale;
				cinfo.State.Rotation += m_State.Rotation;
				cinfo.State.Color    *= m_State.Color;

				cinfo.State.World.RotationZXY(cinfo.State.Rotation);
				cinfo.State.World.Scaling(cinfo.State.Scale, cinfo.State.World);
				cinfo.State.World.SetTranslation(cinfo.State.Position);

				// �X�V���̐���
				m_UpdateBehavior.Move.GetParameter(cinfo.UpdateBehavior.Move);
				m_UpdateBehavior.Scale.GetParameter(cinfo.UpdateBehavior.Scale);
				m_UpdateBehavior.Rotation.GetParameter(cinfo.UpdateBehavior.Rotation);
				m_UpdateBehavior.Color.GetParameter(cinfo.UpdateBehavior.Color);

				// �����̐���
				cinfo.EnvironmentBehavior.Gravity = m_EnvironmentBehavior.Gravity;

				// �p�����[�^�[���̐���
				m_ParameterBehavior.Existance.GetParameter(cinfo.ParameterBehavior.Existance);
				cinfo.ParameterBehavior.Blending = m_ParameterBehavior.Blending;
				cinfo.ParameterBehavior.Flag     = m_ParameterBehavior.Flag;

				// �e�N�X�`���̐ݒ�
				cinfo.pTexture = m_ParameterBehavior.pTexture;

				// ���b�V���̐ݒ�
				cinfo.pMesh = m_ParameterBehavior.pMesh;

				// �p�[�e�B�N���𐶐����ď�����
				CParticle::ParticlePtr pParticle = std::make_shared<CParticle>(cinfo);

				// ���X�g�ɒǉ�
				pList->push_back(pParticle);
			}
			// ������̎��Ԍ���
			m_Time -= m_CreateBehavior.Time;
		}

		// ********************************************************************************
		/// <summary>
		/// ���W�ݒ�
		/// </summary>
		/// <param name="v">���W</param>
		/// <returns>this</returns>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		virtual CEmitter& SetPosition(const CVector3& v)
		{
			m_State.Position = v;
			return *this;
		}

		// ********************************************************************************
		/// <summary>
		/// �X�P�[���ݒ�
		/// </summary>
		/// <param name="v">�X�P�[��</param>
		/// <returns>this</returns>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		virtual CEmitter& SetScale(const CVector3& v)
		{
			m_State.Scale = v;
			return *this;
		}

		// ********************************************************************************
		/// <summary>
		/// ��]�ݒ�
		/// </summary>
		/// <param name="v">��]</param>
		/// <returns>this</returns>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		virtual CEmitter& SetRotation(const CVector3& v)
		{
			m_State.Rotation = v;
			return *this;
		}

		// ********************************************************************************
		/// <summary>
		/// �F�ݒ�
		/// </summary>
		/// <param name="v">�F</param>
		/// <returns>this</returns>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		virtual CEmitter& SetColor(const CVector4& v)
		{
			m_State.Color = v;
			return *this;
		}

		// ********************************************************************************
		/// <summary>
		/// ���[���h�}�g���N�X�ݒ�
		/// </summary>
		/// <param name="v">���[���h�}�g���N�X</param>
		/// <returns>this</returns>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		virtual CEmitter& SetWorldMatrix(const CMatrix44& v)
		{
			m_State.World = v;
			return *this;
		}

		// ********************************************************************************
		/// <summary>
		/// ���Ԑݒ�
		/// </summary>
		/// <param name="t">����</param>
		/// <returns>this</returns>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		virtual CEmitter& SetTime(const MofFloat& t)
		{
			m_Time = t;
			return *this;
		}

		// ********************************************************************************
		/// <summary>
		/// ���W�擾
		/// </summary>
		/// <returns>���W</returns>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		virtual CVector3& GetPosition(void)
		{
			return m_State.Position;
		}

		// ********************************************************************************
		/// <summary>
		/// �X�P�[���擾
		/// </summary>
		/// <returns>�X�P�[��</returns>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		virtual CVector3& GetScale(void)
		{
			return m_State.Scale;
		}

		// ********************************************************************************
		/// <summary>
		/// ��]�擾
		/// </summary>
		/// <returns>��]</returns>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		virtual CVector3& GetRotation(void)
		{
			return m_State.Rotation;
		}

		// ********************************************************************************
		/// <summary>
		/// �F�擾
		/// </summary>
		/// <returns>�F</returns>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		virtual CVector4& GetColor(void)
		{
			return m_State.Color;
		}

		// ********************************************************************************
		/// <summary>
		/// ���[���h�}�g���N�X�擾
		/// </summary>
		/// <returns>���[���h�}�g���N�X</returns>
		/// <created>���̂���,2020/08/04</created>
		/// <changed>���̂���,2020/08/04</changed>
		// ********************************************************************************
		virtual CMatrix44& GetWorldMatrix(void)
		{
			return m_State.World;
		}
	};
}
