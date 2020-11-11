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

		// ********************************************************************************
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="info">生成情報</param>
		/// <created>いのうえ,2020/11/11</created>
		/// <changed>いのうえ,2020/11/11</changed>
		// ********************************************************************************
		explicit CParticle(const CreateInfo& info);

		// ********************************************************************************
		/// <summary>
		/// デストラクタ
		/// </summary>
		/// <created>いのうえ,2020/11/11</created>
		/// <changed>いのうえ,2020/11/11</changed>
		// ********************************************************************************
		virtual ~CParticle(void);

		// ********************************************************************************
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="info">生成情報</param>
		/// <created>いのうえ,2020/11/11</created>
		/// <changed>いのうえ,2020/11/11</changed>
		// ********************************************************************************
		void Initialize(const CreateInfo& info);

		// ********************************************************************************
		/// <summary>
		/// 更新
		/// </summary>
		/// <created>いのうえ,2020/11/11</created>
		/// <changed>いのうえ,2020/11/11</changed>
		// ********************************************************************************
		virtual void Update(void);

		// ********************************************************************************
		/// <summary>
		/// 描画
		/// </summary>
		/// <created>いのうえ,2020/11/11</created>
		/// <changed>いのうえ,2020/11/11</changed>
		// ********************************************************************************
		virtual void Render(void);

		// ********************************************************************************
		/// <summary>
		/// 解放
		/// </summary>
		/// <created>いのうえ,2020/11/11</created>
		/// <changed>いのうえ,2020/11/11</changed>
		// ********************************************************************************
		virtual void Release(void);

		// ********************************************************************************
		/// <summary>
		/// ビューポジションの更新
		/// </summary>
		/// <created>いのうえ,2020/11/11</created>
		/// <changed>いのうえ,2020/11/11</changed>
		// ********************************************************************************
		void UpdateViewPosition(void);

		// ********************************************************************************
		/// <summary>
		/// 終了フラグの取得
		/// </summary>
		/// <returns>終了フラグ</returns>
		/// <created>いのうえ,2020/11/11</created>
		/// <changed>いのうえ,2020/11/11</changed>
		// ********************************************************************************
		MofBool IsEnd(void) const;

		// ********************************************************************************
		/// <summary>
		/// 比較関数
		/// </summary>
		/// <param name="v1">値１</param>
		/// <param name="v2">値２</param>
		/// <returns>値１＞値２</returns>
		/// <created>いのうえ,2020/11/11</created>
		/// <changed>いのうえ,2020/11/11</changed>
		// ********************************************************************************
		static bool ViewComp(ParticlePtr& v1, ParticlePtr& v2);
	};
}