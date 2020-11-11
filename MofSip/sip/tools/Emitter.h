#pragma once

#include "Particle.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// 最小最大値を保持したクラス
	/// </summary>
	// ********************************************************************************
	template < typename T >
	class CMinMaxParameter
	{
	public:
		T                  Min;  //! 最小値
		T                  Max;  //! 最大値

		// ********************************************************************************
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
		// ********************************************************************************
		CMinMaxParameter(void) :
			Min(),
			Max()
		{
		}

		// ********************************************************************************
		/// <summary>
		/// パラメータの設定
		/// </summary>
		/// <param name="min">最小値</param>
		/// <param name="max">最大値</param>
		/// <returns>this</returns>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
		// ********************************************************************************
		CMinMaxParameter& SetParameter(const T& min, const T& max)
		{
			Min = min;
			Max = max;

			return *this;
		}

		// ********************************************************************************
		/// <summary>
		/// デフォルト値の設定
		/// </summary>
		/// <param name="v">デフォルト値</param>
		/// <returns>this</returns>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
		// ********************************************************************************
		CMinMaxParameter& SetDefaultParameter(const T& v)
		{
			Min = Max = v;
			return *this;
		}

		// ********************************************************************************
		/// <summary>
		/// ランダムパラメータの取得
		/// </summary>
		/// <param name="out">出力</param>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
		// ********************************************************************************
		template< typename PT = T >
		void GetParameterImpl(PT& out)
		{
			out = Min + (Max - Min) * CUtilities::Random(1001) * 0.001f;
		}

		// ********************************************************************************
		/// <summary>
		/// ランダムパラメータの取得
		/// </summary>
		/// <param name="out">出力</param>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
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
		/// ランダムパラメータの取得
		/// </summary>
		/// <param name="out">出力</param>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
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
		/// ランダムパラメータの取得
		/// </summary>
		/// <param name="out">出力</param>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
		// ********************************************************************************
		void GetParameter(T& out)
		{
			GetParameterImpl(out);
		}

		// ********************************************************************************
		/// <summary>
		/// ランダムパラメータの取得
		/// </summary>
		/// <returns>パラメータ</returns>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
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
		/// 更新用構造体
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
		/// 設定構造体
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
		/// 生成用構造体
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
		/// 生成用情報
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
		/// コンストラクタ
		/// </summary>
		/// <param name="info">生成情報</param>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
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
		/// コンストラクタ
		/// </summary>
		/// <param name="info">生成情報</param>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
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
		/// デストラクタ
		/// </summary>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
		// ********************************************************************************
		~CEmitter(void)
		{
		}

		// ********************************************************************************
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="info">生成情報</param>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
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
		/// 更新
		/// </summary>
		/// <param name="pList">パーティクルリスト</param>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
		// ********************************************************************************
		void Update(ParticleList* pList)
		{
			// 存在時間の更新
			m_Time++;

			// 行列の更新
			m_State.World.RotationZXY(m_State.Rotation);
			m_State.World.Scaling(m_State.Scale, m_State.World);
			m_State.World.SetTranslation(m_State.Position);

			// 発生時間経過
			if (m_Time < m_CreateBehavior.Time)
			{
				return;
			}

			// パーティクルの生成情報
			CParticle::CreateInfo cinfo;
			for (MofU32 i = 0; i < m_CreateBehavior.Count; i++)
			{
				// 初期状態の設定
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

				// 更新情報の生成
				m_UpdateBehavior.Move.GetParameter(cinfo.UpdateBehavior.Move);
				m_UpdateBehavior.Scale.GetParameter(cinfo.UpdateBehavior.Scale);
				m_UpdateBehavior.Rotation.GetParameter(cinfo.UpdateBehavior.Rotation);
				m_UpdateBehavior.Color.GetParameter(cinfo.UpdateBehavior.Color);

				// 環境情報の生成
				cinfo.EnvironmentBehavior.Gravity = m_EnvironmentBehavior.Gravity;

				// パラメーター情報の生成
				m_ParameterBehavior.Existance.GetParameter(cinfo.ParameterBehavior.Existance);
				cinfo.ParameterBehavior.Blending = m_ParameterBehavior.Blending;
				cinfo.ParameterBehavior.Flag     = m_ParameterBehavior.Flag;

				// テクスチャの設定
				cinfo.pTexture = m_ParameterBehavior.pTexture;

				// メッシュの設定
				cinfo.pMesh = m_ParameterBehavior.pMesh;

				// パーティクルを生成して初期化
				CParticle::ParticlePtr pParticle = std::make_shared<CParticle>(cinfo);

				// リストに追加
				pList->push_back(pParticle);
			}
			// 生成後の時間減少
			m_Time -= m_CreateBehavior.Time;
		}

		// ********************************************************************************
		/// <summary>
		/// 座標設定
		/// </summary>
		/// <param name="v">座標</param>
		/// <returns>this</returns>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
		// ********************************************************************************
		virtual CEmitter& SetPosition(const CVector3& v)
		{
			m_State.Position = v;
			return *this;
		}

		// ********************************************************************************
		/// <summary>
		/// スケール設定
		/// </summary>
		/// <param name="v">スケール</param>
		/// <returns>this</returns>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
		// ********************************************************************************
		virtual CEmitter& SetScale(const CVector3& v)
		{
			m_State.Scale = v;
			return *this;
		}

		// ********************************************************************************
		/// <summary>
		/// 回転設定
		/// </summary>
		/// <param name="v">回転</param>
		/// <returns>this</returns>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
		// ********************************************************************************
		virtual CEmitter& SetRotation(const CVector3& v)
		{
			m_State.Rotation = v;
			return *this;
		}

		// ********************************************************************************
		/// <summary>
		/// 色設定
		/// </summary>
		/// <param name="v">色</param>
		/// <returns>this</returns>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
		// ********************************************************************************
		virtual CEmitter& SetColor(const CVector4& v)
		{
			m_State.Color = v;
			return *this;
		}

		// ********************************************************************************
		/// <summary>
		/// ワールドマトリクス設定
		/// </summary>
		/// <param name="v">ワールドマトリクス</param>
		/// <returns>this</returns>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
		// ********************************************************************************
		virtual CEmitter& SetWorldMatrix(const CMatrix44& v)
		{
			m_State.World = v;
			return *this;
		}

		// ********************************************************************************
		/// <summary>
		/// 時間設定
		/// </summary>
		/// <param name="t">時間</param>
		/// <returns>this</returns>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
		// ********************************************************************************
		virtual CEmitter& SetTime(const MofFloat& t)
		{
			m_Time = t;
			return *this;
		}

		// ********************************************************************************
		/// <summary>
		/// 座標取得
		/// </summary>
		/// <returns>座標</returns>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
		// ********************************************************************************
		virtual CVector3& GetPosition(void)
		{
			return m_State.Position;
		}

		// ********************************************************************************
		/// <summary>
		/// スケール取得
		/// </summary>
		/// <returns>スケール</returns>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
		// ********************************************************************************
		virtual CVector3& GetScale(void)
		{
			return m_State.Scale;
		}

		// ********************************************************************************
		/// <summary>
		/// 回転取得
		/// </summary>
		/// <returns>回転</returns>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
		// ********************************************************************************
		virtual CVector3& GetRotation(void)
		{
			return m_State.Rotation;
		}

		// ********************************************************************************
		/// <summary>
		/// 色取得
		/// </summary>
		/// <returns>色</returns>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
		// ********************************************************************************
		virtual CVector4& GetColor(void)
		{
			return m_State.Color;
		}

		// ********************************************************************************
		/// <summary>
		/// ワールドマトリクス取得
		/// </summary>
		/// <returns>ワールドマトリクス</returns>
		/// <created>いのうえ,2020/08/04</created>
		/// <changed>いのうえ,2020/08/04</changed>
		// ********************************************************************************
		virtual CMatrix44& GetWorldMatrix(void)
		{
			return m_State.World;
		}
	};
}
