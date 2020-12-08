#pragma once

#include "Mof.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// �p�[�e�B�N���N���X
	/// </summary>
	// ********************************************************************************
	class CParticle
	{
	public:

		using TexturePtr  = std::shared_ptr<CTexture>;
		using ParticlePtr = std::shared_ptr<CParticle>;
		using MeshPtr     = std::shared_ptr<CMeshContainer>;

		/// <summary>�t���O��</summary>
		enum Flag : MofU32
		{
			BillBoard = 0x00000001,
		};

		// ********************************************************************************
		/// <summary>
		/// ��ԕۑ��p�\����
		/// </summary>
		// ********************************************************************************
		struct State
		{
			CVector3  Position;
			CVector3  Scale;
			CVector3  Rotation;
			CVector4  Color;
			CMatrix44 World;

			// ********************************************************************************
			/// <summary>
			/// �R���X�g���N�^
			/// </summary>
			/// <created>���̂���,2020/07/28</created>
			/// <changed>���̂���,2020/07/28</changed>
			// ********************************************************************************
			State(void) :
				Position(),
				Scale(1, 1, 1),
				Rotation(),
				Color(1, 1, 1, 1),
				World()
			{
			}
		};

		// ********************************************************************************
		/// <summary>
		/// �X�V�p�\����
		/// </summary>
		// ********************************************************************************
		struct UpdateBehavior
		{
			CVector3 Move;
			CVector3 Scale;
			CVector3 Rotation;
			CVector4 Color;
		};

		// ********************************************************************************
		/// <summary>
		/// �ݒ�Ɋւ���\����
		/// </summary>
		// ********************************************************************************
		struct ParameterBehavior
		{
			MofFloat Existance;
			Blending Blending;
			Flag     Flag;
		};

		// ********************************************************************************
		/// <summary>
		/// �������ɂ��\����
		/// </summary>
		// ********************************************************************************
		struct EnvironmentBehavior
		{
			CVector3 Gravity;
		};

		// ********************************************************************************
		/// <summary>
		/// �����p���\����
		/// </summary>
		// ********************************************************************************
		struct CreateInfo
		{
			State               State;
			UpdateBehavior      UpdateBehavior;
			ParameterBehavior   ParameterBehavior;
			EnvironmentBehavior EnvironmentBehavior;
			TexturePtr          pTexture;
			MeshPtr             pMesh;
		};

	protected:

		MofFloat            m_Time;                     //! Frame�P�ʂ̎���
				            
		State               m_State;
		State               m_InitState;

		UpdateBehavior      m_UpdateBehavior;
		ParameterBehavior   m_ParameterBehavior;
		EnvironmentBehavior m_EnvironmentBehavior;

		TexturePtr          m_pTexture;

	private:

		MeshPtr            m_pMesh;

		CVector3           m_ViewPosition;

	public:

		// ********************************************************************************
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="info">�������</param>
		/// <created>���̂���,2020/11/11</created>
		/// <changed>���̂���,2020/11/11</changed>
		// ********************************************************************************
		explicit CParticle(const CreateInfo& info);

		// ********************************************************************************
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		/// <created>���̂���,2020/11/11</created>
		/// <changed>���̂���,2020/11/11</changed>
		// ********************************************************************************
		virtual ~CParticle(void);

		// ********************************************************************************
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="info">�������</param>
		/// <created>���̂���,2020/11/11</created>
		/// <changed>���̂���,2020/11/11</changed>
		// ********************************************************************************
		void Initialize(const CreateInfo& info);

		// ********************************************************************************
		/// <summary>
		/// �X�V
		/// </summary>
		/// <created>���̂���,2020/11/11</created>
		/// <changed>���̂���,2020/11/11</changed>
		// ********************************************************************************
		virtual void Update(void);

		// ********************************************************************************
		/// <summary>
		/// �`��
		/// </summary>
		/// <created>���̂���,2020/11/11</created>
		/// <changed>���̂���,2020/11/11</changed>
		// ********************************************************************************
		virtual void Render(void);

		// ********************************************************************************
		/// <summary>
		/// ���
		/// </summary>
		/// <created>���̂���,2020/11/11</created>
		/// <changed>���̂���,2020/11/11</changed>
		// ********************************************************************************
		virtual void Release(void);

		// ********************************************************************************
		/// <summary>
		/// �r���[�|�W�V�����̍X�V
		/// </summary>
		/// <created>���̂���,2020/11/11</created>
		/// <changed>���̂���,2020/11/11</changed>
		// ********************************************************************************
		void UpdateViewPosition(void);

		// ********************************************************************************
		/// <summary>
		/// �I���t���O�̎擾
		/// </summary>
		/// <returns>�I���t���O</returns>
		/// <created>���̂���,2020/11/11</created>
		/// <changed>���̂���,2020/11/11</changed>
		// ********************************************************************************
		MofBool IsEnd(void) const;

		// ********************************************************************************
		/// <summary>
		/// ��r�֐�
		/// </summary>
		/// <param name="v1">�l�P</param>
		/// <param name="v2">�l�Q</param>
		/// <returns>�l�P���l�Q</returns>
		/// <created>���̂���,2020/11/11</created>
		/// <changed>���̂���,2020/11/11</changed>
		// ********************************************************************************
		static bool ViewComp(ParticlePtr& v1, ParticlePtr& v2);
	};
}