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

		explicit CParticle(const CreateInfo& info);

		virtual ~CParticle(void);

		void Initialize(const CreateInfo& info);

		virtual void Update(void);

		virtual void Render(void);

		virtual void Release(void);

		void UpdateViewPosition(void);

		MofBool IsEnd(void) const;

		static bool ViewComp(ParticlePtr& v1, ParticlePtr& v2);
	};
}