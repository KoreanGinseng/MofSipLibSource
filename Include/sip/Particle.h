#pragma once

#include "Mof.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// パーティクルクラス
	/// </summary>
	// ********************************************************************************
	class CParticle
	{
	public:

		using TexturePtr  = std::shared_ptr<CTexture>;
		using ParticlePtr = std::shared_ptr<CParticle>;
		using MeshPtr     = std::shared_ptr<CMeshContainer>;

		/// <summary>フラグ列挙</summary>
		enum Flag : MofU32
		{
			BillBoard = 0x00000001,
		};

		// ********************************************************************************
		/// <summary>
		/// 状態保存用構造体
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
			/// コンストラクタ
			/// </summary>
			/// <created>いのうえ,2020/07/28</created>
			/// <changed>いのうえ,2020/07/28</changed>
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
		/// 更新用構造体
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
		/// 設定に関する構造体
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
		/// 発生環境による構造体
		/// </summary>
		// ********************************************************************************
		struct EnvironmentBehavior
		{
			CVector3 Gravity;
		};

		// ********************************************************************************
		/// <summary>
		/// 生成用情報構造体
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

		MofFloat            m_Time;                     //! Frame単位の時間
				            
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