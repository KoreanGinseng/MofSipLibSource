#include "Particle.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="info">生成情報</param>
	/// <created>いのうえ,2020/07/28</created>
	/// <changed>いのうえ,2020/07/28</changed>
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
	/// デストラクタ
	/// </summary>
	/// <created>いのうえ,2020/07/28</created>
	/// <changed>いのうえ,2020/07/28</changed>
	// ********************************************************************************
	CParticle::~CParticle(void)
	{
		Release();
	}
	
	// ********************************************************************************
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="info">生成情報</param>
	/// <created>いのうえ,2020/07/28</created>
	/// <changed>いのうえ,2020/07/28</changed>
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
	/// 更新
	/// </summary>
	/// <created>いのうえ,2020/07/28</created>
	/// <changed>いのうえ,2020/07/28</changed>
	// ********************************************************************************
	void CParticle::Update(void)
	{
		// 存在時間の更新
		m_Time++;

		// 終了判定
		if (IsEnd())
		{
			return;
		}

		// 挙動に合わせて更新
		m_State.Position += m_UpdateBehavior.Move + m_EnvironmentBehavior.Gravity * m_Time;
		m_State.Scale    += m_UpdateBehavior.Scale;
		m_State.Rotation += m_UpdateBehavior.Rotation;
		m_State.Color    += m_UpdateBehavior.Color;

		// 行列の更新
		m_State.World.RotationZXY(m_State.Rotation);
		m_State.World.Scaling(m_State.Scale, m_State.World);
		m_State.World.SetTranslation(m_State.Position);
	}
	
	// ********************************************************************************
	/// <summary>
	/// 描画
	/// </summary>
	/// <created>いのうえ,2020/07/28</created>
	/// <changed>いのうえ,2020/07/28</changed>
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
		// 描画用マトリクス宣言
		CMatrix44 rMat = m_State.World;
		// ビルボードマトリクスをワールドマトリクスに適用する
		if (m_ParameterBehavior.Flag & Flag::BillBoard)
		{
			// カメラを取得する
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
	/// 解放
	/// </summary>
	/// <created>いのうえ,2020/07/28</created>
	/// <changed>いのうえ,2020/07/28</changed>
	// ********************************************************************************
	void CParticle::Release(void)
	{
	}

	// ********************************************************************************
	/// <summary>
	/// ビューポジションの更新
	/// </summary>
	/// <created>いのうえ,2020/08/04</created>
	/// <changed>いのうえ,2020/08/04</changed>
	// ********************************************************************************
	void CParticle::UpdateViewPosition(void)
	{
		LPCamera pCam = CGraphicsUtilities::GetCamera();
		m_State.World.GetTranslation(m_ViewPosition);
		m_ViewPosition *= pCam->GetViewMatrix();
	}
	
	// ********************************************************************************
	/// <summary>
	/// 終了フラグの取得
	/// </summary>
	/// <returns>終了フラグ</returns>
	/// <created>いのうえ,2020/07/28</created>
	/// <changed>いのうえ,2020/07/28</changed>
	// ********************************************************************************
	MofBool CParticle::IsEnd(void) const
	{
		return m_Time >= m_ParameterBehavior.Existance ? TRUE : FALSE;
	}

	// ********************************************************************************
	/// <summary>
	/// Zソート用比較関数
	/// </summary>
	/// <param name="v1">値１</param>
	/// <param name="v2">値２</param>
	/// <returns>大小の比較結果</returns>
	/// <created>いのうえ,2020/08/04</created>
	/// <changed>いのうえ,2020/08/04</changed>
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