#include "ToonShader.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <created>いのうえ,2020/11/06</created>
	/// <changed>いのうえ,2020/11/06</changed>
	// ********************************************************************************
	CToonShader::CToonShader(void)
		: m_ToonShader()
		, m_ToonEdge()
		, m_EdgeBase()
		, m_RenderTex()
		, m_ToonTex()
		, m_ToonMapTex()
	{
	}

	// ********************************************************************************
	/// <summary>
	/// デストラクタ
	/// </summary>
	/// <created>いのうえ,2020/11/06</created>
	/// <changed>いのうえ,2020/11/06</changed>
	// ********************************************************************************
	CToonShader::~CToonShader(void)
	{
		Release();
	}

	// ********************************************************************************
	/// <summary>
	/// シェーダーの作成
	/// </summary>
	/// <returns>TRUE：成功、FALSE：失敗</returns>
	/// <created>いのうえ,2020/11/06</created>
	/// <changed>いのうえ,2020/11/06</changed>
	// ********************************************************************************
	bool CToonShader::Create(void)
	{
		int w = g_pGraphics->GetTargetWidth();
		int h = g_pGraphics->GetTargetHeight();

		MofBool result[] =
		{
			m_ToonShader.Create(),
			m_ToonEdge.Create(),
			m_EdgeBase.Create(),
			m_RenderTex.CreateTarget(w, h, PIXELFORMAT_R8G8B8A8_UNORM, BUFFERACCESS_GPUREADWRITE),
			m_ToonTex.CreateTarget(w, h, PIXELFORMAT_R8G8B8A8_UNORM, BUFFERACCESS_GPUREADWRITE),
		};

		for (MofBool b : result)
		{
			if (!b)
			{
				return false;
			}
		}
		return true;
	}

	// ********************************************************************************
	/// <summary>
	/// 適応するトゥーンマップ画像の読み込み
	/// </summary>
	/// <param name="pFileName">ファイル名</param>
	/// <returns>TRUE：成功、FALSE：失敗</returns>
	/// <created>いのうえ,2020/11/06</created>
	/// <changed>いのうえ,2020/11/06</changed>
	// ********************************************************************************
	bool CToonShader::LoadToonMap(LPCMofChar pFileName)
	{
		if (!m_ToonMapTex.Load(pFileName))
		{
			return false;
		}
		m_ToonShader.SetToonMapTexture(&m_ToonMapTex);
		return true;
	}

	// ********************************************************************************
	/// <summary>
	/// 解放
	/// </summary>
	/// <created>いのうえ,2020/11/06</created>
	/// <changed>いのうえ,2020/11/06</changed>
	// ********************************************************************************
	void CToonShader::Release(void)
	{
		m_ToonShader.Release();
		m_ToonEdge.Release();
		m_EdgeBase.Release();
		m_RenderTex.Release();
		m_ToonTex.Release();
		m_ToonMapTex.Release();
	}

	// ********************************************************************************
	/// <summary>
	/// トゥーンレンダリングの開始
	/// </summary>
	/// <created>いのうえ,2020/11/06</created>
	/// <changed>いのうえ,2020/11/06</changed>
	// ********************************************************************************
	void CToonShader::Begin(void)
	{
		if (CGraphicsUtilities::GetCamera() == nullptr)
		{
			return;
		}
		m_pOriginalRenderTarget = g_pGraphics->GetRenderTarget();
		m_pOriginalDepthTarget = g_pGraphics->GetDepthTarget();

		g_pGraphics->SetRenderTarget(m_RenderTex.GetRenderTarget(), m_pOriginalDepthTarget);

		m_EdgeBase.Begin();

		g_pGraphics->ClearTarget();

		g_pGraphics->SetBlending(BLEND_NONE);

		m_ToonShader.Begin();
	}

	// ********************************************************************************
	/// <summary>
	/// トゥーンレンダリングの終了
	/// </summary>
	/// <created>いのうえ,2020/11/06</created>
	/// <changed>いのうえ,2020/11/06</changed>
	// ********************************************************************************
	void CToonShader::End(void)
	{
		if (CGraphicsUtilities::GetCamera() == nullptr)
		{
			return;
		}
		m_ToonShader.End();
		m_EdgeBase.End();
		g_pGraphics->SetBlending(BLEND_NORMAL);

		m_ToonEdge.Render(&m_ToonTex, &m_RenderTex, &m_EdgeBase);

		g_pGraphics->SetRenderTarget(m_pOriginalRenderTarget, nullptr);
		m_ToonTex.Render(0, 0);

		g_pGraphics->SetRenderTarget(m_pOriginalRenderTarget, m_pOriginalDepthTarget);
		g_pGraphics->SetRenderTargetAt(1, nullptr, nullptr);
		g_pGraphics->SetRenderTargetAt(2, nullptr, nullptr);
		g_pGraphics->SetRenderTargetCount(1);
	}
}
