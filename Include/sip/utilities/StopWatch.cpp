#include "StopWatch.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <created>いのうえ,2020/09/10</created>
	/// <changed>いのうえ,2020/09/10</changed>
	// ********************************************************************************
	CStopWatch::CStopWatch(void)
		 : m_bStart(false)
		 , m_Time(0.0f)
	{
	}

	// ********************************************************************************
	/// <summary>
	/// デストラクタ
	/// </summary>
	/// <created>いのうえ,2020/09/10</created>
	/// <changed>いのうえ,2020/09/10</changed>
	// ********************************************************************************
	CStopWatch::~CStopWatch(void)
	{
	}

	// ********************************************************************************
	/// <summary>
	/// 開始
	/// </summary>
	/// <created>いのうえ,2020/09/10</created>
	/// <changed>いのうえ,2020/09/10</changed>
	// ********************************************************************************
	void CStopWatch::Start(void)
	{
		Reset();
		m_bStart = true;
	}

	// ********************************************************************************
	/// <summary>
	/// 停止
	/// </summary>
	/// <created>いのうえ,2020/09/10</created>
	/// <changed>いのうえ,2020/09/10</changed>
	// ********************************************************************************
	void CStopWatch::Stop(void)
	{
		m_bStart = false;
	}

	// ********************************************************************************
	/// <summary>
	/// 再開
	/// </summary>
	/// <created>いのうえ,2020/09/10</created>
	/// <changed>いのうえ,2020/09/10</changed>
	// ********************************************************************************
	void CStopWatch::Resume(void)
	{
		m_bStart = true;
	}

	// ********************************************************************************
	/// <summary>
	/// リセット
	/// </summary>
	/// <created>いのうえ,2020/09/10</created>
	/// <changed>いのうえ,2020/09/10</changed>
	// ********************************************************************************
	void CStopWatch::Reset(void)
	{
		SetTime(0.0f);
	}

	// ********************************************************************************
	/// <summary>
	/// 更新
	/// </summary>
	/// <created>いのうえ,2020/09/10</created>
	/// <changed>いのうえ,2020/09/10</changed>
	// ********************************************************************************
	void CStopWatch::Update(void)
	{
		if (!m_bStart)
		{
			return;
		}

		m_Time += CUtilities::GetFrameSecond();
	}

	// ********************************************************************************
	/// <summary>
	/// 開始フラグの取得
	/// </summary>
	/// <returns>開始フラグ</returns>
	/// <created>いのうえ,2020/09/10</created>
	/// <changed>いのうえ,2020/09/10</changed>
	// ********************************************************************************
	bool CStopWatch::IsStart(void) const
	{
		return m_bStart;
	}

	// ********************************************************************************
	/// <summary>
	/// 現在の経過時間取得。単位は秒
	/// </summary>
	/// <returns>経過時間(秒)</returns>
	/// <created>いのうえ,2020/09/10</created>
	/// <changed>いのうえ,2020/09/10</changed>
	// ********************************************************************************
	float CStopWatch::GetTime(void) const
	{
		return m_Time;
	}

	// ********************************************************************************
	/// <summary>
	/// 経過時間の設定。単位は秒
	/// </summary>
	/// <param name="t">設定する時間(秒)</param>
	/// <created>いのうえ,2020/09/10</created>
	/// <changed>いのうえ,2020/09/10</changed>
	// ********************************************************************************
	void CStopWatch::SetTime(const float & t)
	{
		m_Time = t;
	}
}

